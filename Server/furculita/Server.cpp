#include "Server.h";

Server::Server() {

}

void Server::run() {
	app.port(8080).multithreaded().run();
}