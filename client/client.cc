#include "httplib.h"
#include <iostream>
#include <map>

using namespace std;
int main(void)
{
	httplib::Client cli("52.78.193.49", 3000);
	map<string, string> test;
	test.insert(pair<string, string>("login_id", "test"));
	test.insert(pair<string, string>("password", "1234qwer"));

	auto res = cli.post("/signin", test);
	if(res && res->status == 200)
	{
		cout<<res->body << endl;
	}
	else
	{
		cout<<"Response없음"<<endl;
	}
}
