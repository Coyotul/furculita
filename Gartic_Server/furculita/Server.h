#include <crow.h>
#include "Logger.h"
import game;

class Server {
public:
    Server();
    void run();

private:
    crow::SimpleApp app;
    gartic::Game myGame;
    Logger logger;

    void configureRoutes();
};

