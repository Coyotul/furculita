#pragma once
#include <chrono>
class Timer
{
private:

	static Timer* sInstance;
	std::chrono::system_clock::time_point m_StartTime;
	std::chrono::duration<float> m_DeltaTime;
	float m_TimeScale;

public:
	static Timer* Instance();
	static void Release();

	void Reset();
	float GetDeltaTime();
	void SetTimeScale(float t = 1.0f);
	float GetTimeScale();
	void Tick();

private:

	Timer();
	~Timer();
};

