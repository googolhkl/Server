#ifndef GAME_MANAGER_H_
#define GAME_MANAGER_H_

#include <iostream>
#include "httplib.h"

class GameManager
{
	public:
		GameManager();
		~GameManager();
        char GetUserInput();
		void ShowLoginScreen();
        bool Login(std::string login_id, std::string password);

	private:
        const char* server_address;
        int server_port;
        bool is_logged;
        char user_input;
		void ClearDisplay();
		void DrawHorizontalLine(char decorate_character='=', int width=100);
};

#endif // GAME_MANAGER_H_
