#include "normalwindow.h"
#include "ui_normalwindow.h"
//#include <QMessageBox>
#include <QDialog>
#include <QTextEdit>
#include <QGridLayout>
#include <QDesktopWidget>
#include <QFile>
#include <QDebug>
#include "dataprocess.h"
extern DataProcess database;

NormalWindow::NormalWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NormalWindowUi)
{
    extern DataProcess database;
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags()&~Qt::WindowMaximizeButtonHint);
    this->setFixedSize(this->width(), this->height());
    this->move ((QApplication::desktop()->width() - this->width())/2,(QApplication::desktop()->height() - this->height())/2);
    for(int i = 0; i < database.games.size(); i ++){
        ui->comboBox_sports->addItem(database.games[i].name);
    }

    connect(ui->pushButton_timer,&QPushButton::clicked,this,&NormalWindow::displaySports);
    connect(ui->pushButton_submit,&QPushButton::clicked,this,&NormalWindow::submit);

}

NormalWindow::~NormalWindow()
{
    delete ui;
}

void NormalWindow::setCollege(QString college)
{
    this->College = college;
}

QString NormalWindow::getCollege()
{
    return this->College;
}


void NormalWindow::displaySports()
{
    static QDialog *mainWindow = new QDialog;

    static QGridLayout *gridLayout = new QGridLayout;

    //create a table
    QTableWidget *table = new QTableWidget(0,5);
    QStringList colLabels;
    colLabels << "Game" << "Date" << "Time" << "Place" << "Number";
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
        QTableWidgetItem *item5;
        item1 = new QTableWidgetItem;
        item2 = new QTableWidgetItem;
        item3 = new QTableWidgetItem;
        item4 = new QTableWidgetItem;
        item5 = new QTableWidgetItem;
        item1->setText(database.games[i].name);
        item1->setTextAlignment(Qt::AlignCenter);
        table->setItem(i, 0, item1);
        item2->setText(database.games[i].date.toString("yyyy-MM-dd"));
        item2->setTextAlignment(Qt::AlignCenter);
        table->setItem(i, 1, item2);
        item3->setText(database.games[i].time.toString("mm:ss"));
        item3->setTextAlignment(Qt::AlignCenter);
        table->setItem(i, 2, item3);
        item4->setText(database.games[i].place);
        item4->setTextAlignment(Qt::AlignCenter);
        table->setItem(i, 3, item4);
        item5->setText(QString::number(database.games[i].number));
        item5->setTextAlignment(Qt::AlignCenter);
        table->setItem(i, 4, item5);
    }


    //Set the height of each row
    for(int i = 0; i < database.games.size(); i++)
        table->setRowHeight(i, 22);
    table->horizontalHeader()->setStretchLastSection(true);

    gridLayout->setColumnStretch(0, 0);
    gridLayout->addWidget(table, 0, 0);

    mainWindow->setLayout(gridLayout);

    mainWindow->resize(680, 80 + database.games.size() * 22);
    mainWindow->setWindowTitle(getCollege() + " Games Timer");
    mainWindow->setGeometry(this->geometry().x() - 680, (QApplication::desktop()->height() - mainWindow->height())/2, 680, 80 + database.games.size() * 22);
    mainWindow->setWindowFlags(mainWindow->windowFlags()&~Qt::WindowMaximizeButtonHint);
    mainWindow->setWindowFlags(Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint);
    mainWindow->setFixedSize(mainWindow->width(), mainWindow->height());
    mainWindow->show();

}


void NormalWindow::submit(){


}

