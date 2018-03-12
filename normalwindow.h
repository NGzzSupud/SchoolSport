#ifndef NORMALWINDOW_H
#define NORMALWINDOW_H

#include <QWidget>
#include <QTableWidget>
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

signals:

private slots:
    void displaySports();
    void addLineEdit();
    void submit();

private:
    Ui::NormalWindowUi *ui;
    QTableWidget *table;
};

#endif // NORMALWINDOW_H
