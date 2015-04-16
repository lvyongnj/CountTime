#include "maincount.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainCount w;
    w.show();

    return a.exec();
}
