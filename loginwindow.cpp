#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "adminwindow.h"
#include "normalwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QSettings>
#include "dataprocess.h"
extern DataProcess database;

LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindowUi)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags()&~Qt::WindowMaximizeButtonHint);
    this->setFixedSize(this->width(), this->height());
    ui->lineEdit_password->setEchoMode(QLineEdit::Password);

    //Readin config file
    QString configFilePath = "config.ini";
    QSettings settings(configFilePath,QSettings::IniFormat);

    Current = settings.value("Game/Current").toInt();

    if(Current < -1 || Current == 0 || Current > 3){
        settings.setValue("Game/Current", "-1");
    }
    //bind action and function
    connect(ui->pushButton_normal, &QPushButton::clicked, this, &LoginWindow::normalLogin);
    connect(ui->pushButton_manager, &QPushButton::clicked, this, &LoginWindow::managerLogin);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::normalLogin()
{
    QString college = ui->lineEdit_college->text();
    QString code = ui->lineEdit_code->text();

    if(!college.isEmpty() && !code.isEmpty()){
        int position;
        //Authenticate college and inviteCode
        if(Current == -1){
            QMessageBox::about(this, tr("Tips"), tr("No game now."));
        }else {
            bool flag = false;
            for(int i=1; i<=database.colleges.size(); i ++){
                //qDebug()<<database.colleges[i].name<<" == "<<college;
                if(!college.compare(database.colleges[i - 1].name)){
                    flag = true;
                    position = i;
                }
            }
            if(flag){
                if(!code.compare(database.colleges[position - 1].code)){
                    //Login successfully
                    normalWin.show();
                    normalWin.college = position;
                    this->close();
                }else{
                    //Wrong code
                    QMessageBox::about(this, tr("Tips"), tr("The code is wrong."));
                }
            }else {
                //Wrong college
                QMessageBox::about(this, tr("Tips"), tr("There is no this college."));
            }
        }
    }else{
        QMessageBox::about(this, tr("Tips"), tr("Input should not be empty."));
    }
}

void LoginWindow::managerLogin()
{
    QString account = ui->lineEdit_account->text();
    QString password = ui->lineEdit_password->text();

    if(account != "" && password != ""){

        //Authenticate account and password
        QString configFilePath = "config.ini";
        QSettings settings(configFilePath,QSettings::IniFormat);
        QString auth = settings.value("Manager/" + account).toString();

        if(!password.compare(auth)){
            //Login successfully
            jumpWindow(Current);
            this->close();
        }else{
            //Login failed
            QMessageBox::about(this, tr("Tips"), tr("Login failed. Please check your account and password."));
        }
    }else{
        QMessageBox::about(this, tr("Tips"), tr("Input should not be empty."));
    }

}

void LoginWindow::jumpWindow(int flag){
    switch (flag) {
    case -1:
        beginWin.show();
        break;
    case 1:
        adminWin_1.show();
        break;
    case 2:
        adminWin_2.show();
        break;
    default:
        break;
    }
}
