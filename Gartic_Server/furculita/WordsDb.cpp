#include "WordsDb.h"
#include <fstream>
#include <vector>
#include <utility>
#include <string>
#include <algorithm>
#include <random>

void populateStorage(Storage& storage)
{
    std::ifstream inputFile("wordsfile.txt");
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

std::vector<WordStruct> WordsDb::getRandomWords(size_t count) const
{
    auto allWords = m_db.get_all<WordStruct>();
    std::vector<WordStruct> filteredWords;

    // Amestecarea cuvintelor
    auto rng = std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count());
    std::shuffle(allWords.begin(), allWords.end(), rng);

    // Alegerea primelor count cuvinte
    filteredWords.assign(allWords.begin(), allWords.begin() + std::min(count, allWords.size()));

    return filteredWords;
}
