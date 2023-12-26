#include <iostream>
#include "Server.h"
import game;
#include <sqlite_orm/sqlite_orm.h>
namespace sql = sqlite_orm;

#include "WordsDb.h"
int main()
{
    Server server;
    server.run();
    

}
