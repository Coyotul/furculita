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
}

