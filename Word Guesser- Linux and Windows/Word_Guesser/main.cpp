#include "selectmain.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SelectMain w;
    w.show();

    return a.exec();
}
