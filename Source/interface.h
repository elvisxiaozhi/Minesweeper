#ifndef INTERFACE_H
#define INTERFACE_H

#include <QMainWindow>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "buttons.h"
#include "labels.h"
#include "timer.h"

class Interface : public QMainWindow
{
    Q_OBJECT

public:
    Interface(QWidget *parent = 0);
    ~Interface();

private:
    QWidget *basicLayout;
    QGridLayout *btnGLayout;
    QVBoxLayout *vLayout;
    QHBoxLayout *hLayout;
    QPushButton *btnSender;
    QString btnObjectName;

    QVector<Buttons*> Btns;
    QVector<int> flagsPos;
    QVector<int> questionMarkPos;

    Labels Lbls;
    Timer setTimer;

    void setLayout();
    void setButtons(int, int, int);
    void setLabels(int, int, int);
    void setBottomBar();
    void getBtnInfo();

private slots:
    void markFlag();
    void showLabel();
};

#endif // INTERFACE_H
