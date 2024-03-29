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
		void startGame();
		void endGame();
		void guessWord(std::string_view guessedWord);
		void displayScores() const;
		void resetScores();
		bool checkGameState() const;
		std::string getMainPlayer();
		void changeMainPlayer();
		void resetGame();
		void sortPlayers();
		void addPlayer(std::string playerName);
		std::vector<std::pair<std::string, int>> getPlayers();
		void calculateScoresBasedOnTime();
		~Game();
		Round m_currentRound;
		std::string chat;
		std::uint16_t m_currentPlayerIndex;
		std::vector<User> m_players;
		std::uint16_t score = 100;
	private:
		std::vector<int> test;
		bool m_gameInProgress;
		int playerIndex = 0;
	};
}