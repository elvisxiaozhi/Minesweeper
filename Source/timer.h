#ifndef TIMER_H
#define TIMER_H

#include <QLabel>
#include <QTimer>

class Timer : public QObject
{
    Q_OBJECT
public:
    Timer();

    QLabel *timerLbl;
    QLabel *timerIconLbl;
    QLabel *minesLbl;
    QLabel *minesIconLbl;
    int runningTime;
    QTimer *startTimer;

    void setBottomBar(int, QWidget *);
    void setTimer();

private slots:
    void updateDisplayTime();
};

#endif // TIMER_H
