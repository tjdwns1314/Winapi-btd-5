#pragma once

// 씬의 액터를 셀 단위로 나눠 보관하는 공간 분할 자료구조.
// 게임 고유 개념(길/설치 가능 등)은 모르며, Actor 버킷 관리만 담당한다.
class Grid
{
public:
	struct GridInfo
	{
		vector<class Actor*> actors;
	};

public:
	void Init(int32 gridCountX, int32 gridCountY, int32 gridSize);

	const GridInfo& GetGridInfo(const Cell& cell) const;
	void UpdateGrid(class Actor* actor, const Vector& prevPos);

	int32 GetGridSize() const { return _gridSize; }

private:
	bool isValidCell(const Cell& cell) const;

private:
	int32 _gridSize = BLOCK_SIZE;
	int32 _gridCountX = 0;
	int32 _gridCountY = 0;

	vector<GridInfo> _grid;
};
