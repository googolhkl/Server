#ifndef SERVER_CHAT_SERVER_HPP
#define SERVER_CHAT_SERVER_HPP

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include <sys/epoll.h>
#include <sys/types.h>
//#include <netinet/in.h>
#include <semaphore.h>

#include <iostream>
#include <thread>

#include "static_semaphore.h"

#define BUF_SIZE 5
#define MAX_CLIENT 256
#define CONNECTION_REQUEST_WAIT_NUMBER 16
#define EPOLL_SIZE 30

using std::cout;
using std::cin;
using std::endl;

class ChatServer {
private:
	static int clientCount;
	static int clientSockets[MAX_CLIENT];
	static scoped_sem_t semaphore;

	int serverSocket;
	int clientSocket;
	sockaddr_in serverAddress;
	sockaddr_in clientAddress;
	socklen_t clientAddressSize;

	struct epoll_event *ep_events;
	struct epoll_event event;
	int epfd, eventCount;
	char buf[BUF_SIZE];

public:
	ChatServer(const char *port);
	~ChatServer();
	void Start();
	static void *ClientHandler(void *clientSocket, void *Count, void *client_sockets, void *ep);
	static void SendMessageToAllClients(char *message, int messageLength);
	void SendException(const char *message);
	void SetNonBlockingMode(int fd);
};

#endif
