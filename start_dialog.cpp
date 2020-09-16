#include "start_dialog.h"
#include "ui_start_dialog.h"

Start_Dialog::Start_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Start_Dialog)
{
    ui->setupUi(this);
    ui->spinBox_clmns->setMaximum(12);
    ui->spinBox_rows->setMaximum(12);
    ui->spinBox_clmns->setWrapping(true);
    ui->spinBox_rows->setWrapping(true);
}

Start_Dialog::~Start_Dialog()
{
    delete ui;
}
