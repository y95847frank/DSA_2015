#include "account.h"

bool string_compare(string a, string b)
{
	if(a.compare(b) < 0)
		return true;
	else
		return false;
}

bool check(std::deque<char> test, std::deque<char> wild)
{
	if(wild.size() == 1 && wild[0] == '*')
		return true;
	else if(wild.size() == 0 && test.size() == 0)
		return true;
	if(wild[0] == '?' || (wild[0] == test[0])) {
		wild.pop_front();
		test.pop_front();
		return check(test, wild);
	}
	else if(wild[0] == '*') {
		if(wild.back() != '*') {
			if(wild.back() == '?' || wild.back() == test.back()){
				wild.pop_back();
				test.pop_back();
				return check(test, wild);
			}
			else
				return false;
		}
		else {
			wild.pop_front();
			int i = 0;
			while(wild[i] != '*')
				i++;
			int success = 0;
			int k;
			int trytime = test.size() - i;
			for(k = 0; k <= trytime; k++) {
				for(int j = 0; j < i; j++) {
					if(wild[j] != test[j] && wild[j] != '?')
						break;
					if(j == i - 1)
						success = 1;
				}
				if(success == 1)
					break;
				else
					test.pop_front();
			}
			if(success == 1) {
				while(i > 0) {
					i--;
					wild.pop_front();
					test.pop_front();
				}
			}
			return check(test, wild);
		}
	}
	else
		return false;
}

void Bank::find(string& now_ID)
{
	//clock_t begin = clock();
	int j;
	std::string wildcard_ID;
	cin >> wildcard_ID;
    /*cout << "\n";
    return ;*/
	int star = 0;
	int qmark = 0;
	char arr[64] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
					'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
					'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '*', '?'};
	for(j = 0; j < 64; j++)
		if(arr[j] == wildcard_ID[0])	break;
	int first = j;
	vector<string> name;
	deque<char> wild;
	deque<char> test;
	int shut = 0;
	for(int i = 0; i < wildcard_ID.size(); i++) {
		if(wildcard_ID[i] == '*')
			star++;
		else if(wildcard_ID[i] == '?')
			qmark++;
	}
	
	
	
	if(star == 0) {
		if(first == 63) {
			for(int i = 0; i < 62; i++) {
				for(itr = data[wildcard_ID.size() - 1][i].begin(); itr != data[wildcard_ID.size() - 1][i].end(); ++itr) {
					int shut = 0;
					for(int j = 0; j < wildcard_ID.size(); j++) {
						if(itr->first[j] == wildcard_ID[j])
							continue;
						else if(itr->first[j] != wildcard_ID[j] && wildcard_ID[j] == '?')
							continue;
						else {
							shut++;
							break;
						}
					}
					if(shut == 0 && itr->first != now_ID)
						name.push_back(itr->first);
				}
			}
		}
		else {
			for(itr = data[wildcard_ID.size() - 1][first].begin(); itr != data[wildcard_ID.size() - 1][first].end(); ++itr) {
				int shut = 0;
				for(int i = 0; i < wildcard_ID.size(); i++) {
					if(itr->first[i] == wildcard_ID[i])
						continue;
					else if(itr->first[i] != wildcard_ID[i] && wildcard_ID[i] == '?')
						continue;
					else {
						shut++;
						break;
					}
				}
				if(shut == 0 && itr->first != now_ID) 
					name.push_back(itr->first);
			}
		}
	}
	else {
		int least = wildcard_ID.length() - star - 1;
        if(wildcard_ID.length() == 1 && wildcard_ID[0] == '*') 
            least = 0;
		for(int i = least; i < 100; i++) {
			for(int j = 0; j < 62; j++) {
				for(itr = data[i][j].begin(); itr != data[i][j].end(); ++itr) {
					deque<char> test, wild;
					for(int i = 0; i < itr->first.length(); i++)
						test.push_back(itr->first[i]);
					for(int i = 0; i < wildcard_ID.length(); i++)
						wild.push_back(wildcard_ID[i]);
					if(check(test, wild)){
						if(now_ID != itr->first)
							name.push_back(itr->first);
					}
				}
			}
		}
	}
	
	sort(name.begin(), name.end(), string_compare);
	for(int m = 0; m < name.size(); m++) {
		cout << name[m];
		if(m != name.size() - 1)
			cout << ",";
	}
	cout << endl;

	//clock_t end = clock();
	//cout << "Find Ex Time = " << ((double)end - begin) / CLOCKS_PER_SEC << endl;	
	return ;
}
