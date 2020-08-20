#include<map>
#include"Record.h"
using namespace std;
#ifndef __MAPIT_H__
#define __MAPIT_H__
extern map<long long,int>StudentIt;
extern map<string,int>LaboratoryIt;
void Init();
void QuestionLaboratory();
void QuestionStudent(long long Temp);
#endif 
