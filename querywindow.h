#ifndef QUERYWINDOW_H
#define QUERYWINDOW_H

#include <QWidget>
#include <QTableWidget>

namespace Ui {
class QueryWindow;
}

class QueryWindow : public QWidget
{
    Q_OBJECT

public:
    explicit QueryWindow(QWidget *parent = 0);
    ~QueryWindow();

private slots:
    void displayGame();
    void displayCollege();

private:
    Ui::QueryWindow *ui;
    QTableWidget *table;
};

#endif // QUERYWINDOW_H
