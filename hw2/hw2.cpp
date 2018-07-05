#include<iostream>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<stdio.h>
#include<assert.h>
#include<time.h>

using namespace std;

typedef struct Infor {
	int Click;
	int Impression;
	char DisplayURL[100];
	int AdID;
	int AdvertiserID;
	int Depth;
	int Position;
	int QueryID;
	int KeywordID;
	int TitleID; 
	int Description;
	int UserID;
} infor;

typedef struct storesum {
	int Click;
	int Impression;
	int UserID;
} StoreSum;

int compareProfit(const void *data1, const void *data2)
{
StoreSum *ptr1 = (StoreSum *)data1;
StoreSum *ptr2 = (StoreSum *)data2;
if(ptr1->UserID < ptr2->UserID)
	return -1;
else if (ptr1->UserID > ptr2->UserID)
	return 1;
}

int compareA(const void *data1, const void *data2)
{
infor *ptr1 = (infor *)data1;
infor *ptr2 = (infor *)data2;
if(ptr1->AdID < ptr2->AdID)
	return -1;
else if (ptr1->AdID > ptr2->AdID)
	return 1;
else {
	if(ptr1->KeywordID < ptr2->KeywordID)
		return -1;
	else if (ptr1->KeywordID > ptr2->KeywordID)
		return 1;
	else {
		if(ptr1->Description < ptr2->Description)
			return -1;
		else if(ptr1->Description > ptr2->Description)
			return 1;
		}
	}
}

int compare(const void *data1, const void *data2)
{
infor *ptr1 = (infor *)data1;
infor *ptr2 = (infor *)data2;
if(ptr1->AdID < ptr2->AdID)
	return -1;
else if (ptr1->AdID > ptr2->AdID)
	return 1;
else {
	if(ptr1->QueryID < ptr2->QueryID)
		return -1;
	else if (ptr1->QueryID > ptr2->QueryID)
		return 1;
	else
		return 0;
	}
}

void process(infor *storeInfor, int i)
{
qsort(storeInfor, i, sizeof(infor), compare);
return ;
}

void processA(infor *storeInfor, int i)
{
qsort(storeInfor, i, sizeof(infor), compareA);
return ;
}

void processprofit (StoreSum *data, int count)
{
qsort(data, count, sizeof(StoreSum), compareProfit);
return ;
}

void get(int newUserID, int newAdID, int newQueryID ,int newPosition,int newDepth,infor *storeInfor,int i)
{
int sumClick = 0;
int sumImpression = 0;
int upper = i - 1;
int down = 0;
int j = i / 2;
while(j == j)
	if(storeInfor[j].AdID == newAdID)
		break;
	else if (storeInfor[j].AdID > newAdID){
		upper = j;
		j = (upper + down ) / 2;
		}
	else {
		down = j;
		j = (upper + down) / 2;
		}
int found = j;
while(storeInfor[found].AdID == newAdID){
	if(storeInfor[found].UserID == newUserID && storeInfor[found].QueryID == newQueryID && storeInfor[found].Position == newPosition&& storeInfor[found].Depth == newDepth){
		sumClick += storeInfor[found].Click;
		sumImpression += storeInfor[found].Impression;
		}
	found++;
	}
found = j - 1;
while(storeInfor[found].AdID == newAdID){
	if(storeInfor[found].UserID == newUserID && storeInfor[found].QueryID == newQueryID && storeInfor[found].Position == newPosition&& storeInfor[found].Depth == newDepth){
		sumClick += storeInfor[found].Click;
		sumImpression += storeInfor[found].Impression;
		}
	found--;
	}

cout<< sumClick << "	" << sumImpression << endl;
return ;
}

void Clicked(int newUserID, infor *storeInfor,int i)
{
int title;
int j;
for(j = 0; j < i; j++) {
	if(storeInfor[j].UserID == newUserID && storeInfor[j].Click > 0) {
		cout<< storeInfor[j].AdID << "	" << storeInfor[j].QueryID << endl;
		break;
		}
	else 
		continue;
	}
title = storeInfor[j].AdID;
int title2 = storeInfor[j].QueryID;
for(j = j + 1; j < i; j++) {
	if(storeInfor[j].UserID == newUserID && storeInfor[j].Click > 0 && (storeInfor[j].AdID != title || storeInfor[j].QueryID != title2)) {
			cout<< storeInfor[j].AdID << "	" << storeInfor[j].QueryID << endl;
		title = storeInfor[j].AdID;
		title2 = storeInfor[j].QueryID;
		}
	else 
		continue;
	}
return ;
}

