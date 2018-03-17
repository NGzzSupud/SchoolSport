#pragma once
//#include<string>
#include"sportThing.h"
using namespace std;
class Student
{
public:
	string name;
	//SportThing * sport_one;
	//SportThing * sport_two;
	//SportThing * sport_three;
	SportThing sportKind[4];

	int YN_join();
};

class Collage
{
public:
	Student students[30];
	int scorePoint;

private:


};
