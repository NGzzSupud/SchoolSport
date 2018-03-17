#ifndef ENTRYWINDOW_H
#define ENTRYWINDOW_H

#include <QDialog>

namespace Ui {
class Entrywindow;
}

class Entrywindow : public QDialog
{
    Q_OBJECT

public:
    explicit Entrywindow(QWidget *parent = 0);
    ~Entrywindow();

private:
    Ui::Entrywindow *ui;
};

#endif // ENTRYWINDOW_H
