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

Entrywindow::Entrywindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Entrywindow)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags()&~Qt::WindowMaximizeButtonHint);
        this->setFixedSize(this->width(), this->height());
        this->move ((QApplication::desktop()->width() - this->width())/2,(QApplication::desktop()->height() - this->height())/2.25);




    /*ui->gridLayout_result;//->setLayout(ui->gridLayout_result);
    QLabel * label_sports = new QLabel(this);
    label_sports->setText("Sport Name:");
    label_sports->setAlignment(Qt::AlignCenter);
    QLabel * label_gameName = new QLabel(this);
    label_gameName->setText("Game");
    label_gameName->setAlignment(Qt::AlignCenter);
    QPushButton * pushButton_submit = new QPushButton(this);
    pushButton_submit->setText("Submit");
    ui->gridLayout_result->setVerticalSpacing(20);

    ui->gridLayout_result->setColumnStretch(0, 1);
    ui->gridLayout_result->setColumnStretch(1, 2);
    ui->gridLayout_result->setColumnStretch(2, 1);
    ui->gridLayout_result->setColumnStretch(3, 2);
    ui->gridLayout_result->setColumnStretch(4, 1);
    ui->gridLayout_result->setRowStretch(0, 1);
    ui->gridLayout_result->setRowStretch(1, 1);
    ui->gridLayout_result->setRowStretch(2, 1);
    ui->gridLayout_result->addWidget(label_sports, 0, 1);
    ui->gridLayout_result->addWidget(label_gameName, 0, 2);
    ui->gridLayout_result->addWidget(pushButton_submit, 2, 3);*/

    //label_sports->setObjectName("label");
    //label_gameName->setObjectName("label");
    //ui->pushButton_submit->setObjectName("button");

    //connect(pushButton_submit,&QPushButton::clicked,this,&Entrywindow::submit);

    //ui->tableWidget_game = new QTableWidget(0,1);
    //ui->tableWidget_game->setRowCount(1);
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
    //connect(ui->pushButton_submit,&QPushButton::clicked,this,&Entrywindow::submit);
    connect(ui->tableWidget_game, &QTableWidget::clicked, this, &Entrywindow::addLineEdit);



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
    qDebug()<<"changed";
    this->setFixedSize(460, 100 + database.teams[ui->tableWidget_game->currentRow()].number * 40);
    QList<QLabel*> labels = ui->gridLayout_result->findChildren<QLabel*>("label");
    QList<QLineEdit*> lines = ui->gridLayout_result->findChildren<QLineEdit*>("line");
    QList<QPushButton*> buttons = ui->gridLayout_result->findChildren<QPushButton*>("button");

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

    foreach (QPushButton* button, buttons) {
        button->setParent(0);
        qDebug()<<button->objectName();
        delete button;
    }

    //ui->label_game->setText(database.games[table->currentRow()].name);
    for(int i=0; i<database.teams[ui->tableWidget_game->currentRow()].number; i++){
        QLabel * label_name = new QLabel(this);
        label_name->setText( database.students[database.teams[ui->tableWidget_game->currentRow()].student_id[0]].name);
        label_name->setAlignment(Qt::AlignCenter);
        label_name->setObjectName("label");
        QLineEdit * lineEdit = new QLineEdit(this);
        lineEdit->setObjectName("line");
        ui->gridLayout_result->setRowStretch(i, 1);
        ui->gridLayout_result->addWidget(label_name, i+1, 1);
        ui->gridLayout_result->addWidget(lineEdit, i+1, 3);
    }

    /*QLabel * label_sports = new QLabel(this);
    label_sports->setText("Sport Name:");
    label_sports->setAlignment(Qt::AlignCenter);
    label_sports->setObjectName("label");
    QLabel * label_gameName = new QLabel(this);
    label_gameName->setText(database.games[ui->tableWidget_game->currentRow()].name);
    label_gameName->setAlignment(Qt::AlignCenter);
    label_gameName->setObjectName("label");
    QPushButton * pushButton_submit = new QPushButton(this);
    pushButton_submit->setText("Submit");
    pushButton_submit->setObjectName("button");

    ui->gridLayout_result->addWidget(label_sports, 0, 1);
    ui->gridLayout_result->addWidget(label_gameName, 0, 2);
    ui->gridLayout_result->addWidget(pushButton_submit, database.games[ui->tableWidget_game->currentRow()].number + 1, 3);*/

    //connect(pushButton_submit,&QPushButton::clicked,this,&Entrywindow::submit);

}

/*
 *  Submit and save the sign up infomation.
 */