void Impressed(int newUserID1,int newUserID2, infor *storeInfor,int i)
{
std::vector<infor> test1;
std::vector<infor> test2;
int number1 = 0;
int number2 = 0;
int where = 0;
for(int j = 0; j < i; j++) 
	if( storeInfor[j].UserID == newUserID1) {
		test1.push_back(storeInfor[j]);
		number1++;
		}
	else if(storeInfor[j].UserID == newUserID2) {
		test2.push_back(storeInfor[j]);
		number2++;
		}

processA(&test1[0], number1);
processA(&test2[0], number2);
std::vector<infor> tmp;
int counttmp = 0;
if(number1 > number2) { 
	for(int i = 0 ; i < number1 ; i++) {
		for(int j = where ; j < number2 ; j++) {
			if(test1[i].AdID == test2[j].AdID) {
				int temp = test1[i].AdID;
				while(test1[i].AdID == temp) {
					tmp.push_back(test1[i]);
					std::vector<infor> tmp;
					counttmp++;
					i++;
					}
				while(test2[j].AdID == temp) {
					tmp.push_back(test2[j]);
					std::vector<infor> tmp;
					counttmp++;
					j++;
					}
				where = j;
				i--;
				break;
				}
			}
		}
	}
else {
	for(int k = 0; k < number2; k++) {
		for(int j = where ; j < number1 ; j++) {
			if(test2[k].AdID == test1[j].AdID) {
				int temp = test2[k].AdID;
				while(test2[k].AdID == temp) {
					tmp.push_back(test2[k]);
					std::vector<infor> tmp;
					counttmp++;
					k++;
					}
				while(test1[j].AdID == temp) {
					tmp.push_back(test1[j]);
					std::vector<infor> tmp;
					counttmp++;
					j++;
					}
				k--;
				where = j;
				break;
				}
			}
		}
	}
processA(&tmp[0], counttmp);
for(int i = 0; i < counttmp; i++) {
	for(int j = i+1; j < counttmp; j++) {
		if(tmp[i].AdID == tmp[j].AdID && tmp[i].AdvertiserID == tmp[j].AdvertiserID && tmp[i].KeywordID == tmp[j].KeywordID && tmp[i].TitleID == tmp[j].TitleID && tmp[i].Description == tmp[j].Description) {
			tmp.erase(tmp.begin()+j);
			j--;
			counttmp--;
			}
		else if(tmp[j].AdID > tmp[i].AdID)
			break;
		}
	}
int line = 0;
int title = tmp[0].AdID;
cout << tmp[0].AdID << "\n" <<"	" <<tmp[0].DisplayURL <<" "<<tmp[0].AdvertiserID <<" " <<tmp[0].KeywordID <<" " << tmp[0].TitleID <<" " <<tmp[0].Description <<endl;
line = 1;
for(int i = 1; i < counttmp; i++){
	if(line == 0 && tmp[i].AdID == title) {
		cout << tmp[i].AdID << "\n" <<"	" <<tmp[i].DisplayURL <<" "<<tmp[i].AdvertiserID <<" " <<tmp[i].KeywordID <<" " << tmp[i].TitleID <<" " <<tmp[i].Description <<endl;
		line = 1;
		}
	else if(line == 1 && tmp[i].AdID == title) 
		cout <<"	" <<tmp[i].DisplayURL <<" "<<tmp[i].AdvertiserID <<" " <<tmp[i].KeywordID <<" " << tmp[i].TitleID <<" " <<tmp[i].Description <<endl;
	else if (tmp[i].AdID != title) {
		cout << tmp[i].AdID << "\n" <<"	" <<tmp[i].DisplayURL <<" "<<tmp[i].AdvertiserID <<" " <<tmp[i].KeywordID <<" " << tmp[i].TitleID <<" " <<tmp[i].Description <<endl;
		line = 1;
		title = tmp[i].AdID;
		}
	}

return ;
}

