#ifndef INTERFACE_H
#define INTERFACE_H

#include <QMainWindow>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "buttons.h"
#include "labels.h"
#include "timer.h"
#include "messagesboxes.h"

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
    MessagesBoxes setMsBox;
    int totalRows, totalCols;

    void setLayout();
    void setMenuBar();
    void startGame(int, int, int);
    void setButtons(int, int, int);
    void setLabels(int, int, int);
    void setBottomBar();
    void getBtnInfo();
    void showAll();
    void showTopBlankLbls(QString);
    void showBottomBlankLbls(QString);
    void showLeftBlankLbls(QString);
    void showRightBlankLbls(QString);
    void recoverMarkedBtns();
    void resetGame();

private slots:
    void markFlag();
    void showLabel();
    void playAgain();
    void easyMode();
    void mediumMode();
    void hardMode();
};

#endif // INTERFACE_H
