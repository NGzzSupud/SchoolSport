#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "adminwindow.h"
#include "normalwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QSettings>


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

    if(Current < -1 || Current == 0 || Current > 5){
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

    if(college != "" && code != ""){

        //Authenticate inviteCode
        if(Current == 1){
            QMessageBox::about(this, tr("Tips"), tr("No game now."));
        }else {
            QString configFilePath = "config.ini";
            QSettings settings(configFilePath,QSettings::IniFormat);
            QString auth = settings.value("InviteCode/" + college).toString();
            if(!code.compare(auth)){
                //Login successfully
                normalWin.setCollege(college);
                normalWin.show();
                this->close();
            }else{
                //Login failed
                QMessageBox::about(this, tr("Tips"), tr("Login failed."));
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
            adminWin.show();
            this->close();
        }else{
            //Login failed
            QMessageBox::about(this, tr("Tips"), tr("Login failed. Please check your account and password."));
        }
    }else{
        QMessageBox::about(this, tr("Tips"), tr("Input should not be empty."));
    }

}
