#include "server.h"

int main(int argc, char *argv[])
{
	ChatServer *server = new ChatServer("9000");
	server->Start();
	return 0;
}
