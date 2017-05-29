#include "server.hpp"

ChatServer::ChatServer(const char *port) {
	cout<<"서버 초기화"<<endl;
	serverSocket = socket(PF_INET, SOCK_STREAM, 0);

	// 주소 할당
	memset(&serverAddress, 0, sizeof(serverSocket));
	serverAddress.sin_family = AF_INET;					// 주소체계를 IPv4로 설정
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);  // 현재 실행한 서버의 주소
	serverAddress.sin_port = htons(atoi(port));			// 포트설정

	// 소켓에 인터넷 주소 할당
	if(bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
		SendException("bind() 에러발생");
	}

}

ChatServer::~ChatServer() {
	cout<<"서버 종료"<<endl;
	close(serverSocket);
}

void ChatServer::Start() {
	cout<<"서버 실행"<<endl;
	if(listen(serverSocket, CONNECTION_REQUEST_WAIT_NUMBER) == -1) {
		SendException("listen() 에러발생");
	}

	while(1) {
		clientAddressSize = sizeof(clientAddress);
		clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressSize);

		// TODO: 벡터로 변경하는걸 고려해보기
		sem_wait(&(semaphore.get()));
		clientSockets[clientCount++] = clientSocket;
		sem_post(&(semaphore.get()));

		std::thread serverThread(ClientHandler, (void*)&clientSocket);
		serverThread.detach();
		cout<<"연결된 클라이언트 IP: "<<inet_ntoa(clientAddress.sin_addr)<<endl;
	}

}

void* ChatServer::ClientHandler(void *clientSocket) {
	int socket = *((int*)clientSocket);
	int stringLength = 0;
	char message[BUF_SIZE];

	while((stringLength = read(socket, message, sizeof(message))) != 0) {
		SendMessageToAllClients(message, stringLength);
	}

	sem_wait(&(semaphore.get()));
	for(int i=0; i<clientCount; i++) {
		if(socket == clientSockets[i]) {
			while(i++ < clientCount-1) {
				clientSockets[i] = clientSockets[i+1];
			}
			break;
		}
	}
	clientCount--;
	sem_post(&(semaphore.get()));
	close(socket);
	return NULL;
}

void ChatServer::SendMessageToAllClients(char *message, int messageLength) {
	sem_wait(&(semaphore.get()));
	for(int i=0; i<clientCount; i++) {
		send(clientSockets[i], message, messageLength, MSG_DONTWAIT);
	}
	sem_post(&(semaphore.get()));
}

void ChatServer::SendException(const char *message) {
	cout<<message<<endl;
}


// 정적 변수 초기화
uint32_t ChatServer::clientCount= 0;
uint32_t ChatServer::clientSockets[MAX_CLIENT] = {0,};
scoped_sem_t ChatServer:: semaphore;

int main(int argc, char *argv[]) {
	ChatServer *server = new ChatServer("9000");
	server->Start();
	return 0;
}
