#include "pch.h"
#include "Util.h"
#include <numbers>  // C++20

std::wstring Utf8ToWide(const std::string& utf8)
{
	if (utf8.empty())
		return std::wstring();

	int32 len = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), static_cast<int>(utf8.size()), nullptr, 0);
	std::wstring wide(len, L'\0');
	MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), static_cast<int>(utf8.size()), wide.data(), len);
	return wide;
}

float RadianToDegree(float radian)
{
	float degree = radian * (180.0f / std::numbers::pi_v<float>);

	degree = fmodf(degree, 360.0f);
	if (degree < 0.0f)
		degree += 360.0f;

	return degree;
}

float DegreeToRadian(float degree)
{
	float radian = degree * (std::numbers::pi_v<float> / 180.0f);

	radian = fmodf(radian, std::numbers::pi_v<float> *2);
	if (radian < 0.0f)
		radian += std::numbers::pi_v<float> *2;

	return radian;
}
