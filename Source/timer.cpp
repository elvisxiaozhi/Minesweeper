#include "timer.h"

Timer::Timer()
{
}

void Timer::setBottomBar(int totalMines, QWidget *mWidget)
{
//    int w, h;

//    timerIconLbl = new QLabel(mWidget);
//    QPixmap timerPixmap(":/timerLbl.ico");
//    timerIconLbl->setMaximumSize(50, 50);
//    timerIconLbl->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    w = timerIconLbl->width();
//    h = timerIconLbl->height();
//    timerIconLbl->setPixmap(timerPixmap.scaled(w, h, Qt::KeepAspectRatio));

    timerLbl = new QLabel(mWidget);
    timerLbl->setText(QString::number(0));
    timerLbl->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    timerLbl->setStyleSheet("background-color: #0041C2; color: white; qproperty-alignment: 'AlignCenter'; font: 30px;");

    minesLbl = new QLabel(mWidget);
    minesLbl->setText(QString::number(totalMines));
    minesLbl->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    minesLbl->setStyleSheet("background-color: #0041C2; color: white; qproperty-alignment: 'AlignCenter'; font: 30px;");

//    minesIconLbl = new QLabel(mWidget);
//    QPixmap minesPixmap(":/mine.ico");
//    minesIconLbl->setMinimumSize(50, 50);
//    minesIconLbl->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    w = minesIconLbl->width();
//    h = minesIconLbl->height();
//    minesIconLbl->setPixmap(minesPixmap.scaled(w, h, Qt::KeepAspectRatio));
//    connect(&mTimer, &Timer::sendTimerValue, this, &MainWindow::changeTimerValue);
}

void Timer::setTimer()
{
    runningTime = 0;
    startTimer = new QTimer();
    startTimer->start(1000);
    connect(startTimer, &QTimer::timeout, this, &Timer::updateDisplayTime);
}

void Timer::updateDisplayTime()
{
    runningTime++;
    timerLbl->setText(QString::number(runningTime));
}
