#ifndef DATAPROCESS_H
#define DATAPROCESS_H

#include <QString>
#include <QDate>
#include<QVector>


struct Game
{
    int id;
    QString name;
    int type;       //1 - Tamosi    2 - Track game
    int date;
    int duration;
    QTime time;
    int place;
    int number;
};

struct College
{
    int id;
    QString name;
    QString code;
};

struct Student
{
    int id;
    int college_id;
    QString name;
    int gameCount_f;
    int gameCount_t;
	int score;
    //int haveTeam;
};
/*
struct Team
{
    int id;
    int number;
    QVector<int> student_id;
};
*/
struct Signup
{
    int id;
    //int team_id;
    int student_id;
    int game_id;
	double result;
};

struct Result
{
    int id;
	int game_id;
	int number;
    QVector<int> students;
};

class DataProcess
{
public:
    QVector<Game> games;
    QVector<Student> students;
    //QVector<Team> teams;
    QVector<Signup> signups;
    QVector<Result> results;
    QVector<College> colleges;

    static void saveCollege();
    static void saveGame();
    static void saveStudent();
    //static void saveTeam();
    static void saveSignup();
    static void saveResult();
    static int studentIsExist(QString name);

private:

};


#endif // DATAPROCESS_H
