#include <iostream>
#include <string>
#include "account.h"


using namespace std;

int main(void)
{
	string commend;
	string current_loginID = "NONE";
	Bank bank;

	while(cin >> commend)
	{
		if(commend == "login")
		{
			string id; string pass;
			cin >> id >> pass;
			bank.login(id, pass, current_loginID);
		}
		else if(commend == "create")
		{
			string id; string pass;
			cin >> id >> pass;
			bank.create(id, pass);
		}
		else if(commend == "delete")
			bank.deleteAccount();
		else if(commend == "merge")
			bank.merge();
		else if(commend == "deposit")
			bank.deposit(current_loginID);
		else if(commend == "withdraw")
			bank.withdraw(current_loginID);
		else if(commend == "transfer")
		{
			string dest; int cash;
			cin >> dest >> cash;
			bank.transfer(current_loginID, dest, cash);
		}
		else if(commend == "find")
			bank.find(current_loginID);
		else
			bank.search(current_loginID);
	}
}