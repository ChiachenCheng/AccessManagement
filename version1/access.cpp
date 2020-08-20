#include<cstdio>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<string>
#include<algorithm>
#include<map>
#define LL long long
using namespace std;
const int MonthDays[13]={0,31,29,31,30,31,30,31,31,30,31,30,31};
const int MAXM=10010,MAXN=110;
int StudentPoint[MAXN],LaboratoryPoint[MAXN],Stack[MAXN];
short Access[MAXN][MAXN];
short Administrator[16];
string Password[MAXN];
map<long long,int>StudentIt;
map<string,int>LaboratoryIt;
int LogInCode;
bool AdminLogIn=false,TXTUse=false;
long long Read(string s,int i){
	long long t=0;
	while(s[i]!=','&&i<s.length())
		t=t*10+s[i++]-48;
	return t;	
}
string ReadString(string s,int i){
	string t;
	t.erase();
	while(s[i]!=','&&i<s.length())
		t+=s[i++];
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
struct Record{
	long long TimeCode,StudentCode;
	string LaboratoryCode;
	bool State,Enter;
	int NextStudent,NextLaboratory;
	void RecordIt(string s){
		TimeCode=Read(s,0);
		StudentCode=Read(s,13);
		Reads(s,&LaboratoryCode,&State,&Enter);
	}
	void Print(){
		cout<<TimeCode<<','<<StudentCode<<',';
		cout<<LaboratoryCode;
		cout<<','<<(State?"Normal":"Fail")<<',';
		cout<<(Enter?"IN":"OUT")<<';'<<endl;
	}
	bool AccessInit(){
		int i=StudentIt[StudentCode],j=LaboratoryIt[LaboratoryCode];
		short x=State?1:0;
		if(Access[i][j]!=-1&&Access[i][j]!=x) return false;
		Access[i][j]=x;
		return true;
	}
}Rec[MAXM];
struct TimeType{
	int t[7];//Digit,Year,Month,Day,Hour,Minute,Second; 
	void Timeit(long long TTemp){
		for(int i=6;i>0;i--){
			t[i]=TTemp%100;
			TTemp/=100;
		}
		t[0]=6;	
	}
	bool Check3(){
		if(t[4]>=24||t[5]>=60||t[6]>=60) return false;
		return true;
	}
	void Print3(){
		printf("%02d:%02d:%02d\n",t[4],t[5],t[6]);
	}
	void DayPlusTemp(){
		for(int j=1;j<t[2];j++)
			t[3]+=MonthDays[j];
		if(t[2]>2&&(t[1]&3)) t[3]--;
	}
};
TimeType TimePlus(TimeType a,TimeType b){
	for(int i=4;i<=6;i++)
		a.t[i]+=b.t[i];
	for(int i=6;i>4;i--){
		a.t[i-1]+=a.t[i]/60;
		a.t[i]%=60;
	}
	a.t[0]=min(a.t[0],3);
	return a; 
}
TimeType TimeMinus(TimeType a,TimeType b){
	if(a.t[1]!=b.t[1]||a.t[2]!=b.t[2]){
		a.DayPlusTemp();
		b.DayPlusTemp();
		a.t[3]+=366*(a.t[1]-b.t[1]);
		for(int j=b.t[1];j<a.t[1];j++)
			if(j&3) a.t[3]--;
	}
	for(int i=3;i<=6;i++)
		a.t[i]-=b.t[i];
	for(int i=6;i>4;i--)
		if(a.t[i]<0){
			a.t[i-1]--;
			a.t[i]+=60;
		}
	a.t[4]+=24*a.t[3];
	a.t[0]=min(a.t[0],3);
	return a; 
}
void PrintFormat(string s){
	if(TXTUse) return;
	printf("Please input your data. Input # to exit.\nFormat:");
	cout<<s<<endl;
}
void PrintNoAcc(){
	printf("You have no access to use this function, please consult Administrator.\n");
} 
long long NumberIt(string s){
	long long sum=0;
	for(int i=0;i<s.length();i++)
		sum=10*sum+s[i]-48;
	return sum;	
}
void FirstInit(){
	Rec[0].TimeCode=0;
	Rec[0].State=true;
	Rec[0].Enter=false;
	StudentPoint[0]=0;
	LaboratoryPoint[0]=0;
	Administrator[0]=0;
	memset(Access,0xff,sizeof(Access));
	freopen("PasswordDatabase.in","r",stdin);
	LL Stu;
	do{
		scanf("%lld",&Stu);
		if(!Stu) break;
		StudentIt[Stu]=++StudentPoint[0];
		cin>>Password[StudentPoint[0]];
	}while(1);
	string s;
	do{
		cin>>s;
		if(s=="#") break;
		Stu=NumberIt(s);
		Administrator[++Administrator[0]]=StudentIt[Stu];
	}while(1); 
	sort(Administrator+1,Administrator+Administrator[0]+1);
	fclose(stdin);
	freopen("CON","r",stdin);
}
void Init(){
	string s;
	int i=Rec[0].TimeCode;
	PrintFormat("Time(YYMMDDHHMMSS 12 digits),StudentID(11 digits),LaboratoryID,(Normal/Fail),(IN/OUT);\n");
	while(1){
		cin>>s;
		if(s=="#") break;
		Rec[++i].RecordIt(s);
		Rec[0].TimeCode++;
		if(StudentIt[Rec[i].StudentCode]==0)
			StudentIt[Rec[i].StudentCode]=++StudentPoint[0];
		int j=StudentIt[Rec[i].StudentCode];
		Rec[i].NextStudent=StudentPoint[j];
		StudentPoint[j]=i;
		if(LaboratoryIt[Rec[i].LaboratoryCode]==0)
			LaboratoryIt[Rec[i].LaboratoryCode]=++LaboratoryPoint[0];
		j=LaboratoryIt[Rec[i].LaboratoryCode];
		Rec[i].NextLaboratory=LaboratoryPoint[j];
		LaboratoryPoint[j]=i;
		if(!Rec[i].AccessInit()){
			printf("Please Check Record:");
			Rec[i].Print();
		}
	}
}
void TestPrintRec(){
	for(int i=1;i<=Rec[0].TimeCode;i++)
		Rec[i].Print();
}
void DFSLaboratory(int i){
	if(i==0) return;
	DFSLaboratory(Rec[i].NextLaboratory);
	Rec[i].Print();
}
void DFSStudent(int i){
	if(i==0) return;
	DFSStudent(Rec[i].NextStudent);
	Rec[i].Print();
}
void DFSStudentCopy(int i,int l,int r){
	if(i==0||i<l) return; 
	DFSStudentCopy(Rec[i].NextStudent,l,r);
	if(i>=l&&i<=r)Stack[++Stack[0]]=i;
}
void QuestionStudent(long long Temp){
	if(!AdminLogIn&&StudentIt[Temp]!=LogInCode){
		PrintNoAcc();
		return;
	}
	if(StudentIt[Temp]==0||StudentPoint[StudentIt[Temp]]==0){
		cout<<"No record!"<<endl;
		return;
	}
	DFSStudent(StudentPoint[StudentIt[Temp]]);
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
bool DateCheck(long long i){
	int y=i/10000,m=(i%10000)/100,d=i%100;
	if(d>MonthDays[m]) return false;
	if(m==2&&(y&3)==1&&d>28) return false;
	return true;
}
bool TimeCheck(long long l,long long r){
	if(l>r) return false;
	if(!DateCheck(l)) return false;
	if(!DateCheck(r)) return false;
	return true;
}
int BinarySearch(long long TTemp){
	int l=1,r=Rec[0].TimeCode;
	while(l<r){
		int mid=(l+r)/2;
		if(TTemp<=Rec[mid].TimeCode)
			r=mid;
		else l=mid+1;	
	}
	return l;
}
void QuestionTime(long long LTemp,long long RTemp){
	int l,r;
	l=BinarySearch(LTemp);
	r=BinarySearch(RTemp);
	bool b=false;
	for(int i=l-1;i<=r+1;i++)
		if(Rec[i].TimeCode>=LTemp&&RTemp>=Rec[i].TimeCode){
			Rec[i].Print();
			b=true;
		}
	if(!b) cout<<"No record!"<<endl;	
}
void TimeSum(string s){
	LL LTemp=Read(s,0),RTemp=Read(s,7),Stu=Read(s,14);
	if(!AdminLogIn&&StudentIt[Stu]!=LogInCode){
		PrintNoAcc();
		return;
	}
	if(!TimeCheck(LTemp,RTemp)){
		cout<<"Wrong Date!\n";
		return;
	}
	int l,r;
	l=BinarySearch(1e6*LTemp)-1;
	r=BinarySearch(1e6*RTemp+235959)+1;
	string Lab=ReadString(s,26);
	bool All=(Lab=="ALL")?true:false;
	memset(Stack,0,sizeof(Stack));
	DFSStudentCopy(StudentPoint[StudentIt[Stu]],l,r);
	bool StuIn=false;
	int iLast=0;
	//Rec[MAXM-2].TimeCode=1e6*LTemp;
	TimeType sum;
	sum.Timeit(0);
	for(int i=1;i<=Stack[0];i++){
		if(!Rec[Stack[i]].State) continue;
		if((!All)&&Rec[Stack[i]].LaboratoryCode!=Lab) continue;
		if(Rec[Stack[i]].TimeCode<1e6*LTemp||Rec[Stack[i]].TimeCode>1e6*RTemp+235959) continue;
		if(Rec[Stack[i]].Enter){
			iLast=i;
			StuIn=true;
		}
		else if(iLast!=0){
			TimeType InTime,OutTime;
			InTime.Timeit(Rec[Stack[iLast]].TimeCode);
			OutTime.Timeit(Rec[Stack[i]].TimeCode);
			OutTime=TimeMinus(OutTime,InTime);
			sum=TimePlus(sum,OutTime);
			StuIn=false;
		}
	}
	/*if(StuIn){
		TimeType InTime,OutTime;
		InTime.Timeit(Rec[iLast].TimeCode);
		OutTime.Timeit(1e6*RTemp+235959);
		OutTime=TimeMinus(OutTime,InTime);
		sum=TimePlus(sum,OutTime);
	}*/
	sum.Print3();
}
void NowCheck(LL TTemp){
	TimeType t,t1;
	t.Timeit(TTemp);
	if(TTemp<Rec[Rec[0].TimeCode].TimeCode||!(DateCheck(TTemp/1000000)&&t.Check3())){
		cout<<"Wrong Date!\n";
		return; 
	}
	int jStart=BinarySearch(TTemp);
	memset(Stack,0,sizeof(Stack));
	while(Rec[jStart].TimeCode<=TTemp&&jStart<=Rec[0].TimeCode) jStart++;
	jStart--;
	for(int i=1;i<=StudentPoint[0];i++){
		int j=StudentPoint[i];
		while(j>jStart||!Rec[j].State)
			j=Rec[j].NextStudent;
		if(Rec[j].Enter) Stack[++Stack[0]]=j;
	}
	sort(Stack+1,Stack+Stack[0]+1);
	for(int i=1;i<=Stack[0];i++){
		cout<<Rec[Stack[i]].StudentCode<<','<<Rec[Stack[i]].LaboratoryCode<<',';
		t1.Timeit(Rec[Stack[i]].TimeCode);
		TimeMinus(t,t1).Print3();
	}
	if(!Stack[0]) cout<<"No record!"<<endl;
}
void AccessCheck(LL StuCd,string LabCd){
	int StuNm=StudentIt[StuCd],LabNm=LaboratoryIt[LabCd];
	switch(Access[StuNm][LabNm]){
		case 0:
			printf("%lld has NO access to the laboratory ",StuCd);
			cout<<LabCd<<endl;
			break;	
		case 1:
			printf("%lld has ACCESS to the laboratory ",StuCd);
			cout<<LabCd<<endl;
			break;
		default:
			printf("Remain Unknown\n");
			break;	
	}
}
void LogIn(){
	int Wrong=0;
	LL Usersname;
	string PWord;
	printf("Please input your USERSNAME\n");
	scanf("%lld",&Usersname);
	printf("Please input your PASSWORD\n");
	cin>>PWord;
	while(StudentIt[Usersname]==0||PWord!=Password[StudentIt[Usersname]]){
		Wrong++;
		if(Wrong>=3){
			printf("Sorry! You have no access to the system!\n");
			cin>>PWord;
			exit(0);
		}
		printf("Wrong password! Please input your PASSWORD again\n");
		cin>>PWord;
	}
	printf("Successfully Login! Welcome %lld\n",Usersname);
	LogInCode=StudentIt[Usersname];
	for(int i=1;Administrator[i]<=LogInCode&&i<=Administrator[0];i++)
		if(LogInCode==Administrator[i]) AdminLogIn=true;
	char c;	
	printf("Do you want to use txt to input and output?(Y/N)\n");
	scanf("%c",&c);
	scanf("%c",&c);
	if(c=='Y'){
		TXTUse=true;
		printf("Please input your filename:\n");
		char TXTName[102];
		scanf("%s",TXTName);
		freopen(TXTName,"r",stdin);
		freopen("USERS.out","w",stdout);
	}		
}
void PassaordChange(){
	printf("Please input OLD password:\n");
	string PWord,PWord0;
	cin>>PWord;
	int Wrong=0;
	while(PWord!=Password[LogInCode]){
		Wrong++;
		if(Wrong>=3){
			printf("Sorry! You have no access to change your password!\n");
			return;
		}
		printf("Wrong password! Please input your OLD password again\n");
		cin>>PWord;
	}
	printf("Please input NEW password:\n");
	cin>>PWord;
	printf("Please input NEW password again:\n");
	cin>>PWord0;
	while(PWord!=PWord0){
		Wrong++;
		if(Wrong>=5){
			printf("Sorry! You have no access to change your password!\n");
			return;
		}
		printf("Wrong password! Please input your NEW password again\n");
		cin>>PWord0;
	}
	Password[LogInCode]=PWord;
	printf("Change password successfully!\n");
} 
void Doit(){
	int T;
	LogIn();
	while(1){
		if(!TXTUse){
			printf("Please input a number to use these functions:\n");
			if(AdminLogIn) printf(" 	1 for input data;\n");
			printf(" 	2 for records of a student;\n");
			if(AdminLogIn) printf(" 	3 for records of a period of time;\n");
			if(AdminLogIn) printf(" 	4 for records of the lab;\n");
			printf(" 	5 for total time in the lab;\n");
			if(AdminLogIn) printf(" 	6 for check labs now;\n");
			printf(" 	7 for accesses;\n");
			printf(" 	8 for change password;\n");
			printf(" 	9 for logout;\n");
			printf(" 	0 for close this system;\n");
		}
		cin>>T;
		switch(T){
			case 0:
				return;
			case 1:
				if(AdminLogIn)
					Init();
				else 
					PrintNoAcc(); 
				break;
			case 2:
				PrintFormat("StudentID(11 digits)");
				while(1){
					string sTemp;
					cin>>sTemp;
					if(sTemp=="#") break;
					QuestionStudent(NumberIt(sTemp));
					sTemp.erase();
				}
				break;
			case 3:
				if(!AdminLogIn){
					PrintNoAcc();
					break;
				}
				PrintFormat("YYMMDD(Start time) YYMMDD(End time)(6 digits)");
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
				if(!AdminLogIn){
					PrintNoAcc();
					break;
				}
				PrintFormat("LaboratoryID");
				QuestionLaboratory();
				break;
			case 5:
				PrintFormat("YYMMDD(Start time),YYMMDD(End time)(6 digits),StudentID(11 digits),(LaboratoryID/ALL)");
				while(1){
					string sTemp;
					cin>>sTemp;
					if(sTemp=="#") break;
					TimeSum(sTemp);
				}
				break;
			case 6:
				PrintFormat("NowTime(YYMMDDHHMMSS 12 digits)");
				if(!AdminLogIn){
					PrintNoAcc();
					break;
				}
				while(1){
					string sTemp;
					cin>>sTemp;
					if(sTemp=="#") break;
					NowCheck(NumberIt(sTemp));
				}
				break;
			case 7:
				PrintFormat("StudentID(11 digits) LaboratoryID");
				while(1){
					string sTemp;
					cin>>sTemp;
					if(sTemp=="#") break;
					LL StuCd=NumberIt(sTemp);
					cin>>sTemp;
					AccessCheck(StuCd,sTemp);
				}
				break;
			case 8:
				PassaordChange(); 
				break;
			case 9:
				LogInCode=0;
				AdminLogIn=false;
				if(TXTUse){
					TXTUse=false; 
					fclose(stdin);
					fclose(stdout);
					freopen("CON","r",stdin);
					freopen("CON","w",stdout);
				} 
				printf("Successfully Logout!\n");
				LogIn();
				break;	
			default:
				break;				
		}
	}
}
int main(){
	FirstInit();
	Doit();
	//fclose(stdin);
	//fclose(stdout);
	return 0;
} 
