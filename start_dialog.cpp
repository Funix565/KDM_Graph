#include "start_dialog.h"
#include "ui_start_dialog.h"
#include "start_type.h"
#include <QDebug>

Start_Dialog::Start_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Start_Dialog)
{
    ui->setupUi(this);

    // Вставновлення мiнiмальних даних для роботи
    ui->spinBox_clmns->setMinimum(3);
    ui->spinBox_rows->setMinimum(3);

    // Встановлення обмежень для вибору
    ui->spinBox_clmns->setMaximum(12);
    ui->spinBox_rows->setMaximum(12);
    ui->spinBox_clmns->setWrapping(true);
    ui->spinBox_rows->setWrapping(true);
}

Start_Dialog::~Start_Dialog()
{
    delete ui;
}

 //Ф-цiя повернення вихiдних даних
TStartM *Start_Dialog::retData() const
{
    int __rows;
    int __clmns;
    bool __dir;
    bool __undir;

    // Отримуємо розмiр таблицi та тип графа
    __rows = ui->spinBox_rows->value();
    __clmns = ui->spinBox_clmns->value();
    __dir = ui->radioButton_dir->isChecked();
    __undir = ui->radioButton_undir->isChecked();

    TStartM *PData = new TStartM;

    // Заносимо у вказiвник для повернення
    PData->clmns = __clmns;
    PData->rows = __rows;
    PData->dir = __dir;
    PData->undir = __undir;

    //emit send_data(PData);

     return PData;
}

void Start_Dialog::on_pushButton_start_clicked()
{
    accept();
}
