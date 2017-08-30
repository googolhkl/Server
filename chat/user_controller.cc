#include "user_controller.h"

UserController::UserController()
{
	std::cout<<"생성자!"<<std::endl;
}

UserController::~UserController()
{
	std::cout<<"소멸자!"<<std::endl;
}

void UserController::AddUser(User* user)
{
	this->users.insert(std::pair<unsigned int, User*>(user->GetID(), user));
	this->userSockets.insert(std::pair<unsigned int, unsigned int>(user->GetSocket(), user->GetID()));
}

void UserController::RemoveUser(unsigned int id)
{
	this->userSockets.erase(this->GetUserSocket(id));
	this->users.erase(id);
}

User* UserController::GetUser(unsigned int id)
{
	return this->users.find(id)->second;
}

unsigned int UserController::GetUserIdBySocket(unsigned int socket)
{
	return this->userSockets.find(socket)->second;
}

std::map<unsigned int, User*> UserController::GetUsers()
{
	return this->users;
}

unsigned int UserController::GetAllUserCount()
{
	return this->users.size();
}

unsigned int UserController::GetUserSocket(unsigned int id)
{
	return this->GetUser(id)->GetSocket();
}

void UserController::ShowAllUsers()
{
	std::map<unsigned int, User*>::iterator iter;
	for(iter = this->users.begin(); iter != this->users.end(); iter++)
	{
		std::cout<< "(" << iter->first << ", " << (iter->second)->GetNickName() << ")" <<std::endl;;
	}
}
