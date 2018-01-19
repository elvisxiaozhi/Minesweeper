#ifndef INTERFACE_H
#define INTERFACE_H

#include <QMainWindow>

class Interface : public QMainWindow
{
    Q_OBJECT

public:
    Interface(QWidget *parent = 0);
    ~Interface();

private:
    QWidget *basicLayout;

    void setLayout();
};

#endif // INTERFACE_H
