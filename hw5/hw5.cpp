#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "binomial_heap.h"

using namespace std;

struct infor {
	int priority;
	int ID;
	};

bool operator > (const infor a, const infor b)
{
if(a.priority > b.priority){
	return true;
	}
else if(a.priority == b.priority){
	if(a.ID < b.ID) {
		return true;
		}
	}
return false;
}



int main()
{
int c, w;
scanf("%d %d ", &c, &w);
BinomialHeap <infor> *computer = new BinomialHeap<infor>[c];
char command[100];
while(scanf("%s", command) != EOF) {
	int cm, id, p, cm1, cm2;
	if(strcmp(command , "assign") == 0) {
		scanf("%d %d %d", &cm, &id, &p);
		infor tmp;
		tmp.priority = p;
		tmp.ID = id;
		computer[cm].insert(tmp);
		cout<< "There are " << computer[cm].size << " tasks on computer "<< cm <<"."<< endl;
		}
	else if(strcmp(command , "merge") == 0){
		scanf("%d %d", &cm1, &cm2);
		if(computer[cm2].size < w)
			cout<<"Merging request failed.\n";
		else {
			computer[cm1].merge(computer[cm2]);
			infor tmp = computer[cm1].pop();
			computer[cm1].insert(tmp);
			cout<< "The largest priority number is now " << tmp.priority << " on " << cm1 << ".\n";
			}
		}
	else if(strcmp(command, "execute")== 0) {
		scanf("%d", &cm);
		infor tmp;
		infor another;
		tmp = computer[cm].pop();
		//another = computer[cm].pop();
		cout<< "Computer " << cm << " executed task "<< tmp.ID << ".\n";
		if(computer[cm].size != 0) {
			another = computer[cm].pop();//cout<<"fuck";
			while(another.priority == tmp.priority) {
				cout<< "Computer " << cm << " executed task "<< another.ID << ".\n";
				if(computer[cm].size == 0)
					break;
				another = computer[cm].pop();
				if(another.priority != tmp.priority){
					computer[cm].insert(another);
					
					break;
					}//cout<<"haha";
				}
			}
		}
		//cout<< "11";
	}
delete computer;
return 0;
}

//g++ -std=gnu++0x hw5.cpp



