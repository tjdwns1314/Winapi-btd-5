#include "pch.h"
#include "Sprite.h"
#include <fstream>
#include <sstream>
#include <regex>

void Sprite::LoadXml(const wchar_t* xmlPath)
{
	_cells.clear();

	std::wifstream file(xmlPath);
	if (!file.is_open()) return;

	std::wstringstream buffer;
	buffer << file.rdbuf();
	std::wstring content = buffer.str();

	// 커스텀 델리미터(XML)를 써서 문자열 안의 )" 조합과 충돌 방지
	std::wregex cellPattern(
		LR"XML(<Cell\s+name="([^"]+)"\s+x="([^"]+)"\s+y="([^"]+)"\s+w="([^"]+)"\s+h="([^"]+)"\s+ax="([^"]+)"\s+ay="([^"]+)"\s+aw="([^"]+)"\s+ah="([^"]+)"\s*/>)XML"
	);

	auto begin = std::wsregex_iterator(content.begin(), content.end(), cellPattern);
	auto end = std::wsregex_iterator();

	for (auto it = begin; it != end; ++it)
	{
		std::wsmatch match = *it;

		std::wstring wname = match[1].str();
		std::string name(wname.begin(), wname.end());

		CellInfo info{};
		info.x = std::stof(match[2].str());
		info.y = std::stof(match[3].str());
		info.w = std::stof(match[4].str());
		info.h = std::stof(match[5].str());
		info.ax = std::stof(match[6].str());
		info.ay = std::stof(match[7].str());
		info.aw = std::stof(match[8].str());
		info.ah = std::stof(match[9].str());

		_cells[name] = info;
	}
}

const CellInfo* Sprite::GetCell(const std::string& name)
{
	auto it = _cells.find(name);
	if (it == _cells.end()) return nullptr;
	return &it->second;
}