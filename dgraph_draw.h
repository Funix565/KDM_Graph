#ifndef DGRAPH_DRAW_H
#define DGRAPH_DRAW_H

#include <QDialog>
#include <QTableWidget>

namespace Ui {
class DGraph_draw;
}

class DGraph_draw : public QDialog
{
    Q_OBJECT

public:
    explicit DGraph_draw(QWidget *parent = 0);
    ~DGraph_draw();

public slots:
    void when_draw_graph(QTableWidget *tab, bool isDir);

private:
    Ui::DGraph_draw *ui;
    QTableWidget *Dtab;     // AdjTable from main
    bool isDir___;

protected:
    void paintEvent(QPaintEvent *e);
};

#endif // DGRAPH_DRAW_H
