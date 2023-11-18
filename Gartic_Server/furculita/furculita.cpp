#include <iostream>
#include "Server.h"
import game;
#include <sqlite_orm/sqlite_orm.h>
namespace sql = sqlite_orm;

#include "WordsDb.h"
int main()
{
    Storage db = createStorage("words.sqlite");
    db.sync_schema();
    auto initialProductsCount = db.count<WordStruct>();
    if (initialProductsCount == 0)
    {
        populateStorage(db);
    }
    

    gartic::Game myGame;
    myGame.startGame();
    
    Server server;
    server.run();

}
