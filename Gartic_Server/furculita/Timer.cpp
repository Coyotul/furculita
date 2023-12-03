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
