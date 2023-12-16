#include "Server.h";
import game;


Server::Server() {
	configureRoutes();
}

void Server::run() {
	app.port(8080).multithreaded().run();
}

void Server::configureRoutes() {
	gartic::Game game;
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

	/*CROW_ROUTE(app, "/addPlayer/<string>")([&game](const crow::request& req, std::string playerName=" ") {
		if (playerName != " ") {
			game.addPlayer(playerName);
			return crow::response(200);
		}

		});*/
	/*CROW_ROUTE(app, "/getPlayersName")([&game]() {
		std::vector<crow::json::wvalue> playersJSON;
		for (const auto& player : game.getPlayers()) {
			crow::json::wvalue playerJSON{
				{"name", player.first},
				{"score", player.second}
			};
			playersJSON.push_back(playerJSON);
		}
		return crow::json::wvalue(playersJSON);

		});*/

	/*CROW_ROUTE(app, "/game")
		([&game](const crow::request& req) -> crow::response {

		if (req.url_params.get("action") == "start") {
			game.startGame();
		}
		else if (req.url_params.get("action") == "guess") {
			std::string guessedWord = req.url_params.get("word");
			game.guessWord(guessedWord);
		}
		else if (req.url_params.get("action") == "end") {
			game.endGame();
		}
		else if (req.url_params.get("action") == "reset") {
			game.resetGame();
			return crow::response{ "Game reset." };
		}



		if (!game.checkGameState()) {

			return crow::response{ "Game over!" };
		}


		return crow::response{ "Hello Gartic 2" };
			});

			*/
}

