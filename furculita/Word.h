#pragma once
#include <string>
#include <fstream>
#include <vector>
class Word
{
public:
	Word();
	Word(const std::string chosen_word, const std::string chosen_category);
	Word(const std::string word_to_be_chosen_from);
	Word(const Word& word);
	std::string GetWord() const;
	static std::vector<Word> GenerateRandomWords(const std::string& filePath, int numWords);


private:
	std::string word;
	std::string category;
};

