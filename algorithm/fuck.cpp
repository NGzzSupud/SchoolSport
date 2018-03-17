#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
#include"想当然排序法.h"


// 地点  1 -- 跑道  2 -- 沙地 3 -- 操场

int sportPlace[20];
int placeAndSport[5][5][160];// placeAndSport[地点][日子][时间] = 运动名称

int xiangmu[20];  //项目人数统计 xiangmu[比赛项目] = 报名人数
int trueXiangmu[20];  //trueXiangmu[顺序] = 比赛项目
int deleteXiangmu[20];
int xiangmuTime[20]; //xiangmu[项目] = 时间
int sportTime[20]; // sportTime[比赛] = 时间

struct PlaygroundControl
{
	int place[4][4]; //place[日期][顺序] = 项目
	int time;  //这些地方能用的时间
};



struct People
{
	int sport[2] = {0}; //参加的比赛[2] = 比赛
	//int place[4] = {0}; //比赛对应的地点
	int sportTime[4] = {0}; //比赛对应的时间
	//int BTime[4] = {0}; // [项目] = 时间
	//int ETime[4] = {0};
};
struct Sport
{
	int sport;
	int sportTime;
	int sportPlace;
}sportThing[20];


//int paodao[4][4];// 跑道[日期][顺序] = 比赛项目
//int caochang[4][4]; //操场[日期][顺序] = 比赛项目
//int shadi[4][4];//沙地[日期][顺序] = 比赛项目

#define peopleNumber 30
const int day = 4;
const int placeNumber = 5;
const int placeTime = 300;
const int placeDay = 4;

//预处理 判断参赛人数够不够
void cel()
{
	
	People people[peopleNumber];
	for(int j = 0;j<peopleNumber;j++)
	for (int i = 0; i < 3; i++)
	{
		if (people[j].sport[i]!=0)
		{
			xiangmu[people[j].sport[i]] ++;
		}
	}
	int trueFlag = 0;
	int deleFlag = 0;
	for (int i = 0; i < 20; i++)  //处理掉不比赛的项目 得到trueXiangmu；
	{
		
		if (xiangmu[i]>=4)
		{
			trueXiangmu[trueFlag] = i;
			trueFlag++;
		}
		else
		{
			deleteXiangmu[deleFlag] = i;
			deleFlag++;
		}
	}
	for (int i = 0; i < peopleNumber; i++)  //将删去的项目从运动员报名的项目中删除
		for (int j = 0; j < 3; j++)
		{
			for (int j1 = 0; j1 < deleFlag; j1++)
			{
				if (people[i].sport[j] == deleteXiangmu[deleFlag])
				{
					people[i].sport[j] = 0;
				}
			}
		}

	//int sportMatrix[placeNumber][placeDay][placeTime];
	//int placeStopTimeFlag[placeNumber];
	//int placeBeginTimeFlag[placeNumber];
	/*for (int i = 0; i < peopleNumber; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			int time = people[j].sportTime[i];
			int sport = people[j].sport[i];
			int place = people[j].place[i];
			
		}
	}*/

}


