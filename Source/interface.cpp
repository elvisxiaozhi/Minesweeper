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
            Btns[i * cols + j]->setMinimumSize(40, 40);
            Btns[i * cols + j]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            btnGLayout->addWidget(Btns[i * cols + j], i, j);
            connect(Btns[i * cols + j], &Buttons::btnRightClicked, this, &Interface::markFlag);

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
}
