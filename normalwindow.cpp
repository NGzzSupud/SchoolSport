#define TAMOSI_LIMITED 1    //The number of tamosi student can sign up
#define TRACK_LIMITED 1     //The number of track game student can sign up

#include "normalwindow.h"
#include "ui_normalwindow.h"
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

/*
 *  Display a window to show Game List
 */
void NormalWindow::displaySports()
{
    static QDialog *mainWindow = new QDialog;

    static QGridLayout *gridLayout = new QGridLayout;

    //create a table
    table = new QTableWidget(0,4);
    QStringList colLabels;
    colLabels << "Game" << "Place" << "Type" << "Number";
    table->setHorizontalHeaderLabels(colLabels);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);


    //Add rows and fill in data
    for(int i = 0; i < database.games.size(); i ++){
        //qDebug()<<games[i].id<<games[i].name<<games[i].date<<games[i].time<<games[i].place<<games[i].number;

        table->setRowCount(i + 1);
        QTableWidgetItem *item1;
        QTableWidgetItem *item2;
        QTableWidgetItem *item3;
        QTableWidgetItem *item4;
        item1 = new QTableWidgetItem;
        item2 = new QTableWidgetItem;
        item3 = new QTableWidgetItem;
        item4 = new QTableWidgetItem;
        item1->setText(database.games[i].name);
        item1->setTextAlignment(Qt::AlignCenter);
        table->setItem(i, 0, item1);
        item2->setText(database.games[i].place);
        item2->setTextAlignment(Qt::AlignCenter);
        table->setItem(i, 1, item2);
        if(database.games[i].type == 1){
            item3->setText("Tamosi");
        }else{
            item3->setText("Track");
        }
        item3->setTextAlignment(Qt::AlignCenter);
        table->setItem(i, 2, item3);
        item4->setText(QString::number(database.games[i].number));
        item4->setTextAlignment(Qt::AlignCenter);
        table->setItem(i, 3, item4);
    }


    //Set the height of each row
    for(int i = 0; i < database.games.size(); i++)
        table->setRowHeight(i, 22);

    //Beautify the table
    table->horizontalHeader()->setStretchLastSection(true);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setAlternatingRowColors(true);

    gridLayout->setColumnStretch(0, 0);
    gridLayout->addWidget(table, 0, 0);

    mainWindow->setLayout(gridLayout);

    mainWindow->resize(550, 80 + database.games.size() * 22);
    mainWindow->setWindowTitle("Games Timer");
    mainWindow->setGeometry(this->geometry().x() - 550, (QApplication::desktop()->height() - mainWindow->height())/2, 550, 80 + database.games.size() * 22);
    mainWindow->setWindowFlags(mainWindow->windowFlags()&~Qt::WindowMaximizeButtonHint);
    mainWindow->setWindowFlags(Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint);
    mainWindow->setFixedSize(mainWindow->width(), mainWindow->height());
    mainWindow->show();

    connect(table, &QTableWidget::clicked, this, &NormalWindow::addLineEdit);

}

/*
 *  Change the number of lineEdits according to game's number.
 */
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
    //qDebug() << table->currentRow();
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

/*
 *  Submit and save the sign up infomation.
 */

void NormalWindow::submit()
{



    /*
    QList<QLineEdit*> lines = this->findChildren<QLineEdit*>("line");
    //qDebug()<<"size:"<<lines.size();
    bool emptyFlag = true;
    for(int i=0; i<lines.size(); i++){
        if(lines[i]->text().isEmpty()){
            QMessageBox::about(this, tr("Tips"), "LineEdit:" + QString::number(i + 1) + " is empty.");
            emptyFlag = false;
            break;
        }
    }
    if(emptyFlag){

        int outfor = 0;
        if(database.games[table->currentRow()].number == 4){
            for(int i=0; i<4; i++){
                for(int j=0; j<4; j++){
                    if(i == j){
                        continue;
                    }else {
                        if(!lines[i]->text().compare(lines[j]->text())){
                            QMessageBox::about(this, tr("Tips"), "The name can't be same.");
                            outfor = 1;
                            break;
                        }
                    }
                }
                if (outfor == 1) break;
            }

            if(!outfor){
                Student student;
                for(int i=0;i<4;i++){
                    int index = 0;
                    int team = 0;
                    if(DataProcess::studentIsExist(lines[i]->text()) == -1){
                        student.id = database.students.size() + 1;
                        student.name = lines[i]->text();
                        student.college_id = college;
                        student.gameCount_f = 0;
                        student.gameCount_t = 0;
                        student.haveTeam = 0;
                        database.students.push_back(student);
                        index = student.id;
                    }else {
                        index = DataProcess::studentIsExist(lines[i]->text());
                        if(database.students[index - 1].haveTeam != 0){
                            qDebug()<<index;
                            QMessageBox::about(this, tr("Tips"), database.students[index - 1].name + " already have a team.");
                            break;
                        }else {
                            if(!(database.games[table->currentRow()].type == 1 && database.students[index].gameCount_f == TAMOSI_LIMITED)){
                                if(!(database.games[table->currentRow()].type == 2 && database.students[index].gameCount_t == TRACK_LIMITED)){
                                    bool flag = true;
                                    for(int i=1; i<=database.signups.size(); i++){
                                        //qDebug()<<"test";
                                        if(database.signups[i - 1].team_id == team && database.signups[i - 1].game_id == table->currentRow()){
                                            //qDebug()<<"test";
                                            QMessageBox::about(this, tr("Tips"), database.students[index - 1].name + " has signed up this game.");
                                            flag = false;
                                            break;
                                        }
                                    }
                                    if(flag){
                                        Signup signup;
                                        signup.team_id = team;
                                        signup.game_id = table->currentRow();
                                        database.signups.push_back(signup);
                                        if(database.games[signup.game_id].type == 1){
                                            database.students[index].gameCount_f ++;
                                        }else {
                                            database.students[index].gameCount_t ++;
                                        }
                                        //qDebug()<<"insert successfully";
                                    }

                                }else {
                                    QMessageBox::about(this, tr("Tips"), database.students[index].name + " has already signed up a track game.");
                                    break;
                                }
                            }else {
                                QMessageBox::about(this, tr("Tips"), database.students[index].name + " has already signed up a tamosi.");
                                break;
                            }


                        }
                    }
                }
            }
        }

    }
    */

}

