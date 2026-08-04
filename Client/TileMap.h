#pragma once
class TileMap
{
public:
	void Init(int32 gridCountX, int32 gridCountY, TileType fillType = TileType::Path);

	TileType GetTile(int32 x, int32 y) const;
	void SetTile(int32 x, int32 y, TileType type);


	void GenerateRandomStartEndPoint();
	Cell GetStartPoint() const { return _startCell; }
	Cell GetEndPoint() const { return _endCell; }


private :
	bool isValidCell(int32 x, int32 y) const;
	vector<Cell> collectBorderCells() const;

	int32 _gridCountX = 0;
	int32 _gridCountY = 0;
	vector<TileType> _tiles;
	Cell _startCell{};
	Cell _endCell{};
};

