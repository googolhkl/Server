#include "client.hpp"

int main(int argc, char *argv[]) {
	cout<<"클라이언트 접속 시도"<<endl;
	ChatClient *client = new ChatClient("52.78.193.49", "9000", "Tester");
	client->Start();
	return 0;
}

