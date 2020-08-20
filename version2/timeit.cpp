#include"timeit.h"
bool DateCheck(long long i){
	int y=i/10000,m=(i%10000)/100,d=i%100;
	if(m>12) return false;
	if(d>Month[m]) return false;
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
