#pragma once

#include "BloonType.h"

class Bloon;
class Scene;
template<typename T>
class ObjectPool;

// 한 라운드의 스폰 데이터
struct WaveData
{
	vector<BloonColor> spawnOrder;
	float spawnInterval = 0.f;
};

class WaveManager
{
public:
	void Init(ObjectPool<Bloon>* pool, const Vector& spawnPos, const vector<Vector>* path, Scene* scene,
		function<void(int32)> onRoundClearBonus = nullptr);

	// 웨이브 진행
	bool StartNextWave();
	void Update(float deltaTime);
	bool IsWaveActive() const { return _state != WaveState::Idle; }

	// 설정 팝업의 자동진행 토글과 연결. true면 웨이브 클리어 후 kAutoStartDelay(1초) 뒤 자동으로 다음 웨이브 시작.
	void SetAutoPlay(bool enabled);

	// 라운드 디버그
	void SetNextRound(int32 roundNumber);
	int32 GetNextRoundNumber() const { return _roundIndex + 1; }
	int32 GetCurrentRoundNumber() const { return IsWaveActive() ? _roundIndex : 0; }
	// HUD 표시용: 진행 중이면 현재 라운드, 대기 중이면 다음에 시작할 라운드.
	int32 GetDisplayRoundNumber() const { return IsWaveActive() ? _roundIndex : GetNextRoundNumber(); }
	int32 GetTotalRoundNumber() const;

private:
	enum class WaveState
	{
		Idle,
		Spawning,
		WaitingClear
	};

	// 라운드 생성
	static WaveData buildRound(int32 roundNumber);

	// 스폰 및 상태 처리
	void spawnNext();
	bool isFieldClear() const;

private:
	// 외부 참조
	ObjectPool<Bloon>* _pool = nullptr;
	const vector<Vector>* _path = nullptr;
	Scene* _scene = nullptr;
	Vector _spawnPos;

	// 라운드 클리어 보너스 골드 지급 콜백. 인자로 지급할 골드량을 넘긴다.
	function<void(int32)> _onRoundClearBonus;

	// 웨이브 상태
	WaveState _state = WaveState::Idle;
	int32 _roundIndex = 0;
	WaveData _currentRound;

	// 스폰 진행 상태
	int32 _spawnIndex = 0;
	float _spawnTimer = 0.f;

	// 자동진행 상태 및 웨이브 클리어 후 다음 웨이브까지 남은 대기 시간(초). 음수면 대기 중 아님.
	bool _autoPlayEnabled = false;
	float _autoStartTimer = -1.f;
};