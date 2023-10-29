#pragma once
#include <string>
class Round
{
public:
	Round(const std::string& wordToDraw, uint8_t duration);
	uint8_t GetTimeLeft();
	uint8_t GetDuration();
	std::string GetWordToDraw();
	bool WordGuessed(std::string guess);
	void StartRound();
private:
	std::string wordToDraw;
	uint8_t duration;
	uint8_t timeLeft;
};

