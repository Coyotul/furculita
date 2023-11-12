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
		std::vector<User> m_players;
		std::uint8_t m_currentPlayerIndex;
		bool m_gameInProgress;
		Round m_currentRound;
		Word m_currentWord;

	};
}