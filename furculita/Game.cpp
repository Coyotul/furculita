
#include "User.h"
#include "Round.h"
import game;
using garlic::Game;

Game::Game() : currentPlayerIndex(0), gameInProgress(false), currentRound("default word", 0) {

}

void Game::addPlayer(const std::string& playerName) {
    players.push_back(User(playerName, 0));
}

void Game::startGame(const std::string& wordToGuess) {
    currentRound = Round(wordToGuess, 60);
    currentWord = wordToGuess;
    gameInProgress = true;
}
void Game::endGame() {
    gameInProgress = false;
    displayScores();

}
void Game::guessWord(const std::string& guessedWord) {
    if (gameInProgress) {
        if (guessedWord == currentWord) {
            players[currentPlayerIndex].SetScore(players[currentPlayerIndex].GetScore() + 1);
        }
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
    }
}
void Game::displayScores()const {

}