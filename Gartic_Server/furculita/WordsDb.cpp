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
    
        auto allWords = m_db.get_all<WordStruct>();
        std::vector<WordStruct> filteredWords(1);
        if (language == "english") {
            int i = 0;
            for (const auto& word : allWords) {
              filteredWords.resize(i+1);
              filteredWords[i].wordInEnglish = word.wordInEnglish;
              i++;
            }
            
        }
        else {
            int i = 0;
            for (const auto& word : allWords) {
                filteredWords.resize(i + 1);
                filteredWords[i].wordInRomanian = word.wordInRomanian;
                i++;
            }
        }
        
        // Shuffle the vector randomly
        std::random_device rd;
        std::mt19937 g(rd());

        std::shuffle(filteredWords.begin(), filteredWords.end(), g);
        
        // Take the first 'count' elements
        if (filteredWords.size() > count) {
            filteredWords.resize(count);
        }

        return filteredWords;

    
    

   
    
}





