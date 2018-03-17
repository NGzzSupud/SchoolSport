#include<algorithm>
#include<math.h>
#include"SportArithmetic.h"
#include"calSportThing.h"
#include<vector>  
#include<iostream>
bool comparisionToBig(SortPlace a, SortPlace b);
bool comparisionToSmall(SortPlace a, SortPlace b);
int str_cmpToBig(const void *a, const void *b);
int str_cmpToSmall(const void *a, const void *b);
using namespace std;


 double Calculate::toBig(SortPlace sortplace[], int len)
{
	//qsort(arr, len, sizeof(double), compareToSmall);
	 sort(sortplace, sortplace + len, comparisionToBig);
	 return 0;
}

 double Calculate::toSmall(SortPlace sortplace[], int len)
{
	//qsort(arr, len, sizeof(double), compareToBig);
	 sort(sortplace, sortplace + len, comparisionToSmall);
	return 0;
}

//int str_cmpToBig(const void *a, const void *b)
//{
//	return *(char *)a - *(char *)b;  //…˝–Ú≈≈–Ú
//}
//int str_cmpToSmall(const void *a, const void *b)
//{
//	return *(char *)b - *(char *)a; //Ωµ–Ú≈≈–Ú
//
//}
 bool comparisionToBig(SortPlace a, SortPlace b) {
	 return a.score < b.score;

 }

 bool comparisionToSmall(SortPlace a, SortPlace b) {
	 return a.score > b.score;

 }

