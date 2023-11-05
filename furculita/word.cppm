import <string>;
import <fstream>;
import <vector>;
export module word;


namespace gartic {

	enum class Language : uint8_t {
		Romanian,
		English
	};

	export class Word
	{
	public:
		Word();
		Word(const std::string chosen_word, const Language chosen_language);
		Word(const std::string word_to_be_chosen_from);
		Word(const Word& word);
		std::string GetWord() const;
		static std::vector<Word> GenerateRandomWords(const std::string& filePath, int numWords);


	private:
		std::string word;
		Language language;
	};
}