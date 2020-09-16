#ifndef START_DIALOG_H
#define START_DIALOG_H

#include <QDialog>

namespace Ui {
class Start_Dialog;
}

class Start_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Start_Dialog(QWidget *parent = 0);
    ~Start_Dialog();

private:
    Ui::Start_Dialog *ui;
};

#endif // START_DIALOG_H
