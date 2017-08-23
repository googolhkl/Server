#ifndef GAME_MANAGER_H_
#define GAME_MANAGER_H_

#include <iostream>

class GameManager
{
	public:
		GameManager();
		~GameManager();
		void ShowLoginScreen();

	private:
		void ClearDisplay();
		void DrawHorizontalLine(char decorate_character='=', int width=100);
};

#endif // GAME_MANAGER_H_
