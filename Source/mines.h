#ifndef MINES_H
#define MINES_H

#include <QVector>

class Mines
{
public:
    Mines();

    QVector<int> minesPos;
    void generateMines(int, int);
};

#endif // MINES_H
