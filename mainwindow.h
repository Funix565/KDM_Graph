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

    void MakeAdjMatrix(TStartM *dt);    // Рисування таблицi Сумiжностi
    void MakeIncMatrix(TStartM *dt);    // Рисування таблицi Iнцидентностi
    bool CheckFillSym();       // Перевiрка заповненостi (симетричнiсть для сумiж неорiнт)
    bool CheckFillInc();       // Перевiрка заповненостi

    void make_matrix(const QVector<QVector<int> > &v);

    TStartM *data;   // Структура з початковою iнфою

private slots:
    void on_pushButton_toInc_clicked();

    void on_pushButton_toAdj_clicked();

    void on_pushButton_rel_clicked();

signals:
    void draw_graph(QTableWidget *tab, bool isDir); // Сигнал для рисування графа

private:
    Ui::MainWindow *ui;
    DGraph_draw *dGraph;
};

#endif // MAINWINDOW_H
