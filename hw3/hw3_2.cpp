#include<iostream>
#include<stdio.h>
#include<math.h>
#include<fstream>
#include<stack>
#include<sstream>
using namespace std;
using std::stack;
#define left_par 1
#define right_par 2
#define si 3
#define co 4
#define ex 5
#define lo 6
#define po 7
#define sqr 8
#define fa 9
#define un_plus 10
#define un_minus 11
#define mul 12
#define plus 13
#define minus 14

bool test(char num)
{
if(num =='0' )
	return true;
else if( num == '1' ) 
	return true;
else if(num == '2')
	return true;
else if(num == '3' )
	return true;
else if( num == '4' )
	return true;
else if(num == '5' )
	return true;
else if(num == '6' )
	return true;
else if(num == '7')
	return true;
else if (num == '8' )
	return true;
else if(num == '9')
	return true;
else if(num == '.')
	return true;
else 
	return false;
}

void deleteclear(char clear[])
{
int i = 0;
while(clear[i] != '\0') {
	clear[i] = '\0';
	i++;
	}
return ;
}

void pull(stack<int> &oper, std::stringstream &newget, stack<double> &numstack)
{
double tmp = 0;
double tmp2 = 0;
switch (oper.top()) {
	case si:
		newget << "sin ";
		tmp = numstack.top();
		numstack.pop();
		oper.pop();
		tmp = sin(tmp);
		numstack.push(tmp);
		break;
	case co:
		newget<< "cos ";
		tmp = numstack.top();
		numstack.pop();
		oper.pop();
		tmp = cos(tmp);
		numstack.push(tmp);
		break;
	case ex:
		newget<< "exp ";
		tmp = numstack.top();
		numstack.pop();
		oper.pop();
		tmp = exp(tmp);
		numstack.push(tmp);
		break;
	case lo:
		newget<< "log ";
		tmp = numstack.top();
		numstack.pop();
		oper.pop();
		tmp = log(tmp);
		numstack.push(tmp);
		break;
	case po:
		newget<< "pow ";
		tmp = numstack.top();
		numstack.pop();
		tmp2 = numstack.top();
		numstack.pop();
		oper.pop();
		tmp = pow(tmp2, tmp);
		numstack.push(tmp);
		break;
	case sqr:
		newget<< "sqrt ";
		tmp = numstack.top();
		numstack.pop();
		oper.pop();
		tmp = sqrt(tmp);
		numstack.push(tmp);
		break;
	case fa:
		newget<< "fabs ";
		tmp = numstack.top();
		numstack.pop();
		oper.pop();
		tmp = fabs(tmp);
		numstack.push(tmp);
		break;
	case un_plus:
		newget<< '+'<<' ';
		oper.pop();
		break;
	case un_minus:
		newget<< '-'<<' ';
		oper.pop();
		tmp = numstack.top();
		tmp = (-tmp);
		numstack.pop();
		numstack.push(tmp);
		break;
	case mul:
		newget<< '*' <<' ';
		oper.pop();
		tmp = numstack.top();
		numstack.pop();
		if(numstack.empty())
			cout<<"fuck * no \n";
		tmp2 = numstack.top();
		numstack.pop();
		tmp *= tmp2;
		numstack.push(tmp);
		break;
	case plus:
		newget<< '+'<<' ';
		oper.pop();
		tmp = numstack.top();
		numstack.pop();
		if(numstack.empty())
			cout<<"fuck + no \n";
		tmp2 = numstack.top();
		numstack.pop();
		//cout<< "tmp = "<<tmp<<" tmp2 = "<<tmp2<<endl;
		tmp += tmp2;
		numstack.push(tmp);
		break;
	case minus:
		newget<< '-'<<' ';
		oper.pop();
		tmp = numstack.top();
		numstack.pop();
		if(numstack.empty())
			cout<<"fuck - no \n";
		tmp2 = numstack.top();
		numstack.pop();
		tmp2 -= tmp;
		numstack.push(tmp2);
		break;
	}
return ;
}

