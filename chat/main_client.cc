#include "client.hpp"

#define MAX_ID_SIZE 100

int main(int argc, char *argv[]) {
	char clientID[MAX_ID_SIZE];
	cout<<"로그인을 해주세요."<<endl;
	//cout<<"채팅에 사용할 아이디를 입력하세요"<<endl;
	//cin>> clientID;
	
	//ChatClient *client = new ChatClient("52.78.193.49", "9000", clientID);
	ChatClient *client = new ChatClient("52.78.193.49", "9000", "tester");
	client->Start();
	return 0;
}

