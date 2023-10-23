#pragma once
#include <string>

class User
{
public:
	User();
	User(const std::string &name, uint16_t score);
	User(const User &user);
private:
	std::string m_name;
	uint16_t m_score;
};