void Profit(int newAdID,float theta, infor *storeInfor,int i) 
{
float sumClick = 0;
float sumImpression = 0;
float a = 0;
int j = i / 2;
int upper = i - 1;
int down = 0;
int found;
int count = 0;

while(storeInfor[j].AdID != newAdID) {
	if(storeInfor[j].AdID > newAdID) {
		upper = j;
		j = (upper + down) / 2;
		}
	else if(storeInfor[j].AdID < newAdID) {
		down = j;
		j = (upper + down) / 2;
		}
	}
int title = storeInfor[j].AdID;

found = j;
StoreSum tmp;
std::vector<StoreSum> data;
while(storeInfor[found].AdID == title) {
	tmp.Click = storeInfor[found].Click;
	tmp.Impression = storeInfor[found].Impression;
	tmp.UserID = storeInfor[found].UserID;
	data.push_back(tmp);
	std::vector<StoreSum> data;
	count++;
	found++;
	}
found = j - 1;

while(storeInfor[found].AdID == title) {
	tmp.Click = storeInfor[found].Click;
	tmp.Impression = storeInfor[found].Impression;
	tmp.UserID = storeInfor[found].UserID;
	data.push_back(tmp);
	std::vector<StoreSum> data;
	count++;
	found--;
	}

processprofit(&data[0], count);

title = data[0].UserID;
for(int k = 0; k < count; k++) {
	if(data[k].UserID == title) {
		sumClick += data[k].Click;
		sumImpression += data[k].Impression;
		}
	else {
		a = sumClick / sumImpression;
		if(a >= theta)
			cout << title << endl;
		title = data[k].UserID;
		sumClick = data[k].Click;
		sumImpression = data[k].Impression;
		}
	if(k == count - 1) {
		a = sumClick / sumImpression;
		if(a >= theta)
			cout << title << endl;
		}
	}

return ;
}

int main(int argc, char* argv[])
{
std::vector<infor> storeInfor;
int i = 0;
infor tmp;

FILE *fp;
fp = fopen(argv[1], "r");
assert(fp != NULL);

while(fscanf(fp, "%d	%d	%s	%d	%d	%d	%d	%d	%d	%d	%d	%d", &tmp.Click, &tmp.Impression,
      &tmp.DisplayURL, &tmp.AdID, &tmp.AdvertiserID, &tmp.Depth, &tmp.Position, &tmp.QueryID, 
	  &tmp.KeywordID, &tmp.TitleID, &tmp.Description, &tmp.UserID) != EOF) {
	storeInfor.push_back(tmp);
	i++;
	std::vector<infor> storeInfor;
	}

process(&storeInfor[0], i);

char command[100];
scanf("%s", command);
while( strcmp( command, "quit" ) != 0) {
	cout<< "********************"<< endl;
	if(strcmp(command, "get" ) == 0) {
		int newUserID, newAdID, newQueryID ,newPosition, newDepth;
		cin >> newUserID >> newAdID >> newQueryID >> newPosition >> newDepth; //cin infor
		get(newUserID, newAdID, newQueryID ,newPosition, newDepth, &storeInfor[0], i); //get fuction
		}
	else if(strcmp(command, "clicked" ) == 0) {
		int newUserID;
		cin>> newUserID; // cin infor
		Clicked(newUserID, &storeInfor[0], i); // Clicked function
		}
	else if(strcmp(command, "impressed" ) == 0){
		int newUserID1, newUserID2;
		cin>> newUserID1 >> newUserID2; //cin infor
		//clock_t begin = clock();
		Impressed(newUserID1, newUserID2, &storeInfor[0], i); // Impressed function
		//clock_t end = clock();
		//cout <<"impressed clock = "<<(double)(end - begin) / CLOCKS_PER_SEC << endl;
		}
	else if(strcmp(command, "profit" ) == 0){
		int newAdID;
		float theta;
		cin>> newAdID >> theta; // cin infor
		Profit(newAdID, theta, &storeInfor[0], i) ;// Profit function
		}
	cout<< "********************"<< endl;
	cin>> command;
	}
fclose(fp);

return 0;
}
