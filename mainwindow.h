#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "start_type.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void MakeAdjMatrix(TStartM *dt);
    void MakeIncMatrix(TStartM *dt);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
