#pragma once
struct CellInfo
{
	float x, y, w, h;
	float ax, ay, aw, ah;
};

class Sprite
{
public:
    void LoadXml(const wchar_t* xmlPath);
    const CellInfo* GetCell(const std::string& name);
private:
    std::unordered_map<std::string, CellInfo> _cells;
};