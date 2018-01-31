#include "labels.h"

Labels::Labels()
{

}

void Labels::setMineIcon(int totalMines, int totalPos)
{
    generatedMines.generateMines(totalMines, totalPos);

    QPixmap minePixmap(":/mine.ico");
    for(int i = 0; i < generatedMines.minesPos.size(); i++) {
        labels[generatedMines.minesPos[i]]->setPixmap(minePixmap);
        labels[generatedMines.minesPos[i]]->setScaledContents(true); //make sure the icon fit into the label
    }
}

void Labels::setLblsStyleSheet(int totalLbls)
{
    for(int i = 0; i < totalLbls; i++) {
        labels[i]->setStyleSheet("border: 2px solid grey");
    }
}
