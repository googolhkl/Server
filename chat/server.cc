#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/epoll.h>

#define BUF_SIZE 1024
#define EPOLL_SIZE 50

#define MAX_CLIENT 255

void error_handling(char *message);

int client_count = 0;
int client_sockets[MAX_CLIENT];

int main(int argc, char* argv[])
{
	int serv_sock, clnt_sock;
	struct sockaddr_in serv_addr, clnt_addr;
	socklen_t adr_sz;
	int str_len, i;

	char buf[BUF_SIZE];

	struct epoll_event *ep_events;
	struct epoll_event event;
	int epfd, event_cnt;

	if(argc != 2)
	{
		printf("사용법: %s <port>\n", argv[0]);
		exit(1);
	}

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	if(serv_sock == -1)
	{
		error_handling("socket() error");
	}
	printf("소켓생성 완료\n");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));

	if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)
	{
		error_handling("bind() error");
	}
	printf("바인딩 완료\n");

	if(listen(serv_sock, 5) == -1)
	{
		error_handling("listen() error");
	}
	printf("리스닝 완료\n");


	epfd = epoll_create(EPOLL_SIZE);
	ep_events = (epoll_event*)malloc(sizeof(struct epoll_event) * EPOLL_SIZE);

	event.events = EPOLLIN;
	event.data.fd = serv_sock;
	epoll_ctl(epfd, EPOLL_CTL_ADD, serv_sock, &event);

	while(1)
	{
		event_cnt = epoll_wait(epfd, ep_events, EPOLL_SIZE, -1);
		if(event_cnt == -1)
		{
			printf("epoll_wait() error!");
			break;
		}

		for(i=0; i<event_cnt; i++)
		{
			if(ep_events[i].data.fd == serv_sock)
			{
				adr_sz = sizeof(clnt_addr);
				clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &adr_sz);
				event.events = EPOLLIN;
				event.data.fd = clnt_sock;
				epoll_ctl(epfd, EPOLL_CTL_ADD, clnt_sock, &event);
				client_sockets[client_count++] = clnt_sock;  // 배열에 클라이언트 정보 삽입
				for(int i=0; i<client_count; i++)
				{
					printf("array[%d]: %d\n", i,client_sockets[i]);
				}
			}
			else
			{
				str_len = read(ep_events[i].data.fd, buf, BUF_SIZE);
				if(str_len == 0) // 종료 요청
				{
					// 배열에 있는 클라이언트 정보 삭제
					for(int j=0; j<client_count; j++)
					{
						if(ep_events[i].data.fd == client_sockets[j])
						{
							while(j++ <= client_count-1)
							{
								client_sockets[j] = client_sockets[j+1];
								client_count--;
							}
							break;
						}
					}

					epoll_ctl(epfd, EPOLL_CTL_DEL, ep_events[i].data.fd, NULL);
					close(ep_events[i].data.fd);
					printf("종료된 클라이언트: %d\n", ep_events[i].data.fd);
				}
				else
				{
					for(int i=0; i<client_count; i++)
					{
						write(client_sockets[i], buf, str_len); // 에코
					}
					//write(ep_events[i].data.fd, buf, str_len); // 에코
				}
			}
		}
	}
	close(serv_sock);
	close(epfd);
	return 0;
}

void error_handling(char * message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
