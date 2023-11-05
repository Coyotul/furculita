#include "Round.h"
#include <iostream>
#include <thread>
#include <chrono>

Round::Round(const std::string& wordToDraw, uint16_t duration)
	:m_wordToDraw(wordToDraw),
	m_duration(duration),
	m_timeLeft(duration),
	m_timerRunning(false)
{
}

uint16_t Round::GetTimeLeft()
{
	return m_timeLeft;
}

uint16_t Round::GetDuration()
{
	return m_duration;
}

std::string Round::GetWordToDraw()
{
	return m_wordToDraw;
}

bool Round::WordGuessed(std::string guess)
{
	if (guess == m_wordToDraw)
	{
		return true;
	}
	return false;
}

void Round::StartRound()
{
	std::cout << "Round start\n";

	while (m_timeLeft > 0)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		m_timeLeft--;

	}
}
