#include "adminwindow.h"
#include "ui_adminwindow.h"

#include <QDebug>
#include <QMessageBox>
#include <QSettings>
#include <QDesktopWidget>

AdminWindow::AdminWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminWindowUi)
{
    ui->setupUi(this);
    this->move ((QApplication::desktop()->width() - this->width())/2,(QApplication::desktop()->height() - this->height())/2);

    //Readin config file
    QString configFilePath = "config.ini";
    QSettings settings(configFilePath,QSettings::IniFormat);

    int Current = settings.value("Game/Current").toInt();

    if(Current < -1 || Current == 0 || Current > 5){
        settings.setValue("Game/Current", "-1");
    }

    display(Current);
}


AdminWindow::~AdminWindow()
{
    delete ui;
}

void AdminWindow::display(int mode)
{

    basPotBtn = new QPushButton();
    basPotBtn->setText("a2s1d32a");
    basPotBtn->setGeometry(0, 21, 20, 50);
    /*switch (mode) {
    case value:-1;

        break;
    case value:1;

        break;
    case value:2;

        break;
    case value:3;

        break;
    case value:4;

        break;
    case value:5;

        break;
    default:
        break;
    }*/
}
