#pragma once
#ifdef TIMER_EXPORTS
#define TIMER_API _declspec(dllexport)
#else
#define TIMER_API _declspec(dllimport)
#endif

#include <chrono>

class TIMER_API Timer
{

};