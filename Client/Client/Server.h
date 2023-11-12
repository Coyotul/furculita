#pragma once
#include <string>

class Server
{

public:
	Server();
	void SetWord(std::string wordToSet);
	std::string GetWord();
private:
	std::string word;
	bool shouldDraw = false;
};

