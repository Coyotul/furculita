#pragma once
#include <string>
#include <vector>

#include <sqlite_orm/sqlite_orm.h>
namespace sql = sqlite_orm;

struct Word
{
	int id;
	std::pair<std::string, std::string> word;
};

inline auto createStorage(const std::string& filename)
{
	return sql::make_storage(
		filename,
		sql::make_table(
			"Words",
			sql::make_column("id", &Word::id, sql::primary_key().autoincrement()),
			sql::make_column("word", &Word::word)
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

