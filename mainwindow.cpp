#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSettings>
#include "loginwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_start,&QPushButton::clicked,this,&MainWindow::changeCurrent);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeCurrent(){
    //qDebug()<<
    QString configFilePath = "config.ini";
    QSettings settings(configFilePath,QSettings::IniFormat);
    settings.setValue("Game/Current", "1");
    adminWin_1.show();
    this->close();
}
