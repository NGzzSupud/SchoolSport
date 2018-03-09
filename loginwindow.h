#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>

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
};

#endif // LOGINWINDOW_H
