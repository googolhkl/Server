#include <iostream>
#include <map>

#include "account_manager.h"

using namespace std;

int main(void)
{
	AccountManager* manager = new AccountManager("127.0.0.1", 3000);
	manager->Login("test", "1234qwer");
	cout<<"로그인 여부: "<<manager->IsLogged()<<endl;;
}
