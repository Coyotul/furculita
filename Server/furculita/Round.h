#pragma once
#include <string>
#include "word.h"
class Round
{
public:
	Round(const std::string& wordToDraw, uint8_t duration);
	uint8_t GetTimeLeft();
	uint8_t GetDuration();
	std::string GetWordToDraw();
	bool WordGuessed(std::string guess);
	void StartRound();
	uint8_t GetRoundNumber() const;
private:
	std::string wordToDraw;
	uint8_t duration;
	uint8_t timeLeft;
	uint8_t roundNumber;
};

