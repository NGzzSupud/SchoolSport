#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
#include"�뵱Ȼ����.h"


// �ص�  1 -- �ܵ�  2 -- ɳ�� 3 -- �ٳ�

int sportPlace[20];
int placeAndSport[5][5][160];// placeAndSport[�ص�][����][ʱ��] = �˶�����

int xiangmu[20];  //��Ŀ����ͳ�� xiangmu[������Ŀ] = ��������
int trueXiangmu[20];  //trueXiangmu[˳��] = ������Ŀ
int deleteXiangmu[20];
int xiangmuTime[20]; //xiangmu[��Ŀ] = ʱ��
int sportTime[20]; // sportTime[����] = ʱ��

struct PlaygroundControl
{
	int place[4][4]; //place[����][˳��] = ��Ŀ
	int time;  //��Щ�ط����õ�ʱ��
};



struct People
{
	int sport[2] = {0}; //�μӵı���[2] = ����
	//int place[4] = {0}; //������Ӧ�ĵص�
	int sportTime[4] = {0}; //������Ӧ��ʱ��
	//int BTime[4] = {0}; // [��Ŀ] = ʱ��
	//int ETime[4] = {0};
};
struct Sport
{
	int sport;
	int sportTime;
	int sportPlace;
}sportThing[20];


//int paodao[4][4];// �ܵ�[����][˳��] = ������Ŀ
//int caochang[4][4]; //�ٳ�[����][˳��] = ������Ŀ
//int shadi[4][4];//ɳ��[����][˳��] = ������Ŀ

#define peopleNumber 30
const int day = 4;
const int placeNumber = 5;
const int placeTime = 300;
const int placeDay = 4;

//Ԥ���� �жϲ�������������
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
	for (int i = 0; i < 20; i++)  //���������������Ŀ �õ�trueXiangmu��
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
	for (int i = 0; i < peopleNumber; i++)  //��ɾȥ����Ŀ���˶�Ա��������Ŀ��ɾ��
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


// �ж� ���� ����
void celHaveSport(int sM[][placeDay][placeTime], int _sportonetime,int _sporttwotime,int _sportone,int _sporttwo,int sportPlace[])
{
	int oneflag = 0;
	int twoflag = 0;
	int oneSportBegin;
	int oneSportStop;
	int twoSportBegin;
	int twoSportStop;
	// �μ����������� ���Թ�
	if (_sportone != 0 && _sporttwo != 0)   
	{
		// 1��û������   ���Թ�
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
		// 2��û��������   ���Թ�
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


		//�����˶����Ѿ�����  ���Թ�
		if (oneflag&&twoflag) 
		{
			bool flag = ynComplict(oneSportBegin, oneSportStop, twoSportBegin, twoSportStop); // �Ƿ���� ���Թ�

			//���ܼ��� ����ʼ�޸�ʱ�� ���Թ�
			if (!flag)  
			{
				int findFlag;
				int dayFlag;
				int timeFlag;
				// һ��ǰ�Ķ�	
				if (oneSportStop >= twoSportStop)  
				{
					findFlag = oneSportStop;  //��һ֮���λ�ÿ�ʼ��λ��
					dayFlag = findFlag / 1000;
					timeFlag = findFlag % 1000;

					int f_begin_day = twoSportBegin / 1000;
					int f_stop_day = twoSportStop / 1000;
					int f_begin_time = twoSportBegin % 1000;
					int f_stop_time = twoSportStop % 1000;
					for (int i = f_begin_day; i <= f_stop_day; i++)  //ȡ�����˶�2�ڰ��ű��е�λ��
						for (int j = f_begin_time; j < f_stop_time; j++)
						{
							sM[sportPlace[_sporttwo]][i][j] = 0;
						}



					for (int f_dayFlag = dayFlag; f_dayFlag <= day; f_dayFlag++) //�����趨�˶�2 ��λ��  <=
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
							if (sM[sportPlace[_sporttwo]][f_dayFlag][f_timeFlag] == 0 && (f_timeFlag + _sporttwotime) <= 300)//һ��ֻ��300���ӵı߽��ж���ôŪ
							{
								//twoSportBegin = f_timeFlag + f_dayFlag * 1000;  
								int _flag = 1;
								for (int newTime = f_timeFlag; newTime < f_timeFlag + _sporttwotime; newTime++)  //�ж��ǲ����п����λ��
								{
									if (sM[sportPlace[_sporttwo]][f_dayFlag][newTime] != 0)
									{
										_flag = 0;
										break;
									}


								}

								if (_flag == 1)
								{
									for (int setTime = f_timeFlag; setTime < f_timeFlag + _sporttwotime; setTime++)  //�п�λ���趨
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
				// ����ǰ��һ
				else 
				{
					findFlag = twoSportStop;  //�Ӷ�֮���λ�ÿ�ʼ��λ��
					dayFlag = findFlag / 1000;
					timeFlag = findFlag % 1000;

					int f_begin_day = oneSportBegin / 1000;
					int f_stop_day = oneSportStop / 1000;
					int f_begin_time = oneSportBegin % 1000;
					int f_stop_time = oneSportStop % 1000;
					for (int i = f_begin_day; i <= f_stop_day; i++)  //ȡ�����˶�1�ڰ��ű��е�λ��
						for (int j = f_begin_time; j < f_stop_time; j++)
						{
							sM[sportPlace[_sportone]][i][j] = 0;
						}



					for (int f_dayFlag = dayFlag; f_dayFlag <= day; f_dayFlag++) //�����趨�˶�1 ��λ��  <=
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
							if (sM[sportPlace[_sportone]][f_dayFlag][f_timeFlag] == 0 && (f_timeFlag + _sportonetime) <= 300)//һ��ֻ��300���ӵı߽��ж���ôŪ
							{
								//oneSportBegin = f_timeFlag + f_dayFlag * 1000;  
								int _flag = 1;
								for (int newTime = f_timeFlag; newTime < f_timeFlag + _sportonetime; newTime++)  //�ж��ǲ����п����λ��
								{
									if (sM[sportPlace[_sportone]][f_dayFlag][newTime] != 0)
									{
										_flag = 0;
										break;
									}


								}

								if (_flag == 1)
								{
									for (int setTime = f_timeFlag; setTime < f_timeFlag + _sportonetime; setTime++)  //�п�λ���趨
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

		//2 �Ѿ����� 1û�� ���Թ�
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

		//1�Ѿ����� 2û�� ���Թ�
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

		//������Ҫû�а��� ���Թ�
		if ((oneflag ==0)&&(twoflag==0))
		{
			//�Ȳ������1
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
		
			//�������2	
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
	

	// ֻ�μ���һ������ 1  ���Թ�
	if(_sportone!=0 && _sporttwo ==0)
	{
		//���� 1 ��û��������
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
		// û�� ����
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

	// ֻ�μ���һ������ 2
	if (_sportone == 0 && _sporttwo != 0)
	{
		//���� 2 ��û��������
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
		// û�� ����
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


// �жϲμӵ����������᲻��ʱ���ͻ 0 ��ͻ 1 ����ͻ  ���Թ�
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



