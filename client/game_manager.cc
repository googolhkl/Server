// C, C++, oother.h, my.h
#include <stdlib.h>
#include <iomanip>
#include "game_manager.h"

// public
GameManager::GameManager(): user_input(0), is_logged(false) 
{
    //this->server_address = "52.78.193.49";
    this->server_address = "127.0.0.1";
    this->server_port = 3000;
}

GameManager::~GameManager() {}

char GameManager::GetUserInput()
{
    return this->user_input;
}

void GameManager::ShowLoginScreen()
{
	ClearDisplay();

	DrawHorizontalLine('=', 100);
	DrawHorizontalLine('=', 100);
	DrawHorizontalLine('=', 100);

	std::cout<<std::setfill('=')<<std::setw(55);
	std::cout<<"  Winners of The Pyramid  ";
	std::cout<<std::setfill('=')<<std::setw(45);
	std::cout<<""<<std::endl;

	DrawHorizontalLine('=', 100);
	DrawHorizontalLine('=', 100);
	DrawHorizontalLine('=', 100);

	std::cout<<"로그인: 1"<<std::endl;
	std::cout<<"클라이언트 종료: 아무키 입력"<<std::endl;
    std::cin>>this->user_input;
}

bool GameManager::Login(std::string login_id, std::string password)
{
    httplib::Client client(this->server_address, server_port);

    std::map<std::string, std::string> data;
    data.insert(std::pair<std::string, std::string>("login_id", login_id));
    data.insert(std::pair<std::string, std::string>("password", password));

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

// private
void GameManager::ClearDisplay()
{
	system("clear");
}

void GameManager::DrawHorizontalLine(char decorate_character, int width)
{
	std::cout<<std::setfill(decorate_character)<<std::setw(width);
	std::cout<<""<<std::endl;
}
