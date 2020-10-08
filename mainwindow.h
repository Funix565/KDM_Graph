#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "start_type.h"
#include <QDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    TStartM* retData() const;  // Повернення вихiдних даних
    void MakeAdjMatrix(TStartM *dt);
    void MakeIncMatrix(TStartM *dt);
    void make_matrix(const QVector<QVector<int>> &v);
    void get_and_set_all_info();
    void draw_graph(const QVector<QVector<int>> &v);
    virtual void paintEvent(QPaintEvent *event);

private slots:
    void on_pushButton_start_clicked();

    void on_pushButton_toInc_clicked();


    void on_pushButton_toAdj_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
