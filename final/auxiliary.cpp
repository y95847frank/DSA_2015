#include "account.h"

int score(string& a,string& b){
	if(a.length() < b.length())
	{
		int L=a.length();
		int c=0,d=0;
		for(int i=1;i<=(b.length()-a.length());i++)
			c+=i;
		for(int i=0;i<L;i++)
			if(a[i]!=b[i])	d+=(L-i);
		return c+d;
	}
	else
	{
		int L=b.length();
		int c=0,d=0;
		for(int i=1;i<=(a.length()-b.length());i++)
			c+=i;
		for(int i=0;i<L;i++)
			if(a[i]!=b[i])	d+=(L-i);
		return c+d;
	}
}

int toIndex(string& str)
{
	char arr[62] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
			'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
			'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
	for(int i = 0; i < 62; i++)
		if(arr[i] == str[0])	return i;

	return -1;
}