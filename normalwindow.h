#ifndef NORMALWINDOW_H
#define NORMALWINDOW_H

#include <QWidget>

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

public slots:

private:
    Ui::NormalWindowUi *ui;
};

#endif // NORMALWINDOW_H
