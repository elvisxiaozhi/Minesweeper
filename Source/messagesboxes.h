#ifndef MESSAGESBOXES_H
#define MESSAGESBOXES_H

#include <QMessageBox>

class MessagesBoxes : public QObject
{
    Q_OBJECT
public:
    MessagesBoxes();
    void showPlayAgainMsBox();
    QMessageBox playAgainMsBox;

signals:
    void playAgain();

public slots:
    void about();
};

#endif // MESSAGESBOXES_H
