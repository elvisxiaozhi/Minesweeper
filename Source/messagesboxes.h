#ifndef MESSAGESBOXES_H
#define MESSAGESBOXES_H

#include <QMessageBox>

class MessagesBoxes : public QObject
{
    Q_OBJECT
public:
    MessagesBoxes();
    void showPlayAgainMsBox();

signals:
    void playAgain();
};

#endif // MESSAGESBOXES_H
