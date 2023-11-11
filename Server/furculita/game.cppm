#include "User.h"
#include "Round.h"
#include "Word.h"
export module game;
import <string>;
import <vector>;

namespace gartic {
	export class Game {
	public:
		Game();
		void addPlayer(const std::string& playerName);
		void startGame();
		void endGame();
		void guessWord(const std::string& guessedWord);
		void displayScores() const;
		void resetScores();
		bool checkGameState() const;

	private:
		//std::string currentWord;
		std::vector<User> players;
		std::uint8_t currentPlayerIndex;
		bool gameInProgress;
		Round currentRound;
		Word currentWord;

	};
}