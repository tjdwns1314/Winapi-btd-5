#pragma once
// 터짐 규칙: 죽으면 바로 아래 등급 풍선 1개가 생성된다. 최하위(Red)는 하위 없이 그대로 삭제된다.
enum class BloonColor
{
    Red,      // HP 1, 최하위, 터지면 삭제(하위 없음)
    Blue,     // HP 1, 터지면 Red
    Green,    // HP 1, 터지면 Blue
    Yellow,   // HP 1, 터지면 Green
    Pink,     // HP 1, 터지면 Yellow
    Black,    // HP 1, 터지면 Pink
    White,    // HP 1, 터지면 Pink
    Lead,     // HP 1, 터지면 Black
    Zebra,    // HP 1, 터지면 Lead
    Rainbow,  // HP 1, 터지면 Zebra
    Ceramic,  // HP 10, 터지면 Rainbow
};
enum class BloonProperty : unsigned int
{

};