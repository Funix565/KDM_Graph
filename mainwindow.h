#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QVector>
#include "start_type.h"
#include "dgraph_draw.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void MakeAdjMatrix(TStartM *dt);    // ���㢠��� ⠡���i ��i�����i
    void MakeIncMatrix(TStartM *dt);    // ���㢠��� ⠡���i I�樤��⭮��i
    bool CheckFillSym();       // ��ॢiઠ �����������i (ᨬ����i��� ��� ��i� ����i��)
    bool CheckFillInc();       // ��ॢiઠ �����������i

    void make_matrix(const QVector<QVector<int> > &v);

    TStartM *data;   // ������� � ���⪮��� i���

private slots:
    void on_pushButton_toInc_clicked();

    void on_pushButton_toAdj_clicked();

    void on_pushButton_rel_clicked();

signals:
    void draw_graph(QTableWidget *tab, bool isDir); // ������ ��� ��㢠��� ���

private:
    Ui::MainWindow *ui;
    DGraph_draw *dGraph;
};

#endif // MAINWINDOW_H
