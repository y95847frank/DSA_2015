#include "account.h"

void Bank::search(string& now_ID)
{
	string ID; cin >> ID;
	/*if(data[ID.length()-1][toIndex(ID)].find(ID) == data[ID.length()-1][toIndex(ID)].end()){
		cout << "no record\n";
		return ;
	}*/
	int count = 0;
	for(list_itr = data[now_ID.length() - 1][toIndex(now_ID)][now_ID].history.begin(); 
		list_itr != data[now_ID.length() - 1][toIndex(now_ID)][now_ID].history.end(); list_itr++)
	{
		if((*list_itr) -> target == ID)
		{
			if((*list_itr) -> IO == FROM)
				cout << "From ";
			else 
				cout << "To ";

			cout << ID << " " << (*list_itr) -> cash << endl;
			count++;
		}
		else 
			continue;
	}

	if (count == 0)
		cout << "no record\n";  //no record exists
	
	return ;
}
