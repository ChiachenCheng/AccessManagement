#include "Record.h"
#include "mapit.h"
using namespace std;
int StudentPoint[MAXN],LaboratoryPoint[MAXN];
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
Record::Record(){
	TimeCode=0;
	StudentCode=0;
	LaboratoryCode.clear();
	State=false;
	Enter=false;
	NextStudent=0;
	NextLaboratory=0;
}
Record::~Record(){
}
void Record::RecordIt(string s){
	TimeCode=Read(s,0);
	StudentCode=Read(s,13);
	Reads(s,&LaboratoryCode,&State,&Enter);
}
void Record::Print(){
	cout<<TimeCode<<','<<StudentCode<<',';
	cout<<LaboratoryCode;
	cout<<','<<(State?"Normal":"Fail")<<',';
	cout<<(Enter?"IN":"OUT")<<';'<<endl;
}
void Record::StudentLink(int i){
	if(StudentIt[StudentCode]==0)
		StudentIt[StudentCode]=++StudentPoint[0];
	NextStudent=StudentPoint[StudentIt[StudentCode]];
	StudentPoint[StudentIt[StudentCode]]=i;
}
void Record::LaboratoryLink(int i){
	if(LaboratoryIt[LaboratoryCode]==0)
		LaboratoryIt[LaboratoryCode]=++LaboratoryPoint[0];
	NextLaboratory=LaboratoryPoint[LaboratoryIt[LaboratoryCode]];
	LaboratoryPoint[LaboratoryIt[LaboratoryCode]]=i;	
}
