#include "user.h"

User::User(unsigned int id, const char* nickName)
{
	std::cout<<"생성자!"<<std::endl;
	this->id = id;
	this->nickName = new char[strlen(nickName) + 1];
	strcpy(this->nickName, nickName);
}

User::~User()
{
	std::cout<<"소멸자!"<<std::endl;
	delete []this->nickName;
}


/* Getter */
unsigned int User::GetID()
{
	return this->id;
}

char* User::GetNickName()
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

void User::SetNickName(char* nickName)
{
	delete []this->nickName;
	this->nickName = new char[strlen(nickName) + 1];
	strcpy(this->nickName, nickName);
}

void User::SetSocket(unsigned int socket)
{
	this->socket= socket;
}
