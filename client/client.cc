#include "game_manager.h"

using namespace std;

int main(void)
{
	GameManager* game_manager= new GameManager();
	game_manager->ShowLoginScreen();
    cout<<game_manager->GetUserInput()<<endl;

    /* 로그인 Flow */
    if(game_manager->GetUserInput() == '1')
    {
       string login_id;
       string password;

       cout<<"아이디: ";
       cin>>login_id;

       cout<<"비밀번호: ";
       cin>>password;


       bool is_login =  game_manager->Login(login_id, password);
       cout<<is_login<<endl;
    }
    else
    {
        cout<<"클라이언트를 종료합니다."<<endl;
        return 0;
    }

}
