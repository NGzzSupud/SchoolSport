#include "adminwindow.h"
#include "ui_adminwindow.h"

#include <QDebug>
#include <QMessageBox>
#include <QSettings>
#include <QDesktopWidget>
#include <QDialog>
#include <QFile>
#include <QGridLayout>
#include <QTableWidget>
#include "dataprocess.h"
#include <QString>
#include "loginwindow.h"
#include "algorithm/fuck.h"
extern DataProcess database;

extern int sportPlace[20];
extern int sM[5][5][300];// placeAndSport[地点][日子][时间] = 运动名称
extern int sportTime[20]; // sportTime[比赛] = 时间

//int xiangmuTime[20]; //xiangmu[项目] = 时间
extern int xiangmu[20]; //项目人数统计 xiangmu[比赛项目] = 报名人数
extern int trueXiangmu[20];  //trueXiangmu[顺序] = 比赛项目
extern int deleteXiangmu[20];
extern People struct_people[300];


AdminWindow::AdminWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminWindowUi)
{
    ui->setupUi(this);
    this->move ((QApplication::desktop()->width() - this->width())/2,(QApplication::desktop()->height() - this->height())/2);
    this->setFixedSize(this->width(), this->height());

    connect(ui->pushButton_release,&QPushButton::clicked,this,&AdminWindow::releaseGame);
    connect(ui->pushButton_search,&QPushButton::clicked,this,&AdminWindow::searchWindow);
    connect(ui->pushButton_complete,&QPushButton::clicked,this,&AdminWindow::changeCurrent);
    ui->lineEdit_duration->setValidator(new QIntValidator(0,300,this));
}


AdminWindow::~AdminWindow()
{
    delete ui;
}

void AdminWindow::changeCurrent(){

    bool ok;
    for(int i=1; i<=database.games.size(); i++){
        sportPlace[i] = database.games[i-1].place;
        sportTime[i] = database.games[i-1].duration;
    }
    //qDebug()<<"jjj";

    for(int i=1; i<=database.signups.size(); i++){
        //qDebug()<<"jjj";
        if(database.games[database.signups[i-1].game_id - 1].type == 1){
            struct_people[database.signups[i-1].student_id].sport_one = database.signups[i-1].game_id;
        }else {
            struct_people[database.signups[i-1].student_id].sport_two = database.signups[i-1].game_id;
        }
    }
    //qDebug()<<"jjj";
    cel();
    for(int i = 0;i<299;i++)
    {
        celHaveSport(sportTime[struct_people[i].sport_one], sportTime[struct_people[i].sport_two], struct_people[i].sport_one, struct_people[i].sport_two);
    }
    //qDebug()<<"jjj";

    int finall_beginTime[5][20];
    int finall_endTime[5][20];
	int finall_placeAndSport[5][20] = { 0 };
    for(int i=0; i<5; i++){
		int time_flag = 0;
        for(int j=0; j<5; j++){
            for(int k=0; k<300; k++){
                if(sM[i][j][k] != 0){
                    int f_flag = sM[i][j][k];
					for (int z = k; z<300; z++) {
						if (sM[i][j][z] != f_flag) {
							finall_endTime[i][f_flag] = j * 1000 + z;
							break;
						}
					}
                    finall_beginTime[i][f_flag] = j*1000 + k;
					finall_placeAndSport[i][time_flag] = f_flag;
					time_flag++;
					break;
                }
            }
        }
    }

	QVector<Game> games;
	Game game;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			int index = finall_placeAndSport[i][j];
			if (index != 0) {
				game.id = games.size() + 1;
				game.name = database.games[index - 1].name; 
				game.duration = database.games[index - 1].duration;
				game.place = database.games[index - 1].place;
				game.date = finall_beginTime[game.place][index] / 1000;
				game.number = database.games[index - 1].number;
				//qDebug()<< QString::number(finall_beginTime[game.place][index] % 1000);
				game.time = QTime::QTime(8,0).addSecs(finall_beginTime[game.place][index] % 1000 * 60);
				//qDebug() << game.time;
				game.type = database.games[index - 1].type;
				games.push_back(game);
			}
		}
	}
	database.games.clear();
	for (int i = 1; i <= games.size(); i++) {
		game.id = i;
		game.name = games[i - 1].name;
		game.duration = games[i - 1].duration;
		game.date = games[i - 1].date;
		game.number = games[i - 1].number;
		game.place = games[i - 1].place;
		game.time = games[i - 1].time;
		game.type = games[i - 1].type;
		database.games.push_back(game);
	}

	//DataProcess::saveGame();

	QVector<Signup> signups;
	Signup signup;
	for (int i = 1; i <= database.signups.size(); i++) {
		if (struct_people[i].sport_one != 0) {
			signup.id = signups.size() + 1;
			signup.student_id = i;
			signup.game_id = struct_people[i].sport_one;
			signup.result = 0;
			signups.push_back(signup);
		}
		if (struct_people[i].sport_two != 0) {
			signup.id = signups.size() + 1;
			signup.student_id = i;
			signup.game_id = struct_people[i].sport_two;
			signup.result = 0;
			signups.push_back(signup);
		}
	}

	database.signups.clear();
	for (int i = 1; i <= signups.size(); i++) {
		signup.id = i;
		signup.student_id = signups[i - 1].student_id;
		signup.game_id = signups[i - 1].game_id;
		signup.result = signups[i - 1].result;
		database.signups.push_back(signup);
	}

	//DataProcess::saveSignup;

    /*
	 *	Jump to next window
	 */
    //QString configFilePath = "config.ini";
    //QSettings settings(configFilePath,QSettings::IniFormat);
    //settings.setValue("Game/Current", "2");
    adminWin_2.show();
    //this->close();
}

