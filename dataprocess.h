#ifndef DATAPROCESS_H
#define DATAPROCESS_H

#include <QString>

struct Game
{
    int id;
    QString name;
    QDate date;
    QTime time;
    QString place;
    int number;
};

struct Student
{
    int id;
    QString college;
    QString name;
};

struct Signup
{
    int id;
    int student_id;
    int game_id;
};

struct Result
{
    int id;
    int student_id;
    QString result;
};

class DataProcess
{
public:
    DataProcess();
    QVector<Game> games;
    QVector<Student> students;
    QVector<Signup> signups;
    Game getGamebyId(int game_id);
    Student getStudentbyId(int student_id);

};

#endif // DATAPROCESS_H
