#include "Round.h"
#include "word.h"

Round::Round(const std::string& wordToDraw, uint8_t duration)
	:wordToDraw(wordToDraw),
	duration(duration),
	timeLeft(duration)
{
}

uint8_t Round::GetTimeLeft()
{
	return timeLeft;
}

uint8_t Round::GetDuration()
{
	return duration;
}

std::string Round::GetWordToDraw()
{
	return wordToDraw;
}

bool Round::WordGuessed(std::string guess)
{
	if (guess == wordToDraw)
	{
		return true;
	}
	return false;
}

void Round::StartRound()
{
}
