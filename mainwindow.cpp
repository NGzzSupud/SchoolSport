#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSettings>
#include <QDialog>
#include <QDebug>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QGridLayout>
#include "loginwindow.h"
#include "dataprocess.h"
extern DataProcess database;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_start,&QPushButton::clicked,this,&MainWindow::changeCurrent);
    connect(ui->pushButton_manage, &QPushButton::clicked, this, &MainWindow::manageCollege);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 *  Change window according to the game.
 */
void MainWindow::changeCurrent()
{
    //qDebug()<<
    QString configFilePath = "config.ini";
    QSettings settings(configFilePath,QSettings::IniFormat);
    settings.setValue("Game/Current", "1");
    settings.setValue("Game/Date", ui->dateEdit->date().toString("yyyy-MM-dd"));
    adminWin_1.show();
    this->close();
}

/*
 *  Display a window to show college information.
 */
void MainWindow::manageCollege()
{
    mainWindow = new QDialog;

    static QGridLayout *gridLayout = new QGridLayout;

    static QPushButton * button_add = new QPushButton(this);
    button_add->setText("Add");
    static QPushButton * button_delete  = new QPushButton(this);
    button_delete->setText("Delete");
    static QPushButton * button_save = new QPushButton(this);
    button_save->setText("Save");

    connect(button_add, &QPushButton::clicked, this, &MainWindow::addRow);
    connect(button_delete, &QPushButton::clicked, this, &MainWindow::deleteRow);
    connect(button_save, &QPushButton::clicked, this, &MainWindow::saveCollege);


    //create a table
    table = new QTableWidget(0,2);
    QStringList colLabels;
    colLabels << "College" << "Code";
    table->setHorizontalHeaderLabels(colLabels);
    //table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //Add rows and fill in data
    for(int i = 0; i < database.colleges.size(); i ++){
        //qDebug()<<games[i].name<<games[i].date<<games[i].time<<games[i].place<<games[i].number;

        table->setRowCount(i + 1);
        QTableWidgetItem *item1;
        QTableWidgetItem *item2;
        item1 = new QTableWidgetItem;
        item2 = new QTableWidgetItem;
        item1->setText(database.colleges[i].name);
        item1->setTextAlignment(Qt::AlignCenter);
        table->setItem(i, 0, item1);
        item2->setText(database.colleges[i].code);
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
    gridLayout->addWidget(table, 0, 0, 1, 3);
    gridLayout->addWidget(button_add, 1, 0);
    gridLayout->addWidget(button_delete, 1, 1);
    gridLayout->addWidget(button_save, 1, 2);

    mainWindow->setLayout(gridLayout);


    mainWindow->resize(360, 250);
    mainWindow->setWindowTitle("College and InviteCode");
    mainWindow->setGeometry(this->geometry().x() - 360, (QApplication::desktop()->height() - mainWindow->height())/2, 360, 250);
    mainWindow->setWindowFlags(mainWindow->windowFlags()&~Qt::WindowMaximizeButtonHint);
    mainWindow->setWindowFlags(Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint);
    mainWindow->setFixedSize(mainWindow->width(), mainWindow->height());
    mainWindow->show();

}

/*
 *  Add a new row on the table.
 */
void MainWindow::addRow()
{
    //qDebug()<<"add";
    int row = table->rowCount();
    table->setRowCount(row);
    table->insertRow(row);
    table->setRowHeight(row, 25);
    QTableWidgetItem *item1;
    QTableWidgetItem *item2;
    item1 = new QTableWidgetItem;
    item2 = new QTableWidgetItem;
    table->setItem(row, 0, item1);
    table->setItem(row, 1, item2);
}

/*
 *  Delete the row which was chosen on the table.
 */
void MainWindow::deleteRow()
{
    int rowIndex = table->currentRow();
    if (rowIndex != -1){
        table->removeRow(rowIndex);
    }
}

/*
 *  Save the college information on the table.
 */
void MainWindow::saveCollege()
{
    //qDebug()<<"save";
    bool flag = true;
    for(int i=0; i<table->rowCount(); i++){
        if(table->item(i, 0)->text().compare("") == 0||table->item(i, 1)->text().compare("") == 0){
            //qDebug()<<table->item(i, 0)->text();
            //qDebug()<<table->item(i, 1)->text();
            flag = false;
            break;
        }
    }
    if(flag){
        //qDebug()<<"clear";
        database.colleges.clear();
        //qDebug()<<database.colleges.size();
        College college;
        for(int i=0; i<table->rowCount(); i++){
            college.name = table->item(i, 0)->text();
            college.code = table->item(i, 1)->text();
            database.colleges.push_back(college);
        }
        //qDebug()<<database.colleges.size();
        DataProcess::saveCollege();

    }else {
        QMessageBox::about(this, tr("Tips"), tr("Input can't be empty."));
    }

}
