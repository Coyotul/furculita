
#include "User.h"
#include "Round.h"
#include "Word.h"
#include <iostream>
#include <cstdint>

import game;
using gartic::Game;

Game::Game() : m_currentPlayerIndex(0), m_gameInProgress(false), m_currentRound("default word", 0), m_currentWord() {

}

void Game::addPlayer(const std::string& playerName) {
    m_players.push_back(User(playerName, 0));
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
        m_gameInProgress = false;
        return;

    }
    m_currentWord = randomWords[userChoice - 1].GetWord();
    m_currentRound = Round(m_currentWord.GetWord(), 60);
    m_gameInProgress = true;
    std::cout << m_currentWord.GetWord();

    
}
void Game::endGame() {
    m_gameInProgress = false;
    displayScores();

}
void Game::guessWord(const std::string& guessedWord) {
    if (m_gameInProgress) {
        if (guessedWord == m_currentRound.GetWordToDraw()) {
            m_players[m_currentPlayerIndex].SetScore(m_players[m_currentPlayerIndex].GetScore() + 1);
        }
        m_currentPlayerIndex = (m_currentPlayerIndex + 1) % m_players.size();
    }
}
void Game::displayScores()const 
{

}

void Game::resetScores() {
    for (auto& player : m_players) {
        player.SetScore(0);
    }
    m_currentPlayerIndex = 0;
    m_gameInProgress = false;
}

bool Game::checkGameState()const {
    const uint8_t maxRounds = 4;
    if (m_currentRound.GetRoundNumber() > maxRounds) {
        std::cout << "Game over! All rounds have been completed." << std::endl;
        displayScores();
        return false;
    }

    return true;
}
