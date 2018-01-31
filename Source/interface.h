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
    QPushButton *btnSender;
    QString btnObjectName;

    QVector<Buttons*> Btns;
    QVector<int> flagsPos;
    QVector<int> questionMarkPos;

    void setLayout();
    void setButtons(int, int, int);
    void getBtnInfo();

private slots:
    void markFlag();
};

#endif // INTERFACE_H
