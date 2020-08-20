#ifndef RECORD_H
#define RECORD_H
#include<iostream>
#include<string>
const int MAXM=10001,MAXN=101;
extern int StudentPoint[MAXN],LaboratoryPoint[MAXN];
extern int N;
long long Read(std::string s,int i);
void Reads(std::string s,std::string *s1,bool *b1,bool *b2);
class Record{
	public:
		Record();
		~Record();
		void RecordIt(std::string s);
		void Print();
		void StudentLink(int i);
		void LaboratoryLink(int i);
		int NextStudent,NextLaboratory;
		long long TimeCode;
	private:
		long long StudentCode;
		std::string LaboratoryCode;
		bool State,Enter;
	protected:
};
extern Record Rec[MAXN];
#endif
