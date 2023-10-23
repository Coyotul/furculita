#pragma once
#include <cstdint>
#include <string>
#include <vector>
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
	 //std::vector<Player> players;
	 std::uint8_t currentPlayerIndex;
	 bool gameInProgress;




};

