#include "normalwindow.h"
#include "ui_normalwindow.h"
//#include <QMessageBox>
#include <QDialog>


NormalWindow::NormalWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NormalWindowUi)
{
    ui->setupUi(this);
    connect(ui->pushButton_timer,&QPushButton::clicked,this,&NormalWindow::clickButton);
}

NormalWindow::~NormalWindow()
{
    delete ui;
}

void NormalWindow::clickButton(){
   //赛程的点击事件
   //QMessageBox::about(this,tr("提示信息"),tr("更新成功"));

    QDialog dialog;
    dialog.setModal(true);
    dialog.exec();
}

