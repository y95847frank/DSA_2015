#include "account.h"

void Bank::merge()
{
	//clock_t begin = clock();
	int correct = 0;
	string ID1, ID2, Password1, Password2;
	cin >> ID1 >> Password1 >> ID2 >> Password2;
	
	int length1 = ID1.size(); int length2 = ID2.size();
	int first1 = toIndex(ID1); int first2 = toIndex(ID2);
	itr = data[length1 - 1][first1].find(ID1);
	map<string, account>::iterator itr2 = data[length2 - 1][first2].find(ID2);

	if(itr == data[length1 - 1][first1].end())
	{
		cout << "ID " << ID1 << " not found\n";
		return;
	}

	if(itr2 == data[length2 - 1][first2].end())
	{
		cout << "ID " << ID2 << " not found\n";
		return;
	}

	if(itr -> second.password != md5(Password1))
	{
		cout << "wrong password1\n";
		return;
	}

	if(itr2 -> second.password != md5(Password2))
	{
		cout << "wrong password2\n";
		return;
	}

	
	// merge money
	data[length1 - 1][first1][ID1].money += data[length2 - 1][first2][ID2].money;
	
	// merge history
	list_itr = itr -> second.history.begin();
	list<record*>::iterator list_itr2 = itr2 -> second.history.begin();
	list<record*> fList;


	
	while(list_itr != itr -> second.history.end() && list_itr2 != itr2 -> second.history.end())
	{
		if((*list_itr) -> timeStamp <= (*list_itr2) -> timeStamp)
		{
			if((*list_itr) -> target == ID2 && (*list_itr) -> deleted == false)	
				(*list_itr) -> target = ID1;

			fList.push_back(*list_itr);
			list_itr++;
		}
		else
		{
			// change related account record from b to a
			(*list_itr2) -> counterpart -> target = ID1;
			
			// In case list 2 has record with itself
			if((*list_itr2) -> target == ID2)	(*list_itr2) -> target = ID1;
			
			fList.push_back(*list_itr2);
			list_itr2++;
		}
	}

	if(list_itr == itr -> second.history.end()) 
	{
		while(list_itr2 != itr2 -> second.history.end())
		{
			(*list_itr2) -> counterpart -> target = ID1;
			
			if((*list_itr2) -> target == ID2)	(*list_itr2) -> target = ID1;
			
			fList.push_back(*list_itr2);
			list_itr2++;
		}
	}
	else
	{
		while(list_itr != itr -> second.history.end())
		{
			if((*list_itr) -> target == ID2 && (*list_itr) -> deleted == false)
				(*list_itr) -> target = ID1;

			
			fList.push_back(*list_itr);
			list_itr++;
		}	
	}

	data[length1 - 1][first1][ID1].history = fList;
	data[length2 - 1][first2].erase(ID2);
	
	cout << "success, " << ID1 << " has " << data[ID1.length()-1][first1][ID1].money << " dollars\n";
	//clock_t end = clock();
	//cout << "Merge Ex Time = " << ((double)end - begin) / CLOCKS_PER_SEC << endl;

	return ;
}
