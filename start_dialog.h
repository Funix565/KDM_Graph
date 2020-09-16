#ifndef START_DIALOG_H
#define START_DIALOG_H

#include <QDialog>
#include "start_type.h"

namespace Ui {
class Start_Dialog;
}

class Start_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Start_Dialog(QWidget *parent = 0);
    ~Start_Dialog();

    TStartM* retData() const;  // повернення вихiдних даних

private slots:
    void on_pushButton_start_clicked();

private:
    Ui::Start_Dialog *ui;

};

#endif // START_DIALOG_H
