#pragma once
//#include"sport.h"

struct SortPlace
{
	int studentID;
	double score;
	
};


 class Calculate
{
public:
	double toBig(SortPlace sortplace[], int len); //����
	double toSmall(SortPlace sortplace[], int len); //����

	//char smallToBig(char str[]);
	//char bigToSmall(char str[]);
	
};


