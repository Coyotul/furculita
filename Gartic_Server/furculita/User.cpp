#include "User.h"

User::User()
{
	
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
