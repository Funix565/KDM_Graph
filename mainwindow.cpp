#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "start_dialog.h"
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Start_Dialog p;
    if (p.exec() == QDialog::Accepted)
    {
        TStartM *dt = p.retData();

        if (dt->matr_adj)
        {
            MakeAdjMatrix(dt);
        }
        else
        {
            MakeIncMatrix(dt);
        }
    }
    else
    {
        exit(0);
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::MakeAdjMatrix(TStartM *dt)
{
    int rows = dt->rows;
    int clmns = dt->clmns;

    ui->tableWidget_adj->setRowCount(rows);
    ui->tableWidget_adj->setColumnCount(clmns);

    QStringList headersA, headersB;

    for (int i = 1; i <= rows; ++i)
    {
        ui->tableWidget_adj->setHorizontalHeaderLabels(headersA << ("x" + QString::number(i)));
    }

    for (int j = 1; j <= clmns; ++j)
    {
        ui->tableWidget_adj->setVerticalHeaderLabels(headersB << ("x" + QString::number(j)));
    }
}

void MainWindow::MakeIncMatrix(TStartM *dt)
{
    int rows = dt->rows;
    int clmns = dt->clmns;

    ui->tableWidget_inc->setRowCount(rows);
    ui->tableWidget_inc->setColumnCount(clmns);

    QStringList headersA, headersB;

    for (int i = 1; i <= rows; ++i)
    {
        ui->tableWidget_inc->setVerticalHeaderLabels(headersA << ("x" + QString::number(i)));
    }

    for (int j = 1; j <= clmns; ++j)
    {
        ui->tableWidget_inc->setHorizontalHeaderLabels(headersB << ("y" + QString::number(j)));
    }









}