void AdminWindow::releaseGame(){

    searchWindow();
    int row = table->rowCount();
    table->setRowCount(row);
    table->insertRow(row);
    table->setRowHeight(row,25);

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
    QString input_name=ui->lineEdit_name->text();
    QString input_duration=ui->lineEdit_duration->text();
    QString input_place=ui->comboBox_place->currentText();
    if(input_name.isEmpty() || input_duration.isEmpty() || input_place.isEmpty()){
       QMessageBox::about(this, tr("Tips"), tr("Input should not be empty."));
       searchWindow();
    }
    else{
    item1->setText(ui->comboBox_type->currentText());
    item2->setText(ui->lineEdit_name->text());
    item3->setText(ui->lineEdit_duration->text());
    item4->setText(ui->comboBox_place->currentText());
    item5->setText(ui->comboBox_number->currentText());
    table->setItem(row, 0, item1);
    table->setItem(row, 1, item2);
    table->setItem(row, 2, item3);
    table->setItem(row, 3, item4);
    table->setItem(row, 4, item5);
    QMessageBox message(QMessageBox::Warning,"Warning","Really to release?",QMessageBox::Yes|QMessageBox::No,NULL);
    if (message.exec()==QMessageBox::Yes)
    {
        //qDebug()<<"clicked yes\n";
        saveGame();
        ui->lineEdit_duration->clear();
        ui->lineEdit_name->clear();
        ui->comboBox_place->setCurrentIndex(0);
        searchWindow();
    }
    else
    {
        //qDebug()<<"clicked no\n";
        searchWindow();
    }
  }
}

