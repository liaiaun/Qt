#include <QApplication>

#include"collectedatawin.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CollecteDataWin c;
    c.show();
    return a.exec();
}
