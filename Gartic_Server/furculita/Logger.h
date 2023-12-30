#pragma once
#include <cstdint>
#include <chrono>
#include <iostream>
class Logger
{
public:
	enum class Level : std::uint8_t
	{
		Info,
		Warning,
		Error
	};
public:
	template <typename... Args>
	static void Log(Level level, Args&&... args)
	{
		switch (level)
		{
			using enum Level;
		case Info:
			std::cout << "[Info]";
			break;
		case Warning:
			std::cout << "[Warning]";
			break;
		case Error:
			std::cout << "[Error]";
			break;

		}

		using std::chrono::system_clock;
		using std::chrono::sys_seconds;
		using std::chrono::floor;
		using std::chrono::seconds;

		sys_seconds now{ floor<seconds>(system_clock::now()) };
		std::cout << std::format("[{:%Y-%m-%d %H:%M:%S}]", now);

		((std::cout << ' ' << std::forward<Args>(args)), ...);

		std::cout << '\n';
	}
};

template <typename... Args>
void logi(Args&&... args)
{
	Logger::Log(Logger::Level::Info, std::forward<Args>(args)...);
}

template <typename... Args>
void logw(Args&&... args)
{
	Logger::Log(Logger::Level::Warning, std::forward<Args>(args)...);
}

template <typename... Args>
void loge(Args&&... args)
{
	Logger::Log(Logger::Level::Error, std::forward<Args>(args)...);
}

