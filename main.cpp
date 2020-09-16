#include "mainwindow.h"
#include "start_dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Start_Dialog p;
    p.show();
//    MainWindow w;
//    w.show();


    return a.exec();
}
