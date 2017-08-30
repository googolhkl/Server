#include "server.h"
#include <fcntl.h>
#include <errno.h>

ChatServer::ChatServer(const char* port)
{
	serverSocket = socket(PF_INET, SOCK_STREAM, 0);

	memset(&serverAddress, 0, sizeof(serverSocket));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddress.sin_port = htons(atoi(port));

	if(bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1)
	{
		SendException("bind() 에러 발생");
	}
}

ChatServer::~ChatServer()
{
	close(serverSocket);
}

void ChatServer::Start()
{
	if(listen(serverSocket, CONNECTION_REQUEST_WAIT_NUMBER) == -1)
	{
		SendException("listen() 에러 발생");
	}

	epfd = epoll_create(EPOLL_SIZE);
	ep_events = (epoll_event*)malloc(sizeof(struct epoll_event) * EPOLL_SIZE);

	SetNonBlockingMode(serverSocket);
	event.events = EPOLLIN;
	event.data.fd = serverSocket;
	epoll_ctl(epfd, EPOLL_CTL_ADD, serverSocket, &event);

	while(1)
	{
		eventCount= epoll_wait(epfd, ep_events, EPOLL_SIZE, -1);
		if(eventCount == -1)
		{
			SendException("epoll_wait() 에러");
			break;
		}
		for(int i=0; i < eventCount; i++)
		{
			if(ep_events[i].data.fd == serverSocket)
			{
				clientAddressSize = sizeof(clientAddress);
				clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressSize);
				SetNonBlockingMode(clientSocket);
				event.events = EPOLLIN | EPOLLET;
				event.data.fd = clientSocket;
				epoll_ctl(epfd, EPOLL_CTL_ADD, clientSocket, &event);

				sem_wait(&(semaphore.get()));
				clientSockets[clientCount++] = clientSocket;
				sem_post(&(semaphore.get()));
				cout<<"들어옴: "<<clientSocket<<", 총 인원: "<<clientCount<<endl;
			}
			else
			{
				std::thread serverThread(ClientHandler, (void*)&(ep_events[i].data.fd), (void*)&(clientCount), (void*)clientSockets, (void*)&(epfd));
				serverThread.detach();
			}
		}
	}
	close(serverSocket);
	close(epfd);
}

void* ChatServer::ClientHandler(void *clientSocket, void *Count, void *clientSockets, void *ep)
{
	int socket = *((int*)clientSocket);
	int epf = *((int*)ep);
	char message[BUF_SIZE];

	while(1)
	{
		int str_len = read(socket, message, BUF_SIZE);
		if(str_len < 0)
		{
			if(errno==EAGAIN)
				break;
		}
		else if(str_len == 0)
		{
			sem_wait(&(semaphore.get()));
			for(int j=0; j < *((int*)Count); j++)
			{
				if(socket == ((int*)clientSockets)[j])
				{
					while(j++ < *((int*)Count) -1)
					{
						((int*)clientSockets)[j] = ((int*)clientSockets)[j+1];
						(*((int*)Count))--;

					}
					if(*((int*)Count) == 1)
					{
						((int*)clientSockets)[0] = 0;
						(*((int*)Count)) = 0;
					}
					break;
				}
			}
			sem_post(&(semaphore.get()));
			epoll_ctl(epf, EPOLL_CTL_DEL, socket, NULL);
			close(socket);
			cout<<"이탈함: "<<socket<<", 총 인원: "<<*((int*)Count)<<endl;
			for(int k=0; k<*((int*)Count); k++)
			{
				cout<<((int*)clientSockets)[k]<<", ";
			}
			cout<<endl;
			break;
		}
		else
		{
			sem_wait(&(semaphore.get()));
			for(int i=0; i< *((int *)Count); i++)
			{
				write(((int *)clientSockets)[i], message, str_len);
			}
			sem_post(&(semaphore.get()));
		}
	}
}

void ChatServer::SendException(const char* message)
{
	cout<<message<<endl;
}

void ChatServer::SetNonBlockingMode(int fd)
{
	int flag = fcntl(fd, F_GETFL, 0);
	fcntl(fd, F_SETFL, flag | O_NONBLOCK);
}

int ChatServer::clientCount = 0;
int ChatServer::clientSockets[MAX_CLIENT] = {0,};
scoped_sem_t ChatServer:: semaphore;
