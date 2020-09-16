#include "mainwindow.h"
#include "start_dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    Start_Dialog p;
    if (p.exec() == QDialog::Accepted)
    {
        w.show();
    }

    return a.exec();
}
