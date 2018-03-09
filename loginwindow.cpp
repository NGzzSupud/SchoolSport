#include "loginwindow.h"
#include "ui_loginwindow.h"


LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindowUi)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags()&~Qt::WindowMaximizeButtonHint);
    connect(ui->pushButton_normal, &QPushButton::clicked, this, &LoginWindow::normalLogin);
    connect(ui->pushButton_manager, &QPushButton::clicked, this, &LoginWindow::managerLogin);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::normalLogin()
{

}

void LoginWindow::managerLogin()
{

}
