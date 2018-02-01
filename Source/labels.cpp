#include "labels.h"

Labels::Labels()
{
}

void Labels::setMineIcon()
{
    QPixmap minePixmap(":/mine.ico");
    int w, h;
    for(int i = 0; i < generatedMines.minesPos.size(); i++) {
        w = labels[generatedMines.minesPos[i]]->width();
        h = labels[generatedMines.minesPos[i]]->height();
        labels[generatedMines.minesPos[i]]->setPixmap(minePixmap.scaled(w, h, Qt::KeepAspectRatio));
    }
}

void Labels::setLblsStyleSheet(int totalLbls)
{
    for(int i = 0; i < totalLbls; i++) {
        labels[i]->setStyleSheet("border: 2px solid grey");
    }
    for(int i = 0; i < totalLbls; i++) {
        if(labels[i]->text() == "1") {
            labels[i]->setStyleSheet("color: '#1569C7'; qproperty-alignment: 'AlignCenter'; font: 30px; border: 2px solid grey;");
        }
        if(labels[i]->text() == "2") {
            labels[i]->setStyleSheet("color: '#41A317'; qproperty-alignment: 'AlignCenter'; font: 30px; border: 2px solid grey;");
        }
        if(labels[i]->text() == "3") {
            labels[i]->setStyleSheet("color: '#E41B17'; qproperty-alignment: 'AlignCenter'; font: 30px; border: 2px solid grey;");
        }
        if(labels[i]->text() == "4") {
            labels[i]->setStyleSheet("color: '#571B7E'; qproperty-alignment: 'AlignCenter'; font: 30px; border: 2px solid grey;");
        }
        if(labels[i]->text() == "5") {
            labels[i]->setStyleSheet("color: '#7E3517'; qproperty-alignment: 'AlignCenter'; font: 30px; border: 2px solid grey;");
        }
        if(labels[i]->text() == "6") {
            labels[i]->setStyleSheet("color: '#000000'; qproperty-alignment: 'AlignCenter'; font: 30px; border: 2px solid grey;");
        }
        if(labels[i]->text() == "7") {
            labels[i]->setStyleSheet("color: '#7E3517'; qproperty-alignment: 'AlignCenter'; font: 30px; border: 2px solid grey;");
        }
        if(labels[i]->text() == "8") {
            labels[i]->setStyleSheet("color: '#7E3517'; qproperty-alignment: 'AlignCenter'; font: 30px; border: 2px solid grey;");
        }
    }
}

void Labels::setLblNotation(int totalLbls, int rows, int cols)
{
    QVector<int> allNumsAround; //记录所有地雷周边的位置
    for(int i = 0; i < totalLbls; i++) {
        for(int j = 0; j < generatedMines.minesPos.size(); j++) {
            if(i == generatedMines.minesPos[j]) {
                QVector<int> numsAround;
                if(i % cols == 0) { //地雷在第一列
                    if(i == 0) { //地雷在第一行第一列第一个位置
                        numsAround = {i + 1, i + cols, i + cols + 1}; //右，下，右下
                    }
                    else if(i == cols * (rows - 1)) { //地雷在最后一行第一个位置
                        numsAround = {i + 1, i - cols, i - cols + 1}; //右，上，右上
                    }
                    else { //地雷在第一列其他位置
                        numsAround = {i - cols, i + cols, i + 1, i - cols + 1, i + cols + 1}; //上，下，右，右上，右下
                    }
                }

                else if(i % cols == cols - 1) { //地雷在最后一列
                    if(i == cols - 1) { //地雷在第一行最后一个
                        numsAround = {i - 1, i + cols, i + cols - 1}; //左，下，左下
                    }
                    else if(i == rows * cols - 1) { //地雷在最后一行最后一个
                        numsAround = {i - 1, i - cols, i - cols -1}; //左，上，左上
                    }
                    else { //地雷在最后一列其他位置
                        numsAround = {i - cols, i + cols, i - 1, i - cols - 1, i + cols - 1}; //上，下，左，左上，左下
                    }
                }

                else if(i < cols && i > 0) { //地雷在第一行
                    numsAround = {i - 1, i + 1, i + cols, i + cols - 1, i + cols + 1}; //左，右，下，左下，左上
                }

                else if(i > cols * (rows - 1) && i < totalLbls) { //地雷在最后一行
                    numsAround = {i - 1, i + 1, i - cols, i - cols - 1, i - cols + 1}; //左，右，上，左上，右上
                }

                else { //地雷不在边缘位置
                    numsAround = {i - cols, i + cols, i - 1, i + 1, i - cols - 1, i - cols + 1, i + cols - 1, i + cols + 1};
                    //上，下，左，右，右上，左上，右下，左下
                }

                for(int k = 0; k < numsAround.size(); k++) {
                    allNumsAround.push_back(numsAround[k]); //把一次循环中符合条件的位置存入到allNumAround的QVector里面
                }
            }
        }
    }

    for(int i = 0; i < allNumsAround.size(); i++) {
        int labelNum = labels[allNumsAround[i]]->text().toInt(); //把QLabel的内容转化为数字
        if(labelNum > 0) {
            labels[allNumsAround[i]]->setText(QString::number(labelNum + 1));
        }
        else {
            labels[allNumsAround[i]]->setText("1");
        }
    }
}

