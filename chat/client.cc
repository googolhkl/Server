#include "client.hpp"

ChatClient::ChatClient(const char *serverIP, const char *serverPort, const char *clientName) {
	sprintf(this->name, "[%s]", clientName);
	this->sock = socket(PF_INET, SOCK_STREAM, 0);

	memset(&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = inet_addr(serverIP); // x.x.x.x(IPv4)로 되어있는 텍스트를 빅엑디언 네트워크 주소로 바꾼다.
	serverAddress.sin_port = htons(atoi(serverPort));
}

ChatClient::~ChatClient() {
	close(sock);
}

void ChatClient::Start() {
	if(connect(sock, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
		SendException("connect() 에러발생");
	}

	std::thread senderThread(SendMessage, (void*)&(this->sock));
	std::thread receiverThread(ReceiveMessage, (void*)&(this->sock));
	senderThread.join();
	receiverThread.join();
}

void* ChatClient::SendMessage(void *socket) {
	int sock = *((int*)socket);
	char nameMessage[NAME_SIZE + BUF_SIZE];

	while(1) {
		fgets(message, BUF_SIZE, stdin);
		if(!strcmp(message, "q\n") || !strcmp(message, "Q\n")) {
			close(sock);
			return (void*)0;
		}
		sprintf(nameMessage, "%s %s", name, message);
		send(sock, nameMessage, strlen(nameMessage) +1, 0);
	}
	return NULL;
}

void* ChatClient::ReceiveMessage(void *socket) {
	int sock = *((int*)socket);
	char nameMessage[NAME_SIZE + BUF_SIZE];

	while(1) {
		int stringLength = recv(sock, nameMessage, sizeof(nameMessage), 0);
		if(stringLength == -1) {
			return (void*)-1;
		}
		nameMessage[stringLength] = 0;
		fputs(nameMessage, stdout);
	}
	return NULL;
}

void ChatClient::SendException(const char *message) {
	cout<<message<<endl;
}

char ChatClient::name[NAME_SIZE] = "[Anonymous]";
char ChatClient::message[BUF_SIZE] = {0,};


int main(int argc, char *argv[]) {
	cout<<"클라이언트 접속 시도"<<endl;
	ChatClient *client = new ChatClient("52.78.193.49", "9000", "Tester");
	client->Start();
	return 0;
}

