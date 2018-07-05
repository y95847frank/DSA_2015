#include "account.h"

void Bank::deleteAccount()
{
	int i;
	std::string ID, Password;
	cin >> ID >> Password;
	int length = ID.size();
	int first = toIndex(ID);
	itr = data[length - 1][first].find(ID);
	if(itr == data[length - 1][first].end()) {
		cout << "ID " << ID << " not found\n";  //no such account ID
		return;
	}
	else {
		if(itr->second.password != md5(Password)) {
			cout << "wrong password\n";  //wrong password
			return;
		}
		else {

			for(list_itr = itr -> second.history.begin(); list_itr != itr -> second.history.end(); list_itr++)
				(*list_itr) -> counterpart -> deleted = true;

			data[length - 1][first].erase(ID);
			cout << "success\n";  //successful delete operation
		}
	}
	return;
}