void process(char clear[], int j, std::stringstream &newget)
{
cout<< "# transform from indix to postfix\n";
stack<int> oper;
stack<double> numstack;
int i = 0;
double temp = 0;
double point = 0;
double tmpnum = 0;
int boolunary = 1;
while(clear[i] != '\0') {
	if(test(clear[i])) {
		if(test(clear[i+1])) {
			if(clear[i] == '.')
				point = 1;
			else if(point > 0) {
				temp = clear[i] - '0';
				for(int i = 0; i < point; i++)
					temp /= 10;
				tmpnum += temp;
				point++;
				}
			else {
				tmpnum *= 10;
				tmpnum += (clear[i] - '0') ;
				}
			}
		else {
			if(point > 0) {
				temp = clear[i] - '0';
				for(int i = 0; i < point; i++)
					temp /=10;
				tmpnum += temp;
				newget << tmpnum << ' ';
				numstack.push(tmpnum);
				cout<< "get num "<< tmpnum << " : push to numstack and output" << endl;
				point = 0;
				}
			else {
				tmpnum *= 10;
				tmpnum += (clear[i] - '0');
				newget<< tmpnum << ' ';
				numstack.push(tmpnum);
				cout<< "get num " ;
				printf("%.6f",  tmpnum );
				cout<<" :  push to numstack & output"<< endl;
				}
			}
		if(clear[i+1] == '.')
			point = 1;
		boolunary = 0;
		}
	else {
		tmpnum = 0;  //process oper-stack
		switch(clear[i]) {
			case '(' :
				cout<<"get oper ( : push to operstack \n";
				oper.push(left_par);
				boolunary = 1;
				break;
			case ')' :
				cout<<"get oper ) : flush the stack to output until meeting '(' \n";
				while(oper.top() != left_par ) {
					pull(oper, newget, numstack);
					}
				oper.pop();
				if(oper.top() < 10 && oper.top() > 2) {
					pull(oper,newget,numstack);
					}
				boolunary = 0;
				break;
			case 's' :
				if(clear[i+1] == 'i') {
					cout<<"get oper sin : push to operstack \n";
					oper.push(si);
					i += 2;
					}
				else {
					cout<<"get oper sqrt : push to operstack \n";
					oper.push(sqr);
					i+= 3;
					}
				boolunary = 1;
				break;
			case 'c':
				cout<<"get oper cos : push to operstack \n";
				oper.push(co);
				i+= 2;
				boolunary = 1;
				break;
			case 'e':
				cout<<"get oper exp : push to operstack \n";
				oper.push(ex);
				i+= 2;
				boolunary = 1;
				break;
			case 'l':
				cout<<"get oper log : push to operstack \n";
				oper.push(lo);
				i+= 2;
				boolunary = 1;
				break;
			case 'p':
				cout<<"get oper pow : push to operstack \n";
				oper.push(po);
				i+= 2;
				boolunary = 1;
				break;
			case 'f' :
				cout<<"get oper fabs : push to operstack \n";
				oper.push(fa);
				i+= 3;
				boolunary = 1;
				break;
			case '+':
				if(boolunary == 1) {
					cout<<"get oper unary+ : push to operstack \n";
					oper.push(un_plus);
					}
				else {
					cout<<"get oper + : push to operstack \n";
					while(!oper.empty() && oper.top() <= minus && oper.top() != left_par) {
						cout<< "	*** operstack.top() has greater precedence ***\n";
						pull(oper, newget, numstack);
						}
					oper.push(plus);
					}
				boolunary = 1;
				break;
			case '-' :
				if(boolunary == 1) {
					cout<<"get oper unary- : push to operstack \n";
					oper.push(un_minus);
					}
				else{
					cout<<"get oper - : push to operstack \n";
					while(!oper.empty() && oper.top() <= minus && oper.top() != left_par) {
						cout<< "	*** operstack.top() has greater precedence ***\n";
						pull(oper, newget, numstack);
						}
					oper.push(minus);
					}
				boolunary = 1;
				break;
			case '*':
				cout<<"get oper * : push to operstack \n";
				while(!oper.empty() && oper.top() <= mul && oper.top() != left_par) {
					cout<< "	*** operstack.top() has greater precedence ***\n";
					pull(oper, newget, numstack);
					}
				oper.push(mul);
				boolunary = 1;
				break;
			case ',':
				while(oper.top() != left_par)
					pull(oper, newget, numstack);
				boolunary = 1;
				break;
			}
		
		}
	stack<double> tmpnum2 = numstack;
	stack<int> tmpoper = oper;
	cout<< "	Current numstack : ";
	while(!tmpnum2.empty()){
		printf("%.6f, ", tmpnum2.top());
		tmpnum2.pop();
		}
	cout<< "\n" << "	Current operstack : ";
	while(!tmpoper.empty()) {
		switch(tmpoper.top()) {
			case 1: case 15:
				cout<< "(, ";
				break;
			case 2: case 16:
				cout<< "), ";
				break;
			case 3:
				cout<< "sin, ";
				break;
			case 4:
				cout<< "cos, ";
				break;
			case 5:
				cout<< "exp, ";
				break;
			case 6:
				cout<<"log, ";
				break;
			case 7:
				cout<< "pow, ";
				break;
			case 8:
				cout<<"sqrt, ";
				break;
			case 9:
				cout<< "fabs, ";
				break;
			case 10: 
				cout<< "+, ";
				break;
			case 11:
				cout<< "-, ";
				break;
			case 12:
				cout<< "*, ";
				break;
			}
		tmpoper.pop();
		}
	cout<< "\n";
	cout<< "	Current output : "<<newget.str()<< endl;
	i++;
	}
int outno = 0;
while(oper.size() != 0) {
	if(outno == 0) {
		cout<< "get NOTHING: flush the stack to output\n";
		outno++;
		}
	pull(oper,newget, numstack);
	}
cout<< "	Current output : "<<newget.str()<< endl;
cout << "# postfix expression transforming complete\n";
cout<< "Postfix Exp: " << newget.str()<< endl;
cout<< "RESULT: "<< numstack.top() << endl;
return ;
}

int main()
{
char line[1000000];
while(cin.getline(line, 1000000)){
	int i = 0;
	int j = 0;
	char clear[1000000];
	std::stringstream newget;
	newget<< fixed;
	newget.precision(6);
	cout<< fixed;
	cout.precision(6);
	while(line[i] != '\0'){
		if(line[i] != ' ') {
			clear[j] = line[i];
			j++;
			}
		i++;
		}
	process(clear, j, newget);
	
	deleteclear(clear);
	}

return 0;
}
