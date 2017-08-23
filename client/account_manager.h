#ifndef ACCOUNT_MANAGER_H_
#define ACCOUNT_MANAGER_H_

#include <iostream>

#include "httplib.h"

class AccountManager
{
	public:
		AccountManager();
		AccountManager(const char* address, int port);
		~AccountManager();
		bool Login(std::string login_id, std::string password);
		bool IsLogged();

	private:
		const char* server_address;
		int server_port;

		bool is_logged;

};

#endif // ACCOUNT_MANAGER_H_
