#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>

#define BUF_SIZE 100
#define NAME_SIZE 20

void *send_message(void *arg);
void *receive_message(void *arg);
void error_handling(char *message);

char name[NAME_SIZE] = "[DEFAULT}";
char message[BUF_SIZE];

int main(int argc, char *argv[])
{
	int sock;
	struct sockaddr_in server_address;
	pthread_t sender_thread;
	pthread_t receiver_thread;
	void *thread_return;

	if(argc != 4)
	{
		printf("Usage: %s <Server IP> <Server Port> <name>\n", argv[0]);
		exit(1);
	}

	sprintf(name, "[%s]", argv[3]);
	sock = socket(PF_INET, SOCK_STREAM, 0);

	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = inet_addr(argv[1]); // convert decimal IP address to big endian 32bit address # FIXME: replace inet_addr to 
	server_address.sin_port = htons(atoi(argv[2]));

	if(connect(sock, (struct sockaddr*) &server_address, sizeof(server_address)) == -1)
		error_handling("connect() error");

	pthread_create(&sender_thread, NULL, send_message, (void*)&sock);
	pthread_create(&receiver_thread, NULL, receive_message, (void*)&sock);
	pthread_join(sender_thread,&thread_return);
	pthread_join(receiver_thread,&thread_return);
	close(sock);
	return 0;
}

void *send_message(void *arg) // send thread main
{
	int sock = *((int*)arg);
	char name_message[NAME_SIZE + BUF_SIZE];

	while(1)
	{
		fgets(message, BUF_SIZE, stdin);
		if(!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
		{
			printf("close!\n");
			close(sock);
			exit(0);
		}
		sprintf(name_message, "%s %s", name, message);
		send(sock, name_message, strlen(name_message) + 1, 0);
	}
	return NULL;
}

void *receive_message(void *arg) // read thread main
{
	int sock = *((int*)arg);
	char name_message[NAME_SIZE + BUF_SIZE];
	int string_length;

	while(1)
	{
		string_length = recv(sock, name_message, sizeof(name_message), 0);
		if(string_length == -1)
		{
			printf("return!\n");
			return (void*)-1;
		}
		name_message[string_length] = 0;
		fputs(name_message, stdout);
	}
	return NULL;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
