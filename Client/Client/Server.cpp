#include "Server.h"

void Server::SetWord(std::string wordToSet)
{
	word.assign(wordToSet);
}

std::string Server::GetWord()
{
	return word;
}

bool Server::CanUserDraw()
{
	return shouldDraw;
}

void Server::MakeUserDraw(bool should)
{
	shouldDraw = should;
}
