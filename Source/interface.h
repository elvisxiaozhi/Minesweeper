#ifndef INTERFACE_H
#define INTERFACE_H

#include <QMainWindow>
#include <QGridLayout>
#include "buttons.h"

class Interface : public QMainWindow
{
    Q_OBJECT

public:
    Interface(QWidget *parent = 0);
    ~Interface();

private:
    QWidget *basicLayout;
    QGridLayout *btnGLayout;

    QVector<Buttons*> Btns;

    void setLayout();
    void setButtons(int, int, int);
};

#endif // INTERFACE_H
