#ifndef BUTTONS_H
#define BUTTONS_H

#include <QPushButton>
#include <QMouseEvent>

class Buttons : public QPushButton
{
    Q_OBJECT
public:
    Buttons();

signals:
    void btnRightClicked();

private slots:
    void mousePressEvent(QMouseEvent *);
};

#endif // BUTTONS_H
