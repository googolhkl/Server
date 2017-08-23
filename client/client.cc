#include "game_manager.h"
#include "account_manager.h"

using namespace std;

int main(void)
{
	GameManager* game_manager= new GameManager();
	game_manager->ShowLoginScreen();
	//AccountManager* account_manager = new AccountManager("127.0.0.1", 3000);
	//account_manager->Login("test", "1234qwer");
	//cout<<"로그인 여부: "<<account_manager->IsLogged()<<endl;;
}
