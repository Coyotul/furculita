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
		void addPlayer(std::string playerName);
		std::vector<std::pair<std::string, int>> getPlayers();
		//const std::vector<std::pair<std::string, uint16_t>>& getPlayers() const;
		void calculateScoresBasedOnTime();
		~Game();
		Round m_currentRound;
		std::string chat;
		std::uint16_t m_currentPlayerIndex;
		std::vector<User> m_players;
	private:
		
		
		std::vector<int> test;
		
		bool m_gameInProgress;
		int playerIndex = 0;
		//Word m_currentWord;

	};
}