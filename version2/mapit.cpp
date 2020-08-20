#include"mapit.h"
map<long long,int>StudentIt;
map<string,int>LaboratoryIt;
void Init(){
	string s;
	int i=N;
	while(1){
		cin>>s;
		if(s=="#") break;
		Rec[++i].RecordIt(s);
		Rec[i].StudentLink(i);
		Rec[i].LaboratoryLink(i);
		
		
	}
	N+=i;
}
void DFSLaboratory(int i){
	if(i==0) return;
	DFSLaboratory(Rec[i].NextLaboratory);
	Rec[i].Print();
}
void QuestionLaboratory(){
	string Temp;
	while(1){
		cin>>Temp;
		if(Temp=="#") break;
		if(LaboratoryIt[Temp]==0||LaboratoryPoint[LaboratoryIt[Temp]]==0){
			cout<<"No record!"<<endl;
			continue;
		}
		DFSLaboratory(LaboratoryPoint[LaboratoryIt[Temp]]);
	}
}
void DFSStudent(int i){
	if(i==0) return;
	DFSStudent(Rec[i].NextStudent);
	Rec[i].Print();
}
void QuestionStudent(long long Temp){
	if(StudentIt[Temp]==0||StudentPoint[StudentIt[Temp]]==0){
		cout<<"No record!"<<endl;
		return;
	}
	DFSStudent(StudentPoint[StudentIt[Temp]]);
}
