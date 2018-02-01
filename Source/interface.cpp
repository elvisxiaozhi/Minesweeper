#include "interface.h"
#include <QDebug>

Interface::Interface(QWidget *parent)
    : QMainWindow(parent)
{
    setLayout();
}

Interface::~Interface()
{

}

void Interface::setLayout()
{
    setWindowTitle("Minesweeper");

    basicLayout = new QWidget(this);
    setCentralWidget(basicLayout);

    setButtons(81, 9, 9);
    setLabels(81, 9, 9);
    Lbls.generatedMines.generateMines(10, 81);
    Lbls.setLblNotation(81, 9, 9);
    Lbls.setMineIcon();
    Lbls.setLblsStyleSheet(81);

    basicLayout->setLayout(btnGLayout);
}

void Interface::setButtons(int totalBtns, int rows, int cols)
{
    btnGLayout = new QGridLayout(basicLayout);
    btnGLayout->setSpacing(0);

    Btns.resize(totalBtns);

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            Btns[i * cols + j] = new Buttons();
            Btns[i * cols + j]->setObjectName(QString::number(i * cols + j));
            Btns[i * cols + j]->setMinimumSize(50, 50);
            Btns[i * cols + j]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            btnGLayout->addWidget(Btns[i * cols + j], i, j);
            connect(Btns[i * cols + j], &Buttons::clicked, this, &Interface::showLabel);
            connect(Btns[i * cols + j], &Buttons::btnRightClicked, this, &Interface::markFlag);
        }
    }
}

void Interface::setLabels(int totalLbls, int rows, int cols)
{
    Lbls.labels.resize(totalLbls);

    for(int i = 0; i < rows; i ++) {
        for(int j = 0; j < cols; j++) {
            Lbls.labels[i * cols + j] = new QLabel(basicLayout);
            Lbls.labels[i * cols + j]->setObjectName(QString::number(i * cols + j));
            Lbls.labels[i * cols + j]->setMinimumSize(50, 50);
            Lbls.labels[i * cols + j]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            btnGLayout->addWidget(Lbls.labels[i * cols + j], i, j);
            Lbls.labels[i * cols + j]->hide();
        }
    }
}

void Interface::getBtnInfo()
{
    btnSender = qobject_cast<QPushButton*>(sender());
    btnObjectName = btnSender->objectName();
}

void Interface::markFlag()
{
    qDebug() << "Right Clicked";
    getBtnInfo();
    for(int i = 0; i < Btns.size(); i++) {
        if(Btns[i]->objectName() == btnObjectName) {
            if(std::find(flagsPos.begin(), flagsPos.end(), i) != flagsPos.end()) {
                flagsPos.erase(std::remove(flagsPos.begin(), flagsPos.end(), i), flagsPos.end());
                questionMarkPos.push_back(i);
                Btns[i]->setIcon(QIcon(":/question_mark.png"));
                Btns[i]->setIconSize(QSize(40, 40));
            }
            else {
                if(std::find(questionMarkPos.begin(), questionMarkPos.end(), i) != questionMarkPos.end()) {
                    questionMarkPos.erase(std::remove(questionMarkPos.begin(), questionMarkPos.end(), i), questionMarkPos.end());
                    Btns[i]->setIcon(QIcon());
                }
                else {
                    Btns[i]->setIcon(QIcon("://flag.ico"));
                    Btns[i]->setIconSize(QSize(40, 40));
                    flagsPos.push_back(i);
                }
            }
        }
    }
}

void Interface::showLabel()
{
    getBtnInfo();
    for(int i = 0; i < Btns.size(); i++) {
        if(Btns[i]->objectName() == btnObjectName) {
            if(std::find(flagsPos.begin(), flagsPos.end(), i) != flagsPos.end() || std::find(questionMarkPos.begin(), questionMarkPos.end(), i) != questionMarkPos.end()) {
                qDebug() << "Can not show label right now";
            }
            else {
                Btns[i]->hide();
                Lbls.labels[i]->show();
            }
        }
    }
}
