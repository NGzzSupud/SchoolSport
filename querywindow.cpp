#include "querywindow.h"
#include "ui_querywindow.h"
#include <QSettings>
#include <QDialog>
#include <QDebug>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QGridLayout>
#include "dataprocess.h"
extern DataProcess database;

QueryWindow::QueryWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QueryWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags()&~Qt::WindowMaximizeButtonHint);
    this->setFixedSize(this->width(), this->height());
    this->move ((QApplication::desktop()->width() - this->width())/2,(QApplication::desktop()->height() - this->height())/2.25);


    connect(ui->pushButton_game, &QPushButton::clicked, this, &QueryWindow::displayGame);
    connect(ui->pushButton_college, &QPushButton::clicked, this, &QueryWindow::displayCollege);
}

QueryWindow::~QueryWindow()
{
    delete ui;
}


/*
 *  Display all games and their result.
 */
void QueryWindow::displayGame()
{
    static QDialog *mainWindow = new QDialog;

    static QGridLayout *gridLayout = new QGridLayout;

    //create a table
    int count = 0;
    QStringList colLabels;
    for(int i=0; i<database.games.size(); i++){
        int isEnd = DataProcess::resultIsExist(database.games[i].id);
        if(isEnd != -1){
            colLabels << database.games[i].name << "Result";

            count ++;
        }
    }
    table = new QTableWidget(20, count * 2);
    table->setHorizontalHeaderLabels(colLabels);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

     //Fill in data
    int count_col = 0;
    for(int i=0; i<database.games.size(); i++){
		//qDebug() << k;
        int isEnd;
        isEnd = DataProcess::resultIsExist(database.games[i].id);
        //qDebug()<<isEnd;
        if(isEnd != -1){
            for(int j=0; j<database.results[isEnd - 1].number; j++){
                QTableWidgetItem *item1;
                QTableWidgetItem *item2;
                //qDebug()<<j;
                //table->setRowCount(j + 1);
                item1 = new QTableWidgetItem;
                item2 = new QTableWidgetItem;
                item1->setTextAlignment(Qt::AlignCenter);
                item2->setTextAlignment(Qt::AlignCenter);
                //qDebug()<<database.students[database.results[isEnd - 1].students[j] - 1].name;
                //qDebug() << i << " and " << j;
                table->setItem(j, count_col * 2, item1);
                table->setItem(j, count_col * 2 + 1, item2);
                item2->setText(QString::number(database.signups[DataProcess::getResult(database.students[database.results[isEnd - 1].students[j] - 1].id, database.games[i].id) - 1].result));
                item1->setText(database.students[database.results[isEnd - 1].students[j] - 1].name);
            }
            count_col ++;
        }
    }

    //Set the height of each row
    for(int i = 0; i < 20; i++)
        table->setRowHeight(i, 25);
    table->horizontalHeader()->setStretchLastSection(true);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setAlternatingRowColors(true);

    gridLayout->setColumnStretch(0, 0);
    gridLayout->addWidget(table, 0, 0);

    mainWindow->setLayout(gridLayout);

    mainWindow->resize(310 * count, 250);
    mainWindow->setWindowTitle("Game Result");
    //mainWindow->setGeometry(this->geometry().x() - 310 * count, (QApplication::desktop()->height() - mainWindow->height())/2, 310 * count, 250);
    mainWindow->setWindowFlags(mainWindow->windowFlags()&~Qt::WindowMaximizeButtonHint);
    mainWindow->setWindowFlags(Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint);
    mainWindow->setFixedSize(mainWindow->width(), mainWindow->height());
    mainWindow->show();

}


/*
 *  Display all college and their rank.
 */
void QueryWindow::displayCollege()
{

    static QDialog *mainWindow = new QDialog;

    static QGridLayout *gridLayout = new QGridLayout;

    //create a table
    table = new QTableWidget(0,2);
    QStringList colLabels;
    colLabels << "College" << "Score";
    table->setHorizontalHeaderLabels(colLabels);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);


    //Calculate the total score of college.
    int score[20] = {0};
    for(int i=1; i<=database.colleges.size(); i++){
        for(int j=0; j<database.students.size(); j++){
            if(database.students[j].college_id == i){
                score[i] += database.students[j].score;
            }
        }
    }

    //Fill in data
    for(int i = 0; i < database.colleges.size(); i ++){

        table->setRowCount(i + 1);
        QTableWidgetItem *item1;
        QTableWidgetItem *item2;
        item1 = new QTableWidgetItem;
        item2 = new QTableWidgetItem;
        item1->setText(database.colleges[i].name);
        item1->setTextAlignment(Qt::AlignCenter);
        table->setItem(i, 0, item1);
        item2->setText(QString::number(score[i + 1]));
        item2->setTextAlignment(Qt::AlignCenter);
        table->setItem(i, 1, item2);
    }


    //Set the height of each row
    for(int i = 0; i < database.colleges.size(); i++)
        table->setRowHeight(i, 25);
    table->horizontalHeader()->setStretchLastSection(true);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setAlternatingRowColors(true);

    gridLayout->setColumnStretch(0, 0);
    gridLayout->addWidget(table, 0, 0);

    mainWindow->setLayout(gridLayout);

    mainWindow->resize(360, 250);
    mainWindow->setWindowTitle("College and Score");
    //mainWindow->setGeometry(this->geometry().x() - 360, (QApplication::desktop()->height() - mainWindow->height())/2, 360, 250);
    mainWindow->setWindowFlags(mainWindow->windowFlags()&~Qt::WindowMaximizeButtonHint);
    mainWindow->setWindowFlags(Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint);
    mainWindow->setFixedSize(mainWindow->width(), mainWindow->height());
    mainWindow->show();


}
