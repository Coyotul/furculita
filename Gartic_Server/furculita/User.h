#pragma once
#include <string>

class User
{
public:
	User();
	User(std::string_view name, uint16_t score);
	User(const User &user);
	std::string GetName() const;
	void SetName(std::string_view name);
	uint16_t GetScore() const;
	void SetScore(uint16_t score);

private:
	std::string m_name;
	uint16_t m_score;
};

