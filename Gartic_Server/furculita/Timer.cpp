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

Timer::~Timer()
{

}
void Timer::Reset()
{
}

float Timer::GetDeltaTime()
{
    return 0.0f;
}

void Timer::SetTimeScale(float t)
{
}

float Timer::GetTimeScale()
{
    return 0.0f;
}

void Timer::Tick()
{
}

Timer::~Timer()
{
}
