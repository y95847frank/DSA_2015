#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <map>
#include <list>
#include <iostream> 
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include "md5.h"
#include <deque>
#include <time.h>

#define FROM true
#define TO false

using namespace std;

typedef struct record
{
	bool IO;
	string target;
	int cash;
	record *counterpart;
	bool deleted;			/*counterpart deleted*/
	long long int timeStamp;
}record;

typedef struct account
{
	string ID;
	string password;
	int money;
	list<record*> history;
}account;

class Bank
{
public:
	list<record*>::iterator list_itr;
	map<string, account> data[100][62];			/* mapping to an account */
	map<string, account>::iterator itr;			/* iterator of map */

	Bank();
	void create(string input, string password);
	void transfer(string& login, string& dest, int num);
	void deposit(string& now_ID);
	void merge();
	void deleteAccount();
	void find(string& now_ID);
	void withdraw(string& now_ID);
	void search(string& now_ID);
	void login(string& ID, string& password, string& current_ID);

	long long int _time;
};

int score(string& a,string& b);
int toIndex(string& str);

#endif
