#pragma once
#include <string>
#include "word.h"
class Round
{
public:
	Round(const std::string& wordToDraw, uint16_t duration);
	uint16_t getTimeLeft();
	uint16_t getDuration();
	std::string getWordToDraw();
	bool wordGuessed(std::string guess);
	void startRound();
	uint16_t getRoundNumber() const;
private:
	std::string m_wordToDraw;
	uint16_t m_duration;
	uint16_t m_timeLeft;
	uint16_t m_roundNumber;
};

