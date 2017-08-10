#include "client.hpp"

#define MAX_ID_SIZE 100

int main(int argc, char *argv[]) {
	char clientID[MAX_ID_SIZE];
	cout<<"클라이언트 접속 시도"<<endl;
	cout<<"채팅에 사용할 아이디를 입력하세요"<<endl;
	cin>> clientID;
	
	ChatClient *client = new ChatClient("52.78.193.49", "9000", clientID);
	client->Start();
	return 0;
}

