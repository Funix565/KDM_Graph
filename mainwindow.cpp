#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "start_dialog.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Start_Dialog p;
    if (p.exec() == QDialog::Accepted)
    {
        TStartM *dt = p.retData();
        qDebug() << dt->clmns;
        ui->label_test->setText(QString::number(dt->clmns));
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
