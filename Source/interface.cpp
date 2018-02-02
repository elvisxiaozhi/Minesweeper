#include "interface.h"
#include <QDebug>
#include <QMenu>
#include <QMenuBar>

Interface::Interface(QWidget *parent)
    : QMainWindow(parent)
{
    setLayout();
    setMenuBar();
    startGame(8, 8, 10);
    connect(&setMsBox, &MessagesBoxes::playAgain, this, &Interface::playAgain);
}

Interface::~Interface()
{

}

void Interface::setLayout()
{
    setWindowTitle("Minesweeper");

    basicLayout = new QWidget(this);
    setCentralWidget(basicLayout);

    btnGLayout = new QGridLayout;
    btnGLayout->setSpacing(0);

    vLayout = new QVBoxLayout;
    basicLayout->setLayout(vLayout);

    vLayout->addLayout(btnGLayout);
}

void Interface::setMenuBar()
{
    QMenu *levelMenu = new QMenu(basicLayout);
    levelMenu = menuBar()->addMenu("Level");
    QAction *easyAction = new QAction;
    easyAction->setText("Easy");
    QAction *mediumAction = new QAction;
    mediumAction->setText("Medium");
    QAction *hardAction = new QAction;
    hardAction->setText("Hard");
    levelMenu->addAction(easyAction);
    levelMenu->addAction(mediumAction);
    levelMenu->addAction(hardAction);
    connect(easyAction, &QAction::triggered, this, &Interface::easyMode);
    connect(mediumAction, &QAction::triggered, this, &Interface::mediumMode);
    connect(hardAction, &QAction::triggered, this, &Interface::hardMode);
}

void Interface::startGame(int rows, int cols, int totalMines)
{
    setButtons(rows * cols, rows, cols);
    setLabels(rows * cols, rows, cols);
    Lbls.generatedMines.generateMines(totalMines, rows * cols);
    Lbls.setLblNotation(rows * cols, rows, cols);
    Lbls.setMineIcon();
    Lbls.setLblsStyleSheet(rows * cols);
    setBottomBar();
}

void Interface::setButtons(int totalBtns, int rows, int cols)
{
    totalRows = rows, totalCols = cols;
    qDebug() << "rows: " << totalRows << "cols: " << totalCols;

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

void Interface::setBottomBar()
{
    setTimer.setBottomBar(Lbls.generatedMines.minesPos.size(), basicLayout);
    setTimer.setTimer();
    hLayout = new QHBoxLayout;
//    hLayout->addWidget(setTimer.timerIconLbl);
    hLayout->addWidget(setTimer.timerLbl);
    hLayout->addWidget(setTimer.minesLbl);
//    hLayout->addWidget(setTimer.minesIconLbl);

    vLayout->addLayout(hLayout);
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
                if(std::find(Lbls.generatedMines.minesPos.begin(), Lbls.generatedMines.minesPos.end(), i) != Lbls.generatedMines.minesPos.end()) {
                    Lbls.labels[i]->setStyleSheet("background-color: red");
                    showAll();
                }
                else if(Lbls.labels[i]->pixmap() == 0) {
                    QString clickedLblObjectName = Lbls.labels[i]->objectName();
                    showTopBlankLbls(clickedLblObjectName);
                    showBottomBlankLbls(clickedLblObjectName);
                    showLeftBlankLbls(clickedLblObjectName);
                    showRightBlankLbls(clickedLblObjectName);
                    recoverMarkedBtns();
                }
            }
        }
    }
}

void Interface::playAgain()
{
    if(totalCols == 8) {
        easyMode();
    }
    else if(totalCols == 16) {
        mediumMode();
    }
    else {
        hardMode();
    }
}

void Interface::easyMode()
{
    resetGame();
    startGame(8, 8, 10);
}

void Interface::mediumMode()
{
    resetGame();
    startGame(16, 16, 40);
}

