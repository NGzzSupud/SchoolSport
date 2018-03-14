#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QTableWidget>

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
    void addRow();
    void deleteRow();
    void saveGame();
private:
    Ui::AdminWindowUi *ui;
    void changeCurrent();
    QTableWidget *table;
};

#endif // ADMINWINDOW_H
