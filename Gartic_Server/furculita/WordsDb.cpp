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
	}

	inputFile.close();

	storage.insert_range(words.begin(), words.end());	
}

WordsDb::WordsDb(Storage& storage):
	m_db { storage }
{

}

std::vector<WordStruct> WordsDb::getRandomWords(size_t count, const std::string& language) const
{
	auto allWords = m_db.get_all<WordStruct>();

	// Filter by language
	auto languageFilter = [&language](const WordStruct& word) {
		return (language == "english") ? !word.wordInEnglish.empty() : !word.wordInRomanian.empty();
	};

	allWords.erase(std::remove_if(allWords.begin(), allWords.end(), languageFilter), allWords.end());

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





