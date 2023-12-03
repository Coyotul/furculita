#include "Timer.h"

Timer* Timer::Instance()
{
    return nullptr;
}

void Timer::Release()
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
