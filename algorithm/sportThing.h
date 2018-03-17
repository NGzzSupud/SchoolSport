#pragma once
#include<string>
using namespace std;

class SportThing
{
private:
	string sportName;
	string placeName;
	int peopleNumber;
	int flag_place;
	double begin_time;
	double end_time;
	double time_long;
public:
	void changePeopleNumber(int peo);
	int getPeopleNumber();
	int getFlag_place();
	void changeFlag_place(int p);
	void changeTime_long(double t);
	double getTime_long();
	void changeSportName(string s);
	void changePlaceName(string p);
	void changeBTime(double b);
	void changeETime(double E);
	double getSportBeginTime();
	double getSportEndTime();


};

