#include "normalwindow.h"
#include "ui_normalwindow.h"

NormalWindow::NormalWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NormalWindowUi)
{
    ui->setupUi(this);
}

NormalWindow::~NormalWindow()
{

}
