#include "account.h"

void Bank::login(string& ID, string& password, string& current_ID)
{
	int len = ID.length();
	int index = toIndex(ID);

	itr = data[len - 1][index].find(ID);
	if(itr == data[len - 1][index].end())
		cout << "ID " << ID << " not found" << endl;
	else
	{
		if(md5(password) != itr -> second.password)
			cout << "wrong password" << endl;
		else
		{
			current_ID = ID;		
			cout << "success" << endl;
		}
	}
}