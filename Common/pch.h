#pragma once

#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>
#include <iostream>
#include <windows.h>
#include <string>
#include <unordered_map>
#include <set>
#include <vector>
#include <functional>
#include <queue>
#include <algorithm>
#include <limits>

#include "Util.h"
using namespace std;

using int8 = char;		// 1byte 정수형
using int16 = short;	// 2byte 정수형
using int32 = int;		// 4byte 정수형
using int64 = long long;// 8byte 정수형

using uint8 = unsigned char;		// 1byte 정수형
using uint16 = unsigned short;	// 2byte 정수형
using uint32 = unsigned int;		// 4byte 정수형
using uint64 = unsigned long long;// 8byte 정수형

constexpr int32 GWinSizeX = 1760;
constexpr int32 GWinSizeY = 1040;
constexpr int32 GameAreaWidth = 1440;
constexpr int32 GameAreaHeight = 1040;
constexpr int32 BLOCK_SIZE = 80;
constexpr int32 GRID_COUNT_X = GameAreaWidth / BLOCK_SIZE;
constexpr int32 GRID_COUNT_Y = GameAreaHeight / BLOCK_SIZE;
static_assert(GRID_COUNT_X* BLOCK_SIZE == GameAreaWidth, "BLOCK_SIZE가 GameAreaWidth를 나누어떨어뜨리지 않습니다");
static_assert(GRID_COUNT_Y* BLOCK_SIZE == GameAreaHeight, "BLOCK_SIZE가 GameAreaHeight를 나누어떨어뜨리지 않습니다");
constexpr int32 GameAreaCenterX = GameAreaWidth / 2;
constexpr int32 GameAreaCenterY = GameAreaHeight / 2;



#define SMALL_NUMBER			(1.e-8f)

struct Vector
{
	float x = 0;
	float y = 0;

	Vector() {}
	Vector(float x, float y) : x(x), y(y) {}
	Vector(POINT pt) : x((float)pt.x), y((float)pt.y) {}

	Vector operator+(const Vector& other)
	{
		Vector ret;
		ret.x = x + other.x;
		ret.y = y + other.y;
		return ret;
	}

	Vector operator-(const Vector& other)
	{
		Vector ret;
		ret.x = x - other.x;
		ret.y = y - other.y;
		return ret;
	}

	Vector operator*(float value)
	{
		Vector ret;
		ret.x = x * value;
		ret.y = y * value;
		return ret;
	}
	void operator+=(const Vector& other)
	{
		x += other.x;
		y += other.y;
	}

	void operator-=(const Vector& other)
	{
		x -= other.x;
		y -= other.y;
	}

	void operator*=(float ratio)
	{
		x *= ratio;
		y *= ratio;
	}

	bool operator==(const Vector& other) const
	{
		return (x == other.x && y == other.y);
	}

	bool operator==(Vector& other)
	{
		return (x == other.x && y == other.y);
	}


	// 내적
	// 외적
	// 정규화
	// 크기
	float LengthSquared()
	{
		return x * x + y * y;
	}
	float Length()
	{
		return ::sqrt(LengthSquared());
	}

	void Normalize()
	{
		float length = Length();
		if (length < SMALL_NUMBER)
			return;

		x /= length;
		y /= length;
	}

	// Dot 내적
	// float = cos(A)
	float Dot(Vector other)
	{
		return x * other.x + y * other.y;
	}

	// Cross 외적
	// 결과가 3D 벡터여야하는데, 2D 좌표계라서 Z=0, float 하나를 리턴시킨다. (0,0,x)
	float Cross(Vector other)
	{
		return x * other.y - y * other.x;
	}

	Vector Rotate(float radian)
	{
		float cosA = cosf(radian);
		float sinA = sinf(radian);

		return Vector(x * cosA - y * sinA, x * sinA + y * cosA);
	}
};



struct Cell
{
	int32 iX = 0;
	int32 iY = 0;

	static Cell ConvertToCEll(Vector pos, int32 size)
	{
		if (pos.x < 0 || pos.y < 0)
			return Cell{ -1,-1 };

		return Cell{ (int32)pos.x / size,(int32)pos.y / size };
	}
};