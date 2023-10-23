#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include "User.h"
#include "Round.h"

class Game
{
public:
	Game();
	void addPlayer(const std::string& playerName);
	void startGame(const std::string& wordToGuess);
	void endGame();
	void guessWord(const std::string& guessedWord);
	void displayScores() const;

private:
	 std::string currentWord;
	 std::vector<User> players;
	 std::uint8_t currentPlayerIndex;
	 bool gameInProgress;
	 Round currentRound;



};

