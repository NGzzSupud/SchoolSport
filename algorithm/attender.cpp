#include<iostream>
#include<stdlib.h>
#include<string>
#include"attender.h"
#include<vector>
#include<algorithm>
using namespace std;



struct timeCalculate
{
	double B;
	double E;
};


bool comparison(timeCalculate a, timeCalculate b) {
	return a.B < b.B;
}


int Student:: YN_join() //flag = 0 则不能报名
{
	int flag = 1;

	vector<timeCalculate> timecalculate(3);
	//double beginTime[4];
	//double endTime[4];
	for (int i = 0; i < 3; i++)
	{
		timecalculate[i].B = (sportKind[i].getSportBeginTime());
		timecalculate[i].E= (sportKind[i].getSportEndTime());
	}
	sort(timecalculate.begin(), timecalculate.end(), comparison);
	/*for (int i = 0; i < 3; i++)
	{
		cout << timecalculate[i].B << endl;
	}*/
	for (int i = 1; i < 3; i++)
	{
		if (timecalculate[i].B < timecalculate[i-1].E)
		{
			flag = 0;
			break;
		}
	}
	return flag;
}

