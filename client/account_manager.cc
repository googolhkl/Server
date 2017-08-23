// C, C++, oother.h, my.h
#include <iostream>
#include <map>

#include "account_manager.h"

AccountManager::AccountManager(): server_address("52.78.193.49"), server_port(3000)
{
	this->is_logged = false;
}

AccountManager::AccountManager(const char* address, int port): server_address(address), server_port(port)
{
	this->is_logged = false;
}

AccountManager::~AccountManager() {}

bool AccountManager::Login(std::string login_id, std::string password)
{
	httplib::Client client(this->server_address, server_port);

	std::map<std::string, std::string> data;
	data.insert(std::pair<std::string, std::string>("login_id", "test"));
	data.insert(std::pair<std::string, std::string>("password", "1234qwer"));

	auto response = client.post("/signin", data);
	if(response && (response->status == 200))
	{
		is_logged = true;
	}
	else
	{
		is_logged = false;
	}
	return is_logged;
}

bool AccountManager::IsLogged()
{
	return this->is_logged;
}
