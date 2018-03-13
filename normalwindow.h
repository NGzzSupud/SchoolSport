#ifndef NORMALWINDOW_H
#define NORMALWINDOW_H

#include <QWidget>
#include <QTableWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include "dataprocess.h"

namespace Ui {
class NormalWindowUi;
}

class NormalWindow : public QWidget
{
    Q_OBJECT
public:
    explicit NormalWindow(QWidget *parent = nullptr);
    ~NormalWindow();
    int college;

signals:

private slots:
    void displaySports();
    void addLineEdit();
    void submit();

private:
    Ui::NormalWindowUi *ui;
    QTableWidget *table;
    QGridLayout *grid;
};

#endif // NORMALWINDOW_H
