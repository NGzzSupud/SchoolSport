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


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);

    //Read all files
    QFile fileCollege("College.txt");
    QFile fileGame("Game.txt");
    QFile fileStudent("Student.txt");
    QFile fileTeam("Team.txt");
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
    if(!fileTeam.open(QIODevice::ReadOnly | QIODevice::Text)) {
           qDebug()<<"Can't open the team file!";
    }
    if(!fileSignup.open(QIODevice::ReadOnly | QIODevice::Text)) {
           qDebug()<<"Can't open the singup file!";
    }
    if(!fileResult.open(QIODevice::ReadOnly | QIODevice::Text)) {
           qDebug()<<"Can't open the result file!";
    }

    College college;
    while(!fileCollege.atEnd()){
        QByteArray line = fileCollege.readLine();
        QString str(line);
        //qDebug()<<str;
        if(str != "\n"){
            bool ok;
            college.id = str.section("|", 0, 0).toInt(&ok, 10);
            college.name = str.section("|", 1, 1);
            college.code = str.section("|", 2, 2);

            database.colleges.push_back(college);
        }
    }
    qDebug()<<"Read file college successfully.";

    Game game;
    while(!fileGame.atEnd()){
        QByteArray line = fileGame.readLine();
        QString str(line);
        //qDebug()<<str;
        if(str != "\n"){
            bool ok;
            game.id = str.section("|", 0, 0).toInt(&ok, 10);
            game.name = str.section("|", 1, 1);
            game.date = str.section("|", 2, 2).toInt(&ok, 10);
            game.duration = str.section("|", 3, 3).toInt(&ok, 10);
            game.time = QTime::fromString(str.section("|", 4, 4), "hh:mm");
            game.place = str.section("|", 5, 5);
            game.number = str.section("|", 6, 6).toInt(&ok, 10);
            game.type = str.section("|", 7, 7).toInt(&ok, 10);
            database.games.push_back(game);
        }
    }
    qDebug()<<"Read file game successfully.";

    Student student;
    while(!fileStudent.atEnd()){
        QByteArray line = fileStudent.readLine();
        QString str(line);
        //qDebug()<<str;
        if(str != "\n"){
            bool ok;
            student.id = str.section("|", 0, 0).toInt(&ok, 10);
            student.name = str.section("|", 1, 1);
            student.college_id = str.section("|", 2, 2).toInt(&ok, 10);
            student.gameCount_f = str.section("|", 3, 3).toInt(&ok, 10);
            student.gameCount_t = str.section("|", 4, 4).toInt(&ok, 10);
            student.haveTeam = str.section("|", 5, 5).toInt(&ok, 10);
            database.students.push_back(student);
        }
    }
    qDebug()<<"Read file student successfully.";

    Team team;
    while(!fileTeam.atEnd()){
        QByteArray line = fileTeam.readLine();
        QString str(line);
        //qDebug()<<str;
        if(str != "\n"){
            bool ok;
            team.id = str.section("|", 0, 0).toInt(&ok, 10);
            team.number = str.section("|", 1, 1).toInt(&ok, 10);
            for(int i=0; i<team.number; i++){
                team.student_id.push_back(str.section("|", i+2, i+2).toInt(&ok, 10));
            }
            database.teams.push_back(team);
        }
    }
    qDebug()<<"Read file team successfully.";

    Signup signup;
    while(!fileSignup.atEnd()){
        QByteArray line = fileSignup.readLine();
        QString str(line);
        //qDebug()<<str;
        if(str != "\n"){
            bool ok;
            signup.id = str.section("|", 0, 0).toInt(&ok, 10);
            signup.team_id = str.section("|", 1, 1).toInt(&ok, 10);
            signup.game_id = str.section("|", 2, 2).toInt(&ok, 10);
            database.signups.push_back(signup);
            /*
            if(database.games[signup.game_id].type == 1){
                qDebug()<<"111";
                for(int i=0; i<database.teams[signup.team_id].number; i++){
                    qDebug()<<i;
                    database.students[database.teams[signup.team_id].student_id[i]].gameCount_f ++;
                }
            }else {
                qDebug()<<"222";
                for(int i=0; i<database.teams[signup.team_id].number; i++){
                    qDebug()<<i;
                    database.students[database.teams[signup.team_id].student_id[i]].gameCount_t ++;
                }
            }
            */
        }
    }
    DataProcess::saveStudent();
    qDebug()<<"Read file signup successfully.";

    Result result;
    while(!fileResult.atEnd()){
        QByteArray line = fileResult.readLine();
        QString str(line);
        //qDebug()<<str;
        if(str != "\n"){
            bool ok;
            result.id = str.section("|", 0, 0).toInt(&ok, 10);
            result.game_id = str.section("|", 1, 1).toInt(&ok, 10);
            result.team_id = str.section("|", 2, 2).toInt(&ok, 10);
            result.result = str.section("|", 3, 3);

            database.results.push_back(result);
        }
    }
    qDebug()<<"Read file result successfully.";

    //Close file
    fileCollege.close();
    fileGame.close();
    fileStudent.close();
    fileTeam.close();
    fileSignup.close();
    fileResult.close();

    qDebug()<<"Size of colleges:"<<database.colleges.size();
    qDebug()<<"Size of games:"<<database.games.size();
    qDebug()<<"Size of students:"<<database.students.size();
    qDebug()<<"Size of teams:"<<database.teams.size();
    qDebug()<<"Size of signups:"<<database.signups.size();
    qDebug()<<"Size of results:"<<database.results.size();


    LoginWindow loginWin;
    loginWin.show();
    loginWin.move ((QApplication::desktop()->width() - loginWin.width())/2,(QApplication::desktop()->height() - loginWin.height())/2);

    return a.exec();
}
