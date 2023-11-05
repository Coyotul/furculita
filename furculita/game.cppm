#include "Round.h"
export module game;
import <string>;
import <vector>;
import word;
using gartic::Word;
import user;
using gartic::User;

namespace gartic {
	export class Game {
	public:
		Game();
		void addPlayer(const std::string& playerName);
		void startGame();
		void endGame();
		void guessWord(const std::string& guessedWord);
		void displayScores() const;

	private:
		//std::string currentWord;
		std::vector<User> players;
		std::uint8_t currentPlayerIndex;
		bool gameInProgress;
		Round currentRound;
		Word currentWord;

	};
}