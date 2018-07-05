#include "account.h"

using namespace std;

void Bank::deposit(string& now_ID)
{
	int i;
	int num;
	cin >> num;
	int length = now_ID.size();
	int first = toIndex(now_ID);
	data[length - 1][first][now_ID].money += num;
	cout << "success, " << data[length - 1][first][now_ID].money <<" dollars in current account\n";  //money in account after operation
	return ;
}
