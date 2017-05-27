#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <semaphore.h>

#define BUF_SIZE 100
#define MAX_CLIENT 256

void *handle_client(void *arg);
void send_message(char *message, int length);
void error_handling(char *message);

int client_count = 0;
int client_sockets[MAX_CLIENT];
static sem_t semaphore;

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

	sem_init(&semaphore, 0, 1);
	server_socket = socket(PF_INET,SOCK_STREAM, 0);

	memset(&server_address, 0, sizeof(server_socket));
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(atoi(argv[1]));

	if(bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address)) == -1)
		error_handling((char*)"bind() error");  // you should convert const char* to char *
	
	if(listen(server_socket, 5) == -1)
		error_handling((char*)"listen() error");

	while(1)
	{
		client_address_size = sizeof(client_address);
		client_socket = accept(server_socket, (struct sockaddr*) &client_address, &client_address_size);

		sem_wait(&semaphore);
		client_sockets[client_count++] = client_socket;
		sem_post(&semaphore);

		pthread_create(&thread_id, NULL, handle_client, (void*)&client_socket);
		pthread_detach(thread_id);
		printf("Connected client IP: %s \n", inet_ntoa(client_address.sin_addr));

	}
	sem_destroy(&semaphore);
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

	sem_wait(&semaphore);
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
	sem_post(&semaphore);
	close(client_socket);
	return NULL;
}

void send_message(char *message, int length) // send to all
{
	int i;
	sem_wait(&semaphore);
	for(i = 0; i < client_count; i++)
		send(client_sockets[i], message, length, MSG_DONTWAIT);
	sem_post(&semaphore);
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
