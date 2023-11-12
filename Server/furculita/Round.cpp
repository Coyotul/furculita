#include "Round.h"
#include "word.h"

Round::Round(const std::string& wordToDraw, uint8_t duration)
	:m_wordToDraw(wordToDraw),
	m_duration(duration),
	m_timeLeft(duration),
	m_roundNumber(1)
{
}

uint8_t Round::getTimeLeft()
{
	return m_timeLeft;
}

uint8_t Round::getDuration()
{
	return m_duration;
}

std::string Round::getWordToDraw()
{
	return m_wordToDraw;
}

bool Round::wordGuessed(std::string guess)
{
	if (guess == m_wordToDraw)
	{
		return true;
	}
	return false;
}

void Round::startRound()
{
}

uint8_t Round::getRoundNumber() const
{
	return m_roundNumber;
}
