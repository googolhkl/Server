#include <iostream>
#include <thread>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024

void error_handling(char *message);
void* SendMessage(void* socket);
void* ReceiveMessage(void* socket);

int main(int argc, char* argv[])
{
	int sock;
	struct sockaddr_in serv_addr;
	char message[BUF_SIZE];
	int str_len, recv_len, recv_cnt;

	if(argc != 3)
	{
		printf("사용법: %s <IP> <port>\n", argv[0]);
		exit(1);
	}

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if(sock == -1)
	{
		error_handling("socket() error");
	}

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));

	if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
	{
		error_handling("connect() error");
	}
	else
	{
		puts("연결됨.............");
		std::thread senderThread(SendMessage, (void*)&(sock));
		std::thread receiverThread(ReceiveMessage, (void*)&(sock));
		senderThread.join();
		receiverThread.join();
	}

	close(sock);
	return 0;

}

void error_handling(char * message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

void* SendMessage(void* socket)
{
	int sock = *((int*)socket);
	char message[BUF_SIZE];

	while(1)
	{
		fgets(message, BUF_SIZE, stdin);
		if(!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
		{
			close(sock);
			return (void*)0;
		}
		send(sock, message, strlen(message) + 1, 0);
	}
	return NULL;
}

void* ReceiveMessage(void *socket)
{
	int sock = *((int*)socket);
	char message[BUF_SIZE];

	while(1)
	{
		int stringLength = recv(sock, message, sizeof(message), 0);
		if(stringLength == -1)
		{
			return (void*)-1;
		}
		message[stringLength] = 0;
		fputs(message, stdout);
	}
	return NULL;
}
