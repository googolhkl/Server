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
				User* user = new User(clientSocket, "tester");  // TODO: 실제 유저 정보로 채워 넣기
				user->SetSocket(clientSocket);
				userController->AddUser(user);
				sem_post(&(semaphore.get()));

				cout<<"들어옴: "<<user->GetNickName()<<", 총 인원: "<<userController->GetAllUserCount()<<endl;
			}
			else
			{
				std::thread serverThread(ClientHandler, (void*)&(ep_events[i].data.fd),(void*)&(epfd));
				serverThread.detach();
			}
		}
	}
	close(serverSocket);
	close(epfd);
}

void* ChatServer::ClientHandler(void *clientSocket, void *ep)
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
			userController->RemoveUser(userController->GetUserIdBySocket(socket));
			sem_post(&(semaphore.get()));
			epoll_ctl(epf, EPOLL_CTL_DEL, socket, NULL);
			close(socket);
			cout<<"이탈함: "<<socket<<", 총 인원: "<<userController->GetAllUserCount()<<endl;
			break;
		}
		else
		{
			// 모든 유저에게 전송
			sem_wait(&(semaphore.get()));
			std::map<unsigned int, User*> users = userController->GetUsers();
			std::map<unsigned int, User*>::iterator iter;
			for(iter = users.begin(); iter != users.end(); iter++)
			{
				write(iter->first, message, str_len);
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

UserController* ChatServer::userController = new UserController();
scoped_sem_t ChatServer:: semaphore;
