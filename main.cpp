#include "mainwindow.h"
#include "loginwindow.h"
#include "adminwindow.h"
#include "normalwindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QFile>
#include <QDebug>
#include <QTextCodec>
#include "dataprocess.h"
DataProcess database;

int DataProcess::studentIsExist(QString name)
{
    for(int i=0; i<database.students.size(); i++){
        if(!database.students[i].name.compare(name)){
            return i;
        }
    }
    return -1;
}

void DataProcess::saveCollege()
{
    QFile fileCollege("College.txt");
    if(!fileCollege.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate)) {
        qDebug()<<"Can't open the college file!";
    }else {
        for(int i=0; i < database.colleges.size(); i ++){
            QString str = database.colleges[i].name + "|" + database.colleges[i].code + "|";
            QTextStream in(&fileCollege);
            in<<str<<"\n";
        }
        fileCollege.close();
    }
}

void DataProcess::saveGame()
{
    QFile fileGame("Game.txt");
    if(!fileGame.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate)) {
        qDebug()<<"Can't open the game file!";
    }else {
        for(int i=0; i < database.games.size(); i ++){
            QString str = database.games[i].name + "|" + QString::number(database.games[i].date)
                    + "|" + QString::number(database.games[i].duration)
                    + "|" + database.games[i].time.toString("hh:mm")
                    + "|" + database.games[i].place
                    + "|" + QString::number(database.games[i].number)
                    + "|" + QString::number(database.games[i].type) + "|";
            QTextStream in(&fileGame);
            in<<str<<"\n";
        }
        fileGame.close();
    }
}

void DataProcess::saveStudent()
{
    QFile fileStudent("Student.txt");
    if(!fileStudent.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate)) {
        qDebug()<<"Can't open the student file!";
    }else {
        for(int i=0; i < database.students.size(); i ++){
            QString str = database.students[i].name + "|" + QString::number(database.students[i].college_id)+ "|"
                    + QString::number(database.students[i].gameCount_f) + "|"
                    + QString::number(database.students[i].gameCount_w) + "|";
            QTextStream in(&fileStudent);
            in<<str<<"\n";
        }
        fileStudent.close();
    }
}

void DataProcess::saveSignup()
{
    QFile fileSignup("Signup.txt");
    if(!fileSignup.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate)) {
        qDebug()<<"Can't open the signup file!";
    }else {
        for(int i=0; i < database.signups.size(); i ++){
            QString str = QString::number(database.signups[i].student_id) + "|" + QString::number(database.signups[i].game_id)+ "|";
            QTextStream in(&fileSignup);
            in<<str<<"\n";
        }
        fileSignup.close();
    }
}

void DataProcess::saveResult()
{
    QFile fileResult("Result.txt");
    if(!fileResult.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate)) {
        qDebug()<<"Can't open the result file!";
    }else {
        for(int i=0; i < database.results.size(); i ++){
            QString str = QString::number(database.results[i].student_id) + "|"
                    + QString::number(database.results[i].game_id)+ "|"
                    + database.results[i].result+ "|";
            QTextStream in(&fileResult);
            in<<str<<"\n";
        }
        fileResult.close();
    }
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);

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
            game.date = str.section("|", 1, 1).toInt(&ok, 10);
            game.duration = str.section("|", 2, 2).toInt(&ok, 10);
            game.time = QTime::fromString(str.section("|", 3, 3), "hh:mm");
            game.place = str.section("|", 4, 4);
            game.number = str.section("|", 5, 5).toInt(&ok, 10);
            game.type = str.section("|", 6, 6).toInt(&ok, 10);
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
            student.gameCount_f = 0;
            student.gameCount_w = 0;
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
            if(database.games[signup.game_id - 1].type == 1){
                database.students[signup.student_id - 1].gameCount_f ++;
            }else {
                database.students[signup.student_id - 1].gameCount_w ++;
            }
            database.signups.push_back(signup);
        }
    }

    DataProcess::saveStudent();

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
