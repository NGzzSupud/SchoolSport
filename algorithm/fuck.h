#pragma once
bool ynComplict(int oneB, int oneE, int twoB, int twoE);



/*
struct PlaygroundControl
{
    int place[4][4]; //place[日期][顺序] = 项目
    int time;  //这些地方能用的时间
};
*/


struct People
{
    int sport_one = 0; //田赛
    int sport_two = 0; //径赛
    //int sport[2] = {0}; //参加的比赛[2] = 比赛
    //int place[4] = {0}; //比赛对应的地点
    //int sportTime[4] = {0}; //比赛对应的时间
    //int BTime[4] = {0}; // [项目] = 时间
    //int ETime[4] = {0};
};


/*
struct Sport
{
    int sport;
    int sportTime;
    int sportPlace;
}sportThing[20];
*/

//int paodao[4][4];// 跑道[日期][顺序] = 比赛项目
//int caochang[4][4]; //操场[日期][顺序] = 比赛项目
//int shadi[4][4];//沙地[日期][顺序] = 比赛项目

#define peopleNumber 30
const int day = 4;
const int placeNumber = 5;
const int placeTime = 300;
const int placeDay = 4;

void cel();
bool ynComplict(int oneB, int oneE, int twoB, int twoE);
void celHaveSport(int _sportonetime,int _sporttwotime,int _sportone,int _sporttwo);
//void celHaveSport(int sM[][placeDay][placeTime], int _sportonetime,int _sporttwotime,int _sportone,int _sporttwo,int sportPlace[]);
