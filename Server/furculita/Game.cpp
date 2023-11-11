
#include "User.h"
#include "Round.h"
#include "Word.h"
#include <iostream>
#include <cstdint>

import game;
using gartic::Game;

Game::Game() : currentPlayerIndex(0), gameInProgress(false), currentRound("default word", 0), currentWord() {

}

void Game::addPlayer(const std::string& playerName) {
    players.push_back(User(playerName, 0));
}

void Game::startGame() {
    const uint16_t numChoices = 3;
    std::vector<Word> randomWords = Word::GenerateRandomWords("words.txt", 3);


    for (const auto&word:randomWords) {
        std::cout<<word.GetWord() << std::endl;
    }


    uint16_t userChoice;
    std::cout << "Choose a number (1-" << numChoices << "): ";
    

    if (!(std::cin >> userChoice) || userChoice < 1 || userChoice > numChoices) {
        std::cout << "Invalid option" << std::endl;
        gameInProgress = false;
        return;

    }
    currentWord = randomWords[userChoice - 1].GetWord();
    currentRound = Round(currentWord.GetWord(), 60);
    gameInProgress = true;
    std::cout << currentWord.GetWord();

    
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
