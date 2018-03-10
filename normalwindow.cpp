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
    this->setFixedSize(this->width(), this->height());
    this->move ((QApplication::desktop()->width() - this->width())/2,(QApplication::desktop()->height() - this->height())/2);

    Game game;
    int rows = 0;

    QFile file("Game.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
           qDebug()<<"Can't open the file!"<<endl;
    }

    //Add items into combobox
    while(!file.atEnd()){
        QByteArray line = file.readLine();
        QString str(line);
        //qDebug()<<str;
        if(str != "\n"){
            rows ++;
            bool ok;
            game.id = rows;
            game.name = str.section("|", 0, 0);
            game.date = QDate::fromString(str.section("|", 1, 1), "yyyy-MM-dd");
            game.time = QTime::fromString(str.section("|", 2, 2), "mm:ss");
            game.place = str.section("|", 3, 3);
            game.number = str.section("|", 4, 4).toInt(&ok, 10);

            games.push_back(game);
            ui->comboBox_sports->addItem(game.name);
        }
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

void NormalWindow::setCollege(QString college)
{
    this->College = college;
}

QString NormalWindow::getCollege()
{
    return this->College;
}


void NormalWindow::displaySports()
{
    static QDialog *mainWindow = new QDialog;

    static QGridLayout *gridLayout = new QGridLayout;

    //Read in game file.

    QFile file("Game.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
           qDebug()<<"Can't open the file!"<<endl;
    }

    //create a table
    QTableWidget *table = new QTableWidget(0,5);
    QStringList colLabels;
    colLabels << "Game" << "Date" << "Time" << "Place" << "Number";
    table->setHorizontalHeaderLabels(colLabels);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //Add rows and fill in data
    for(int i = 0; i < games.size(); i ++){
        //qDebug()<<games[i].id<<games[i].name<<games[i].date<<games[i].time<<games[i].place<<games[i].number;

        table->setRowCount(i + 1);
        QTableWidgetItem *item1;
        QTableWidgetItem *item2;
        QTableWidgetItem *item3;
        QTableWidgetItem *item4;
        QTableWidgetItem *item5;
        item1 = new QTableWidgetItem;
        item2 = new QTableWidgetItem;
        item3 = new QTableWidgetItem;
        item4 = new QTableWidgetItem;
        item5 = new QTableWidgetItem;
        item1->setText(games[i].name);
        item1->setTextAlignment(Qt::AlignCenter);
        table->setItem(i, 0, item1);
        item2->setText(games[i].date.toString("yyyy-MM-dd"));
        item2->setTextAlignment(Qt::AlignCenter);
        table->setItem(i, 1, item2);
        item3->setText(games[i].time.toString("mm:ss"));
        item3->setTextAlignment(Qt::AlignCenter);
        table->setItem(i, 2, item3);
        item4->setText(games[i].place);
        item4->setTextAlignment(Qt::AlignCenter);
        table->setItem(i, 3, item4);
        item5->setText(QString::number(games[i].number));
        item5->setTextAlignment(Qt::AlignCenter);
        table->setItem(i, 4, item5);
    }

    //Set the height of each row
    for(int i = 0; i < games.size(); i++)
        table->setRowHeight(i, 22);
    table->horizontalHeader()->setStretchLastSection(true);

    gridLayout->setColumnStretch(0, 0);
    gridLayout->addWidget(table, 0, 0);

    mainWindow->setLayout(gridLayout);

    mainWindow->resize(680, 80 + games.size() * 22);
    mainWindow->setWindowTitle(getCollege() + " Games Timer");
    mainWindow->setGeometry(this->geometry().x() - 680, (QApplication::desktop()->height() - mainWindow->height())/2, 680, 80 + games.size() * 22);
    mainWindow->setWindowFlags(mainWindow->windowFlags()&~Qt::WindowMaximizeButtonHint);
    mainWindow->setWindowFlags(Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint);
    mainWindow->setFixedSize(mainWindow->width(), mainWindow->height());
    mainWindow->show();

}


void NormalWindow::submit(){


}

