#include "listalign.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    listAlign w;
    w.show();

    return a.exec();
}
