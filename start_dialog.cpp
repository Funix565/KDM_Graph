#include "start_dialog.h"
#include "ui_start_dialog.h"
#include "start_type.h"
#include <QDebug>
#include <QMessageBox>

Start_Dialog::Start_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Start_Dialog)
{
    ui->setupUi(this);

    // ��⠢�������� �i�i���쭨� ����� ��� ஡��
    ui->spinBox_clmns->setMinimum(3);
    ui->spinBox_rows->setMinimum(3);

    // ��⠭������� �������� ��� ������
    ui->spinBox_clmns->setMaximum(12);
    ui->spinBox_rows->setMaximum(12);
    ui->spinBox_clmns->setWrapping(true);
    ui->spinBox_rows->setWrapping(true);
}

Start_Dialog::~Start_Dialog()
{
    delete ui;
}

 //�-�i� ����୥��� ���i���� �����
TStartM *Start_Dialog::retData() const
{
    int __rows;
    int __clmns;
    bool __dir;
    bool __matr_adj;

    // ��ਬ�� ஧�i� ⠡���i � ⨯ ���
    __rows = ui->spinBox_rows->value();
    __clmns = ui->spinBox_clmns->value();
    __dir = ui->radioButton_dir->isChecked();
    __matr_adj = ui->radioButton_adj->isChecked();

    qDebug() << "matr = " << __matr_adj;

    TStartM *PData = new TStartM;

    // ����ᨬ� � ����i���� ��� ����୥���
    PData->clmns = __clmns;
    PData->rows = __rows;
    PData->dir = __dir;
    PData->matr_adj = __matr_adj;

    return PData;
}

void Start_Dialog::on_pushButton_start_clicked()
{
    if (ui->radioButton_adj->isChecked())
    {
        if (ui->spinBox_clmns->value() == ui->spinBox_rows->value())
        {
            accept();
        }
        else
        {
            QMessageBox::warning(this, "Invalid size", "Adjacency matrix has to be square");
        }
    }
    else
    {
        accept();
    }
}
