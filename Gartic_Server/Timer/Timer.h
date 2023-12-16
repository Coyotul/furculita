#pragma once
#ifdef TIMER_EXPORTS
#define TIMER_API _declspec(dllexport)
#else
#define TIMER_API _declspec(dllimport)
#endif

#include <chrono>

class TIMER_API Timer
{
private:
	static Timer* sInstance;
	std::chrono::system_clock::time_point m_StartTime;
	std::chrono::duration<float> m_DeltaTime;
	float m_TimeScale;
	Timer();
	~Timer();
};