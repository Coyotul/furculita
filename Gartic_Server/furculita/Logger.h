#pragma once
#include <cstdint>
class Logger
{
public:
	enum class Level : std::uint8_t
	{
		Info,
		Warning,
		Error
	};
};

