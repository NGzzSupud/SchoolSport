#include "normalwindow.h"
#include "ui_normalwindow.h"
//#include <QMessageBox>
#include <QDialog>
#include <QTextEdit>
#include <QGridLayout>
#include <QDesktopWidget>
#include <QFile>
#include <QDebug>

NormalWindow::NormalWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NormalWindowUi)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags()&~Qt::WindowMaximizeButtonHint);
    this->move ((QApplication::desktop()->width() - this->width())/2,(QApplication::desktop()->height() - this->height())/2);

    QFile file("Game.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
           qDebug()<<"Can't open the file!"<<endl;
    }

    QString content;
    //Add items into combobox
    while(!file.atEnd()){
        QByteArray line = file.readLine();
        QString str(line);
        content = str.section("|", 0, 0);

        ui->comboBox_sports->addItem(content);
    }

    //Close file
    file.close();

    connect(ui->pushButton_timer,&QPushButton::clicked,this,&NormalWindow::displaySports);
    connect(ui->pushButton_submit,&QPushButton::clicked,this,&NormalWindow::submit);
}

NormalWindow::~NormalWindow()
{
    delete ui;
}

void NormalWindow::displaySports(){

    static QDialog *mainWindow = new QDialog;

    static QGridLayout *gridLayout = new QGridLayout;

    //Read in game file.

    QFile file("Game.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
           qDebug()<<"Can't open the file!"<<endl;
    }

    //create a table
    QTableWidget *table = new QTableWidget(0,3);
    QStringList colLabels;
    colLabels << "Game" << "Time" << "Place";
    table->setHorizontalHeaderLabels(colLabels);

    //Add rows and fill in data
    int rows = 0;
    while(!file.atEnd()){
        QByteArray line = file.readLine();
        QString str(line);
        rows ++;

        QString content;
        table->setRowCount(rows);
        QTableWidgetItem *newRows = new QTableWidgetItem(QString("%1").arg(rows));
        table->setVerticalHeaderItem(rows - 1, newRows);

        QTableWidgetItem *item;

        for(int i = 0; i < 3; i ++){
            item = new QTableWidgetItem;
            content = str.section("|", i, i);
            item->setText(content);
            table->setItem(rows - 1, i, item);
        }

    }

    //Close file
    file.close();

    //Set the height of each row
    for(int i = 0; i < rows; i++)
        table->setRowHeight(i, 22);
    table->horizontalHeader()->setStretchLastSection(true);

    gridLayout->setColumnStretch(0, 0);
    gridLayout->addWidget(table, 0, 0);

    mainWindow->setLayout(gridLayout);

    mainWindow->resize(400, 45 + rows * 22);
    mainWindow->setGeometry(this->geometry().x() - 400, (QApplication::desktop()->height() - mainWindow->height())/2, 400, 45 + rows * 22);
    mainWindow->setWindowFlags(mainWindow->windowFlags()&~Qt::WindowMaximizeButtonHint);
    mainWindow->setWindowTitle(QWidget::tr("Game timer"));
    mainWindow->show();

}


void NormalWindow::submit(){


}

