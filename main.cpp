#include "mainwindow.h"
#include "loginwindow.h"
#include "adminwindow.h"
#include "normalwindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QFile>
#include <QDebug>
#include "dataprocess.h"
DataProcess database;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Read all files
    QFile fileCollege("College.txt");
    QFile fileGame("Game.txt");
    QFile fileStudent("Student.txt");
    QFile fileSignup("Signup.txt");
    QFile fileResult("Result.txt");
    if(!fileCollege.open(QIODevice::ReadOnly | QIODevice::Text)) {
           qDebug()<<"Can't open the college file!";
    }
    if(!fileGame.open(QIODevice::ReadOnly | QIODevice::Text)) {
           qDebug()<<"Can't open the game file!";
    }
    if(!fileStudent.open(QIODevice::ReadOnly | QIODevice::Text)) {
           qDebug()<<"Can't open the student file!";
    }
    if(!fileSignup.open(QIODevice::ReadOnly | QIODevice::Text)) {
           qDebug()<<"Can't open the singup file!";
    }
    if(!fileResult.open(QIODevice::ReadOnly | QIODevice::Text)) {
           qDebug()<<"Can't open the result file!";
    }

    int rows = 0;

    College college;
    while(!fileCollege.atEnd()){
        QByteArray line = fileCollege.readLine();
        QString str(line);
        //qDebug()<<str;
        if(str != "\n"){
            rows ++;
            college.id = rows;
            college.name = str.section("|", 0, 0);
            college.code = str.section("|", 1, 1);

            database.colleges.push_back(college);
        }
    }

    Game game;
    while(!fileGame.atEnd()){
        QByteArray line = fileGame.readLine();
        QString str(line);
        //qDebug()<<str;
        if(str != "\n"){
            rows ++;
            bool ok;
            game.id = rows;
            game.name = str.section("|", 0, 0);
            game.date = QDate::fromString(str.section("|", 1, 1), "yyyy-MM-dd");
            game.time = QTime::fromString(str.section("|", 2, 2), "hh:mm");
            game.place = str.section("|", 3, 3);
            game.number = str.section("|", 4, 4).toInt(&ok, 10);

            database.games.push_back(game);
        }
    }

    Student student;
    while(!fileStudent.atEnd()){
        QByteArray line = fileStudent.readLine();
        QString str(line);
        //qDebug()<<str;
        if(str != "\n"){
            rows ++;
            bool ok;
            student.id = rows;
            student.name = str.section("|", 0, 0);
            student.college_id = str.section("|", 1, 1).toInt(&ok, 10);

            database.students.push_back(student);
        }
    }

    Signup signup;
    while(!fileSignup.atEnd()){
        QByteArray line = fileSignup.readLine();
        QString str(line);
        //qDebug()<<str;
        if(str != "\n"){
            rows ++;
            bool ok;
            signup.id = rows;
            signup.student_id = str.section("|", 0, 0).toInt(&ok, 10);
            signup.game_id = str.section("|", 1, 1).toInt(&ok, 10);

            database.signups.push_back(signup);
        }
    }

    Result result;
    while(!fileResult.atEnd()){
        QByteArray line = fileResult.readLine();
        QString str(line);
        //qDebug()<<str;
        if(str != "\n"){
            rows ++;
            bool ok;
            result.id = rows;
            result.game_id = str.section("|", 0, 0).toInt(&ok, 10);
            result.student_id = str.section("|", 1, 1).toInt(&ok, 10);
            result.result = str.section("|", 2, 2);

            database.results.push_back(result);
        }
    }

    //Debug
    //qDebug()<<"college:"<<database.colleges.size();
    //qDebug()<<"game:"<<database.games.size();
    //qDebug()<<"student:"<<database.students.size();
    //qDebug()<<"signup:"<<database.signups.size();
    //qDebug()<<"result:"<<database.results.size();

    //Close file
    fileCollege.close();
    fileGame.close();
    fileStudent.close();
    fileSignup.close();
    fileResult.close();


    LoginWindow loginWin;
    loginWin.show();
    loginWin.move ((QApplication::desktop()->width() - loginWin.width())/2,(QApplication::desktop()->height() - loginWin.height())/2);
    //NormalWindow normalWin;
    //normalWin.show();
    //AdminWindow adminWin;
    //adminWin.show();
    return a.exec();
}
