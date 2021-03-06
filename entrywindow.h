#ifndef ENTRYWINDOW_H
#define ENTRYWINDOW_H

#include <QDialog>
#include <QTableWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include "dataprocess.h"
#include "querywindow.h"

namespace Ui {
class Entrywindow;
}

class Entrywindow : public QDialog
{
    Q_OBJECT

public:
    explicit Entrywindow(QWidget *parent = nullptr);
    ~Entrywindow();

private slots:
    void addLineEdit();
    void complete();
    void displayGames();
    void submit();
private:
    Ui::Entrywindow *ui;
    QTableWidget *table;
    QGridLayout *grid;
    QueryWindow queryWin;
};

#endif // ENTRYWINDOW_H
