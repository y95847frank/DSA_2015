#include "account.h"

bool compare(string a, string b)
{
	if(a.compare(b) < 0)
		return true;
	else
		return false;
}

void Bank::create(string input,string password)
{
	int count = 0, sum = 0;
	itr = data[input.size()-1][toIndex(input)].find(input);
	char arr[62] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
			'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
			'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
	if(itr == data[input.size()-1][toIndex(input)].end()){
		account a = {input, md5(password), 0};
		data[input.size()-1][toIndex(input)].insert( pair<string,account>(input,a) );
		cout<<"success"<<endl;
		return;
	}
	else{
		cout << "ID " << input << " exists, ";
		vector <string> recom; 
		//score = 1
		if(input.size() > 1) {
			string tmp = input.substr(0, input.size()-1);
			if(data[tmp.length() - 1][toIndex(tmp)].find(tmp) == data[tmp.length()-1][toIndex(tmp)].end()) {
				recom.push_back(tmp);
				count++;
				sum++;
			}
		}
		for(int i = 0; i < 62; i++) {
			string tmp = input + arr[i];
			if(data[tmp.length() - 1][toIndex(tmp)].find(tmp) == data[tmp.length()-1][toIndex(tmp)].end()) {
				recom.push_back(tmp);
				count++;
				sum++;
			}
		}
		for(int i = 0; i < 62; i++) {
			string tmp = input.substr(0, input.size()-1) + arr[i];
			if(data[tmp.length() - 1][toIndex(tmp)].find(tmp) == data[tmp.length()-1][toIndex(tmp)].end() && tmp != input) {
				recom.push_back(tmp);
				count++;
				sum++;
			}
		}
		if(count > 0) {
			sort(recom.begin(), recom.end(), compare);
			for(int a = 0; a < recom.size() && a < 10; a++){
				cout << recom[a];
				if(a != 9)
					cout << ",";
				else 
					cout << endl;
			}
			if(sum > 9)
				return ;
			recom.clear();
			count = 0;
		}
		//score = 2
		
		if(input.size() > 1) {
			for(int i = 0; i < 62; i++) {
				const char* array = arr + i;
				string tmp = input.replace(input.size()-2, input.size()-2, array);
				if(data[tmp.length() - 1][toIndex(tmp)].find(tmp) == data[tmp.length()-1][toIndex(tmp)].end() && tmp != input) {
					recom.push_back(tmp);
					count++;
				}
			}
		}
		if(count > 0) {
			for(int a = 0; a < recom.size() && a < (10 - sum); a++){
				cout << recom[a];
				if(a != (10 - sum)-1)
					cout << ",";
				else 
					cout << endl;
			}
			sum += count;
			if(sum > 9)
				return ;
			recom.clear();
			count = 0;
		}
		//score = 3
		if(input.size() > 2) {
			string tmp = input.substr(0, input.size()-2);
			if(data[tmp.length() - 1][toIndex(tmp)].find(tmp) == data[tmp.length()-1][toIndex(tmp)].end()) {
				recom.push_back(tmp);
				count++;
			}
		}
		if(input.size() > 2) {
			for(int i = 0; i < 62; i++) {
				const char* array = arr + i;
				string tmp = input.replace(input.size()-3, input.size()-3, array);
				if(data[tmp.length() - 1][toIndex(tmp)].find(tmp) == data[tmp.length()-1][toIndex(tmp)].end() && tmp != input) {
					recom.push_back(tmp);
					count++;
				}
			}
		}
		if(input.size() > 1) {
			for(int i = 0; i < 62; i++) {
				const char* array = arr + i;
				string tmp = input.replace(input.size()-2, input.size()-2, array);
				for(int j = 0; j < 62; j++) {
					const char* array = arr + j;
					tmp = tmp.replace(tmp.size()-1, tmp.size()-1, array);
					if(data[tmp.length() - 1][toIndex(tmp)].find(tmp) == data[tmp.length()-1][toIndex(tmp)].end() && tmp != input) {
						recom.push_back(tmp);
						count++;
					}
				}
			}
		}
		for(int i = 0; i < 62; i++)
			for(int j = 0; j < 62; j++) {
				string tmp = input + arr[i] + arr[j];
				if(data[tmp.length() - 1][toIndex(tmp)].find(tmp) == data[tmp.length()-1][toIndex(tmp)].end()) {
					count++;
					recom.push_back(tmp);
				}
			}
		if(count > 0) {
			sort(recom.begin(), recom.end(), compare);
			for(int a = 0; a < recom.size() && a < (10 - sum); a++){
				cout << recom[a];
				if(a != (10 - sum)-1)
					cout << ",";
				else 
					cout << endl;
			}
			sum += count;
			if(sum > 9)
				return ;
			recom.clear();
			count = 0;
		}
		//score = 4
		if(input.size() > 2) {
			for(int i = 0; i < 62; i++) {
				const char* array = arr + i;
				string tmp = input.replace(input.size()-3, input.size()-3, array);
				for(int j = 0; j < 62; j++) {
					tmp = tmp + arr[j];
					if(data[tmp.length() - 1][toIndex(tmp)].find(tmp) == data[tmp.length()-1][toIndex(tmp)].end()) {
						recom.push_back(tmp);
						count++;
					}
				}
			}
		}
		if(input.size() > 1) {
			for(int i = 0; i < 62; i++) {
				const char* array = arr + i;
				string tmp = input.replace(input.size()-2, input.size()-2, array);
				for(int j = 0; j < 62; j++) {
					const char* array = arr + j;
					tmp = tmp.replace(tmp.size()-1, tmp.size()-1, array);
					for(int k = 0; k < 62; k++) {
						tmp = tmp + arr[k];
						if(data[tmp.length() - 1][toIndex(tmp)].find(tmp) == data[tmp.length()-1][toIndex(tmp)].end()) {
							recom.push_back(tmp);
							count++;
						}
					}
				}
			}
		}
		for(int i = 0; i < 62; i++){
			const char* array = arr + i;
			string tmp = tmp.replace(tmp.size()-1, tmp.size()-1, array);
			for(int j = 0; j < 62; j++) {
				tmp = tmp + arr[j];
				for(int k = 0; k < 62; k++) {
					tmp = tmp + arr[k];
					if(data[tmp.length() - 1][toIndex(tmp)].find(tmp) == data[tmp.length()-1][toIndex(tmp)].end()) {
						recom.push_back(tmp);
						count++;
					}
				}
			}
		}
		if(count > 0) {
			sort(recom.begin(), recom.end(), compare);
			for(int a = 0; a < recom.size() && a < (10 - sum); a++) {
				cout << recom[a];
				if(a != (10 - sum)-1)
					cout << ",";
				else 
					cout << endl;
			}
			sum += count;
			if(sum > 9)
				return ;
			recom.clear();
			count = 0;
		}
	}
	return ;
}
