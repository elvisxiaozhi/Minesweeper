#include "interface.h"

Interface::Interface(QWidget *parent)
    : QMainWindow(parent)
{
    setLayout();
}

Interface::~Interface()
{

}

void Interface::setLayout()
{
    setWindowTitle("Minesweeper");

    basicLayout = new QWidget(this);
    setCentralWidget(basicLayout);
}
