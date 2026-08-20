#pragma once
#include "SaveData.h"

// SaveData <-> JSON 파일 변환만 담당한다. GameScene 등 게임 상태는 전혀 모른다.
class SaveManager
{
public:
	static bool WriteToFile(const SaveData& data, const wstring& path);
	static bool ReadFromFile(SaveData& outData, const wstring& path);
	static void DeleteFile(const wstring& path);
	static bool FileExists(const wstring& path);
};
