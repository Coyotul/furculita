import user;
using gartic::User;

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

std::string User::GetName()
{
	return this->m_name;
}

void User::SetName(const std::string& name)
{
	m_name = name;
}

uint16_t User::GetScore()
{
	return this->m_score;
}

void User::SetScore(uint16_t score)
{
	m_score = score;
}

void gartic::User::AddPoints(uint16_t points)
{
	m_score = m_score + points;
}
