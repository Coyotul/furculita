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
	std::string getWord() const;
	std::string getLanguage() const;
	static std::vector<Word> generateRandomWords(const std::string& filePath, int numWords);
private:
	std::string m_word;
	std::string m_language;
};