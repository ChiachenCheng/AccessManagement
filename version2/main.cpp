#include<cstdio>
#include<cstring>
#include"Record.h"
#include"mapit.h"
#include"numberit.h"
#include"timeit.h"
Record Rec[MAXN];
int N=0;
void FirstInit(){
	StudentPoint[0]=0;
	LaboratoryPoint[0]=0;
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
}
void TestPrintRec(){
	for(int i=1;i<=N;i++)
		Rec[i].Print();
}
void Doit(){
	int t;
	while(cin>>t)
		switch(t){
			case 0:
				return;
			case 1:
				Init();
				break;
			case 2:
				while(1){
					string sTemp;
					cin>>sTemp;
					if(sTemp=="#") break;
					QuestionStudent(NumberIt(sTemp));
					sTemp.erase();
				}
				break;
			case 3:
				while(1){
					string sTemp;
					cin>>sTemp;
					if(sTemp=="#") break;
					long long lTemp=NumberIt(sTemp),rTemp;
					cin>>rTemp;
					if(!TimeCheck(lTemp,rTemp)){
						cout<<"Wrong Date!\n";
						continue;
					}
					QuestionTime(1e6*lTemp,1e6*rTemp+235959);
					sTemp.erase();
				}
				break;
			case 4:
				QuestionLaboratory();
				break;
			case 5:
				break;
			case 6:
				break;
			case 7:
				break;
			default:
				break;				
		}

}
int main(){
	FirstInit();
	Doit();
	//fclose(stdin);
	//fclose(stdout);
	return 0;
} 
