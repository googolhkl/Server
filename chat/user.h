#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#define BUF_SIZE 5
#define MAX_CLIENT 256
#define CONNECTION_REQUEST_WAIT_NUMBER 16
#define EPOLL_SIZE 30

class User {
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar &id;
		ar &nickName;
		ar &socket;
	}

	unsigned int id;
	std::string nickName;
	unsigned int socket;


public:
	User();
	User(unsigned int id, std::string nickName);
	~User();

	unsigned int GetID();
	std::string GetNickName();
	unsigned int GetSocket();

	void SetID(unsigned int id);
	void SetNickName(std::string nickName);
	void SetSocket(unsigned int socket);
};

#endif
