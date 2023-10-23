#pragma once
#include <string>
class Round
{
public:
	Round(const std::string& wordToDraw, uint8_t duration, uint8_t timeLeft);
	uint8_t GetTimeLeft();
	uint8_t GetDuration();
	uint8_t GetWordToDraw();
private:
	std::string wordToDraw;
	uint8_t duration;
	uint8_t timeLeft;
};

