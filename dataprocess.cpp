#include "dataprocess.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

extern DataProcess database;

int DataProcess::studentIsExist(QString name)
{
    for(int i=0; i<database.students.size(); i++){
        if(!database.students[i].name.compare(name)){
            return i + 1;
        }
    }
    return -1;
}

int DataProcess::resultIsExist(int game_id)
{
	for (int a = 0; a<database.results.size(); a++) {
		if (database.results[a].game_id == game_id) {
			return a + 1;
		}
	}
	return -1;
}

double DataProcess::getResult(int student_id, int game_id)
{
    for(int i=0; i<database.signups.size(); i++){
        if(database.signups[i].student_id == student_id && database.signups[i].game_id == game_id){
            return i + 1;
        }
    }
    return -1;
}

QVector<int> DataProcess::getStudentByGame(int game_id)
{
    QVector<int>students;

    for(int i=0; i<database.signups.size(); i++){
        if(database.signups[i].game_id == game_id){
            students.push_back(database.signups[i].student_id);
        }
    }

    return students;
}

void DataProcess::saveCollege()
{
    QFile fileCollege("College.txt");
    if(!fileCollege.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate)) {
        qDebug()<<"Can't open the college file!";
    }else {
        for(int i=0; i < database.colleges.size(); i ++){
            QString str = QString::number(database.colleges[i].id) + "|" + database.colleges[i].name + "|" + database.colleges[i].code + "|";
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
            QString str = QString::number(database.games[i].id) + "|" + database.games[i].name + "|" + QString::number(database.games[i].date)
                    + "|" + QString::number(database.games[i].duration)
                    + "|" + database.games[i].time.toString("hh:mm")
                    + "|" + QString::number(database.games[i].place)
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
            QString str = QString::number(database.students[i].id) + "|" + database.students[i].name + "|" + QString::number(database.students[i].college_id)+ "|"
                    + QString::number(database.students[i].gameCount_f) + "|"
                    + QString::number(database.students[i].gameCount_t) + "|"
					+ QString::number(database.students[i].score) + "|";
                    //+ QString::number(database.students[i].haveTeam) + "|";
            QTextStream in(&fileStudent);
            in<<str<<"\n";
        }
        fileStudent.close();
    }
}
/*
void DataProcess::saveTeam()
{
    QFile fileTeam("Team.txt");
    if(!fileTeam.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate)) {
        qDebug()<<"Can't open the team file!";
    }else {
        for(int i=0; i < database.teams.size(); i ++){
            QString str = QString::number(database.teams[i].id) + "|" + QString::number(database.teams[i].number) + "|";
            for(int j=0; j<database.teams[i].number; j++){
                str.append(database.teams[i].student_id[j] + "|");
            }
            QTextStream in(&fileTeam);
            in<<str<<"\n";
        }
        fileTeam.close();
    }
}
*/

void DataProcess::saveSignup()
{
    QFile fileSignup("Signup.txt");
    if(!fileSignup.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate)) {
        qDebug()<<"Can't open the signup file!";
    }else {
        for(int i=0; i < database.signups.size(); i ++){
            QString str = QString::number(database.signups[i].id) + "|" 
				+ QString::number(database.signups[i].student_id) + "|" 
				+ QString::number(database.signups[i].game_id)+ "|"
				+ QString::number(database.signups[i].result) + "|";
            QTextStream in(&fileSignup);
            in<<str<<"\n";
        }
        fileSignup.close();
    }
}

void DataProcess::saveResult()
{
	QFile fileResult("Result.txt");
	if (!fileResult.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate)) {
		qDebug() << "Can't open the result file!";
	}
	else {
		for (int i = 0; i < database.results.size(); i++) {
			QString str = QString::number(database.results[i].id) + "|"
				+ QString::number(database.results[i].game_id) + "|"
				+ QString::number(database.results[i].number) + "|";
			for (int j = 0; j<database.results[i].number; j++) {
				str.append(QString::number(database.results[i].students[j]) + "|");
			}
			QTextStream in(&fileResult);
			in << str << "\n";
		}
		fileResult.close();
	}
}
