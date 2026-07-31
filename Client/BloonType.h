#pragma once
enum class BloonColor
{
    Red,      // HP 1, 기본
    Blue,     // HP 1, 터지면 Red
    Green,    // HP 1, 터지면 Blue
    Yellow,   // HP 1, 터지면 Green
    Pink,     // HP 1, 터지면 Yellow
    Black,    // HP 1, 폭발 면역, 터지면 Pink x2
    White,    // HP 1, 냉동 면역, 터지면 Pink x2
    Lead,     // HP 1, 날카로움/넉백 면역, 터지면 Black x2
    Zebra,    // HP 1, 폭발+냉동 면역, 터지면 Black + White
    Rainbow,  // HP 1, 터지면 Zebra x2
    Ceramic,  // HP 10, 터지면 Rainbow x2
};
enum class BloonProperty : unsigned int
{

};