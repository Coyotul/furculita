#include "User.h"

User::User() :
	m_name(" "), m_score(0)
{
}

User::User(std::string_view name, uint16_t score) :
	m_name(name), m_score(score)
{
}

User::User(const User& user) :
	m_name(user.m_name), m_score(user.m_score)
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
