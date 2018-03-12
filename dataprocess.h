#ifndef DATAPROCESS_H
#define DATAPROCESS_H

#include <QString>
#include <QDate>


struct Game
{
    int id;
    QString name;
    int date;
    int duration;
    QTime time;
    QString place;
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
    int game_id;
    int student_id;
    QString result;
};

class DataProcess
{
public:
    QVector<Game> games;
    QVector<Student> students;
    QVector<Signup> signups;
    QVector<Result> results;
    QVector<College> colleges;

    static void saveCollege();
    static void saveGame();
    static void saveStudent();
    static void saveSignup();
    static void saveResult();
    static Game getGameById(int id);
    static Student getStudentById(int id);
    static College getCollegeById(int id);

private:

};


#endif // DATAPROCESS_H
