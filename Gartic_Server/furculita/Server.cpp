#include "Server.h";
#include "Word.h"
#include "WordsDb.h"
import game;


Server::Server() {
	configureRoutes();
}

void Server::run() {
	app.port(8080).multithreaded().run();
}



void Server::configureRoutes() {
	gartic::Game game;
	int language = 1;
	Storage db = createStorage("words.sqlite");
	db.sync_schema();
	auto initialProductsCount = db.count<WordStruct>();
	if (initialProductsCount == 0) {
		populateStorage(db);
	}
	WordsDb wordsDb(db);
	std::vector<WordStruct> randomWords = wordsDb.getRandomWords(3, "romana");



	CROW_ROUTE(app, "/")([]() {

		return "Hello Gartic";

		});
	CROW_ROUTE(app, "/endpoint")
		.methods("POST"_method)
		([](const crow::request& req) {
		// Afișează datele primite prin cererea POST
		std::cout << "Date primite: " << req.body << std::endl;

		// Returnează un răspuns simplu
		return "Cererea POST a fost primită cu succes!";
			});
	CROW_ROUTE(app, "/language")([&language](const crow::request& req)
		{
			// Accesează direct parametrul de query string "language"
			auto languageParam = req.url_params.get("language");

			// Verifică dacă parametrul există
			if (languageParam) {
				try {
					// Convertește la int
					int chosenLanguage = std::stoi(languageParam);

					// Setează valoarea limbajului
					language = chosenLanguage;

					// Afișează valoarea limbajului în consolă
					std::cout << "Limba aleasa este: " << chosenLanguage << std::endl;

					// Returnează un răspuns 200 OK
					return crow::response(200);
				}
				catch (const std::exception& e) {
					// În caz de eroare la conversie
					std::cerr << "Eroare la conversia limbajului: " << e.what() << std::endl;
					return crow::response(400); // Returnează un răspuns 400 Bad Request
				}
			}
			else {
				// În cazul în care parametrul "language" lipsește
				std::cerr << "Parametrul 'language' lipseste." << std::endl;
				return crow::response(400); // Returnează un răspuns 400 Bad Request
			}
		});
	CROW_ROUTE(app, "/words")(
		[&randomWords,wordsDb]()
		{
			randomWords = wordsDb.getRandomWords(3, "romana");
			std::vector<crow::json::wvalue>wordsJSON;
			for (const auto& word : randomWords)
			{
				crow::json::wvalue word{ { "word", word } };
				wordsJSON.push_back(word);
			}
			return crow::json::wvalue(wordsJSON);
		}
	);

}

