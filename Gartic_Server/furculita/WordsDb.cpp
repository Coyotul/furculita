#include "WordsDb.h"
#include <fstream>
#include <vector>
#include <utility>
#include <string>
#include <algorithm>
#include <random>

void populateStorage(Storage& storage)
{
    std::ifstream inputFile("words.txt");
    if (!inputFile.is_open())
    {
        std::cerr << "Error opening file " << std::endl;
        return;
    }

    std::vector<WordStruct> words;

    std::string line;
    while (std::getline(inputFile, line))
    {
        std::istringstream iss(line);
        std::string word1, word2;

        if (iss >> word1 >> word2)
        {
            WordStruct element;
            element.id = -1;
            element.wordInEnglish = word1;
            element.wordInRomanian = word2;

            words.push_back(element);
        }
        else
        {
            std::cerr << "Error reading line: " << line << std::endl;
        }
    }

    inputFile.close();

    if (!words.empty())
    {
        storage.insert_range(words.begin(), words.end());
        std::cout << "Database populated successfully." << std::endl;
    }
    else
    {
        std::cerr << "No data to populate the database." << std::endl;
    }
    
}

WordsDb::WordsDb(Storage& storage):
	m_db { storage }
{
    
}

std::vector<WordStruct> WordsDb::getRandomWords(size_t count, const std::string& language) const
{   
    try {
        auto allWords = m_db.get_all<WordStruct>();

        auto languageFilter = [&language](const WordStruct& word) {
            return (language == "english") ? !word.wordInEnglish.empty() : !word.wordInRomanian.empty();
        };
        std::cout << "Words before language filtering: ";
        for (const auto& word : allWords) {
            std::cout << word.wordInEnglish << " | " << word.wordInRomanian << ", ";
        }
        std::cout << std::endl;
        std::cout << "Number of words before language filtering: " << allWords.size() << std::endl;
        allWords.erase(std::remove_if(allWords.begin(), allWords.end(), languageFilter), allWords.end());
        std::cout << "Number of words after language filtering: " << allWords.size() << std::endl;
        // Shuffle the vector randomly
        std::random_device rd;
        std::mt19937 g(rd());

        std::shuffle(allWords.begin(), allWords.end(), g);

        // Take the first 'count' elements
        if (allWords.size() > count) {
            allWords.resize(count);
        }

        

        return allWords;

    }
    catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    // Filter by language
    
}





