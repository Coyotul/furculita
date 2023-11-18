#pragma once
#include <string>
#include <vector>

#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
namespace sql = sqlite_orm;

struct WordStruct
{
	int id;
	std::string wordInEnglish;
	std::string wordInRomanian;

};

inline auto createStorage(const std::string& filename)
{
	return sql::make_storage(
		filename,
		sql::make_table(
			"Words",
			sql::make_column("id", &WordStruct::id, sql::primary_key().autoincrement()),
			sql::make_column("word_in_english", &WordStruct::wordInEnglish),
			sql::make_column("word_in_romanian", &WordStruct::wordInRomanian)

		)
	);
}

using Storage = decltype(createStorage(""));

void populateStorage(Storage& storage);

class WordsDb
{
public:
	WordsDb(Storage& storage);

private:
	Storage& m_db;
};

