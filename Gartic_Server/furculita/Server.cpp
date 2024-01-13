#include "Server.h";
#include "Word.h"
#include "WordsDb.h"
#include <thread>
import game;

Server::Server() {
	configureRoutes();
}

void Server::run() {
	app.port(8080).multithreaded().run();
}

void Server::configureRoutes() {
	
	int language = 1;
	int currentPlayer;
	int score=100;
	std::string username = " ";
	CROW_ROUTE(app, "/words")
		([](const crow::request& req)-> crow::response {
		Storage db = createStorage("words.sqlite");
		db.sync_schema();
		auto initialProductsCount = db.count<WordStruct>();
		if (initialProductsCount == 0) {
			populateStorage(db);
		}
		WordsDb wordsDb(db);
		std::vector<WordStruct> randomWords = wordsDb.getRandomWords(3);
		std::vector<crow::json::wvalue> wordsJSON;

		auto lang = req.url_params.get("language");
		if (lang) {
			try {
				if (std::stoi(lang) == 1)
				{
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
					for (const auto& word : randomWords) {
						crow::json::wvalue wordJSON{
							{"word", word.wordInEnglish}
						};
						wordsJSON.push_back(wordJSON);
					}
					return crow::json::wvalue{ wordsJSON };
				}
				else return crow::response(400,"Nu stiu ce are bossule");

			}
			catch (const std::exception& e) {
				std::cerr << "Eroare la conversia limbajului: " << e.what() << std::endl;
				return crow::response(400);
			}
		}
		else {
			return crow::response(400, "Limba specificată nu este validă");
		}

		return crow::json::wvalue(wordsJSON);});

	CROW_ROUTE(app, "/endpoint")
		.methods("POST"_method)
		([](const crow::request& req) {
		std::cout << "Date primite: " << req.body << std::endl;
		return "Cererea POST a fost primită cu succes!";
			});
	CROW_ROUTE(app, "/wordToDraw")
		.methods("POST"_method)([&](const crow::request & req) -> crow::response {
		auto chosenWord = req.url_params.get("chosenWord");
		if (chosenWord) {
			std::string wordToDraw = chosenWord;
			if (myGame.m_currentRound.getRoundNumber() == 1)
			{
				std::thread roundThread([=]() {
					myGame.m_currentRound.startRound();
					});
				roundThread.detach();
			}

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
			{"word", word}
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
			currentPlayer = myGame.m_currentPlayerIndex;
			myGame.m_currentPlayerIndex++;
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
			auto languageParam = req.url_params.get("language");
			if (languageParam) {
				try {
					int chosenLanguage = std::stoi(languageParam);
					language = chosenLanguage;
					std::cout << "Limba aleasa este: " << chosenLanguage << std::endl;
					return crow::response(200);
				}
				catch (const std::exception& e) {
					std::cerr << "Eroare la conversia limbajului: " << e.what() << std::endl;
					return crow::response(400); 
				}
			}
			else {
				std::cerr << "Parametrul 'language' lipseste." << std::endl;
				return crow::response(400); 
			}
		});
	CROW_ROUTE(app, "/drawing")
		.methods("POST"_method)([&](const crow::request& req) -> crow::response {
		auto data = req.body;
		std::cout << data.size();
		std::ofstream file("received_image.png", std::ios::binary);
		file.write(data.c_str(), data.size());
		file.close();
		return crow::response{ 200 };
			});

	CROW_ROUTE(app, "/getDrawing")
		.methods("GET"_method)([&]() -> crow::response {
		std::ifstream file("received_image.png", std::ios::binary | std::ios::ate);
		if (!file.is_open()) {
			std::cerr << "Eroare la deschiderea fișierului temporar." << std::endl;
			return crow::response(500);  
		}
		std::streamsize size = file.tellg();
		file.seekg(0, std::ios::beg);

		std::vector<char> buffer(size);
		if (file.read(buffer.data(), size)) {
			crow::response response;
			response.add_header("Content-Type", "image/png");
			response.add_header("Content-Length", std::to_string(size));
			response.body.assign(buffer.data(), buffer.size());
			return response;
		}
		else {
			std::cerr << "Eroare la citirea fișierului temporar." << std::endl;
			return crow::response(500);
		}
			});

	CROW_ROUTE(app, "/chat")
		.methods("POST"_method) ([&](const crow::request& req) -> crow::response {
		auto data = req.url_params.get("chat");
		myGame.chat = data;
		size_t lastNewlineIndex = myGame.chat.find_last_of('\n');

		if (lastNewlineIndex != std::string::npos) {
			std::string lastLine = myGame.chat.substr(lastNewlineIndex + 1);

			size_t separatorIndex = lastLine.find(": ");

			if (separatorIndex != std::string::npos) {
				size_t firstSpaceIndex = lastLine.find(' ', separatorIndex + 2);
				std::string firstWord = lastLine.substr(separatorIndex + 2, firstSpaceIndex - separatorIndex - 2);
				size_t secondSpaceIndex = lastLine.find(' ', firstSpaceIndex + 1);
				std::string secondWord;
				if (secondSpaceIndex != std::string::npos) {
					secondWord = lastLine.substr(firstSpaceIndex + 1, secondSpaceIndex - firstSpaceIndex - 1);
				}
				else {
					secondWord = lastLine.substr(firstSpaceIndex + 1);
				}

				secondWord.pop_back();
				std::string copy;
				for (char it : firstWord)
				{
					it = tolower(it);
					copy.push_back(it);
				}
				copy[0] = toupper(copy[0]);
				if (copy == myGame.m_currentRound.getWordToDraw())
				{
					for (auto& it : myGame.m_players)
					{
						if (it.GetName() == secondWord)
						{
							it.SetScore(it.GetScore() + myGame.score);
							myGame.score -= 10;
						}
					}
				}
			}
			
		}
		return crow::response(200);
			});
	CROW_ROUTE(app, "/guessedWord")
		.methods("POST"_method) ([&](const crow::request& req) -> crow::response {
		auto data = req.url_params.get("word");
		auto data2 = req.url_params.get("name");
		if (data == myGame.m_currentRound.getWordToDraw())
		{
			for (auto& it : myGame.m_players)
			{
				if (it.GetName() == data2)
				{
					it.SetScore(it.GetScore() + myGame.score);
					myGame.score -= 10;
				}
			}
		}
		return crow::response(200);
			});

	CROW_ROUTE(app, "/getChat")
		.methods("GET"_method)([&]() -> crow::response {
		crow::json::wvalue chatJSON{
			{"chat", myGame.chat}
		};
		std::cout << myGame.chat << '\n';
		return crow::json::wvalue{ chatJSON };
			});
	CROW_ROUTE(app, "/getMainPlayer")
		.methods("GET"_method)([&]() -> crow::response {
		crow::json::wvalue player{
			{"name", myGame.getMainPlayer()},
		};
		return crow::json::wvalue{ player };
			});

	CROW_ROUTE(app, "/getTimeLeft")
		.methods("GET"_method)([&]() -> crow::response {
		const auto timeLeft = myGame.m_currentRound.getTimeLeft();
		crow::json::wvalue timeLeftJSON{
			{"timeLeft", timeLeft}
		};
		std::thread cycleThread([=]() {
			if (timeLeft == 0)
			{
				myGame.sortPlayers();
				myGame.score = 100;
				myGame.m_currentRound.finishRound();
				std::this_thread::sleep_for(std::chrono::seconds(10));
				if (myGame.m_currentRound.getRoundNumber() <= myGame.m_players.size() && myGame.m_currentRound.getRoundNumber() != 1
						&& !myGame.m_currentRound.isInProgress())
					{
						myGame.changeMainPlayer();
						std::thread roundThread([=]() {
							myGame.m_currentRound.startRound();
							});
						roundThread.detach();
					}

				}
				});
			cycleThread.detach();
		return crow::json::wvalue{ timeLeftJSON };
			});
}

