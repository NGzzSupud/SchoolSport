#include<algorithm>
#include<math.h>
#include"SportArithmetic.h"
#include"calSportThing.h"
int compareToBig(const void *a, const void *b);
int compareToSmall(const void *a, const void *b);
int str_cmpToBig(const void *a, const void *b);
int str_cmpToSmall(const void *a, const void *b);



 double Calculate::bigToSmall(double arr[], int len)
{
	qsort(arr, len, sizeof(double), compareToSmall);
	return 0;
}

 double Calculate::smallToBig(double arr[], int len)
{
	qsort(arr, len, sizeof(double), compareToBig);
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
int compareToBig(const void *a, const void *b)
{
	return *(double*)a>*(double*)b ? 1 : -1; //…˝–Ú≈≈¡–
}

int compareToSmall(const void *a, const void *b)
{
	return *(double*)b>*(double*)a ? 1 : -1; //Ωµ–Ú≈≈–Ú
}

