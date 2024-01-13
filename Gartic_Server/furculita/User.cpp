#include "User.h"

User::User()
{
	m_score = 0;
}



 std::string User::GetName() const
{
	return this->m_name;
}

void User::SetName(std::string_view name)
{
	m_name = name;
}

uint16_t User::GetScore() const
{
	
	return this->m_score;
}

void User::SetScore(uint16_t score)
{
	m_score = score;
}

void User::AddScore(uint16_t score)
{
	m_score += score;
}
