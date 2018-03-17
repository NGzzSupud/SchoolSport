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
//	return *(char *)a - *(char *)b;  //��������
//}
//int str_cmpToSmall(const void *a, const void *b)
//{
//	return *(char *)b - *(char *)a; //��������
//
//}
int compareToBig(const void *a, const void *b)
{
	return *(double*)a>*(double*)b ? 1 : -1; //��������
}

int compareToSmall(const void *a, const void *b)
{
	return *(double*)b>*(double*)a ? 1 : -1; //��������
}

