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
    this->setFixedSize(this->width(), this->height());
    connect(ui->pushButton_release,&QPushButton::clicked,this,&AdminWindow::changeCurrent);
}


AdminWindow::~AdminWindow()
{
    delete ui;
}

void AdminWindow::changeCurrent(){
    QString configFilePath = "config.ini";
    QSettings settings(configFilePath,QSettings::IniFormat);
    settings.setValue("Game/Current", "2");
}
