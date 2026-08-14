#pragma once
#include <cmath>

// 공용 2D 수학 타입과 수치 유틸리티
using int8 = char;		// 1byte 정수형
using int16 = short;	// 2byte 정수형
using int32 = int;		// 4byte 정수형
using int64 = long long;// 8byte 정수형

using uint8 = unsigned char;		// 1byte 정수형
using uint16 = unsigned short;	// 2byte 정수형
using uint32 = unsigned int;		// 4byte 정수형
using uint64 = unsigned long long;// 8byte 정수형

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

	float Dot(Vector other)
	{
		return x * other.x + y * other.y;
	}

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

	static Cell ConvertToCell(Vector pos, int32 size)
	{
		if (pos.x < 0 || pos.y < 0)
			return Cell{ -1,-1 };

		return Cell{ (int32)pos.x / size,(int32)pos.y / size };
	}
};
