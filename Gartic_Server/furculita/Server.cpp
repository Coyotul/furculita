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
	
	int language = 1; // Acest lucru nu pare a fi folosit în codul tău, îl poți elimina dacă nu este necesar.
	std::string username = " ";
	Storage db = createStorage("words.sqlite");
	db.sync_schema();
	auto initialProductsCount = db.count<WordStruct>();
	if (initialProductsCount == 0) {
		populateStorage(db);
	}
	WordsDb wordsDb(db);

	CROW_ROUTE(app, "/words")
		([&db, &wordsDb](const crow::request& req)-> crow::response {
		std::vector<crow::json::wvalue> wordsJSON;

		// Obține limba specificată de client din query string
		auto lang = req.url_params.get("lang");

		// Verifică dacă limba este specificată și este validă (romana sau engleza)
		if (lang == "romana" || lang == "engleza") {
			std::vector<WordStruct> randomWords = wordsDb.getRandomWords(3, lang);

			// Filtrăm cuvintele în funcție de limba specificată
			for (const auto& word : randomWords) {
				crow::json::wvalue wordJSON{
					{"name", word.wordInRomanian} // Presupunând că atributul pe care vrei să-l afișezi este "name"
				};
				wordsJSON.push_back(wordJSON);
			}
		}
		else {
			// Limba nu este validă, poți returna o eroare sau o listă goală
			// în funcție de cerințele tale
			return crow::response(400, "Limba specificată nu este validă");
		}

		return crow::json::wvalue(wordsJSON);
			});

	CROW_ROUTE(app, "/endpoint")
		.methods("POST"_method)
		([](const crow::request& req) {
		// Afișează datele primite prin cererea POST
		std::cout << "Date primite: " << req.body << std::endl;

		// Returnează un răspuns simplu
		return "Cererea POST a fost primită cu succes!";
			});
	CROW_ROUTE(app, "/addPlayer")
		.methods("POST"_method)([&](const crow::request& req) -> crow::response {
		auto usernameParam = req.url_params.get("username");
		language = 2;
		if (usernameParam) {
			std::string playerName=usernameParam;
			std::cout << std::endl << "sefule numele tau este: " << playerName;
			
			myGame.addPlayer(playerName);
			
			return crow::response{ "Player added successfully" };
		}
		else {
			return crow::response(400, "Bad Request: 'username' parameter missing");
		}
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
	/*CROW_ROUTE(app, "/words")(
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
	);*/

	std::cout << "limba este" << language;

}

