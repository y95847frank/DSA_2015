#include<iostream>
#include<stdio.h>
#include<fstream>
#include<stack>
#include<sstream>
using namespace std;
using std::stack;
#define left_par 1
#define right_par 2
#define bit_not 3
#define un_plus 4
#define un_minus 5
#define log_not 6
#define mul 7
#define divide 8
#define mod 9
#define plus 10
#define minus 11
#define bit_left 12
#define bit_right 13
#define bit_and 14
#define bit_xor 15
#define bit_or 16
#define log_and 17
#define log_or 18

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

void pull(stack<int> &oper, std::stringstream &newget, stack<int> &numstack)
{
int tmp = 0;
int tmp2 = 0;
switch (oper.top()) {
	case bit_not: 
		newget<< '~'<<' ';
		oper.pop();
		tmp = numstack.top();
		tmp = (~tmp);
		numstack.pop();
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
	case log_not:
		newget << '!'<<' ';
		oper.pop();
		tmp = numstack.top();
		tmp = (!tmp);
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
	case divide:
		newget<< '/' <<' ';
		oper.pop();
		tmp = numstack.top();
		numstack.pop();
		if(numstack.empty())
			cout<<"fuck / no \n";
		tmp2 = numstack.top();
		numstack.pop();
		tmp2 /= tmp;
		numstack.push(tmp2);
		break;
	case mod:
		newget<< '%'<<' ';
		oper.pop();
		tmp = numstack.top();
		numstack.pop();
		if(numstack.empty())
			cout<<"fuck % no \n";
		tmp2 = numstack.top();
		numstack.pop();
		tmp2 %= tmp;
		numstack.push(tmp2);
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
	case bit_left:
		newget<< "<<" <<' ';
		oper.pop();
		tmp = numstack.top();
		numstack.pop();
		if(numstack.empty())
			cout<<"fuck << no \n";
		tmp2 = numstack.top();
		numstack.pop();
		tmp = (tmp2 << tmp);
		numstack.push(tmp);
		break;
	case bit_right:
		newget<< ">>" << ' ';
		oper.pop();
		tmp = numstack.top();
		numstack.pop();
		if(numstack.empty())
			cout<<"fuck >> no \n";
		tmp2 = numstack.top();
		numstack.pop();
		tmp = (tmp2 >> tmp);
		numstack.push(tmp);
		break;
	case bit_and:
		newget<< '&'<< ' ';
		oper.pop();
		tmp = numstack.top();
		numstack.pop();
		if(numstack.empty())
			cout<<"fuck & no \n";
		tmp2 = numstack.top();
		numstack.pop();
		tmp = (tmp2 & tmp);
		numstack.push(tmp);
		break;
	case bit_xor:
		newget<< '^'<<' ';
		oper.pop();
		tmp = numstack.top();
		numstack.pop();
		if(numstack.empty())
			cout<<"fuck ^ no \n";
		tmp2 = numstack.top();
		numstack.pop();
		tmp = (tmp2 ^ tmp);
		numstack.push(tmp);
		break;
	case bit_or:
		newget<< '|'<< ' ';
		oper.pop();
		tmp = numstack.top();
		numstack.pop();
		if(numstack.empty())
			cout<<"fuck | no \n";
		tmp2 = numstack.top();
		numstack.pop();
		tmp = (tmp2 | tmp);
		numstack.push(tmp);
		break;
	case log_and:
		newget<< "&&"<< ' ';
		oper.pop();
		tmp = numstack.top();
		numstack.pop();
		if(numstack.empty())
			cout<<"fuck && no \n";
		tmp2 = numstack.top();
		numstack.pop();
		tmp = (tmp2 && tmp);
		numstack.push(tmp);
		break;
	case log_or:
		newget<< "||"<< ' ';
		oper.pop();
		tmp = numstack.top();
		numstack.pop();
		if(numstack.empty())
			cout<<"fuck || no \n";
		tmp2 = numstack.top();
		numstack.pop();
		tmp = (tmp2 || tmp);
		numstack.push(tmp);
		break;
	}
return ;
}

