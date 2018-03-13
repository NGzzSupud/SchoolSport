#include "normalwindow.h"
#include "ui_normalwindow.h"
//#include <QMessageBox>
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

NormalWindow::NormalWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NormalWindowUi)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags()&~Qt::WindowMaximizeButtonHint);
    this->setFixedSize(this->width(), this->height());
    this->move ((QApplication::desktop()->width() - this->width())/2,(QApplication::desktop()->height() - this->height())/2.25);

    grid = new QGridLayout;

    this->setLayout(grid);
    QLabel * label_select = new QLabel(this);
    label_select->setText("Selected Game:");
    label_select->setAlignment(Qt::AlignCenter);
    QLabel * label_gameName = new QLabel(this);
    label_gameName->setText("Game");
    label_gameName->setAlignment(Qt::AlignCenter);
    QPushButton * pushButton_timer = new QPushButton(this);
    QPushButton * pushButton_submit = new QPushButton(this);
    pushButton_timer->setText("Game Timer");
    pushButton_submit->setText("Submit");

    grid->setVerticalSpacing(20);

    grid->setColumnStretch(0, 1);
    grid->setColumnStretch(1, 2);
    grid->setColumnStretch(2, 1);
    grid->setColumnStretch(3, 2);
    grid->setColumnStretch(4, 1);
    grid->setRowStretch(0, 1);
    grid->setRowStretch(1, 1);
    grid->setRowStretch(2, 1);
    grid->addWidget(label_select, 0, 1);
    grid->addWidget(label_gameName, 0, 2);
    grid->addWidget(pushButton_timer, 2, 1);
    grid->addWidget(pushButton_submit, 2, 3);

    label_select->setObjectName("label");
    label_gameName->setObjectName("label");
    pushButton_timer->setObjectName("button");
    pushButton_submit->setObjectName("button");


    connect(pushButton_timer,&QPushButton::clicked,this,&NormalWindow::displaySports);
    connect(pushButton_submit,&QPushButton::clicked,this,&NormalWindow::submit);

}

NormalWindow::~NormalWindow()
{
    delete ui;
}

void NormalWindow::displaySports()
{
    static QDialog *mainWindow = new QDialog;

    static QGridLayout *gridLayout = new QGridLayout;

    //create a table
    table = new QTableWidget(0,3);
    QStringList colLabels;
    colLabels << "Game" << "Place" << "Number";
    table->setHorizontalHeaderLabels(colLabels);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //Add rows and fill in data

    for(int i = 0; i < database.games.size(); i ++){
        //qDebug()<<games[i].id<<games[i].name<<games[i].date<<games[i].time<<games[i].place<<games[i].number;

        table->setRowCount(i + 1);
        QTableWidgetItem *item1;
        QTableWidgetItem *item2;
        QTableWidgetItem *item3;
        item1 = new QTableWidgetItem;
        item2 = new QTableWidgetItem;
        item3 = new QTableWidgetItem;
        item1->setText(database.games[i].name);
        item1->setTextAlignment(Qt::AlignCenter);
        table->setItem(i, 0, item1);
        item2->setText(database.games[i].place);
        item2->setTextAlignment(Qt::AlignCenter);
        table->setItem(i, 1, item2);
        item3->setText(QString::number(database.games[i].number));
        item3->setTextAlignment(Qt::AlignCenter);
        table->setItem(i, 2, item3);
    }


    //Set the height of each row
    for(int i = 0; i < database.games.size(); i++)
        table->setRowHeight(i, 22);
    table->horizontalHeader()->setStretchLastSection(true);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setAlternatingRowColors(true);

    gridLayout->setColumnStretch(0, 0);
    gridLayout->addWidget(table, 0, 0);

    mainWindow->setLayout(gridLayout);

    mainWindow->resize(450, 80 + database.games.size() * 22);
    mainWindow->setWindowTitle("Games Timer");
    mainWindow->setGeometry(this->geometry().x() - 450, (QApplication::desktop()->height() - mainWindow->height())/2, 450, 80 + database.games.size() * 22);
    mainWindow->setWindowFlags(mainWindow->windowFlags()&~Qt::WindowMaximizeButtonHint);
    mainWindow->setWindowFlags(Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint);
    mainWindow->setFixedSize(mainWindow->width(), mainWindow->height());
    mainWindow->show();

    connect(table, &QTableWidget::clicked, this, &NormalWindow::addLineEdit);

}

