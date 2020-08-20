#include"student.h"
long long Read(string s,int i){
	long long t=0;
	while(s[i]!=',')
		t=t*10+s[i++]-48;
	return t;	
}
void Reads(string s,string *s1,bool *b1,bool *b2){
	int i=25;
	while(s[i]!=',')
		*s1+=s[i++];
	string sTemp="\0";
	i++;
	while(s[i]!=',')
		sTemp+=s[i++];
	if(sTemp=="Normal") *b1=true;
	if(sTemp=="Fail") *b1=false;
	sTemp="\0";
	i++;
	while(s[i]!=';')
		sTemp=sTemp+s[i++];
	if(sTemp=="IN") *b2=true;
	if(sTemp=="OUT") *b2=false;
}
