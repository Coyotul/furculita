
#include "User.h"
#include "Round.h"
#include "Word.h"
#include "WordsDb.h"
#include <iostream>
#include <cstdint>


import game;
using gartic::Game;

Game::Game() : m_currentPlayerIndex(0), m_gameInProgress(false), m_currentRound("default word", 0) {
   
}

void Game::addPlayer(std::string playerName) {
    //std::cout << "a intrat";
    if (playerName.empty()) {
        std::cout << "Invalid player name" << std::endl;
        
        return;
    }
    User user;
    user.SetName(playerName);
    user.SetScore(0);
    std::cout << std::endl << "acum vedem daca merge ba";
    m_players.push_back(user);
    std::cout << m_players[0].GetName();
}


Game::~Game() {
   
}


void Game::startGame() 
{
    
    std::cout << "Server started.\n";
    std::cout << "Waiting for clients.\n";
}
void Game::endGame() {
    m_gameInProgress = false;
    displayScores();

}
void Game::guessWord(std::string_view guessedWord) {
    if (m_gameInProgress) {
        if (guessedWord == m_currentRound.getWordToDraw()) {
            //int scoreToAdd = calculateScoreBasedOnTime(); // Implement this function
           // m_players[m_currentPlayerIndex].SetScore(m_players[m_currentPlayerIndex].GetScore() + scoreToAdd);
        }
        m_currentPlayerIndex = (m_currentPlayerIndex + 1) % m_players.size();
    }
}
void Game::displayScores()const 
{

}

void Game::resetScores() {
    /*for (auto& player : m_players) {
        player.SetScore(0);
    }*/
    m_currentPlayerIndex = 0;
    m_gameInProgress = false;
}

void Game::resetGame() {
    resetScores();
    //m_players.clear();

}

//const std::vector<std::pair<std::string, uint16_t>>& gartic::Game::getPlayers() const {
//    static std::vector<std::pair<std::string, uint16_t>> playerNames;
//    playerNames.clear();  
//    if (m_players.size() != 0) {
//        //for (auto& user : m_players) {
//        //    playerNames.push_back(std::make_pair(user.GetName(), 0/*user.GetScore()*/));
//        //}
//    }
//
//    // Return the vector of strings
//    return playerNames;
//}

void gartic::Game::calculateScoresBasedOnTime()
{
    int scoreToBeAdded=0;
}




bool Game::checkGameState()const {
    const uint8_t maxRounds = 4;
    if (m_currentRound.getRoundNumber() > maxRounds) {
        std::cout << "Game over! All rounds have been completed." << std::endl;
        displayScores();
        return false;
    }

    return true;
}


