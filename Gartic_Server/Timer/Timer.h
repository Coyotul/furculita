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
public:
	static Timer* Instance();
	static void Release();
	void Reset();
	float GetDeltaTime();
	void SetTimeScale(float t = 1.0f);
	float GetTimeScale();
	void Tick();
};