#include"numberit.h"
long long NumberIt(string s){
	long long sum=0;
	for(int i=0;i<s.length();i++)
		sum=10*sum+s[i]-48;
	return sum;	
}
