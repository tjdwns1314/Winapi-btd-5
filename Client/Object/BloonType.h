#pragma once
// 터짐 규칙: 죽으면 하위 개체(등급마다 1개 또는 2개, Zebra는 서로 다른 두 종류)가 생성된다.
// 최하위(Red)는 하위 없이 그대로 삭제된다. 자세한 표와 데미지 관통 규칙은 .claude/plan.md 5절 참고.
enum class BloonColor
{
    Red,      // 레이어 HP 1, 최하위, 터지면 삭제(하위 없음)
    Blue,     // 레이어 HP 1, 터지면 Red x1
    Green,    // 레이어 HP 1, 터지면 Blue x1
    Yellow,   // 레이어 HP 1, 터지면 Green x1
    Pink,     // 레이어 HP 1, 터지면 Yellow x1
    Black,    // 레이어 HP 1, 터지면 Pink x2
    White,    // 레이어 HP 1, 터지면 Pink x2
    Lead,     // 레이어 HP 1, 터지면 Black x2
    Zebra,    // 레이어 HP 1, 터지면 Black x1 + White x1
    Rainbow,  // 레이어 HP 1, 터지면 Zebra x2
    Ceramic,  // 레이어 HP 10, 터지면 Rainbow x2
};

struct BloonChildSpawn
{
    BloonColor color;
    int32 count;
};

struct BloonStat
{
    BloonColor color;
    int32 layerHp;
    float speed;
    int32 goldReward;
    wstring spriteKey;
    vector<BloonChildSpawn> children;

};

const BloonStat& GetBloonStat(BloonColor color);
BloonColor ParseBloonColorName(const string& name);

enum class BloonProperty : unsigned int
{

};