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
    void setCollege(QString college);
    QString getCollege();

signals:

private slots:
    void displaySports();
    void submit();

private:
    Ui::NormalWindowUi *ui;
    QVector<Game> games;
    QString College;
};

#endif // NORMALWINDOW_H
