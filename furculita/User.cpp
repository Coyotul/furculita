#include "User.h"

User::User() :
	m_name(" "), m_score(0)
{
}

User::User(const std::string& name, uint16_t score) :
	m_name(name), m_score(score)
{
}

User::User(const User& user) :
	m_name(user.m_name), m_score(user.m_score)
{
}