void NormalWindow::addLineEdit()
{
    //qDebug()<<"changed";
    this->setFixedSize(460, 100 + database.games[table->currentRow()].number * 40);
    QList<QLabel*> labels = this->findChildren<QLabel*>("label");
    QList<QLineEdit*> lines = this->findChildren<QLineEdit*>("line");
    QList<QPushButton*> buttons = this->findChildren<QPushButton*>("button");

    foreach(QLineEdit*line, lines)
    {
        line->setParent(0);
        //qDebug()<<line->objectName();
        delete line;
    }

    foreach (QLabel* label, labels) {
        label->setParent(0);
        //qDebug()<<label->objectName();
        delete label;
    }

    foreach (QPushButton* button, buttons) {
        button->setParent(0);
        //qDebug()<<button->objectName();
        delete button;
    }

    //ui->label_game->setText(database.games[table->currentRow()].name);
    for(int i=0; i<database.games[table->currentRow()].number; i++){
        QLabel * label_name = new QLabel(this);
        label_name->setText("Name:");
        label_name->setAlignment(Qt::AlignCenter);
        label_name->setObjectName("label");
        QLineEdit * lineEdit = new QLineEdit(this);
        lineEdit->setObjectName("line");
        grid->setRowStretch(i, 1);
        grid->addWidget(label_name, i+1, 1);
        grid->addWidget(lineEdit, i+1, 3);
    }

    QLabel * label_select = new QLabel(this);
    label_select->setText("Selected Game:");
    label_select->setAlignment(Qt::AlignCenter);
    label_select->setObjectName("label");
    QLabel * label_gameName = new QLabel(this);
    label_gameName->setText(database.games[table->currentRow()].name);
    label_gameName->setAlignment(Qt::AlignCenter);
    label_gameName->setObjectName("label");
    QPushButton * pushButton_timer = new QPushButton(this);
    QPushButton * pushButton_submit = new QPushButton(this);
    pushButton_timer->setText("Game Timer");
    pushButton_submit->setText("Submit");
    pushButton_timer->setObjectName("button");
    pushButton_submit->setObjectName("button");

    grid->addWidget(label_select, 0, 1);
    grid->addWidget(label_gameName, 0, 2);
    grid->addWidget(pushButton_timer, database.games[table->currentRow()].number + 1, 1);
    grid->addWidget(pushButton_submit, database.games[table->currentRow()].number + 1, 3);


    connect(pushButton_timer,&QPushButton::clicked,this,&NormalWindow::displaySports);
    connect(pushButton_submit,&QPushButton::clicked,this,&NormalWindow::submit);

}

void NormalWindow::submit()
{
    QList<QLineEdit*> lines = this->findChildren<QLineEdit*>("line");
    qDebug()<<"size:"<<lines.size();
    int rows = database.students.size();
    Student student;
    int position = 0;
    foreach (QLineEdit* line, lines) {
        bool flag = true;
        if(DataProcess::studentIsExist(line->text()) == -1){
            student.id = rows;
            student.name = line->text();
            student.college_id = college;
            student.gameCount_f = 0;
            student.gameCount_w = 0;
            database.students.push_back(student);
            position = database.students.size() - 1;
            rows ++;
        }else {
            position = DataProcess::studentIsExist(line->text());
        }
        //qDebug()<<position;
        if(database.students[position].gameCount_f < 1){
            //qDebug()<<"test2";
            for(int i=0; i<database.signups.size(); i++){
                //qDebug()<<"test3";
                if(database.signups[i].student_id == position && database.signups[i].game_id == table->currentRow()){
                    //qDebug()<<"test4";
                    QMessageBox::about(this, tr("Tips"), database.students[position].name + " has signed up this game.");
                    flag = false;
                    break;
                }
            }
            if(flag){
                Signup signup;
                signup.id = database.signups.size() + 1;
                signup.student_id = position;
                signup.game_id = table->currentRow();
                database.signups.push_back(signup);
                database.students[position].gameCount_f ++;
                //qDebug()<<"insert successfully";
            }
        }else {
            QMessageBox::about(this, tr("Tips"), database.students[position].name + " has signed up two games.");
            break;
        }
    }
    //qDebug()<<database.students.size();
    DataProcess::saveStudent();

    DataProcess::saveSignup();

}

