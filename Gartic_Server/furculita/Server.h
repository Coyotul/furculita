#include <crow.h>
import game;

class Server {
public:
    Server();
    void run();

private:
    crow::SimpleApp app;
    gartic::Game myGame;

    void configureRoutes();
};

