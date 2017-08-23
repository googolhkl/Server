// C, C++, oother.h, my.h
#include <stdlib.h>
#include <iomanip>
#include "game_manager.h"

// public
GameManager::GameManager() {}

GameManager::~GameManager() {}

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
	std::cout<<"클라이언트 종료: Q"<<std::endl;
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
