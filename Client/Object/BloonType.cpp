#include "pch.h"
#include "BloonType.h"
#include "External/json.hpp"
#include <fstream>

namespace
{
    vector<BloonStat> loadBloonStats()
    {
        vector<BloonStat> stats;
        std::ifstream file("Resource\\Data\\BloonType.json");
        if (!file.is_open())
        {
            MessageBox(nullptr, L"Resource\\Data\\BloonType.json", L"BloonType 데이터 로드 실패", MB_OK);
            return stats;
        }
        nlohmann::json root;
        file >> root;

        for (const auto& entry : root.at("bloons"))
        {
            BloonStat stat;
            stat.color =
                ParseBloonColorName(entry.at("color").get<string>());

            stat.layerHp =
                entry.at("layerHp").get<int32>();
            stat.speed =
                entry.at("speed").get<float>();
            stat.goldReward =
                entry.at("goldReward").get<int32>();

            const string spriteKey =
                entry.at("spriteKey").get<string>();

            stat.spriteKey.assign(spriteKey.begin(),
                spriteKey.end());

            for (const auto& child : entry.at("children"))
            {
                BloonChildSpawn spawn;
                spawn.color =
                    ParseBloonColorName(entry.at("color").get<string>());

                spawn.count =
                    child.at("count").get<int32>();
                stat.children.push_back(spawn);
            }
            stats.push_back(std::move(stat));
        }
        std::sort(stats.begin(), stats.end(), [](const BloonStat& a, const BloonStat& b)
        {
            return static_cast<int32>(a.color) < static_cast<int32>(b.color);
        });
            return stats;
    }
}


const BloonStat& GetBloonStat(BloonColor color)
{
    static const vector<BloonStat> stats = loadBloonStats();
    return stats[static_cast<size_t>(color)];
}

BloonColor ParseBloonColorName(const string& name)
{
    static const unordered_map<string, BloonColor> table
        =
    {
        {"Red",BloonColor::Red},
        {"Blue",BloonColor::Blue},
        {"Green",BloonColor::Green},
        {"Yellow",BloonColor::Yellow},
        {"Pink",BloonColor::Pink},
        {"Black",BloonColor::Black},
        {"White",BloonColor::White},
        {"Lead",BloonColor::Lead},
        {"Zebra",BloonColor::Zebra},
        {"Rainbow",BloonColor::Rainbow},
        {"Ceramic",BloonColor::Ceramic},
    };
    return table.at(name);
}
