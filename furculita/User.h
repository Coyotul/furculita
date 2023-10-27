#pragma once
#include <string>

class User
{
public:
	User();
	User(const std::string &name, uint16_t score);
	User(const User &user);
	std::string GetName();
	void SetName(const std::string& name);
	uint16_t GetScore();
	void SetScore(uint16_t score);

private:
	std::string m_name;
	uint16_t m_score;
};

