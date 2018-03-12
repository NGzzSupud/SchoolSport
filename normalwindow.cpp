#include "normalwindow.h"
#include "ui_normalwindow.h"
//#include <QMessageBox>
#include <QDialog>
#include <QLineEdit>
#include <QGridLayout>
#include <QLabel>
#include <QDesktopWidget>
#include <QFile>
#include <QDebug>
#include "dataprocess.h"
extern DataProcess database;

NormalWindow::NormalWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NormalWindowUi)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags()&~Qt::WindowMaximizeButtonHint);
    this->setFixedSize(this->width(), this->height());
    this->move ((QApplication::desktop()->width() - this->width())/2,(QApplication::desktop()->height() - this->height())/2);

    connect(ui->pushButton_timer,&QPushButton::clicked,this,&NormalWindow::displaySports);
    connect(ui->pushButton_submit,&QPushButton::clicked,this,&NormalWindow::submit);

}

NormalWindow::~NormalWindow()
{
    delete ui;
}

void NormalWindow::displaySports()
{
    static QDialog *mainWindow = new QDialog;

    static QGridLayout *gridLayout = new QGridLayout;

    //create a table
    table = new QTableWidget(0,3);
    QStringList colLabels;
    colLabels << "Game" << "Place" << "Number";
    table->setHorizontalHeaderLabels(colLabels);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //Add rows and fill in data

    for(int i = 0; i < database.games.size(); i ++){
        //qDebug()<<games[i].id<<games[i].name<<games[i].date<<games[i].time<<games[i].place<<games[i].number;

        table->setRowCount(i + 1);
        QTableWidgetItem *item1;
        QTableWidgetItem *item2;
        QTableWidgetItem *item3;
        item1 = new QTableWidgetItem;
        item2 = new QTableWidgetItem;
        item3 = new QTableWidgetItem;
        item1->setText(database.games[i].name);
        item1->setTextAlignment(Qt::AlignCenter);
        table->setItem(i, 0, item1);
        item2->setText(database.games[i].place);
        item2->setTextAlignment(Qt::AlignCenter);
        table->setItem(i, 1, item2);
        item3->setText(QString::number(database.games[i].number));
        item3->setTextAlignment(Qt::AlignCenter);
        table->setItem(i, 2, item3);
    }


    //Set the height of each row
    for(int i = 0; i < database.games.size(); i++)
        table->setRowHeight(i, 22);
    table->horizontalHeader()->setStretchLastSection(true);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setAlternatingRowColors(true);

    gridLayout->setColumnStretch(0, 0);
    gridLayout->addWidget(table, 0, 0);

    mainWindow->setLayout(gridLayout);

    mainWindow->resize(450, 80 + database.games.size() * 22);
    mainWindow->setWindowTitle("Games Timer");
    mainWindow->setGeometry(this->geometry().x() - 450, (QApplication::desktop()->height() - mainWindow->height())/2, 450, 80 + database.games.size() * 22);
    mainWindow->setWindowFlags(mainWindow->windowFlags()&~Qt::WindowMaximizeButtonHint);
    mainWindow->setWindowFlags(Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint);
    mainWindow->setFixedSize(mainWindow->width(), mainWindow->height());
    mainWindow->show();

    connect(table, &QTableWidget::clicked, this, &NormalWindow::addLineEdit);

}

void NormalWindow::addLineEdit()
{
    //qDebug()<<"changed";
    QList<QLabel*> labels = this->findChildren<QLabel*>("name");
    QList<QLineEdit*> lines = this->findChildren<QLineEdit*>("name");
    foreach(QLineEdit*line, lines)
    {
        line->setParent(0);
        //qDebug()<<line->objectName();
        delete line;
    }

    foreach (QLabel* label, labels) {
        label->setParent(0);
        //qDebug()<<label->objectName();
        delete label;
    }

    ui->label_game->setText(database.games[table->currentRow()].name);
    for(int i=0; i<database.games[table->currentRow()].number; i++){
        QLabel * label_name = new QLabel(this);
        label_name->setText("Name:");
        label_name->setObjectName("name");
        QLineEdit * lineEdit = new QLineEdit(this);
        lineEdit->setObjectName("name");
        ui->gridLayout_lineEdit->setColumnStretch(0, 0);
        ui->gridLayout_lineEdit->addWidget(label_name, i, 0);
        ui->gridLayout_lineEdit->addWidget(lineEdit, i, 1);
    }


}

void NormalWindow::submit()
{


}

