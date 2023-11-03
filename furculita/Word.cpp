#include <cstdlib>

import word;
using gartic::Word;

Word::Word()
{
	word.assign("");
	language = Language::Romanian;
}

Word::Word(const std::string chosen_word, const Language chosen_language)
{
	word.assign(chosen_word);
	language = chosen_language;
}

Word::Word(const std::string word_to_be_chosen_from, const Language chosen_language)
{
	word.assign(word_to_be_chosen_from);
	language = chosen_language;
}

Word::Word(const Word& word)
{
	this->word.assign(word.word);
	this->language = word.language;
}

std::string Word::GetWord() const
{
	return word;
}


std::vector<Word> Word::GenerateRandomWords(const std::string& filePath, int numWords)
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