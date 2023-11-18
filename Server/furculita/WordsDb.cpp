#include "WordsDb.h"
#include <fstream>
#include <vector>
#include <utility>
#include <string>
void populateStorage(Storage& storage)
{
	std::ifstream inputFile("words.txt");
	std::vector<Word2> words;

	std::string line;
	while (std::getline(inputFile, line))
	{
		std::istringstream iss(line);
		std::string word1, word2;

		if (iss >> word1 >> word2)
		{
			Word2 element;
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
