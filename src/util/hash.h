#pragma once
#include <cstdint>
#include <string_view>

namespace hash
{
	constexpr std::uint32_t BASE = 0x811C9DC5;
	constexpr std::uint32_t PRIME = 0x1000193;

	// compile-time FNV hash
	consteval std::uint32_t CompileTime(const std::string_view data, const std::uint32_t value = BASE) noexcept
	{
		return (data[0] == '\0') ? value : CompileTime(&data[1], (value ^ unsigned int(data[0])) * PRIME);
	}

	// run-time FNV hash
	inline const std::uint32_t RunTime(const std::string_view data) noexcept
	{
		std::uint32_t hashed = BASE;

		for (const char& character : data)
		{
			hashed ^= character;
			hashed *= PRIME;
		}

		return hashed;
	}
}
