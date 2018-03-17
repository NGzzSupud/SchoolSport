#include "entrywindow.h"
#include "ui_entrywindow.h"
#include <QDialog>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QFile>
#include <QDebug>
#include "dataprocess.h"
extern DataProcess database;

int gamePlayerNum[10],gamePlayer[10][10];

Entrywindow::Entrywindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Entrywindow)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags()&~Qt::WindowMaximizeButtonHint);
        this->setFixedSize(this->width(), this->height());
        this->move ((QApplication::desktop()->width() - this->width())/2,(QApplication::desktop()->height() - this->height())/2.25);



    //label_sports->setObjectName("label");
    //label_gameName->setObjectName("label");
    //ui->pushButton_submit->setObjectName("button");


    ui->tableWidget_game->setColumnCount(1);
    QStringList colLabels;
    colLabels << "Game";
    ui->tableWidget_game->setHorizontalHeaderLabels(colLabels);
    ui->tableWidget_game->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //Add rows and fill in data
    for(int i = 0; i < database.games.size(); i ++){
        //qDebug()<<games[i].id<<games[i].name<<games[i].date<<games[i].time<<games[i].place<<games[i].number;

        ui->tableWidget_game->setRowCount(i + 1);
        QTableWidgetItem *item1;
        item1 = new QTableWidgetItem;
        item1->setText(database.games[i].name);
        item1->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_game->setItem(i, 0, item1);

    }

    connect(ui->pushButton_submit,&QPushButton::clicked,this,&Entrywindow::submit);
    connect(ui->tableWidget_game, &QTableWidget::clicked, this, &Entrywindow::addLineEdit);


    for(int i=1;i<=database.games.size();i++)
    {
        gamePlayerNum[i-1]=0;
        for(int j=0;j<database.signups.size();j++){
            if(database.signups[j].game_id==i){   //qDebug()<<"1";
                gamePlayer[i-1][gamePlayerNum[i-1]]=database.signups[j].student_id;
                gamePlayerNum[i-1]++;
                //sizeof(gamePlayer[i])/sizeof(int);
            }
        }
    }


}

Entrywindow::~Entrywindow()
{
    delete ui;
}



/*
 *  Change the number of lineEdits according to athletes's number.
 */
void Entrywindow::addLineEdit()
{
    this->setFixedSize(460, 100 + sizeof(gamePlayer[ui->tableWidget_game->currentRow()])/sizeof(int) * 40);
    QList<QLabel*> labels = this->findChildren<QLabel*>("label");
    QList<QLineEdit*> lines = this->findChildren<QLineEdit*>("line");
   // QList<QPushButton*> buttons = this->findChildren<QPushButton*>("button");

    foreach(QLineEdit*line, lines)
    {
        line->setParent(0);
        qDebug()<<line->objectName();
        delete line;
    }

    foreach (QLabel* label, labels) {
        label->setParent(0);
        qDebug()<<label->objectName();
        delete label;
    }
/*
    foreach (QPushButton* button, buttons) {
        button->setParent(0);
        qDebug()<<button->objectName();
        delete button;
    }
*/

    //ui->label_game->setText(database.games[table->currentRow()].name);
    for(int i=0; i<gamePlayerNum[ui->tableWidget_game->currentRow()]; i++){
        //qDebug()<<j;
        qDebug()<<"changed";
        QLabel * label_name = new QLabel(this);
        label_name->setText(database.students[gamePlayer[ui->tableWidget_game->currentRow()][i] - 1].name);
        label_name->setAlignment(Qt::AlignCenter);
        label_name->setObjectName("label");
        QLineEdit * lineEdit = new QLineEdit(this);
        //lineEdit->setText();输出上次输入成绩
        lineEdit->setObjectName("line");
        ui->gridLayout_result->setRowStretch(i, 1);
        ui->gridLayout_result->addWidget(label_name, i+1, 1);
        ui->gridLayout_result->addWidget(lineEdit, i+1, 3);
    }
    qDebug()<<"changed";

}

/*
 *  Submit and save the sign up infomation.
 */
void Entrywindow::submit(){

}
