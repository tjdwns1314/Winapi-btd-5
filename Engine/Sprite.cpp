#include "pch.h"
#include "Sprite.h"
#include <fstream>
#include <sstream>
#include <regex>

namespace
{
    float GetAttr(const std::wsmatch& tagMatch, const wchar_t* attrName)
    {
        std::wstring tag = tagMatch[0].str();
        std::wregex attrPattern(std::wstring(attrName) + LR"XML(="([^"]+)")XML");
        std::wsmatch m;
        if (std::regex_search(tag, m, attrPattern))
            return std::stof(m[1].str());
        return 0.f;
    }

    std::string GetName(const std::wsmatch& tagMatch)
    {
        std::wregex namePattern(LR"XML(name="([^"]+)")XML");
        std::wsmatch m;
        std::wstring tag = tagMatch[0].str();
        if (std::regex_search(tag, m, namePattern))
        {
            std::wstring wname = m[1].str();
            return std::string(wname.begin(), wname.end());
        }
        return {};
    }
}

void Sprite::LoadXml(const wchar_t* xmlPath)
{
    _cells.clear();

    std::wifstream file(xmlPath);
    if (!file.is_open()) return;

    std::wstringstream buffer;
    buffer << file.rdbuf();
    std::wstring content = buffer.str();

    // 속성 순서에 상관없이 <Cell .../> 태그 하나를 통째로 캡처
    std::wregex cellPattern(LR"XML(<Cell\s+[^>]*/>)XML");

    auto begin = std::wsregex_iterator(content.begin(), content.end(), cellPattern);
    auto end = std::wsregex_iterator();

    for (auto it = begin; it != end; ++it)
    {
        const std::wsmatch& match = *it;

        std::string name = GetName(match);
        if (name.empty()) continue;

        CellInfo info{};
        info.x = GetAttr(match, L"x");
        info.y = GetAttr(match, L"y");
        info.w = GetAttr(match, L"w");
        info.h = GetAttr(match, L"h");
        info.ax = GetAttr(match, L"ax");
        info.ay = GetAttr(match, L"ay");
        info.aw = GetAttr(match, L"aw");
        info.ah = GetAttr(match, L"ah");

        _cells[name] = info;
    }
}

const CellInfo* Sprite::GetCell(const std::string& name)
{
    auto it = _cells.find(name);
    if (it == _cells.end()) return nullptr;
    return &it->second;
}