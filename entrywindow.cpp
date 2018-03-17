#include "entrywindow.h"
#include "ui_entrywindow.h"

Entrywindow::Entrywindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Entrywindow)
{
    ui->setupUi(this);
}

Entrywindow::~Entrywindow()
{
    delete ui;
}
