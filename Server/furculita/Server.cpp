#include "Server.h";
import game;


Server::Server() {
	configureRoutes();
}

void Server::run() {
	app.port(8080).multithreaded().run();
}

void Server::configureRoutes() {
    
	CROW_ROUTE(app, "/")([]() {
		
		return "Hello Gartic";
		});
    CROW_ROUTE(app, "/game")
        ([](const crow::request& req) {
        gartic::Game game;
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

        
        if (!game.checkGameState()) {
            
            return "Game over!";
        }

        
        return "Hello Gartic 2";
            });
}