// 判断 插入 比赛
void celHaveSport(int sM[][placeDay][placeTime], int _sportonetime,int _sporttwotime,int _sportone,int _sporttwo,int sportPlace[])
{
	int oneflag = 0;
	int twoflag = 0;
	int oneSportBegin;
	int oneSportStop;
	int twoSportBegin;
	int twoSportStop;
	// 参加了两个比赛 测试过
	if (_sportone != 0 && _sporttwo != 0)   
	{
		// 1有没在里面   测试过
		if (_sportone != 0) 
			for (int j = 1; j <= day; j++)
				for (int i = 0; i <= placeTime; i++)
				{
					if (_sportone == sM[sportPlace[_sportone]][j][i])
					{
						oneSportBegin = j * 1000 + i;
						oneflag = 1;
						for (int i1 = i; i1 < placeTime; i1++)
						{
							if (_sportone != sM[sportPlace[_sportone]][j][i1])
							{
								oneSportStop = j * 1000 + i1;
								break;
							}
						}
						break;
					}
				}
		// 2有没有在里面   测试过
		if (_sporttwo != 0) 
		{
			for (int j = 1; j <= day; j++)
				for (int i = 0; i < placeTime; i++)
				{
					if (_sporttwo == sM[sportPlace[_sporttwo]][j][i])
					{
						twoSportBegin = j * 1000 + i;
						twoflag = 1;
						for (int i1 = i; i1 < placeTime; i1++)
						{
							if (_sporttwo != sM[sportPlace[_sporttwo]][j][i1])
							{
								twoSportStop = j * 1000 + i1;
								break;
							}
						}
						break;
					}
				}
		}


		//两个运动都已经安排  测试过
		if (oneflag&&twoflag) 
		{
			bool flag = ynComplict(oneSportBegin, oneSportStop, twoSportBegin, twoSportStop); // 是否兼容 测试过

			//不能兼容 ，开始修改时间 测试过
			if (!flag)  
			{
				int findFlag;
				int dayFlag;
				int timeFlag;
				// 一在前改二	
				if (oneSportStop >= twoSportStop)  
				{
					findFlag = oneSportStop;  //从一之后的位置开始找位置
					dayFlag = findFlag / 1000;
					timeFlag = findFlag % 1000;

					int f_begin_day = twoSportBegin / 1000;
					int f_stop_day = twoSportStop / 1000;
					int f_begin_time = twoSportBegin % 1000;
					int f_stop_time = twoSportStop % 1000;
					for (int i = f_begin_day; i <= f_stop_day; i++)  //取消掉运动2在安排表中的位置
						for (int j = f_begin_time; j < f_stop_time; j++)
						{
							sM[sportPlace[_sporttwo]][i][j] = 0;
						}



					for (int f_dayFlag = dayFlag; f_dayFlag <= day; f_dayFlag++) //重新设定运动2 的位置  <=
					{
						int outfor = 0;
						int f_timeFlag;
						if (f_dayFlag == dayFlag)
						{
							f_timeFlag = timeFlag;
						}
						else
						{
							f_timeFlag = 0;
						}
						for (f_timeFlag; f_timeFlag <= placeTime; f_timeFlag++)
						{
							if (sM[sportPlace[_sporttwo]][f_dayFlag][f_timeFlag] == 0 && (f_timeFlag + _sporttwotime) <= 300)//一天只有300分钟的边界判断怎么弄
							{
								//twoSportBegin = f_timeFlag + f_dayFlag * 1000;  
								int _flag = 1;
								for (int newTime = f_timeFlag; newTime < f_timeFlag + _sporttwotime; newTime++)  //判断是不是有空余的位置
								{
									if (sM[sportPlace[_sporttwo]][f_dayFlag][newTime] != 0)
									{
										_flag = 0;
										break;
									}


								}

								if (_flag == 1)
								{
									for (int setTime = f_timeFlag; setTime < f_timeFlag + _sporttwotime; setTime++)  //有空位就设定
									{
										sM[sportPlace[_sporttwo]][f_dayFlag][setTime] = _sporttwo;

									}
									outfor = 1;
									break;

								}
							}

						}

						if (outfor == 1)
						{
							break;

						}
					}
				}
				// 二在前改一
				else 
				{
					findFlag = twoSportStop;  //从二之后的位置开始找位置
					dayFlag = findFlag / 1000;
					timeFlag = findFlag % 1000;

					int f_begin_day = oneSportBegin / 1000;
					int f_stop_day = oneSportStop / 1000;
					int f_begin_time = oneSportBegin % 1000;
					int f_stop_time = oneSportStop % 1000;
					for (int i = f_begin_day; i <= f_stop_day; i++)  //取消掉运动1在安排表中的位置
						for (int j = f_begin_time; j < f_stop_time; j++)
						{
							sM[sportPlace[_sportone]][i][j] = 0;
						}



					for (int f_dayFlag = dayFlag; f_dayFlag <= day; f_dayFlag++) //重新设定运动1 的位置  <=
					{
						int outfor = 0;
						int f_timeFlag;
						if (f_dayFlag == dayFlag)
						{
							f_timeFlag = timeFlag;
						}
						else
						{
							f_timeFlag = 0;
						}
						for (f_timeFlag; f_timeFlag <= placeTime; f_timeFlag++)
						{
							if (sM[sportPlace[_sportone]][f_dayFlag][f_timeFlag] == 0 && (f_timeFlag + _sportonetime) <= 300)//一天只有300分钟的边界判断怎么弄
							{
								//oneSportBegin = f_timeFlag + f_dayFlag * 1000;  
								int _flag = 1;
								for (int newTime = f_timeFlag; newTime < f_timeFlag + _sportonetime; newTime++)  //判断是不是有空余的位置
								{
									if (sM[sportPlace[_sportone]][f_dayFlag][newTime] != 0)
									{
										_flag = 0;
										break;
									}


								}

								if (_flag == 1)
								{
									for (int setTime = f_timeFlag; setTime < f_timeFlag + _sportonetime; setTime++)  //有空位就设定
									{
										sM[sportPlace[_sportone]][f_dayFlag][setTime] = _sportone;

									}
									outfor = 1;
									break;

								}
							}

						}

						if (outfor == 1)
						{
							break;

						}
					}
				}
			}
		} 

		//2 已经安排 1没有 测试过
		if ((oneflag == 0) && (twoflag == 1))  
		{
			//int onedayB = oneSportBegin / 1000;
			//int onedayE = oneSportStop / 1000;
			//int onetimeB = oneSportBegin % 1000;
			//int onetimeE = oneSportStop % 1000;		
			for (int f_day = 1; f_day <= day; f_day++)
			{
				int outfor = 0;
				for (int f_time = 0; f_time <= placeTime ; f_time++)
				{
					int flag = 0;
					if (sM[sportPlace[_sportone]][f_day][f_time] == 0 && ((f_time + _sportonetime)<= placeTime ) && sM[sportPlace[_sporttwo]][f_day][f_time] != _sporttwo)
					{
						flag = 1;
						for (int setTime = f_time; setTime < f_time+_sportonetime; setTime++)
						{
							if (sM[sportPlace[_sportone]][f_day][setTime] != 0 || sM[sportPlace[_sporttwo]][f_day][setTime]== _sporttwo)
							{
								flag = 0;
								break;
							}
						}
					}
					if (flag == 1)
					{
						for (int newtime = f_time; newtime < f_time + _sportonetime; newtime++)
						{
							sM[sportPlace[_sportone]][f_day][newtime] = _sportone;
						}
						outfor = 1;
						break;
					}

				}
				if (outfor == 1)
				{
					break;
				}
			}

		}

		//1已经安排 2没有 测试过
		if ((oneflag == 1) && (twoflag == 0))  
		{
			//int onedayB = oneSportBegin / 1000;
			//int onedayE = oneSportStop / 1000;
			//int onetimeB = oneSportBegin % 1000;
			//int onetimeE = oneSportStop % 1000;		
			for (int f_day = 1; f_day <= day; f_day++)
			{
				int outfor = 0;
				for (int f_time = 0; f_time <= placeTime; f_time++)
				{
					int flag = 0;
					if (sM[sportPlace[_sporttwo]][f_day][f_time] == 0 && ((f_time + _sporttwotime) <= placeTime) && sM[sportPlace[_sportone]][f_day][f_time] != _sportone)
					{
						flag = 1;
						for (int setTime = f_time; setTime < f_time + _sporttwotime; setTime++)
						{
							if ((sM[sportPlace[_sporttwo]][f_day][setTime] != 0) || (sM[sportPlace[_sportone]][f_day][setTime] == _sportone))
							{
								flag = 0;
								break;
							}
						}
					}
					if (flag == 1)
					{
						for (int newtime = f_time; newtime < f_time + _sporttwotime; newtime++)
						{
							sM[sportPlace[_sporttwo]][f_day][newtime] = _sporttwo;
						}
						outfor = 1;
						break;
					}

				}
				if (outfor == 1)
				{
					break;
				}
			}

		}

		//两个都要没有安排 测试过
		if ((oneflag ==0)&&(twoflag==0))
		{
			//先插入比赛1
			for (int f_day = 1; f_day <= day ; f_day++)
			{
				int outfor = 0;
				for (int f_time = 0; f_time < placeTime; f_time++)
				{
					int f_flag = 0;
					if (sM[sportPlace[_sportone]][f_day][f_time] == 0 && (f_time+_sportonetime <= placeTime))
					{
						f_flag = 1;
						for (int setTime = f_time; setTime < f_time + _sportonetime; setTime++)
						{
							if (sM[sportPlace[_sportone]][f_day][setTime] != 0)
							{
								f_flag = 0;
								break;
							}
						}

					}

					if (f_flag == 1)
					{
						for (int newTime = 0; newTime < f_time + _sportonetime; newTime++)
						{
							sM[sportPlace[_sportone]][f_day][newTime] = _sportone;
						}
						outfor = 1;
						break;
					}
				}
				if (outfor == 1)
				{
					break;
				}
			}
		
			//插入比赛2	
			for (int f_day = 1; f_day <= day; f_day++)
				{
					int outfor = 0;
					for (int f_time = 0; f_time <= placeTime; f_time++)
					{
						int flag = 0;
						if (sM[sportPlace[_sporttwo]][f_day][f_time] == 0 && ((f_time + _sporttwotime) <= placeTime) && sM[sportPlace[_sportone]][f_day][f_time] != _sportone)
						{
							flag = 1;
							for (int setTime = f_time; setTime < f_time + _sporttwotime; setTime++)
							{
								if ((sM[sportPlace[_sporttwo]][f_day][setTime] != 0) || (sM[sportPlace[_sportone]][f_day][setTime] == _sportone))
								{
									flag = 0;
									break;
								}
							}
						}
						if (flag == 1)
						{
							for (int newtime = f_time; newtime < f_time + _sporttwotime; newtime++)
							{
								sM[sportPlace[_sporttwo]][f_day][newtime] = _sporttwo;
							}
							outfor = 1;
							break;
						}

					}
					if (outfor == 1)
					{
						break;
					}
				}
			
		}
	}
	

	// 只参加了一个比赛 1  测试过
	if(_sportone!=0 && _sporttwo ==0)
	{
		//查找 1 有没有在里面
		for (int j = 1; j <= day; j++)   
			for (int i = 0; i <= placeTime; i++)
			{
				if (_sportone == sM[sportPlace[_sportone]][j][i])
				{
					oneSportBegin = j * 1000 + i;
					oneflag = 1;
					for (int i1 = i; i1 < placeTime; i1++)
					{
						if (_sportone != sM[sportPlace[_sportone]][j][i1])
						{
							oneSportStop = j * 1000 + i1;
							break;
						}
					}
					break;
				}
			}
		// 没有 插入
		if (oneflag == 0) 
		{
			for (int f_day = 1; f_day <= day; f_day++)
			{
				int outfor = 0;
				for (int f_time = 0; f_time < placeTime; f_time++)
				{
					int f_flag = 0;
					if (sM[sportPlace[_sportone]][f_day][f_time] == 0 && (f_time + _sportonetime <= placeTime))
					{
						f_flag = 1;
						for (int setTime = f_time; setTime < f_time + _sportonetime; setTime++)
						{
							if (sM[sportPlace[_sportone]][f_day][setTime] != 0)
							{
								f_flag = 0;
								break;
							}
						}

					}

					if (f_flag == 1)
					{
						for (int newTime = 0; newTime < f_time + _sportonetime; newTime++)
						{
							sM[sportPlace[_sportone]][f_day][newTime] = _sportone;
						}
						outfor = 1;
						break;
					}
				}
				if (outfor == 1)
				{
					break;
				}
			}
		}

	}

	// 只参加了一个比赛 2
	if (_sportone == 0 && _sporttwo != 0)
	{
		//查找 2 有没有在里面
		for (int j = 1; j <= day; j++)
			for (int i = 0; i <= placeTime; i++)
			{
				if (_sporttwo == sM[sportPlace[_sporttwo]][j][i])
				{
					twoSportBegin = j * 1000 + i;
					twoflag = 1;
					for (int i1 = i; i1 < placeTime; i1++)
					{
						if (_sporttwo != sM[sportPlace[_sporttwo]][j][i1])
						{
							twoSportStop = j * 1000 + i1;
							break;
						}
					}
					break;
				}
			}
		// 没有 插入
		if (twoflag == 0)
		{
			for (int f_day = 1; f_day <= day; f_day++)
			{
				int outfor = 0;
				for (int f_time = 0; f_time < placeTime; f_time++)
				{
					int f_flag = 0;
					if (sM[sportPlace[_sporttwo]][f_day][f_time] == 0 && (f_time + _sporttwotime <= placeTime))
					{
						f_flag = 1;
						for (int setTime = f_time; setTime < f_time + _sporttwotime; setTime++)
						{
							if (sM[sportPlace[_sporttwo]][f_day][setTime] != 0)
							{
								f_flag = 0;
								break;
							}
						}

					}

					if (f_flag == 1)
					{
						for (int newTime = 0; newTime < f_time + _sporttwotime; newTime++)
						{
							sM[sportPlace[_sporttwo]][f_day][newTime] = _sporttwo;
						}
						outfor = 1;
						break;
					}
				}
				if (outfor == 1)
				{
					break;
				}
			}
		}

	}
}


// 判断参加的两个比赛会不会时间冲突 0 冲突 1 不冲突  测试过
bool ynComplict(int oneB, int oneE, int twoB, int twoE)
{
	if (( (oneE>twoB) && (oneB < twoE) )|| ( (twoE>oneB) && (twoB < oneE)) )
	{
		return 0;
	}
	else {
		return 1;
	}
}