void process(char clear[], int j, std::stringstream &newget)
{
cout<< "# transform from indix to postfix\n";
stack<int> oper;
stack<int> numstack;
int i = 0;
int consenum = 0;
int tmpnum = 0;
int result = 0;
int boolunary = 1;
while(clear[i] != '\0') {
	if(test(clear[i])) {
		if(test(clear[i+1])) {
			tmpnum *= 10;
			tmpnum += (clear[i] - '0') ;
			}
		else {
			tmpnum *= 10;
			tmpnum += (clear[i] - '0');
			newget<< tmpnum << ' ';
			numstack.push(tmpnum);
			cout<< "get num " << tmpnum <<" :  push to numstack and output"<< endl;
			}
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
				while(oper.top() != left_par) {
					pull(oper, newget, numstack);
					}
				oper.pop();
				boolunary = 0;
				break;
			case '~' :
				cout<<"get oper ~ : push to operstack \n";
				oper.push(bit_not);
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
			case '!':
				cout<<"get oper ! : push to operstack \n";
				oper.push(log_not);
				boolunary = 1;
				break;
			case '*':
				cout<<"get oper * : push to operstack \n";
				while(!oper.empty() && oper.top() <= mod && oper.top() != left_par) {
					cout<< "	*** operstack.top() has greater precedence ***\n";
					pull(oper, newget, numstack);
					}
				oper.push(mul);
				boolunary = 1;
				break;
			case '/':
				cout<<"get oper / : push to operstack \n";
				while(!oper.empty() && oper.top() <= mod && oper.top() != left_par) {
					cout<< "	*** operstack.top() has greater precedence ***\n";
					pull(oper, newget, numstack);
					}
				oper.push(divide);
				boolunary = 1;
				break;
			case '%':
				cout<<"get oper % : push to operstack \n";
				while(!oper.empty() && oper.top() <= mod && oper.top() != left_par) {
					cout<< "	*** operstack.top() has greater precedence ***\n";
					pull(oper, newget, numstack);
					}
				oper.push(mod);
				boolunary = 1;
				break;
			case '<':
				cout<<"get oper << : push to operstack \n";
				while(!oper.empty() && oper.top() <= bit_right && oper.top() != left_par) {
					cout<< "	*** operstack.top() has greater precedence ***\n";
					pull(oper, newget, numstack);
					}
				oper.push(bit_left);
				i++;
				boolunary = 1;
				break;
			case '>':
				cout<<"get oper >> : push to operstack \n";
				while(!oper.empty() && oper.top() <= bit_right && oper.top() != left_par) {
					cout<< "	*** operstack.top() has greater precedence ***\n";
					pull(oper, newget, numstack);
					}
				oper.push(bit_right);
				i++;
				boolunary = 1;
				break;
			case '&' :
				if(clear[i+1] != '&') {
					cout<<"get oper & : push to operstack \n";
					while(!oper.empty() && oper.top() <= bit_and && oper.top() != left_par) {
						cout<< "	*** operstack.top() has greater precedence ***\n";
						pull(oper, newget, numstack);
						}
					oper.push(bit_and);
					}
				else {
					cout<<"get oper && : push to operstack \n";
					while(!oper.empty() && oper.top() <= log_and && oper.top() != left_par) {
						cout<< "	*** operstack.top() has greater precedence ***\n";
						pull(oper, newget, numstack);
						}
					oper.push(log_and);
					i++;
					}
				boolunary = 1;
				break;
			case '^' :
				cout<<"get oper ^ : push to operstack \n";
				while(!oper.empty() && oper.top() <= bit_xor && oper.top() != left_par) {
					cout<< "	*** operstack.top() has greater precedence ***\n";
					pull(oper, newget, numstack);
					}
				oper.push(bit_xor);
				boolunary = 1;
				break;
			case '|':
				if(clear[i+1] != '|') {
					cout<<"get oper | : push to operstack \n";
					while(!oper.empty() && oper.top() <= bit_or && oper.top() != left_par) {
						cout<< "	*** operstack.top() has greater precedence ***\n";
						pull(oper, newget, numstack);
						}
					oper.push(bit_or);
					}
				else {
					cout<<"get oper || : push to operstack \n";
					while(!oper.empty() && oper.top() <= log_or && oper.top() != left_par) {
						cout<< "	*** operstack.top() has greater precedence ***\n";
						pull(oper, newget, numstack);
						}
					oper.push(log_or);
					i++;
					}
				boolunary = 1;
				break;
			}
		
		}
	stack<int> tmpnum2 = numstack;
	stack<int> tmpoper = oper;
	cout<< "	Current numstack : ";
	while(!tmpnum2.empty()){
		cout<< tmpnum2.top() << ", ";
		tmpnum2.pop();
		}
	cout<< "\n" << "	Current operstack : ";
	while(!tmpoper.empty()) {
		switch(tmpoper.top()) {
			case 1:
				cout<< "(, ";
				break;
			case 2:
				cout<< "), ";
				break;
			case 3:
				cout<< "~, ";
				break;
			case 4: case 10:
				cout<< "+, ";
				break;
			case 5: case 11:
				cout<< "-, ";
				break;
			case 6:
				cout<< "!, ";
				break;
			case 7:
				cout<< "*, ";
				break;
			case 8:
				cout<< "/, ";
				break;
			case 9:
				cout<< "%, ";
				break;
			case 12:
				cout<< "<<, ";
				break;
			case 13:
				cout<< ">>, ";
				break;
			case 14:
				cout<< "&, ";
				break;
			case 15:
				cout<< "^, ";
				break;
			case 16:
				cout<< "|, ";
				break;
			case 17:
				cout<< "&&, ";
				break;
			case 18:
				cout<< "||, ";
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
