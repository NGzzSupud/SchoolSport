#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include "adminwindow.h"
#include "normalwindow.h"

namespace Ui {
class LoginWindowUi;
}

class LoginWindow : public QWidget
{
    Q_OBJECT
public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

signals:

private slots:
    void normalLogin();
    void managerLogin();

private:
    Ui::LoginWindowUi *ui;
    AdminWindow adminWin;
    NormalWindow normalWin;
    int Current;
};

#endif // LOGINWINDOW_H
