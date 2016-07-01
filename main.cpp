#include "mainwindow.h"
#include <QApplication>
#include <tests/alltests.h>

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    allTests tests;
    tests.runTests();
    return 0;

//    return a.exec();
}
