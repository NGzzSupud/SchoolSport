#ifndef ENTRYWINDOW_H
#define ENTRYWINDOW_H

#include <QDialog>
#include <QTableWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include "dataprocess.h"

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
    void save();
    void complete();


private:
    Ui::Entrywindow *ui;
};

#endif // ENTRYWINDOW_H
