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
		void resetGame();
		void addPlayer(std::string playerName);
		//const std::vector<std::pair<std::string, uint16_t>>& getPlayers() const;
		void calculateScoresBasedOnTime();
		~Game();
		
		
	private:
		
		std::vector<User> m_players;
		std::vector<int> test;
		std::uint8_t m_currentPlayerIndex;
		bool m_gameInProgress;
		Round m_currentRound;
		//Word m_currentWord;

	};
}