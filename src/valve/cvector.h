#pragma once
#include <cstdint>

class CVector
{
public:
	constexpr CVector operator+(const CVector& other) noexcept
	{
		return { x + other.x, y + other.y, z + other.z };
	}

	constexpr CVector operator-(const CVector& other) noexcept
	{
		return { x - other.x, y - other.y, z - other.z };
	}

	float x{ }, y{ }, z{ };
};
