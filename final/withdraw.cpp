#include "account.h"

void Bank::withdraw(string& now_ID)
{
	int num;
	cin >> num;
	int length = now_ID.length();
	int first = toIndex(now_ID);
	if(num > data[length - 1][first][now_ID].money)  //not enough money
		cout << "fail, " << data[length - 1][first][now_ID].money << " dollars only in current account\n";
	else {  //money left in account
		data[length - 1][first][now_ID].money -= num;
		cout << "success, " << data[length - 1][first][now_ID].money << " dollars left in current account\n";
	}
	return ;
}