void Interface::hardMode()
{
    resetGame();
    startGame(16, 30, 99);
}

void Interface::resetGame()
{
    flagsPos.clear();
    questionMarkPos.clear();
    for(int i = 0; i < Btns.size(); i++) {
        delete Btns[i];
        delete Lbls.labels[i];
    }
    delete setTimer.timerLbl;
    delete setTimer.minesLbl;
    delete setTimer.startTimer;
}

void Interface::showAll()
{
    for(int i = 0; i < Btns.size(); i++) {
        Btns[i]->hide();
        Lbls.labels[i]->show();
    }
    setTimer.startTimer->stop();
    setMsBox.showPlayAgainMsBox();
}

void Interface::showTopBlankLbls(QString clickedLblObjectName)
{
    for(int i = 0; i < totalRows; i++) {
        for(int j = 0; j < totalCols; j++) {
            if(Lbls.labels[i * totalCols + j]->objectName() == clickedLblObjectName) {
                if(Lbls.labels[i * totalCols + j]->text() == "" && i * totalCols + j - totalCols >= 0) { //如果点击的位置为空白，且该位置不在第一行
                    if(Lbls.labels[i * totalCols +  j - totalCols]->text() == "" && Lbls.labels[i * totalCols +  j - totalCols]->pixmap() == 0) { //如果上面一个位置为空白，且不是雷
                        Lbls.labels[i * totalCols +  j - totalCols]->show();
                        Btns[i * totalCols + j - totalCols]->hide();
                        QString lblObjectName = Lbls.labels[i * totalCols +  j - totalCols]->objectName(); //对它上面一个位置进行递归所需要的传入参数
                        showTopBlankLbls(lblObjectName);
                        showLeftBlankLbls(lblObjectName);
                        showRightBlankLbls(lblObjectName);
//                        hiddenBtns.push_back(i * totalCols + j - totalCols);
                    }
                    else if(Lbls.labels[i * totalCols +  j - totalCols]->text() != "" && Lbls.labels[i * totalCols +  j - totalCols]->pixmap() == 0) {
                        Lbls.labels[i * totalCols +  j - totalCols]->show();
                        Btns[i * totalCols + j - totalCols]->hide();
//                        hiddenBtns.push_back(i * totalCols + j - totalCols);
                    }
                }
            }
        }
    }
}

void Interface::showBottomBlankLbls(QString clickedLblObjectName)
{
    for(int i = 0; i < totalRows; i++) {
        for(int j = 0; j < totalCols; j++) {
            if(Lbls.labels[i * totalCols + j]->objectName() == clickedLblObjectName) {
                if(Lbls.labels[i * totalCols + j]->text() == "" && i * totalCols + j + totalCols < totalCols * totalRows) { //如果点击的位置为空白，且该位置不在最后一行
                    if(Lbls.labels[i * totalCols +  j + totalCols]->text() == "" && Lbls.labels[i * totalCols +  j + totalCols]->pixmap() == 0) { //如果上面一个位置为空白，且不是雷
                        Lbls.labels[i * totalCols +  j + totalCols]->show();
                        Btns[i * totalCols + j + totalCols]->hide();
                        QString lblObjectName = Lbls.labels[i * totalCols +  j + totalCols]->objectName(); //对它上面一个位置进行递归所需要的传入参数
                        showBottomBlankLbls(lblObjectName);
                        showLeftBlankLbls(lblObjectName);
                        showRightBlankLbls(lblObjectName);
//                        hiddenBtns.push_back(i * totalCols + j + totalCols);
                    }
                    else if(Lbls.labels[i * totalCols +  j + totalCols]->text() != "" && Lbls.labels[i * totalCols +  j + totalCols]->pixmap() == 0) {
                        Lbls.labels[i * totalCols +  j + totalCols]->show();
                        Btns[i * totalCols + j + totalCols]->hide();
//                        hiddenBtns.push_back(i * totalCols + j + totalCols);
                    }
                }
            }
        }
    }
}

