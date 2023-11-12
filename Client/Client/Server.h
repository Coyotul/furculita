#pragma once
#include <string>

class Server
{

public:
	Server();
	void SetWord(std::string wordToSet);
	std::string GetWord();
	bool CanUserDraw();
	void MakeUserDraw(bool should);

private:
	std::string word;
	bool shouldDraw = false;
};

