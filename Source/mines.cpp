#include "mines.h"
#include <QDebug>

Mines::Mines()
{

}

void Mines::generateMines(int totalMines, int totalPos)
{
    minesPos.clear();
    minesPos.resize(totalMines);

    for(int i = 0; i < totalMines; i++) {
        int pos = rand() % totalPos; //generate random mine posistion
        minesPos[i] = pos;
    }

    //make sure no postions are generated in the same place
    for(int i = 0; i < totalMines; i++) {
        int tempPos = minesPos[i];
        for(int j = i + 1; j < totalMines; j++) {
            if(tempPos == minesPos[j]) {
                minesPos[j] = rand() % totalPos;
                i = 0;
            }
        }
    }
    qDebug() << "Mines' postions: " <<  minesPos;
}
