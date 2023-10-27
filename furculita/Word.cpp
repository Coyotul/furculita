#include "Word.h"

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

Word::Word(const Word& word)
{
	this->word.assign(word.word);
	this->category.assign(word.category);
}
