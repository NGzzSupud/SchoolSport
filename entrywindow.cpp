#define MAXGAME 20
#define MAXPLAYER 20
#include "entrywindow.h"
#include "ui_entrywindow.h"
#include <QDialog>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QFile>
#include <QDebug>
#include "dataprocess.h"
#include "algorithm/SportArithmetic.h"
extern DataProcess database;

int gamePlayerNum[MAXPLAYER];
int gamePlayer[MAXGAME][MAXPLAYER];

Entrywindow::Entrywindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Entrywindow)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags()&~Qt::WindowMaximizeButtonHint);
    this->setFixedSize(this->width(), this->height());
    this->move ((QApplication::desktop()->width() - this->width())/2,(QApplication::desktop()->height() - this->height())/2.25);

    grid = new QGridLayout;

    this->setLayout(grid);
    QLabel * label_select = new QLabel(this);
    label_select->setText("Selected Game:");
    label_select->setAlignment(Qt::AlignCenter);
    QLabel * label_gameName = new QLabel(this);
    label_gameName->setText("Game");
    label_gameName->setAlignment(Qt::AlignCenter);
    QPushButton * pushButton_timer = new QPushButton(this);
    QPushButton * pushButton_submit = new QPushButton(this);
    QPushButton * pushButton_complete= new QPushButton(this);
    pushButton_timer->setText("Game Table");
    pushButton_submit->setText("Submit");
    pushButton_complete->setText("complete");

    /*
    //Add rows and fill in data
    for(int i = 0; i < database.games.size(); i ++){
        //qDebug()<<games[i].id<<games[i].name<<games[i].date<<games[i].time<<games[i].place<<games[i].number;

        ui->tableWidget_game->setRowCount(i + 1);
        QTableWidgetItem *item1;
        item1 = new QTableWidgetItem;
        item1->setText(database.games[i].name);
        item1->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_game->setItem(i, 0, item1);

    }
    */
    grid->setVerticalSpacing(20);

    grid->setColumnStretch(0, 1);
    grid->setColumnStretch(1, 2);
    grid->setColumnStretch(2, 1);
    grid->setColumnStretch(3, 2);
    grid->setColumnStretch(4, 1);
    grid->setRowStretch(0, 1);
    grid->setRowStretch(1, 1);
    grid->setRowStretch(2, 1);
    grid->addWidget(label_select, 0, 1);
    grid->addWidget(label_gameName, 0, 2);
    grid->addWidget(pushButton_timer, 2, 1);
    grid->addWidget(pushButton_submit, 2, 2);
    grid->addWidget(pushButton_complete,2,3);

    label_select->setObjectName("label");
    label_gameName->setObjectName("label");
    pushButton_timer->setObjectName("button");
    pushButton_submit->setObjectName("button");
    pushButton_complete->setObjectName("button");

    connect(pushButton_timer,&QPushButton::clicked,this,&Entrywindow::displayGames);
    connect(pushButton_submit,&QPushButton::clicked,this,&Entrywindow::submit);
    connect(pushButton_complete,&QPushButton::clicked,this,&Entrywindow::complete);
}

Entrywindow::~Entrywindow()
{
    delete ui;
}


void Entrywindow::displayGames(){
    static QDialog *mainWindow = new QDialog;

    static QGridLayout *gridLayout = new QGridLayout;

    table = new QTableWidget(0,1);
    QStringList colLabels;
    colLabels << "Games";
    table->setHorizontalHeaderLabels(colLabels);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    for(int i=0;i<database.games.size();i++){
        //qDebug() << database.games[i].name;
        table->setRowCount(i + 1);
        QTableWidgetItem *item1;
        item1 = new QTableWidgetItem;
        item1->setText(database.games[i].name);
        //qDebug() << item1->text();
        item1->setTextAlignment(Qt::AlignCenter);
        table->setItem(i, 0, item1);
    }

    for(int i = 0; i < database.games.size(); i++)
        table->setRowHeight(i, 22);

    table->horizontalHeader()->setStretchLastSection(true);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setAlternatingRowColors(true);

    gridLayout->setColumnStretch(0, 0);
    //qDebug() <<"test";
    gridLayout->addWidget(table, 0, 0);

    mainWindow->setLayout(gridLayout);
    mainWindow->resize(450, 80 + database.games.size() * 22);
    mainWindow->setWindowTitle("Games Timer");
    mainWindow->setGeometry(this->geometry().x() - 450, (QApplication::desktop()->height() - mainWindow->height())/2, 450, 80 + database.games.size() * 22);
    mainWindow->setWindowFlags(mainWindow->windowFlags()&~Qt::WindowMaximizeButtonHint);
    mainWindow->setWindowFlags(Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint);
    mainWindow->setFixedSize(mainWindow->width(), mainWindow->height());
    mainWindow->show();

    connect(table, &QTableWidget::clicked, this, &Entrywindow::addLineEdit);
}

