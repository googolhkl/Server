#ifndef SERVER_CHAT_CLIENT_HPP
#define SERVER_CHAT_CLIENT_HPP

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include <iostream>
#include <thread>

#define BUF_SIZE 100
#define NAME_SIZE 20

using std::cout;
using std::cin;
using std::endl;

class ChatClient {
private:
	static char name[NAME_SIZE];
	static char message[BUF_SIZE];

	int sock;
	struct sockaddr_in serverAddress;

public:
	ChatClient(const char *serverIP, const char *serverPort, const char *clientName);
	~ChatClient();
	void Start();
	static void *SendMessage(void *socket);
	static void *ReceiveMessage(void *socket);
	void SendException(const char *message);
};

#endif
