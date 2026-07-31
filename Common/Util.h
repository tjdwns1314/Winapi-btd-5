#pragma once
float RadianToDegree(float radina);
float DegreeToRadian(float degree);

enum class RenederLayer
{
	Background,
	Enemy,
	Bullet,
	Tower,
	Effect,

	Count,
};

enum class ActorType
{
	Background,
	Block,
	Enemy,
	Tower,
	Effect,
	Count,
};

enum class SceneType
{
	Lobby,
	Game,
	Editor,
	Max,
};

enum class ColliderType
{
	Circfle,
	AABB,
	Max
};

enum FontSize
{
	FONT_12 = 12,
	FONT_20 = 20,
	FONT_30 = 30,
};

enum DirType
{
	DIR_UP,
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT,
};

