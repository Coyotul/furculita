#include "Round.h"
#include "word.h"
#include "../Timer/Timer.h"
#include <iostream>

Round::Round(const std::string& wordToDraw, uint16_t duration)
	:m_wordToDraw{ wordToDraw },
	m_duration{ duration },
	m_timeLeft{ duration },
	m_roundNumber{ 1 },
	m_inProgress{ false }
{
}

uint16_t Round::getTimeLeft()
{
	return m_timeLeft;
}

uint16_t Round::getDuration()
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
	Timer* timer = Timer::Instance();
	bool isRunning = true;
	m_inProgress = true;
	while (isRunning)
	{
		timer->Tick();

		if (timer->GetDeltaTime() >= 1) {

			timer->Reset();
			m_timeLeft--;
			if (m_timeLeft == 0) isRunning = false;
		}
	}
}

void Round::finishRound()
{
	if (m_timeLeft == 0)
	{
		std::cout << "Round " << m_roundNumber << " has finished!\n";
		m_timeLeft = m_duration;
		m_roundNumber++;
		m_inProgress = false;
	}
}


uint16_t Round::getRoundNumber() const
{
	return m_roundNumber;
}

void Round::setWordToDraw(std::string word)
{
	m_wordToDraw = word;
}

bool Round::isInProgress()
{
	return m_inProgress;
}