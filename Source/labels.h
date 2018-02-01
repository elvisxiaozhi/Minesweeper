#ifndef LABELS_H
#define LABELS_H

#include <QLabel>
#include "mines.h"

class Labels
{
public:
    Labels();

    QVector<QLabel*> labels;
    Mines generatedMines;

    void setMineIcon();
    void setLblsStyleSheet(int);
    void setLblNotation(int, int, int);
};

#endif // LABELS_H
