
#include "User.h"
#include "Round.h"
#include "Word.h"
#include <iostream>

import game;
using gartic::Game;

Game::Game() : currentPlayerIndex(0), gameInProgress(false), currentRound("default word", 0), currentWord() {

}

void Game::addPlayer(const std::string& playerName) {
    players.push_back(User(playerName, 0));
}

void Game::startGame() {
    
    std::vector<Word> randomWords = Word::GenerateRandomWords("words.txt", 3);


    for (int i = 0; i < 3; ++i) {
        std::cout << i + 1 << ". " << randomWords[i].GetWord() << std::endl;
    }


    int userChoice;
    std::cout << "Choose a number (1-3): ";
    std::cin >> userChoice;

    if (userChoice >= 1 && userChoice <= 3) {
        currentWord = randomWords[userChoice - 1].GetWord();
        currentRound = Round(currentWord.GetWord(), 60);
        gameInProgress = true;
        std::cout << currentWord.GetWord();
    }
    else {
        std::cout << "Invalid option" << std::endl;
        gameInProgress = false;
    }

    
}
void Game::endGame() {
    gameInProgress = false;
    displayScores();

}
void Game::guessWord(const std::string& guessedWord) {
    if (gameInProgress) {
        if (guessedWord == currentRound.GetWordToDraw()) {
            players[currentPlayerIndex].SetScore(players[currentPlayerIndex].GetScore() + 1);
        }
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
    }
}
void Game::displayScores()const 
{

}
