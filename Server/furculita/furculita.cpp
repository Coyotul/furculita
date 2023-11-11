#include <iostream>
#include "Server.h"
import game;

int main()
{
    gartic::Game myGame;
    myGame.startGame();
    
    Server server;
    server.run();

}
