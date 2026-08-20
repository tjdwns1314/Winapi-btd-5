#include "pch.h"
#include "SaveManager.h"
#include "External/json.hpp"
#include <fstream>
#include <filesystem>
#include <system_error>

namespace
{
	const char* TowerTypeToString(TowerType type)
	{
		switch (type)
		{
		case TowerType::DartMonkey:   return "DartMonkey";
		case TowerType::TackShooter:  return "TackShooter";
		case TowerType::SniperMonkey: return "SniperMonkey";
		case TowerType::BombTower:    return "BombTower";
		}
		return "DartMonkey";
	}

	const char* ObstacleTypeToString(ObstacleType type)
	{
		switch (type)
		{
		case ObstacleType::BananaFarmChimney: return "BananaFarmChimney";
		}
		return "BananaFarmChimney";
	}

	ObstacleType ParseObstacleTypeName(const string& name)
	{
		if (name == "BananaFarmChimney")
			return ObstacleType::BananaFarmChimney;
		return ObstacleType::BananaFarmChimney;
	}

	nlohmann::json CellToJson(const Cell& cell)
	{
		nlohmann::json j;
		j["x"] = cell.iX;
		j["y"] = cell.iY;
		return j;
	}

	Cell CellFromJson(const nlohmann::json& j)
	{
		return Cell{ j.value("x", 0), j.value("y", 0) };
	}
}

bool SaveManager::WriteToFile(const SaveData& data, const wstring& path)
{
	std::filesystem::path fsPath(path);
	if (fsPath.has_parent_path())
		std::filesystem::create_directories(fsPath.parent_path());

	nlohmann::json root;
	root["version"] = SaveData::kVersion;
	root["gold"] = data.gold;
	root["hp"] = data.hp;
	root["nextRound"] = data.nextRound;
	root["autoPlay"] = data.autoPlay;
	root["speedEnabled"] = data.speedEnabled;
	root["startCell"] = CellToJson(data.startCell);
	root["endCell"] = CellToJson(data.endCell);

	for (const TowerSaveData& tower : data.towers)
	{
		nlohmann::json entry;
		entry["type"] = TowerTypeToString(tower.type);
		entry["grade"] = tower.grade;
		entry["cell"] = CellToJson(tower.cell);
		root["towers"].push_back(entry);
	}

	for (const ObstacleSaveData& obstacle : data.obstacles)
	{
		nlohmann::json entry;
		entry["type"] = ObstacleTypeToString(obstacle.type);
		entry["cell"] = CellToJson(obstacle.cell);
		root["obstacles"].push_back(entry);
	}

	std::ofstream file(fsPath);
	if (!file.is_open())
		return false;

	file << root.dump(2);
	return true;
}

bool SaveManager::ReadFromFile(SaveData& outData, const wstring& path)
{
	std::filesystem::path fsPath(path);
	std::ifstream file(fsPath);
	if (!file.is_open())
		return false;

	nlohmann::json root;
	file >> root;

	SaveData data;
	data.gold = root.value("gold", 0);
	data.hp = root.value("hp", 0);
	data.nextRound = root.value("nextRound", 1);
	data.autoPlay = root.value("autoPlay", false);
	data.speedEnabled = root.value("speedEnabled", false);
	if (root.contains("startCell"))
		data.startCell = CellFromJson(root.at("startCell"));
	if (root.contains("endCell"))
		data.endCell = CellFromJson(root.at("endCell"));

	if (root.contains("towers"))
	{
		for (const auto& entry : root.at("towers"))
		{
			TowerSaveData tower;
			tower.type = ParseTowerTypeName(entry.at("type").get<string>());
			tower.grade = entry.value("grade", 1);
			tower.cell = CellFromJson(entry.at("cell"));
			data.towers.push_back(tower);
		}
	}

	if (root.contains("obstacles"))
	{
		for (const auto& entry : root.at("obstacles"))
		{
			ObstacleSaveData obstacle;
			obstacle.type = ParseObstacleTypeName(entry.at("type").get<string>());
			obstacle.cell = CellFromJson(entry.at("cell"));
			data.obstacles.push_back(obstacle);
		}
	}

	outData = data;
	return true;
}

void SaveManager::DeleteFile(const wstring& path)
{
	std::error_code ec;
	std::filesystem::remove(std::filesystem::path(path), ec); // 파일이 원래 없어도 에러 아님
}

bool SaveManager::FileExists(const wstring& path)
{
	return std::filesystem::exists(std::filesystem::path(path));
}
