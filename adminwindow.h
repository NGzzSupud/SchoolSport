#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QDialog>
#include "entrywindow.h"

namespace Ui {
class AdminWindowUi;
}

class AdminWindow : public QWidget
{
    Q_OBJECT
public:
    explicit AdminWindow(QWidget *parent = nullptr);
    ~AdminWindow();

signals:

public slots:
    void searchWindow();
    void deleteRow();
    void saveGame();

private:
    Ui::AdminWindowUi *ui;
    void changeCurrent();
    void releaseGame();
    QTableWidget *table;
    QPushButton *button_delete;
    QPushButton *button_save;
    Entrywindow adminWin_2;
};

#endif // ADMINWINDOW_H
