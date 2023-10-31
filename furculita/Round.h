#pragma once
#include <string>
import word;
using gartic::Word;
class Round
{
public:
	Round(const std::string& wordToDraw, uint16_t duration);
	uint16_t GetTimeLeft();
	uint16_t GetDuration();
	std::string GetWordToDraw();
	bool WordGuessed(std::string guess);
	void StartRound();
private:
	std::string m_wordToDraw;
	uint16_t m_duration;
	uint16_t m_timeLeft;
	bool m_timerRunning;
};

