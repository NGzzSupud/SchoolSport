#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include "adminwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void changeCurrent();
    void manageCollege();
    void addRow();
    void deleteRow();
    void saveCollege();

private:
    Ui::MainWindow *ui;
    AdminWindow adminWin_1;
    QTableWidget *table;
    QPushButton * button_add;
    QPushButton * button_delete;
    QPushButton * button_save;
};

#endif // MAINWINDOW_H
