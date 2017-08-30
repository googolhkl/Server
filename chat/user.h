#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 5
#define MAX_CLIENT 256
#define CONNECTION_REQUEST_WAIT_NUMBER 16
#define EPOLL_SIZE 30

class User {
private:
	unsigned int id;
	char* nickName;
	unsigned int socket;

public:
	User(unsigned int id, const char* nickName);
	~User();

	unsigned int GetID();
	char* GetNickName();
	unsigned int GetSocket();

	void SetID(unsigned int id);
	void SetNickName(char* nickName);
	void SetSocket(unsigned int socket);
};

#endif
