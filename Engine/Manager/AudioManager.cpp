#include "pch.h"
#include "AudioManager.h"
#include "TimeManager.h"
#include <cstdio>
#include <cstring>

void AudioManager::Init()
{
	// 1. XAudio2 엔진 인스턴스를 생성한다.
	//    COM은 Graphic::Init에서 이미 CoInitialize 했으므로 여기서 다시 호출하지 않는다.
	if (FAILED(XAudio2Create(&_xaudio2, 0, XAUDIO2_DEFAULT_PROCESSOR)))
	{
		MessageBox(nullptr, L"XAudio2Create 실패", L"AudioManager::Init", MB_OK);
		return;
	}

	// 2. 최종 출력 장치로 나가는 마스터링 보이스를 생성한다.
	if (FAILED(_xaudio2->CreateMasteringVoice(&_masterVoice)))
		MessageBox(nullptr, L"CreateMasteringVoice 실패", L"AudioManager::Init", MB_OK);
}

void AudioManager::Update()
{
	// 재생이 끝난(큐에 남은 버퍼가 없는) 효과음 보이스를 찾아 파괴하고 목록에서 제거한다.
	for (auto it = _sfxVoices.begin(); it != _sfxVoices.end();)
	{
		XAUDIO2_VOICE_STATE state;
		(*it)->GetState(&state);

		if (state.BuffersQueued == 0)
		{
			(*it)->DestroyVoice();
			it = _sfxVoices.erase(it);
		}
		else
		{
			++it;
		}
	}

	// 배경음 볼륨을 목표 배율로 서서히 페이드한다.
	if (_bgmVoice != nullptr && _bgmVolumeScale != _bgmTargetVolumeScale)
	{
		const float deltaTime = TimeManager::GetInstance().GetDT();
		const float maxStep = _bgmFadeSpeed * deltaTime;
		const float diff = _bgmTargetVolumeScale - _bgmVolumeScale;

		_bgmVolumeScale += std::clamp(diff, -maxStep, maxStep);
		_bgmVoice->SetVolume(_bgmBaseVolume * _bgmVolumeScale);
	}
}

void AudioManager::Cleanup()
{
	StopBgm();

	for (auto* voice : _sfxVoices)
		voice->DestroyVoice();
	_sfxVoices.clear();

	if (_masterVoice)
	{
		_masterVoice->DestroyVoice();
		_masterVoice = nullptr;
	}

	if (_xaudio2)
	{
		_xaudio2->Release();
		_xaudio2 = nullptr;
	}

	_clips.clear();
}

void AudioManager::LoadSound(const wchar_t* key, const wchar_t* filePath)
{
	SoundClip clip;
	if (!loadWavFile(filePath, clip))
	{
		MessageBox(nullptr, filePath, L"LoadSound 실패: WAV 로드 실패", MB_OK);
		return;
	}

	_clips[key] = std::move(clip);
}

void AudioManager::LoadSoundsInDirectory(const wchar_t* directory)
{
	wstring searchPath = wstring(directory) + L"\\*.wav";

	WIN32_FIND_DATAW findData;
	HANDLE hFind = FindFirstFileW(searchPath.c_str(), &findData);
	if (hFind == INVALID_HANDLE_VALUE)
		return;

	do
	{
		if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			continue;

		// 확장자를 뺀 파일명을 키로 사용한다(예: "pop1.wav" -> "pop1").
		wstring fileName = findData.cFileName;
		wstring key = fileName.substr(0, fileName.find_last_of(L'.'));
		wstring fullPath = wstring(directory) + L"\\" + fileName;

		LoadSound(key.c_str(), fullPath.c_str());

	} while (FindNextFileW(hFind, &findData));

	FindClose(hFind);
}

void AudioManager::PlaySfx(const wchar_t* key, float volume)
{
	auto it = _clips.find(key);
	if (it == _clips.end())
	{
		MessageBox(nullptr, key, L"PlaySfx 실패: Preload 되지 않은 사운드", MB_OK);
		return;
	}

	SoundClip& clip = it->second;

	// 1. 이 효과음 전용 소스 보이스를 새로 만든다 -> 여러 개가 동시에 겹쳐 재생될 수 있다.
	IXAudio2SourceVoice* voice = nullptr;
	if (FAILED(_xaudio2->CreateSourceVoice(&voice, &clip.format)))
		return;

	voice->SetVolume(volume);

	// 2. 캐싱해둔 PCM 데이터를 그대로 제출한다.
	XAUDIO2_BUFFER buffer = {};
	buffer.AudioBytes = static_cast<UINT32>(clip.data.size());
	buffer.pAudioData = clip.data.data();
	buffer.Flags = XAUDIO2_END_OF_STREAM;

	voice->SubmitSourceBuffer(&buffer);
	voice->Start();

	_sfxVoices.push_back(voice);
}

