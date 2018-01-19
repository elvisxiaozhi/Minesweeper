#include "buttons.h"

Buttons::Buttons()
{

}

void Buttons::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::RightButton) {
        emit btnRightClicked();
    }
    QPushButton::mousePressEvent(e);
}
