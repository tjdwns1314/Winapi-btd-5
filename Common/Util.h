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
	Main,	// 타이틀 화면
	Lobby,	// 스테이지(1-1/1-2/1-3) 선택
	Game,	// 실제 플레이
	Editor,
	Max,
};

enum class ColliderType
{
	Circfle,
	AABB,	// 회전하지 않는 일반 풍선용
	OBB,	// 이동 방향으로 회전하는 보스 풍선용
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

