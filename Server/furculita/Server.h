#include <crow.h>

class Server {
public:
	Server();
	void run();


private:
	crow::SimpleApp app;

	void configureRoutes();
};

