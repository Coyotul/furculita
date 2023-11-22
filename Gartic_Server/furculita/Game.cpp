
#include "User.h"
#include "Round.h"
#include "Word.h"
#include "WordsDb.h"
#include <iostream>
#include <cstdint>


import game;
using gartic::Game;

Game::Game() : m_currentPlayerIndex(0), m_gameInProgress(false), m_currentRound("default word", 0), m_currentWord() {

}

void Game::addPlayer(std::string_view playerName) {
    m_players.push_back(User(playerName, 0));
}



void Game::startGame() {
    const uint16_t numChoices = 3;

    // Ask the user to choose the language
    std::cout << "Choose the language (1. English, 2. Romanian): ";
    int languageChoice;
    std::cin >> languageChoice;

    std::string language;
    switch (languageChoice) {
    case 1:
        language = "english";
        break;
    case 2:
        language = "romanian";
        break;
    default:
        std::cout << "Invalid language choice" << std::endl;
        m_gameInProgress = false;
        return;
    }

    Storage db = createStorage("words.sqlite");
    db.sync_schema();
    auto initialProductsCount = db.count<WordStruct>();
    if (initialProductsCount == 0) {
        populateStorage(db);
    }
    WordsDb wordsDb(db);
    std::vector<WordStruct> randomWords = wordsDb.getRandomWords(numChoices, language);

    for (size_t i = 0; i < randomWords.size(); ++i) {
        std::cout << i + 1 << ". " << ((language == "english") ? randomWords[i].wordInEnglish : randomWords[i].wordInRomanian) << std::endl;
    }

    uint16_t userChoice;
    std::cout << "Choose a number (1-" << numChoices << "): ";

    if (!(std::cin >> userChoice) || userChoice < 1 || userChoice > numChoices) {
        std::cout << "Invalid option" << std::endl;
        m_gameInProgress = false;
        return;
    }
    
    if (userChoice <= randomWords.size()) {
        m_currentWord = (language == "english") ? randomWords[userChoice - 1].wordInEnglish : randomWords[userChoice - 1].wordInRomanian;
        m_currentRound = Round(m_currentWord.getWord(), 60);
        m_gameInProgress = true;
        std::cout << m_currentWord.getWord();
    }
    else {
        std::cout << "Invalid option" << std::endl;
        m_gameInProgress = false;
    }
}
void Game::endGame() {
    m_gameInProgress = false;
    displayScores();

}
void Game::guessWord(std::string_view guessedWord) {
    if (m_gameInProgress) {
        if (guessedWord == m_currentRound.getWordToDraw()) {
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

void Game::resetGame() {
    resetScores();
    m_players.clear();


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


