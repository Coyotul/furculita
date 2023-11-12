#pragma once
#include <string>
#include "word.h"
class Round
{
public:
	Round(const std::string& wordToDraw, uint8_t duration);
	uint8_t getTimeLeft();
	uint8_t getDuration();
	std::string getWordToDraw();
	bool wordGuessed(std::string guess);
	void startRound();
	uint8_t getRoundNumber() const;
private:
	std::string m_wordToDraw;
	uint8_t m_duration;
	uint8_t m_timeLeft;
	uint8_t m_roundNumber;
};