void Interface::showLeftBlankLbls(QString clickedLblObjectName)
{
    for(int i = 0; i < totalRows; i++) {
        for(int j = 0; j < totalCols; j++) {
            if(Lbls.labels[i * totalCols + j]->objectName() == clickedLblObjectName) {
                if(Lbls.labels[i * totalCols + j]->text() == "" && (i * totalCols + j + totalCols) % totalCols != 0) { //如果点击的位置为空白，且该位置不在最后一行
                    if(Lbls.labels[i * totalCols +  j - 1]->text() == "" && Lbls.labels[i * totalCols +  j - 1]->pixmap() == 0) { //如果上面一个位置为空白，且不是雷
                        Lbls.labels[i * totalCols +  j - 1]->show();
                        Btns[i * totalCols + j - 1]->hide();
                        QString lblObjectName = Lbls.labels[i * totalCols +  j - 1]->objectName(); //对它上面一个位置进行递归所需要的传入参数
                        showLeftBlankLbls(lblObjectName);
//                        hiddenBtns.push_back(i * totalCols + j - 1);
                    }
                    else if(Lbls.labels[i * totalCols +  j - 1]->text() != "" && Lbls.labels[i * totalCols +  j - 1]->pixmap() == 0) {
                        Lbls.labels[i * totalCols +  j - 1]->show();
                        Btns[i * totalCols + j - 1]->hide();
//                        hiddenBtns.push_back(i * totalCols + j - 1);
                    }
                }
            }
        }
    }
}

void Interface::showRightBlankLbls(QString clickedLblObjectName)
{
    for(int i = 0; i < totalRows; i++) {
        for(int j = 0; j < totalCols; j++) {
            if(Lbls.labels[i * totalCols + j]->objectName() == clickedLblObjectName) {
                if(Lbls.labels[i * totalCols + j]->text() == "" && (i * totalCols + j + totalCols) % totalCols != totalCols - 1) { //如果点击的位置为空白，且该位置不在最后一行
                    if(Lbls.labels[i * totalCols +  j + 1]->text() == "" && Lbls.labels[i * totalCols +  j + 1]->pixmap() == 0) { //如果上面一个位置为空白，且不是雷
                        Lbls.labels[i * totalCols +  j + 1]->show();
                        Btns[i * totalCols + j + 1]->hide();
                        QString lblObjectName = Lbls.labels[i * totalCols +  j + 1]->objectName(); //对它上面一个位置进行递归所需要的传入参数
                        showRightBlankLbls(lblObjectName);
//                        hiddenBtns.push_back(i * totalCols + j + 1);
                    }
                    else if(Lbls.labels[i * totalCols +  j + 1]->text() != "" && Lbls.labels[i * totalCols +  j + 1]->pixmap() == 0) {
                        Lbls.labels[i * totalCols +  j + 1]->show();
                        Btns[i * totalCols + j + 1]->hide();
//                        hiddenBtns.push_back(i * totalCols + j + 1);
                    }
                }
            }
        }
    }
}

void Interface::recoverMarkedBtns()
{
    if(flagsPos.size() > 0) {
        for(int i = 0; i < flagsPos.size(); i++) {
            Btns[flagsPos[i]]->setIcon(QIcon("://flag.ico"));
            Btns[flagsPos[i]]->setIconSize(QSize(40, 40));
            Btns[flagsPos[i]]->show();
            Lbls.labels[flagsPos[i]]->hide();
        }
    }

    if(questionMarkPos.size() > 0) {
        for(int i = 0; i < questionMarkPos.size(); i++) {
            Btns[questionMarkPos[i]]->setIcon(QIcon(":/question_mark.png"));
            Btns[questionMarkPos[i]]->setIconSize(QSize(40, 40));
            Btns[questionMarkPos[i]]->show();
            Lbls.labels[questionMarkPos[i]]->hide();
        }
    }
}