void AudioManager::PlayBgm(const wchar_t* key, float volume, bool loop)
{
	auto it = _clips.find(key);
	if (it == _clips.end())
	{
		MessageBox(nullptr, key, L"PlayBgm 실패: Preload 되지 않은 사운드", MB_OK);
		return;
	}

	// 배경음은 하나만 재생되어야 하므로, 재생 중이던 배경음을 먼저 정지한다.
	StopBgm();

	SoundClip& clip = it->second;

	if (FAILED(_xaudio2->CreateSourceVoice(&_bgmVoice, &clip.format)))
		return;

	// 새 배경음을 틀 때마다 페이드 상태를 초기화한다.
	_bgmBaseVolume = volume;
	_bgmVolumeScale = 1.0f;
	_bgmTargetVolumeScale = 1.0f;
	_bgmVoice->SetVolume(_bgmBaseVolume);

	XAUDIO2_BUFFER buffer = {};
	buffer.AudioBytes = static_cast<UINT32>(clip.data.size());
	buffer.pAudioData = clip.data.data();
	buffer.LoopCount = loop ? XAUDIO2_LOOP_INFINITE : 0;
	buffer.Flags = XAUDIO2_END_OF_STREAM;

	_bgmVoice->SubmitSourceBuffer(&buffer);
	_bgmVoice->Start();
}

void AudioManager::StopBgm()
{
	if (!_bgmVoice)
		return;

	_bgmVoice->Stop();
	_bgmVoice->DestroyVoice();
	_bgmVoice = nullptr;
}

void AudioManager::SetBgmVolumeScale(float targetScale, float fadeSeconds)
{
	_bgmTargetVolumeScale = targetScale;
	_bgmFadeSpeed = (fadeSeconds > 0.f) ? (1.0f / fadeSeconds) : 1000.0f; // 0 이하면 사실상 즉시 전환
}

bool AudioManager::loadWavFile(const wchar_t* filePath, SoundClip& outClip)
{
	FILE* file = nullptr;
	if (_wfopen_s(&file, filePath, L"rb") != 0 || file == nullptr)
		return false;

	char riffId[4];
	uint32 riffSize;
	char waveId[4];
	fread(riffId, 1, 4, file);
	fread(&riffSize, sizeof(uint32), 1, file);
	fread(waveId, 1, 4, file);

	if (memcmp(riffId, "RIFF", 4) != 0 || memcmp(waveId, "WAVE", 4) != 0)
	{
		fclose(file);
		return false;
	}

	bool hasFmt = false;
	bool hasData = false;

	// "fmt "/"data" 청크를 찾을 때까지 순서에 상관없이 청크를 순회한다.
	while (!feof(file))
	{
		char chunkId[4];
		uint32 chunkSize;

		if (fread(chunkId, 1, 4, file) != 4)
			break;
		if (fread(&chunkSize, sizeof(uint32), 1, file) != 1)
			break;

		if (memcmp(chunkId, "fmt ", 4) == 0)
		{
			fread(&outClip.format, 1, std::min(chunkSize, static_cast<uint32>(sizeof(WAVEFORMATEX))), file);
			if (chunkSize > sizeof(WAVEFORMATEX))
				fseek(file, chunkSize - sizeof(WAVEFORMATEX), SEEK_CUR);
			hasFmt = true;
		}
		else if (memcmp(chunkId, "data", 4) == 0)
		{
			outClip.data.resize(chunkSize);
			fread(outClip.data.data(), 1, chunkSize, file);
			hasData = true;
		}
		else
		{
			fseek(file, chunkSize, SEEK_CUR);
		}

		// 청크는 짝수 바이트로 정렬된다.
		if (chunkSize % 2 != 0)
			fseek(file, 1, SEEK_CUR);
	}

	fclose(file);
	return hasFmt && hasData;
}
