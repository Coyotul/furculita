#pragma once
#include <cstdint>
#include <string>
#include <vector>
class Game
{
public:
	Game();

private:
	 std::string currentWord;
	 //std::vector<Player> players;
	 std::uint8_t currentPlayerIndex;
	 bool gameInProgress;



};

