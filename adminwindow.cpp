#include "adminwindow.h"
#include "ui_adminwindow.h"

#include <QDebug>
#include <QMessageBox>
#include <QSettings>
#include <QDesktopWidget>
#include <QDialog>
#include <QGridLayout>
#include <QTableWidget>
#include "dataprocess.h"
#include <QString>
extern DataProcess database;

AdminWindow::AdminWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminWindowUi)
{
    ui->setupUi(this);
    this->move ((QApplication::desktop()->width() - this->width())/2,(QApplication::desktop()->height() - this->height())/2);
    this->setFixedSize(this->width(), this->height());
    connect(ui->pushButton_release,&QPushButton::clicked,this,&AdminWindow::releaseGame);
    connect(ui->pushButton_search,&QPushButton::clicked,this,&AdminWindow::searchWindow);
    connect(ui->pushButton_complete,&QPushButton::clicked,this,&AdminWindow::changeCurrent);
}


AdminWindow::~AdminWindow()
{
    delete ui;
}

void AdminWindow::changeCurrent(){
    QString configFilePath = "config.ini";
    QSettings settings(configFilePath,QSettings::IniFormat);
    settings.setValue("Game/Current", "2");
    //admin_2.show();
    //this->close();
}

void AdminWindow::releaseGame(){
    searchWindow();
    int row = table->rowCount();
    table->setRowCount(row);
    table->insertRow(row);
    table->setRowHeight(row,25);

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
    QString input_name=ui->lineEdit_name->text();
    QString input_duration=ui->lineEdit_duration->text();
    QString input_place=ui->lineEdit_place->text();
    if(input_name.isEmpty() || input_duration.isEmpty() || input_place.isEmpty()){
       QMessageBox::about(this, tr("Tips"), tr("Input should not be empty."));
       searchWindow();
    }
    else{
    item1->setText(ui->comboBox_type->currentText());
    item2->setText(ui->lineEdit_name->text());
    item3->setText(ui->lineEdit_duration->text());
    item4->setText(ui->lineEdit_place->text());
    item5->setText(ui->comboBox_number->currentText());
    table->setItem(row, 0, item1);
    table->setItem(row, 1, item2);
    table->setItem(row, 2, item3);
    table->setItem(row, 3, item4);
    table->setItem(row, 4, item5);
    QMessageBox message(QMessageBox::Warning,"Warning","Really to release?",QMessageBox::Yes|QMessageBox::No,NULL);
    if (message.exec()==QMessageBox::Yes)
    {
       //qDebug()<<"clicked yes\n";
        saveGame();
        ui->lineEdit_duration->clear();
        ui->lineEdit_name->clear();
        ui->lineEdit_place->clear();
        searchWindow();
    }
    else
    {
        //qDebug()<<"clicked no\n";
        searchWindow();
    }
  }
}

void AdminWindow::searchWindow(){

    static QDialog *gameWindow = new QDialog;
    static QGridLayout *gridlayout = new QGridLayout;

    /*button_add = new QPushButton(this);
    button_add->setText("Add");*/
    button_delete  = new QPushButton(this);
    button_delete->setText("Delete");
    button_save = new QPushButton(this);
    button_save->setText("Save");

    connect(button_delete, &QPushButton::clicked, this, &AdminWindow::deleteRow);
    connect(button_save, &QPushButton::clicked, this, &AdminWindow::saveGame);

    table = new QTableWidget(0,5);
    QStringList colLabels;
    colLabels << "Type" << "Game" << "Duration" << "Place" << "Number";
    table->setHorizontalHeaderLabels(colLabels);

    for(int i = 0;i<database.games.size();i++){
        table->setRowCount(i+1);
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
        if(database.games[i].type == 1){
           item1->setText("Tamosi");
        }
        else{
           item1->setText("Track");
        }

        item1->setTextAlignment(Qt::AlignCenter);
        table->setItem(i, 0, item1);
        item2->setText(database.games[i].name);
        item2->setTextAlignment(Qt::AlignCenter);
        table->setItem(i, 1, item2);
        item3->setText(QString::number(database.games[i].duration));
        item3->setTextAlignment(Qt::AlignCenter);
        table->setItem(i, 2, item3);
        item4->setText(database.games[i].place);
        item4->setTextAlignment(Qt::AlignCenter);
        table->setItem(i, 3, item4);
        item5->setText(QString::number(database.games[i].number));
        item5->setTextAlignment(Qt::AlignCenter);
        table->setItem(i, 4, item5);
    }

    for(int i=0;i<database.games.size();i++){
        table->setRowHeight(i,25);
    }
    table->horizontalHeader()->setStretchLastSection(true);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setAlternatingRowColors(true);

    gridlayout->setColumnStretch(0,0);
    gridlayout->addWidget(table,0,0,1,5);
    gridlayout->addWidget(button_delete,1,0,1,1);
    gridlayout->addWidget(button_save,1,4,1,1);

    gameWindow->setLayout(gridlayout);

    gameWindow->resize(480,250);
    gameWindow->setWindowTitle("Game message");
    gameWindow->setGeometry(this->geometry().x()-480,(QApplication::desktop()->height()-gameWindow->height())/2,480,250);
    gameWindow->setWindowFlags(gameWindow->windowFlags()&~Qt::WindowMaximizeButtonHint);
    gameWindow->setWindowFlags(Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint);
    gameWindow->setFixedSize(gameWindow->width(), gameWindow->height());
    gameWindow->show();
}

void AdminWindow::deleteRow(){
    int rowIndex = table->currentRow();
    if (rowIndex != -1){
        table->removeRow(rowIndex);
    }
}

void AdminWindow::saveGame(){
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
         database.games.clear();            //qDebug()<<database.games.size();
         Game game;
         bool ok;
         for(int i=0; i<table->rowCount(); i++){
             game.type = table->item(i, 0)->text().toInt(&ok,10);
             game.name = table->item(i, 1)->text();
             game.duration = table->item(i, 2)->text().toInt(&ok,10);
             game.place = table->item(i, 3)->text();
             game.number = table->item(i, 4)->text().toInt(&ok,10);
             database.games.push_back(game);
         }
         //qDebug()<<database.games.size();
         DataProcess::saveGame();

     }else {
         QMessageBox::about(this, tr("Tips"), tr("Input can't be empty."));
     }
}
