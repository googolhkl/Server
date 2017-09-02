#include "user.h"

User::User() 
{
	id = 0;
	nickName = "";
	socket = 0;
}
User::User(unsigned int id, std::string nickName)
{
	std::cout<<"생성자: "<<id<<std::endl;
	this->id = id;
	this->nickName = nickName;
	socket = 0;
}

User::~User()
{
	std::cout<<"소멸자: "<<this->id<<std::endl;
}


/* Getter */
unsigned int User::GetID()
{
	return this->id;
}

std::string User::GetNickName()
{
	return this->nickName;
}

unsigned int User::GetSocket()
{
	return this->socket;
}


/* Setter*/
void User::SetID(unsigned int id)
{
	this->id = id;
}

void User::SetNickName(std::string nickName)
{
	this->nickName = nickName;
}

void User::SetSocket(unsigned int socket)
{
	this->socket= socket;
}
