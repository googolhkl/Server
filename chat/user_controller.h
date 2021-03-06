#ifndef USER_CONTROLLER_HPP
#define USER_CONTROLLER_HPP

#include <iostream>
#include <map>

#include <string.h>

#include "user.h"


class UserController {
private:
	std::map<unsigned int, User*> users;
	std::map<unsigned int, unsigned int> userSockets;

public:
	UserController();
	~UserController();

	void AddUser(User* user);
	void RemoveUser(unsigned int id);

	User* GetUser(unsigned int id);
	unsigned int GetUserIdBySocket(unsigned int socket);
	std::map<unsigned int, User*> GetUsers();
	unsigned int GetAllUserCount();
	unsigned int GetUserSocket(unsigned int id);

	void ShowAllUsers();
};

#endif
