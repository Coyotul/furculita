#include "Timer.h"

Timer* Timer::sInstance = nullptr;

Timer* Timer::Instance()
{
    if (sInstance == nullptr)
        sInstance = new Timer();
    return sInstance;
}

void Timer::Release()
{
    delete sInstance;
    sInstance = nullptr;
}

Timer::Timer()
{
    Reset();
    m_TimeScale = 1.0f;
    m_DeltaTime = std::chrono::duration<float>{ 0.0f };
}


void Timer::Reset()
{
    m_StartTime = std::chrono::system_clock::now();
}

float Timer::GetDeltaTime()
{
    return m_DeltaTime.count();
}

void Timer::SetTimeScale(float t)
{
    m_TimeScale = t;
}

float Timer::GetTimeScale()
{
    return m_TimeScale;
}

void Timer::Tick()
{
    m_DeltaTime = std::chrono::system_clock::now() - m_StartTime;
}

Timer::~Timer()
{
}
