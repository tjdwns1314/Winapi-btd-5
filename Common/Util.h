#pragma once
#include <string>
float RadianToDegree(float radina);
float DegreeToRadian(float degree);

// JSON 등 UTF-8 문자열을 Direct2D DrawString에 넘길 wide 문자열로 변환.
std::wstring Utf8ToWide(const std::string& utf8);

enum class RenderLayer
{
	Background,
	Bloon,
	Tower,
	Obstacle,
	Effect,
	Projectile,

	Count,
};

enum class ActorType
{
	Background,
	Projectile,
	Block,
	Bloon,
	Tower,
	Effect,
	Count,
};

enum class SceneType
{
	Main,	// 타이틀 화면
	Lobby,	// 스테이지(1-1/1-2/1-3) 선택
	Game,	// 실제 플레이
	Editor,
	Max,
};

enum class ColliderType
{
	Circle,
	Ellipse,
	Max
};

enum FontSize
{
	FONT_12 = 12,
	FONT_20 = 20,
	FONT_30 = 30,
	FONT_35 = 35,
	FONT_40 = 40,
};

enum DirType
{
	DIR_UP,
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT,
};
enum class TileType
{
	Path,
	Buildable,
	Obstacle,
	Count,
};

