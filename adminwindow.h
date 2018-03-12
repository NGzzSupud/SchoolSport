#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QWidget>
#include <QPushButton>

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

private:
    Ui::AdminWindowUi *ui;
    void changeCurrent();
};

#endif // ADMINWINDOW_H
