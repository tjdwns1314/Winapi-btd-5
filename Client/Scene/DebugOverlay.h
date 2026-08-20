#pragma once

#include "Util.h"

class Graphic;
class MapSystem;
class Actor;

// F2 디버그 오버레이(그리드/경로/시작-끝/콜라이더/디버그 서클) 전담.
// GameScene::Render()의 디버그 표시 로직을 여기로 위임해 GameScene을 오케스트레이션 전용으로 남긴다.
class DebugOverlay
{
public:
	void Toggle() { _enabled = !_enabled; }
	bool IsEnabled() const { return _enabled; }

	void AddCircle(const Vector& pos, float radius, float duration);
	void Update(float deltaTime);
	void Clear() { _circles.clear(); }

	// isDragging: 타워/장애물 드래그 중이면 오버레이가 꺼져 있어도 그리드/경로를 옅게 보여준다.
	void Render(Graphic& graphic, const MapSystem& map, bool isDragging, const vector<Actor*>& bloons,
		bool isSpecialWaveActive) const;

private:
	void renderCircles(Graphic& graphic) const;
	void renderColliders(Graphic& graphic, const vector<Actor*>& bloons) const;

	struct DebugCircle
	{
		Vector pos;
		float radius;
		float remaining;
	};
	vector<DebugCircle> _circles;
	bool _enabled = false;
};
