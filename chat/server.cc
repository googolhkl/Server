#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define BUF_SIZE 100
#define MAX_CLIENT 256

void *handle_client(void *arg);
void send_message(char *message, int length);
void error_handling(char *message);

int client_count = 0;
int client_sockets[MAX_CLIENT];
pthread_mutex_t mutex;

int main(int argc, char *argv[])
{
	int server_socket;
	int client_socket;
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;
	socklen_t client_address_size;
	pthread_t thread_id;

	if(argc != 2)
	{
		printf("Usage: %s <port>\n", argv[0]);
		exit(1);
	}

	pthread_mutex_init(&mutex, NULL);
	server_socket = socket(PF_INET,SOCK_STREAM, 0);

	memset(&server_address, 0, sizeof(server_socket));
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(atoi(argv[1]));

	if(bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address)) == -1)
		error_handling("bind() error");
	
	if(listen(server_socket, 5) == -1)
		error_handling("listen() error");

	while(1)
	{
		client_address_size = sizeof(client_address);
		client_socket = accept(server_socket, (struct sockaddr*) &client_address, &client_address_size);

		pthread_mutex_lock(&mutex);
		client_sockets[client_count++] = client_socket;
		pthread_mutex_unlock(&mutex);

		pthread_create(&thread_id, NULL, handle_client, (void*)&client_socket);
		pthread_detach(thread_id);
		printf("Connected client IP: %s \n", inet_ntoa(client_address.sin_addr));

	}
	close(server_socket);
	return 0;
}

void *handle_client(void *arg)
{
	int client_socket = *((int*)arg);
	int string_length = 0;
	int i;
	char message[BUF_SIZE];

	while((string_length = read(client_socket, message, sizeof(message))) != 0)
		send_message(message, string_length);

	pthread_mutex_lock(&mutex);
	for(i = 0; i < client_count; i++) // remove disconnected client  TODO: replace with vector
	{
		if(client_socket == client_sockets[i])
		{
			while(i++ < client_count-1)
				client_sockets[i] = client_sockets[i+1];
			break;
		}
	}
	client_count--;
	pthread_mutex_unlock(&mutex);
	close(client_socket);
	return NULL;
}

void send_message(char *message, int length) // send to all
{
	int i;
	pthread_mutex_lock(&mutex);
	for(i = 0; i < client_count; i++)
		send(client_sockets[i], message, length, MSG_DONTWAIT);
	pthread_mutex_unlock(&mutex);
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
