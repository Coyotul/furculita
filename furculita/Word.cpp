#include "Word.h"
#include <cstdlib>

Word::Word()
{
	word.assign("");
	category.assign("");
}

Word::Word(const std::string chosen_word, const std::string chosen_category)
{
	word.assign(chosen_word);
	category.assign(chosen_category);
}
Word::Word(const std::string word_to_be_chosen_from)
{
	word.assign(word_to_be_chosen_from);
	
}

Word::Word(const Word& word)
{
	this->word.assign(word.word);
	this->category.assign(word.category);
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
		int selectedWords = 0;

		while (selectedWords < numWords) {
			int randomIndex = rand() % totalWords;
			for (int i = 0; i < randomIndex; i++) {
				inputFile >> currentWord;
			}
			words.push_back(Word(currentWord));
			selectedWords++;

		}
		inputFile.close();

		return words;
	}
	else {
		throw std::runtime_error("File could not open");
	}
	
}