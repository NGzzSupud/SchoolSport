#include<math.h>

#include"sportThing.h"
using namespace std;

int SportThing::getPeopleNumber()
{
	return this->peopleNumber;
}

void SportThing::changePeopleNumber(int peo)
{
	this->peopleNumber = peo;

}

int SportThing::getFlag_place()
{
	return this->flag_place;
}

void SportThing::changeFlag_place(int p)
{
	this->flag_place = p;
}

double SportThing::getSportBeginTime()
{
	return this->begin_time;
}


double SportThing::getSportEndTime()
{
	return this->end_time;
}

void SportThing::changeBTime(double btime)
{
	this->begin_time = btime;
}

void SportThing::changeETime(double etime)
{
	this->end_time = etime;
}

void SportThing::changeSportName(string s)
{
	this->sportName = s;
}
void SportThing::changePlaceName(string p)
{
	this->placeName = p;
}

void SportThing::changeTime_long(double t)
{
	this->time_long = t;
}

double SportThing::getTime_long()
{
	return this->time_long;
}

