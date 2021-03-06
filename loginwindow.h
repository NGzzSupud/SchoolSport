#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include "adminwindow.h"
#include "normalwindow.h"
#include "mainwindow.h"
#include "adminwindow.h"
#include "entrywindow.h"
#include "querywindow.h"

namespace Ui {
class LoginWindowUi;
}

class LoginWindow : public QWidget
{
    Q_OBJECT
public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();


private slots:
    void normalLogin();
    void managerLogin();
    void jumpWindow(int flag);

private:
    Ui::LoginWindowUi *ui;
    NormalWindow normalWin;
    MainWindow beginWin;
    AdminWindow adminWin_1;
    Entrywindow adminWin_2;
    QueryWindow queryWin;
  //SignupWindow adminWin_2;
    int Current;
};

#endif // LOGINWINDOW_H