void AdminWindow::searchWindow(){

    static QDialog *gameWindow = new QDialog;
    static QGridLayout *gridlayout = new QGridLayout;

    /*button_add = new QPushButton(this);
    button_add->setText("Add");*/
    button_delete  = new QPushButton(this);
    button_delete->setText("Delete");
    button_save = new QPushButton(this);
    button_save->setText("Save");

    connect(button_delete, &QPushButton::clicked, this, &AdminWindow::deleteRow);
    connect(button_save, &QPushButton::clicked, this, &AdminWindow::saveGame);

    table = new QTableWidget(0,5);
    QStringList colLabels;
    colLabels << "Type" << "Game" << "Duration" << "Place" << "Number";
    table->setHorizontalHeaderLabels(colLabels);

    for(int i = 0;i<database.games.size();i++){
        table->setRowCount(i+1);
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
        if(database.games[i].type == 1){
           item1->setText("Tamosi");
        }
        else{
           item1->setText("Track");
        }

        item1->setTextAlignment(Qt::AlignCenter);
        table->setItem(i, 0, item1);
        item2->setText(database.games[i].name);
        item2->setTextAlignment(Qt::AlignCenter);
        table->setItem(i, 1, item2);
        item3->setText(QString::number(database.games[i].duration));
        item3->setTextAlignment(Qt::AlignCenter);
        table->setItem(i, 2, item3);
        QString configFilePath = "config.ini";
        QSettings settings(configFilePath,QSettings::IniFormat);
        QString place = settings.value("Place/" + database.games[i].place).toString();
        item4->setText(place);
        item4->setTextAlignment(Qt::AlignCenter);
        table->setItem(i, 3, item4);
        item5->setText(QString::number(database.games[i].number));
        item5->setTextAlignment(Qt::AlignCenter);
        table->setItem(i, 4, item5);
    }

    for(int i=0;i<database.games.size();i++){
        table->setRowHeight(i,25);
    }
    table->horizontalHeader()->setStretchLastSection(true);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setAlternatingRowColors(true);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    gridlayout->setColumnStretch(0,0);
    gridlayout->addWidget(table,0,0,1,5);
    gridlayout->addWidget(button_delete,1,0,1,1);
    gridlayout->addWidget(button_save,1,4,1,1);

    gameWindow->setLayout(gridlayout);

    gameWindow->resize(480,250);
    gameWindow->setWindowTitle("Game message");
    gameWindow->setGeometry(this->geometry().x()-480,(QApplication::desktop()->height()-gameWindow->height())/2,480,250);
    gameWindow->setWindowFlags(gameWindow->windowFlags()&~Qt::WindowMaximizeButtonHint);
    gameWindow->setWindowFlags(Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint);
    gameWindow->setFixedSize(gameWindow->width(), gameWindow->height());
    gameWindow->show();
}

void AdminWindow::deleteRow(){
    int rowIndex = table->currentRow();
    if (rowIndex != -1){
        table->removeRow(rowIndex);
    }
}

void AdminWindow::saveGame(){
    //qDebug()<<"save";
    bool flag = true;
    for(int i=0; i<table->rowCount(); i++){
        if(table->item(i, 0)->text().isEmpty()||table->item(i, 1)->text().isEmpty()){
            //qDebug()<<table->item(i, 0)->text();
            //qDebug()<<table->item(i, 1)->text();
            flag = false;
            break;
        }
     }
     if(flag){
         //qDebug()<<"clear";
         database.games.clear();            //qDebug()<<database.games.size();
         Game game;
         bool ok;
         for(int i=0; i<table->rowCount(); i++){
             game.id = i + 1;
             game.type = table->item(i, 0)->text().toInt(&ok,10);
             game.name = table->item(i, 1)->text();
             game.duration = table->item(i, 2)->text().toInt(&ok,10);
             QString configFilePath = "config.ini";
             QSettings settings(configFilePath,QSettings::IniFormat);
             QString place = settings.value("Place/" + table->item(i, 3)->text()).toString();
             game.place = place.toInt(&ok, 10);
             game.number = table->item(i, 4)->text().toInt(&ok,10);
             database.games.push_back(game);
         }
         //qDebug()<<database.games.size();
         DataProcess::saveGame();

     }else {
         QMessageBox::about(this, tr("Tips"), tr("Input can't be empty."));
     }
}
