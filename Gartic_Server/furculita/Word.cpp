#include "Word.h"
#include <cstdlib>

Word::Word()
{
	m_word.assign("");
	m_language.assign("");
}

Word::Word(const std::string chosen_word, const std::string chosen_category)
{
	m_word.assign(chosen_word);
	m_language.assign(chosen_category);
}
Word::Word(const std::string word_to_be_chosen_from)
{
	m_word.assign(word_to_be_chosen_from);
	
}

Word::Word(const Word& word)
{
	this->m_word.assign(word.m_word);
	this->m_language.assign(word.m_language);
}

std::string Word::getWord() const
{
	return m_word;
}

std::vector<Word> Word::generateRandomWords(const std::string& filePath, int numWords)
{
	std::vector<Word>words;
	std::ifstream inputFile("words.txt");

	if (inputFile.is_open()) {
		std::string currentWord;

		int totalWords = 0;
		while (inputFile >> currentWord) {
			totalWords++;
		}

		inputFile.close();

		if (numWords > totalWords) {
			throw std::runtime_error("There are not enought words in the file");
		}

		srand(time(0));

		inputFile.open(filePath);
		std::vector<int> selectedIndices;

		while (words.size() < numWords) {
			int randomIndex = rand() % totalWords;
			if (std::find(selectedIndices.begin(), selectedIndices.end(), randomIndex) == selectedIndices.end()) {
				selectedIndices.push_back(randomIndex);
				for (int i = 0; i < randomIndex; i++) {
					inputFile >> currentWord;
				}
				words.push_back(Word(currentWord));

			}
		}
		inputFile.close();

		return words;
	}
	else {
		throw std::runtime_error("File could not open");
	}
	
}