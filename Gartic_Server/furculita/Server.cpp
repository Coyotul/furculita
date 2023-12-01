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

	CROW_ROUTE(app, "/addPlayer")([&game](const crow::request& req)->crow::response {
		if (req.method == crow::HTTPMethod::Post) {

			std::string playerName = req.url_params.get("playerName");
			game.addPlayer(playerName);

			return crow::response{ "Player added: " + playerName };
		}
		else {
			return crow::response(400, "BadRequest");
		}


		});

	CROW_ROUTE(app, "/game")
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
}

