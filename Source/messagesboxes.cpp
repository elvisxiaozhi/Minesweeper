#include "messagesboxes.h"

MessagesBoxes::MessagesBoxes()
{

}

void MessagesBoxes::showPlayAgainMsBox()
{
//    QMessageBox playAgainMsBox;
//    playAgainMsBox.setWindowTitle("Game Over");
    playAgainMsBox.setText("Do you want to play it again?");
    playAgainMsBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    playAgainMsBox.setDefaultButton(QMessageBox::No);
//    playAgainMsBox.setMaximumSize(500, 500); //如果太小，会出现"setGeometry: Unable to set geometry"的警告,这段代码是防止出现这种警告
    playAgainMsBox.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    playAgainMsBox.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
    playAgainMsBox.setStyleSheet("QLabel{min-width: 200px;}");
    int ret = playAgainMsBox.exec();

    switch (ret) {
    case QMessageBox::Yes:
        emit playAgain();
        break;
    case QMessageBox::No:
        playAgainMsBox.close();
        break;
    default:
        break;
    }
}

void MessagesBoxes::about()
{
    QMessageBox aboutMsBox;
    aboutMsBox.setWindowTitle("About");
    aboutMsBox.setText("A Theodore Tang Production");
    aboutMsBox.setInformativeText("© 2017");
    aboutMsBox.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    aboutMsBox.setStyleSheet("QLabel{min-width: 300px; qproperty-alignment: 'AlignCenter';}");
    int ret = aboutMsBox.exec();

    switch (ret) {
    case QMessageBox::Close:
        aboutMsBox.close();
    default:
        break;
    }
}

