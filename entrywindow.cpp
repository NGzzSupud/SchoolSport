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
#include <QSettings>
#include <QDebug>
#include "dataprocess.h"
#include "algorithm/SportArithmetic.h"
extern DataProcess database;

int gamePlayerNum[MAXPLAYER];
int gamePlayer[MAXGAME][MAXPLAYER];
int scorePlayer[MAXGAME][MAXPLAYER];

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



	for (int i = 1; i <= database.games.size(); i++)
	{
		gamePlayerNum[i] = 0;
		for (int j = 0; j<database.signups.size(); j++) {
			if (database.signups[j].game_id == database.games[i - 1].id) {   //qDebug()<<"1";
				gamePlayer[i][gamePlayerNum[i]] = database.signups[j].student_id;
				scorePlayer[i][gamePlayerNum[i]] = database.signups[j].result;
				gamePlayerNum[i]++;
				//sizeof(gamePlayer[i])/sizeof(int);
			}
		}
	}

}

/*
 *  Change the number of lineEdits according to athletes's number.
 */
void Entrywindow::addLineEdit()
{

    this->setFixedSize(460, 100 + gamePlayerNum[table->currentRow() + 1] * 40);
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
    for(int i=0; i<gamePlayerNum[table->currentRow() + 1]; i++){
        qDebug()<<i<<"changed";
        QLabel * label_name = new QLabel(this);
        label_name->setText(database.students[gamePlayer[table->currentRow() + 1][i] - 1].name);
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
    grid->addWidget(pushButton_timer, gamePlayerNum[table->currentRow() + 1] + 1, 1);
    grid->addWidget(pushButton_submit, gamePlayerNum[table->currentRow() + 1] + 1, 2);
    grid->addWidget(pushButton_complete,gamePlayerNum[table->currentRow() + 1] + 1,3);
    connect(pushButton_timer,&QPushButton::clicked,this,&Entrywindow::displayGames);
    connect(pushButton_submit,&QPushButton::clicked,this,&Entrywindow::submit);
    connect(pushButton_complete,&QPushButton::clicked,this,&Entrywindow::complete);
}

/*
 *  Save the result and calculate the score.
 */
void Entrywindow::submit()
{
    QList<QLineEdit*> lines = this->findChildren<QLineEdit*>("line");

	SortPlace results[MAXPLAYER];

	QString configFilePath = "config.ini";
	QSettings settings(configFilePath, QSettings::IniFormat);
	QString rankName[5] = { "Champion", "Runner-up", "Third", "Fourth", "Fifth" };
	int score[5];
	for (int i = 0; i < 5; i++) {
		score[i] = settings.value("Rank/" + rankName[i]).toInt();
	}

	bool flag = true;
    foreach (QLineEdit *line , lines){
		if (line->text().isEmpty()) {
			flag = false;
		}
	}
	if (flag) {

		for (int i = 0; i<lines.size(); i++) {
			double result = lines[i]->text().toDouble();
			int id = gamePlayer[table->currentRow() + 1][i];
			for (int j = 0; j<database.signups.size(); j++) {
				if (database.signups[j].student_id == id && database.signups[j].game_id == database.games[table->currentRow()].id) {
					database.signups[j].result = result;
					results[i].studentID = id;
					results[i].score = result;
					scorePlayer[table->currentRow() + 1][i] = result;
				}
			}
		}

		Calculate cal;
		if (database.games[table->currentRow()].type == 1) {
			cal.toSmall(results, gamePlayerNum[table->currentRow() + 1]);
		}
		else {
			cal.toBig(results, gamePlayerNum[table->currentRow() + 1]);
		}

		int index;
		if (DataProcess::resultIsExist(database.games[table->currentRow()].id) != -1) {

			QMessageBox::about(this, tr("Tips"), tr("This game already had a result."));
			/*
			index = DataProcess::resultIsExist(database.games[table->currentRow()].id);
			database.results[index - 1].number;
			database.results[index - 1].students.clear;
			for (int i = 0; i < database.results[index - 1].number; i++) {
				database.results[index - 1].students.push_back(results[i].studentID);
			}
			*/
		}
		else
		{
			index = database.results.size() + 1;
			Result result;
			result.id = index;
			result.game_id = database.games[table->currentRow()].id;
			result.number = gamePlayerNum[table->currentRow() + 1];
			for (int i = 0; i < result.number; i++) {
				result.students.push_back(results[i].studentID);
			}
			database.results.push_back(result);

			for (int j = 0; j < 5; j++) {
				database.students[results[j].studentID - 1].score += score[j];
			}

		}

		//DataProcess::saveSignup();
		//DataProcess::saveResult();
		//DataProcess::saveStudent();

	}
	else
	{
		QMessageBox::about(this, tr("Tips"), tr("Input can't be empty."));
	}
}


/*
 *  Complete the game.
 */
void Entrywindow::complete()
{
    queryWin.show();
}
