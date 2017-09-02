// g++ -std=c++11 -o t test.cc user.cc user_controller.cc -lboost_serialization

#include "user.h"
#include "user_controller.h"

class Header
{
	private:
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive &ar, const unsigned int version)
		{
			ar & number;
		}
	public:
		Header() { this->number=0;}
		int number;
};

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
	//std::cout<<"User Socket: "<<userController->GetUserSocket(1)<<std::endl;

	//std::cout<<"UserID: "<<userController->GetUserIdBySocket(11)<<std::endl;
	delete user1;
	delete user2;
	delete user3;

	std::cout<<std::endl<<std::endl<<"시리얼 라이저 테스트"<<std::endl;
	// 쓰기
	User user_test1 = User(999, "user_test1");
	Header header1;
	header1.number = 12345;
	std::ofstream ofs("hello.txt");
	boost::archive::text_oarchive oa(ofs);
	oa << user_test1 << header1;
	ofs.close();
	std::cout<<"쓸 객체\n"<<"ID: "<<user_test1.GetID()<<std::endl<<"NickName: "<<user_test1.GetNickName()<<std::endl<<"Socket: "<< user_test1.GetSocket()<<std::endl<<std::endl;

	// 읽기
	User user_test2;
	std::ifstream ifs("hello.txt");
	boost::archive::text_iarchive ia(ifs);
	Header header2;
	ia >> user_test2 >> header2;
	ifs.close();

	std::cout<<"가져올 객체1"<<std::endl;
	std::cout<<"ID: "<<user_test2.GetID()<<std::endl;
	std::cout<<"NickName: "<<user_test2.GetNickName()<<std::endl;
	std::cout<<"Socket: "<<user_test2.GetSocket()<<std::endl;

	std::cout<<"header: "<<header2.number<<std::endl;
}
