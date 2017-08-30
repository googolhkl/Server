#include "user.h"
#include "user_controller.h"

int main()
{
	UserController* userController = new UserController();

	User* user1 = new User(1, "user1!");
	User* user2 = new User(2, "user2!");
	User* user3 = new User(3, "user3!");
	user1->SetSocket(11);
	user2->SetSocket(22);
	user3->SetSocket(33);

	userController->AddUser(user1);
	userController->AddUser(user2);
	userController->AddUser(user3);

	userController->ShowAllUsers();
	std::cout<<std::endl;

	userController->RemoveUser(2);
	userController->ShowAllUsers();
	std::cout<<std::endl;

	User* u = userController->GetUser(1);
	std::cout<<"User: "<<u->GetNickName()<<std::endl;

	std::cout<<"Users number: "<<userController->GetAllUserCount()<<std::endl;
	std::cout<<std::endl;

	std::map<unsigned int, User*> users = userController->GetUsers();
	std::map<unsigned int, User*>::iterator iter;
	for(iter = users.begin(); iter != users.end(); iter++)
	{
		std::cout<< "(" << iter->first << ", " << (iter->second)->GetNickName() << ")" <<std::endl;;
	}
	std::cout<<"User Socket: "<<userController->GetUserSocket(1)<<std::endl;
}