/*
 *  Change the number of lineEdits according to athletes's number.
 */
void Entrywindow::addLineEdit()
{

	for (int i = 1; i <= MAXGAME; i++)
	{
		gamePlayerNum[i] = 0;
		for (int j = 0; j<database.signups.size(); j++) {
			if (database.signups[j].game_id == i) {   //qDebug()<<"1";
				gamePlayer[i][gamePlayerNum[i]] = database.signups[j].student_id;
				gamePlayerNum[i]++;
				//sizeof(gamePlayer[i])/sizeof(int);
			}
		}
	}

    this->setFixedSize(460, 100 + gamePlayerNum[table->currentRow()] * 40);
    QList<QLabel*> labels = this->findChildren<QLabel*>("label");
    QList<QLineEdit*> lines = this->findChildren<QLineEdit*>("line");
    QList<QPushButton*> buttons = this->findChildren<QPushButton*>("button");

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

    foreach (QPushButton* button, buttons) {
        button->setParent(0);
        //qDebug()<<button->objectName();
        delete button;
    }

    //ui->label_game->setText(database.games[table->currentRow()].name);
    for(int i=0; i<gamePlayerNum[table->currentRow()]; i++){
        //qDebug()<<"changed";
        QLabel * label_name = new QLabel(this);
        label_name->setText(database.students[gamePlayer[table->currentRow()][i] - 1].name);
        label_name->setAlignment(Qt::AlignCenter);
        label_name->setObjectName("label");
        QLineEdit * lineEdit = new QLineEdit(this);
        //lineEdit->setText();
        lineEdit->setObjectName("line");
        grid->setRowStretch(i, 1);
        //grid->addWidget(label_name, i, 1, 1, 2);
        //grid->addWidget(lineEdit, i, 4, 1, 1);
        grid->addWidget(label_name, i+1, 1);
        grid->addWidget(lineEdit, i+1, 3);
    }
    //qDebug()<<"changed";
    QLabel * label_select = new QLabel(this);
    label_select->setText("Selected Game:");
    label_select->setAlignment(Qt::AlignCenter);
    label_select->setObjectName("label");
    QLabel * label_gameName = new QLabel(this);
    label_gameName->setText(database.games[table->currentRow()].name);
    label_gameName->setAlignment(Qt::AlignCenter);
    label_gameName->setObjectName("label");
    QPushButton * pushButton_timer = new QPushButton(this);
    QPushButton * pushButton_submit = new QPushButton(this);
    QPushButton * pushButton_complete= new QPushButton(this);
    pushButton_timer->setText("Game Table");
    pushButton_submit->setText("Submit");
    pushButton_complete->setText("complete");
    pushButton_timer->setObjectName("button");
    pushButton_submit->setObjectName("button");
    pushButton_complete->setObjectName("button");
    grid->addWidget(label_select, 0, 1);
    grid->addWidget(label_gameName, 0, 2);
    grid->addWidget(pushButton_timer, gamePlayerNum[table->currentRow()]+1, 1);
    grid->addWidget(pushButton_submit, gamePlayerNum[table->currentRow()]+1, 2);
    grid->addWidget(pushButton_complete,gamePlayerNum[table->currentRow()]+1,3);

    connect(pushButton_timer,&QPushButton::clicked,this,&Entrywindow::displayGames);
    connect(pushButton_submit,&QPushButton::clicked,this,&Entrywindow::submit);
    connect(pushButton_complete,&QPushButton::clicked,this,&Entrywindow::complete);
}

/*
 *  Submit and save the result.
 */
void Entrywindow::submit()
{
    //QList<QLineEdit*> lines = this->findChildren<QLineEdit*>("line");
	/*
    for(int i=0; i<lines.size(); i++){
        Result result;
        result.id = database.results.size() + 1;
        result.game_id = ui->tableWidget_game->currentRow() + 1;
        result.student_id = gamePlayer[ui->tableWidget_game->currentRow()][i];
        result.result = lines[i]->text();
        database.results.push_back(result);
    }

    DataProcess::saveResult();
	*/
}


/*
 *  Complete the game and calculate the result.
 */
void Entrywindow::complete()
{

}
