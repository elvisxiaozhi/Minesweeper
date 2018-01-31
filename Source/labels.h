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

    void setMineIcon(int, int);
    void setLblsStyleSheet(int);
};

#endif // LABELS_H
