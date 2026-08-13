#include "pch.h"
#include "WaveManager.h"
#include "Bloon.h"
#include "BloonFactory.h"
#include "Scene.h"
#include "Actor.h"
#include <random>

namespace
{
	// plan.md 8절: 스테이지 전체 30라운드 고정. 라운드 번호로부터 공식으로 스폰 구간을 생성한다.
	constexpr int32 kRoundCount = 30;
	constexpr int32 kBaseWeightBudget = 20;
	constexpr int32 kGrowthWeightBudget = 20;

	struct BloonWaveInfo
	{
		BloonColor color;
		int32 weight;        // 클수록 상위 등급. 같은 예산을 소모할 때 마리수가 그만큼 줄어든다.
		int32 unlockRound;   // 이 라운드부터 등장
		int32 retireRound;   // 이 라운드까지만 등장(0이면 계속 등장)
	};

	const vector<BloonWaveInfo>& GetBloonWaveTable()
	{
		static const vector<BloonWaveInfo> table =
		{
			{ BloonColor::Red,      1,  1, 8 },
			{ BloonColor::Blue,     2,  3, 10 },
			{ BloonColor::Green,    3,  5, 12 },
			{ BloonColor::Yellow,   4,  7, 14 },
			{ BloonColor::Pink,     5,  8,  0 },
			{ BloonColor::Black,    6, 10,  0 },
			{ BloonColor::White,    6, 10,  0 },
			{ BloonColor::Lead,     10, 13,  0 },
			{ BloonColor::Zebra,    12, 15,  0 },
			{ BloonColor::Rainbow,  15, 17,  0 },
			{ BloonColor::Ceramic, 20, 20,  0 },
		};
		return table;
	}
}

void WaveManager::Init(ObjectPool<Bloon>* pool, const Vector& spawnPos, const vector<Vector>* path, Scene* scene)
{
	_pool = pool;
	_spawnPos = spawnPos;
	_path = path;
	_scene = scene;

	// 재시작 시 GameScene이 이 WaveManager 인스턴스를 재사용하므로,
	// 이전 판의 라운드 진행 상태가 그대로 남지 않도록 여기서 리셋한다.
	_state = WaveState::Idle;
	_roundIndex = 0;
	_spawnIndex = 0;
	_spawnTimer = 0.f;
	_currentRound = WaveData{};
}

bool WaveManager::StartNextWave()
{
	// 1. 이미 웨이브가 진행 중인지 검사
	if (_state != WaveState::Idle)
		return false;

	// 2. 최대 라운드에 도달했는지 검사
	if (_roundIndex >= kRoundCount)
		return false;

	// 3. 라운드 증가 및 웨이브 데이터 빌드
	++_roundIndex;
	_currentRound = buildRound(_roundIndex);

	// 4. 스폰 관련 진행 상황 및 타이머 초기화
	_spawnIndex = 0;
	_spawnTimer = 0.f;

	// 5. 상태 변경 (대기중 -> 스폰중)
	_state = WaveState::Spawning;

	// 6. 첫 몬스터(풍선) 스폰 수행 및 성공 반환
	spawnNext();
	return true;
}

void WaveManager::SetNextRound(int32 roundNumber)
{
	if (_state != WaveState::Idle)
		return;

	if (roundNumber < 1)
		roundNumber = 1;
	if (roundNumber > kRoundCount)
		roundNumber = kRoundCount;

	_roundIndex = roundNumber - 1;
}

void WaveManager::Update(float deltaTime)
{
	// 1. 대기 상태 (웨이브 시작 전)
	if (_state == WaveState::Idle)
		return;

	// 2. 스폰 완료 후 필드의 모든 적 처치 대기 상태
	if (_state == WaveState::WaitingClear)
	{
		if (isFieldClear())
			_state = WaveState::Idle;
		return;
	}

	// 3. 스폰 중 상태: 라운드 전체에 동일하게 적용되는 스폰 간격(interval) 체크

	_spawnTimer += deltaTime;
	if (_spawnTimer < _currentRound.spawnInterval)
		return;

	// 스폰 간격(interval)을 채웠으면 타이머 차감 후 다음 적 스폰
	_spawnTimer -=_currentRound.spawnInterval;
	spawnNext();
}

void WaveManager::spawnNext()
{
	const BloonColor color =
		_currentRound.spawnOrder[_spawnIndex];

	Bloon* bloon = BloonFactory::Create(*_pool, color, _spawnPos, _path);
	if (bloon != nullptr && _scene != nullptr)
		_scene->AddActor(bloon);

	if (++_spawnIndex < static_cast<int32>(_currentRound.spawnOrder.size()))
		return;
	_state = WaveState::WaitingClear;
}

bool WaveManager::isFieldClear() const
{
	// 1. 씬(Scene) 객체가 없으면 비어있는 것으로 간주
	if (_scene == nullptr)
		return true;

	// 2. 풍선 레이어(RenderLayer::Bloon)에 있는 모든 몬스터(Actor)를 순회
	for (Actor* actor : _scene->GetActors(RenderLayer::Bloon))
	{
		// 3. 하나라도 '삭제 예정(죽은 상태)'이 아닌, 멀쩡히 살아있는 풍선이 있다면!
		if (!actor->IsPendingKill())
			return false; // 필드가 아직 싹 정리되지 않았으므로 false 반환
	}

	// 4. 살아있는 풍선이 하나도 없으면 라운드 클리어!
	return true;
}

WaveData WaveManager::buildRound(int32 roundNumber)
{
	// 1. 이번 라운드가 소모할 가중치 예산과 스폰 간격 계산
	const int32 weightBudget = kBaseWeightBudget + kGrowthWeightBudget * (roundNumber - 1);

	float spawnInterval = 1.0f - 0.05f * (roundNumber - 1);
	if (spawnInterval < 0.3f)
		spawnInterval = 0.3f;

	WaveData round;
	round.spawnInterval = spawnInterval;

	// 2. 이번 라운드에 등장 가능한 등급 목록 계산
	const vector<BloonWaveInfo>& table = GetBloonWaveTable();

	vector<const BloonWaveInfo*> available;
	for (const BloonWaveInfo& info : table)
	{
		if (roundNumber < info.unlockRound)
			continue;
		if (info.retireRound != 0 && roundNumber > info.retireRound)
			continue;

		available.push_back(&info);
	}

	if (available.empty())
		return round;

	// 3. 남은 예산으로 뽑을 수 있는(weight가 예산 이하인) 등급들 중 가중치 비례로 무작위 추첨.
	//    뽑을 때마다 예산을 깎고, 남은 예산으로 더 뽑을 수 있는 등급이 없으면 종료한다.
	static std::mt19937 rng{ std::random_device{}() };

	int32 remainingBudget = weightBudget;
	vector<const BloonWaveInfo*> candidates;
	vector<int32> candidateWeights;

	while (true)
	{
		candidates.clear();
		candidateWeights.clear();
		for (const BloonWaveInfo* info : available)
		{
			if (info->weight > remainingBudget)
				continue;
			candidates.push_back(info);
			candidateWeights.push_back(info->weight);
		}

		if (candidates.empty())
			break;

		std::discrete_distribution<int32> dist(candidateWeights.begin(), candidateWeights.end());
		const BloonWaveInfo* picked = candidates[dist(rng)];

		round.spawnOrder.push_back(picked->color);
		remainingBudget -= picked->weight;
	}

	return round;
}