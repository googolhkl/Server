#include "server.h"

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
				event.events = EPOLLIN;
				event.data.fd = clientSocket;
				epoll_ctl(epfd, EPOLL_CTL_ADD, clientSocket, &event);
				clientSockets[clientCount++] = clientSocket;
			}
			else
			{
				int str_len = read(ep_events[i].data.fd, buf, BUF_SIZE);
				if(str_len == 0)
				{
					for(int j=0; j < clientCount; j++)
					{
						if(ep_events[i].data.fd == clientSockets[j])
						{
							while(j++ < clientCount -1)
							{
								clientSockets[j] = clientSockets[j+1];
								clientCount--;
							}
							break;
						}
					}
					epoll_ctl(epfd, EPOLL_CTL_DEL, ep_events[i].data.fd, NULL);
					close(ep_events[i].data.fd);
				}
				else
				{
					for(int i=0; i<clientCount; i++)
					{
						write(clientSockets[i], buf, str_len);
					}
				}
			}
		}
	}
	close(serverSocket);
	close(epfd);
}


void ChatServer::SendException(const char* message)
{
	cout<<message<<endl;
}

uint32_t ChatServer::clientCount = 0;
uint32_t ChatServer::clientSockets[MAX_CLIENT] = {0,};
scoped_sem_t ChatServer:: semaphore;
