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
	std::vector<WordStruct> randomWords = wordsDb.getRandomWords(3);
	

	CROW_ROUTE(app, "/words")
		([randomWords](const crow::request& req)-> crow::response {
		std::vector<crow::json::wvalue> wordsJSON;

		// Obține limba specificată de client din query string
		auto lang = req.url_params.get("language");
		// Verifică dacă limba este specificată și este validă (romana sau engleza)
		if (lang) {
			try {
				if (std::stoi(lang) == 1)
				{
					// Filtrăm cuvintele în funcție de limba specificată
					for (const auto& word : randomWords) {
						crow::json::wvalue wordJSON{
							{"word", word.wordInRomanian}
						};
						wordsJSON.push_back(wordJSON);
					}
					return crow::json::wvalue{ wordsJSON };
				}
				else if (std::stoi(lang)==2)
				{
					// Filtrăm cuvintele în funcție de limba specificată
					for (const auto& word : randomWords) {
						crow::json::wvalue wordJSON{
							{"word", word.wordInEnglish}
						};
						wordsJSON.push_back(wordJSON);
					}
					return crow::json::wvalue{ wordsJSON };
				}
				else return crow::response(400,"Nu stiu ce are bossule"); // Returnează un răspuns 400 Bad Request

			}
			catch (const std::exception& e) {
				// În caz de eroare la conversie
				std::cerr << "Eroare la conversia limbajului: " << e.what() << std::endl;
				return crow::response(400); // Returnează un răspuns 400 Bad Request
			}
		}
		else {
			// Limba nu este validă, poți returna o eroare sau o listă goală
			// în funcție de cerințele tale
			return crow::response(400, "Limba specificată nu este validă");
		}

		return crow::json::wvalue(wordsJSON);});

	CROW_ROUTE(app, "/endpoint")
		.methods("POST"_method)
		([](const crow::request& req) {
		// Afișează datele primite prin cererea POST
		std::cout << "Date primite: " << req.body << std::endl;

		// Returnează un răspuns simplu
		return "Cererea POST a fost primită cu succes!";
			});
	CROW_ROUTE(app, "/wordToDraw")
		.methods("POST"_method)([&](const crow::request & req) -> crow::response {
		auto chosenWord = req.url_params.get("chosenWord");
		if (chosenWord) {
			std::string wordToDraw = chosenWord;

			myGame.m_currentRound.setWordToDraw(wordToDraw);
			logi("Word to draw is: ", wordToDraw);
			return crow::response{ 200 };

		}
		else {
			loge("Bad request: Word not chosen");
			return crow::response{ 400 };
		}
	});
	CROW_ROUTE(app, "/getWord")
		.methods("GET"_method)([&]() -> crow::response {
		std::vector<crow::json::wvalue> wordsJSON;
		const auto& word = myGame.m_currentRound.getWordToDraw();
		crow::json::wvalue wordJSON{
			{"word to be drawn:", word}
			};
			wordsJSON.push_back(wordJSON);
		
		return crow::json::wvalue{ wordsJSON };
			});

	CROW_ROUTE(app, "/addPlayer")
		.methods("POST"_method)([&](const crow::request& req) -> crow::response {
		auto usernameParam = req.url_params.get("username");
		language = 2;
		if (usernameParam) {
			std::string playerName=usernameParam;
			
			myGame.addPlayer(playerName);
			
			return crow::response{ "Player added successfully" };
		}
		else {
			return crow::response(400, "Bad Request: 'username' parameter missing");
		}
			});
	CROW_ROUTE(app, "/getPlayers")
		.methods("GET"_method)([&]() -> crow::response {
		std::vector<crow::json::wvalue> wordsJSON;
		for (const auto& it : myGame.getPlayers()) {
			crow::json::wvalue wordJSON{
				{"name", it.first},
				{"score",it.second}
			};
			wordsJSON.push_back(wordJSON);
		}
		return crow::json::wvalue{ wordsJSON };
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
	CROW_ROUTE(app, "/drawing")
		.methods("POST"_method)([&](const crow::request& req) -> crow::response {
		// Obțineți datele din corpul cererii POST
		auto data = req.body;
		std::cout << data.size();
		// Salvați datele într-un fișier temporar (în loc să le stocați direct într-o variabilă, puteți
		// alege să salvați aceste date în baza de date sau în alt loc în funcție de necesități)
		std::ofstream file("received_image.png", std::ios::binary);
		file.write(data.c_str(), data.size());
		file.close();

		// Răspuns OK
		return crow::response{ 200 };
			});

	CROW_ROUTE(app, "/getDrawing")
		.methods("GET"_method)([&]() -> crow::response {
		// Încarcă imaginea din fișierul temporar
		std::ifstream file("received_image.png", std::ios::binary | std::ios::ate);
		if (!file.is_open()) {
			std::cerr << "Eroare la deschiderea fișierului temporar." << std::endl;
			return crow::response(500);  // Server error
		}

		std::streamsize size = file.tellg();
		file.seekg(0, std::ios::beg);

		std::vector<char> buffer(size);
		if (file.read(buffer.data(), size)) {
			// Răspuns cu imaginea încărcată
			crow::response response;
			response.add_header("Content-Type", "image/png");
			response.add_header("Content-Length", std::to_string(size));
			response.body.assign(buffer.data(), buffer.size());  // Convertirea vectorului în șir
			return response;
		}
		else {
			std::cerr << "Eroare la citirea fișierului temporar." << std::endl;
			return crow::response(500);  // Server error
		}
			});

	CROW_ROUTE(app, "/chat")
		.methods("POST"_method) ([&](const crow::request& req) -> crow::response {
		// Extract chat text from the request body
		std::string chatText = req.body;
		std::ofstream fout("chat.txt");
		if (!fout.is_open())
		{
			std::cerr << "Nu s-a putut deschide fisierul.\n";
			return crow::response{ 500 };
		}
		fout.clear();
		fout << chatText;
		fout.close();
		return crow::response{ 200 };
			});

	CROW_ROUTE(app, "/getChat")
		.methods("GET"_method)([&]() -> crow::response {
		std::ifstream fin("chat.txt");
		if (!fin.is_open())
		{
			std::cerr << "Nu s-a putut deschide fisierul.\n";
			return crow::response{ 500 };
		}
		std::string chatText;
		while (fin)
			chatText += fin.get();
		crow::json::wvalue chatJSON{
			{"chat", chatText}
		};
		return chatJSON;
			});
}

