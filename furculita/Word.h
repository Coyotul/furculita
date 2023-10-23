#pragma once
#include <string>
#include <fstream>
class Word
{
public:
	Word();
	Word(const std::string chosen_word, const std::string chosen_category);
	Word(const Word& word);

private:
	std::string word;
	std::string category;
};

