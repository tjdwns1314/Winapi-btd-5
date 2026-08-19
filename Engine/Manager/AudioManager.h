#pragma once
#include "Singleton.h"
#include <xaudio2.h>

// 오디오 클립(사운드 원본 데이터) 캐시 + 배경음/효과음 재생을 담당하는 매니저.
// - 배경음(Bgm): 동시에 하나만 재생(새로 틀면 기존 것을 정지하고 교체).
// - 효과음(Sfx): 여러 개가 동시에 겹쳐 재생 가능.
class AudioManager : public Singleton<AudioManager>
{
	friend Singleton<AudioManager>;

public:
	void Init();
	void Update();		// 재생이 끝난 효과음 보이스를 정리
	void Cleanup();

	// filePath의 PCM WAV 데이터를 읽어 key로 캐싱해둔다(캐싱메모리).
	void LoadSound(const wchar_t* key, const wchar_t* filePath);

	// directory 안의 모든 .wav를 스캔해서 로드한다. 키는 확장자를 뺀 파일명(예: "pop1", "dance").
	void LoadSoundsInDirectory(const wchar_t* directory);

	void PlaySfx(const wchar_t* key, float volume = 1.0f);
	void PlayBgm(const wchar_t* key, float volume = 1.0f, bool loop = true);
	void StopBgm();

	// 배경음 볼륨을 targetScale 배율로 fadeSeconds초에 걸쳐 부드럽게 전환한다(예: 설정창 열림/닫힘 덕킹).
	void SetBgmVolumeScale(float targetScale, float fadeSeconds = 0.3f);

	// 배경음 음소거 토글. 끄면 정지하고, 다시 켜면 마지막에 재생하던 곡을 처음부터 다시 재생한다.
	void SetBgmMuted(bool muted);
	bool IsBgmMuted() const { return _bgmMuted; }

	// 효과음 음소거 토글. 켜져 있는 동안은 PlaySfx 호출을 무시한다.
	void SetSfxMuted(bool muted) { _sfxMuted = muted; }
	bool IsSfxMuted() const { return _sfxMuted; }

private:
	AudioManager() = default;
	~AudioManager() = default;

	struct SoundClip
	{
		WAVEFORMATEX format = {};
		vector<BYTE> data;
	};

	bool loadWavFile(const wchar_t* filePath, SoundClip& outClip);

	IXAudio2* _xaudio2 = nullptr;
	IXAudio2MasteringVoice* _masterVoice = nullptr;
	IXAudio2SourceVoice* _bgmVoice = nullptr;

	float _bgmBaseVolume = 1.0f;			// PlayBgm에 전달된 원래 볼륨
	float _bgmVolumeScale = 1.0f;			// 현재 페이드 배율(0~1)
	float _bgmTargetVolumeScale = 1.0f;	// 목표 배율
	float _bgmFadeSpeed = 1.0f;			// 초당 배율 변화량
	bool _bgmMuted = false;
	bool _sfxMuted = false;
	wstring _lastBgmKey;					// 음소거 해제 시 다시 재생할 마지막 배경음 key
	float _lastBgmVolume = 1.0f;
	bool _lastBgmLoop = true;

	unordered_map<wstring, SoundClip> _clips;		// 파일명(key) -> 로드된 PCM 데이터 캐시
	vector<IXAudio2SourceVoice*> _sfxVoices;		// 현재 재생 중인 효과음 보이스 목록(중복 재생 허용)
};
