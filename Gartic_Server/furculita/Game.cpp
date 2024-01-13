
#include "User.h"
#include "Round.h"
#include "Word.h"
#include "WordsDb.h"
#include <iostream>
#include <cstdint>


import game;
using gartic::Game;

Game::Game() : m_currentPlayerIndex(0), m_gameInProgress(false), m_currentRound("default word", 60) {
   
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
    m_players.push_back(user);
    std::cout << m_players[0].GetName();
}

std::vector<std::pair<std::string, int>> gartic::Game::getPlayers()
{
    std::vector<std::pair<std::string, int>> players;
    for (auto it : m_players)
    {
        players.push_back(std::make_pair(it.GetName(), it.GetScore()));
    }

    return players;
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

int comparator(User p1, User p2)
{
    return (p1.GetScore() < p2.GetScore());
}
void gartic::Game::sortPlayers()
{
    std::sort(m_players.begin(), m_players.end(), comparator);
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
    const uint8_t maxRounds = 3;
    if (m_currentRound.getRoundNumber() > maxRounds) {
        std::cout << "Game over! All rounds have been completed." << std::endl;
        displayScores();
        return false;
    }

    return true;
}

std::string Game::getMainPlayer()
{
    return m_players[playerIndex].GetName();
}

void Game::changeMainPlayer()
{
    playerIndex++;
    if (playerIndex > m_players.size() - 1)
    {
        playerIndex = 0;
    }
}


