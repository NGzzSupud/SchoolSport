#include "mainwindow.h"
#include "loginwindow.h"
#include "adminwindow.h"
#include "normalwindow.h"
#include <QApplication>
#include <QDesktopWidget>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //LoginWindow loginWin;
    //loginWin.show();
    //loginWin.move ((QApplication::desktop()->width() - loginWin.width())/2,(QApplication::desktop()->height() - loginWin.height())/2);
    NormalWindow normalWin;
    normalWin.show();
    //AdminWindow adminWin;
    //adminWin.show();
    return a.exec();
}
