#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QDialog>
#include <QVector>
#include <QPair>
#include <QPainter>
#include <QPaintEvent>

using namespace std;
QVector<QVector<int>> matrix;
QVector<QVector<int>> second_matrix;

bool draw = false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->spinBox_clmns->setMinimum(3);
    ui->spinBox_rows->setMinimum(3);

    // Встановлення обмежень для вибору
    ui->spinBox_clmns->setMaximum(12);
    ui->spinBox_rows->setMaximum(12);
    ui->spinBox_clmns->setWrapping(true);
    ui->spinBox_rows->setWrapping(true);
}

void MainWindow::paintEvent(QPaintEvent *event) {
    if (draw) {
       // if (ui->radioButton_undir->isChecked() && ui->radioButton_inc->isChecked()) {
            // drawing newly generated matrix
            int nodes = matrix.size();
            QPainter el(this);
            QVector<QRect *> nodes_ptr;
            // 1-st param left, second - top
            int left = 10, top = 10;
            for (int i = 0; i < nodes; ++i) {
                if (i == 3) { top += 50; left = 10; }
                QRect *r = new QRect(left, top, 30, 30);
                nodes_ptr.push_back(r);
                left += 50;
            }
            int count = 1;
            for (auto p : nodes_ptr) {
                el.drawEllipse(*p);
                el.drawText(*p, Qt::AlignCenter, QString::number(count++));
            }

//            for (int i = 0; i < nodes; ++i) {
//                for (int j = i; j < nodes; ++j) {
//                    if (matrix[i][j] == 1) {
//                        int from_x = (*nodes_ptr[i]).center().x(), from_y = (*nodes_ptr[i]).center().y();
//                        int to_x = (*nodes_ptr[j]).center().x(), to_y = (*nodes_ptr[j]).center().y();
//                        el.drawLine(from_x, from_y, to_x, to_y);
//                    }
//                }
//            }
//        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

TStartM *MainWindow::retData() const
{
    int __rows;
    int __clmns;
    bool __dir;
    bool __matr_adj;

    // Отримуємо розмiр таблицi та тип графа
    __rows = ui->spinBox_rows->value();
    __clmns = ui->spinBox_clmns->value();
    __dir = ui->radioButton_dir->isChecked();
    __matr_adj = ui->radioButton_adj->isChecked();

    TStartM *PData = new TStartM;

    // Заносимо у вказiвник для повернення
    PData->clmns = __clmns;
    PData->rows = __rows;
    PData->dir = __dir;
    PData->matr_adj = __matr_adj;

    return PData;
}

void MainWindow::on_pushButton_start_clicked()
{
    TStartM *dt = MainWindow::retData();
    if (dt->matr_adj) {
        if (ui->spinBox_rows->value() == ui->spinBox_clmns->value()) { MakeAdjMatrix(dt); }
        else {  QMessageBox::warning(this, "Invalid size", "Adjacency matrix has to be square"); }
    }
    else {  MakeIncMatrix(dt); }
}

void MainWindow::MakeAdjMatrix(TStartM *dt)
{
    int rows = dt->rows;
    int clmns = dt->clmns;

    ui->tableWidget_adj->setRowCount(rows);
    ui->tableWidget_adj->setColumnCount(clmns);
    ui->tableWidget_adj->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget_adj->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget_adj->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableWidget_adj->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    int w = ui->tableWidget_adj->verticalHeader()->width() +4;
    for (int i = 0; i < ui->tableWidget_adj->columnCount(); i++)
    {
        w += ui->tableWidget_adj->columnWidth(i);
    }
    int h = ui->tableWidget_adj->horizontalHeader()->height() + 4;
    for (int i = 0; i < ui->tableWidget_adj->rowCount(); i++)
    {
        h += ui->tableWidget_adj->rowHeight(i);
    }
    QSize p = QSize(w, h);
    // установка фиксированного размера таблицы
    ui->tableWidget_adj->setFixedSize(p);
    QStringList headersA, headersB;

    for (int i = 1; i <= rows; ++i)
    {
        ui->tableWidget_adj->setHorizontalHeaderLabels(headersA << ("x" + QString::number(i)));
    }

    for (int j = 1; j <= clmns; ++j)
    {
        ui->tableWidget_adj->setVerticalHeaderLabels(headersB << ("x" + QString::number(j)));
    }
}

void MainWindow::make_matrix(const QVector<QVector<int> > &v) {
    // if adjacency, then need to draw incidence
    if (ui->radioButton_adj->isChecked()) {
        ui->tableWidget_inc->setRowCount(v.size());
        ui->tableWidget_inc->setColumnCount(v[0].size());
        ui->tableWidget_inc->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        ui->tableWidget_inc->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        ui->tableWidget_inc->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ui->tableWidget_inc->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        int w = ui->tableWidget_inc->verticalHeader()->width() +4;
        for (int i = 0; i < ui->tableWidget_inc->columnCount(); i++) {  w += ui->tableWidget_inc->columnWidth(i); }
        int h = ui->tableWidget_inc->horizontalHeader()->height() + 4;
        for (int i = 0; i < ui->tableWidget_inc->rowCount(); i++) { h += ui->tableWidget_inc->rowHeight(i); }
        QSize p = QSize(w, h);
        // установка фиксированного размера таблицы
        ui->tableWidget_inc->setFixedSize(p);
        QStringList headersA, headersB;
        for (int i = 1; i <= ui->tableWidget_inc->rowCount(); ++i)
        {
            ui->tableWidget_inc->setVerticalHeaderLabels(headersA << ("x" + QString::number(i)));
        }

        for (int j = 1; j <= ui->tableWidget_inc->columnCount(); ++j)
        {
            ui->tableWidget_inc->setHorizontalHeaderLabels(headersB << ("y" + QString::number(j)));
        }
    }
    // if incidence, need to draw adjacency
    else {
        ui->tableWidget_adj->setRowCount(v.size());
        ui->tableWidget_adj->setColumnCount(v[0].size());
        ui->tableWidget_adj->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        ui->tableWidget_adj->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        ui->tableWidget_adj->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ui->tableWidget_adj->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        int w = ui->tableWidget_adj->verticalHeader()->width() +4;
        for (int i = 0; i < ui->tableWidget_adj->columnCount(); i++) {  w += ui->tableWidget_adj->columnWidth(i); }
        int h = ui->tableWidget_adj->horizontalHeader()->height() + 4;
        for (int i = 0; i < ui->tableWidget_adj->rowCount(); i++) {  h += ui->tableWidget_adj->rowHeight(i); }
        QSize p = QSize(w, h);
        ui->tableWidget_adj->setFixedSize(p);
        QStringList headersA, headersB;
        for (int i = 1; i <= ui->tableWidget_adj->columnCount(); ++i) {
            ui->tableWidget_adj->setHorizontalHeaderLabels(headersA << ("x" + QString::number(i)));
            ui->tableWidget_adj->setVerticalHeaderLabels(headersB << ("x" + QString::number(i)));
        }
    }
    // filling matrix
    for (int i = 0; i < v.size(); ++i) {
        for (int j = 0; j < v[0].size(); ++j) {
            QTableWidgetItem *itm = new QTableWidgetItem();
            itm->setData(Qt::EditRole, v[i][j]);
            if (ui->radioButton_adj->isChecked()) {
                ui->tableWidget_inc->setItem(i, j, itm);
            }
            else {
                ui->tableWidget_adj->setItem(i, j, itm);
            }
        }
    }
}


void MainWindow::MakeIncMatrix(TStartM *dt)
{
    int rows = dt->rows;
    int clmns = dt->clmns;

    ui->tableWidget_inc->setRowCount(rows);
    ui->tableWidget_inc->setColumnCount(clmns);
    ui->tableWidget_inc->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget_inc->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget_inc->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableWidget_inc->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    int w = ui->tableWidget_inc->verticalHeader()->width() +4;
    for (int i = 0; i < ui->tableWidget_inc->columnCount(); i++)
    {
        w += ui->tableWidget_inc->columnWidth(i);
    }
    int h = ui->tableWidget_inc->horizontalHeader()->height() + 4;
    for (int i = 0; i < ui->tableWidget_inc->rowCount(); i++)
    {
        h += ui->tableWidget_inc->rowHeight(i);
    }
    QSize p = QSize(w, h);
    // установка фиксированного размера таблицы
    ui->tableWidget_inc->setFixedSize(p);
    QStringList headersA, headersB;

    for (int i = 1; i <= rows; ++i)
    {
        ui->tableWidget_inc->setVerticalHeaderLabels(headersA << ("x" + QString::number(i)));
    }

    for (int j = 1; j <= clmns; ++j)
    {
        ui->tableWidget_inc->setHorizontalHeaderLabels(headersB << ("y" + QString::number(j)));
    }
}

// FROM ADJACENCY MATRIX TO INCIDENCE
void MainWindow::on_pushButton_toInc_clicked()
{
    // undirected graph
    if (ui->radioButton_undir->isChecked()) {
        for (int i = 0; i < ui->tableWidget_adj->rowCount(); ++i) {
            for (int j = 0; j < ui->tableWidget_adj->columnCount(); ++j) {
                QTableWidgetItem *item = ui->tableWidget_adj->item(i, j);
                QTableWidgetItem *symmetric_item = ui->tableWidget_adj->item(j, i);
                if (item->text() != '1' && item->text() != '0' && item->text() != '2') {
                    QMessageBox::warning(this, "Wrong input", "The value in adjacency table must be 1, 0 or 2!");
                    return;
                }
                else if (item->text() != symmetric_item->text()) {
                    QMessageBox::warning(this, "Wrong input", "The adjacency matrix must be symmetric about the main"                                                          "diagonal!");
                    return;
                }
            }
        }
        QVector<QVector<int>> matr;
        QVector<QPair<int, int>> edge_between_two_vertices;
        int count_edges = 0;
        for (int i = 0; i < ui->tableWidget_adj->rowCount(); ++i) {
            for (int j = i; j < ui->tableWidget_adj->rowCount(); ++j) {
                QTableWidgetItem *itm = ui->tableWidget_adj->item(i, j);
                if (itm->text() == '1') {
                    count_edges++;
                    edge_between_two_vertices.push_back(QPair<int,int>(i, j));
                }
            }
        }
        // make matrix
        for (int i = 0; i < ui->tableWidget_adj->rowCount(); ++i) {
            // count of strings in incidence matrix equals to row count.
            // count_edges - count of columns in incidence matrix.
            // we initializing all elements in matrix with zeros
            matr.push_back(QVector<int>(count_edges, 0));
        }
        // if we have at least one edge (1)
        if (!edge_between_two_vertices.empty()) {
            // after reverse this index will point to the first element of the pair nodes which are united by an edge
            int index = edge_between_two_vertices.size() - 1;
            int current_edge = 0;
            reverse(edge_between_two_vertices.begin(), edge_between_two_vertices.end());
            while(index >= 0) {
                if (matr[edge_between_two_vertices[index].first] != matr[edge_between_two_vertices[index].second]) {
                    matr[edge_between_two_vertices[index].first][current_edge] =
                            matr[edge_between_two_vertices[index].second][current_edge] = 1;
                }
                // petlya
                else if (matr[edge_between_two_vertices[index].first] == matr[edge_between_two_vertices[index].second]) {
                    matr[edge_between_two_vertices[index].first][current_edge] =
                            matr[edge_between_two_vertices[index].second][current_edge] = 2;
                }
                current_edge++;
                index--;
            }
        }
        draw = true;
        matrix = matr;
        make_matrix(matr);
        matrix.clear();
        draw = false;
    }

    // directed graph
    else {
        for (int i = 0; i < ui->tableWidget_adj->rowCount(); ++i) {
            for (int j = 0; j < ui->tableWidget_adj->columnCount(); ++j) {
                QTableWidgetItem *item = ui->tableWidget_adj->item(i, j);
                bool ok = false;
                int n = item->text().toInt(&ok, 10);
                if (!ok || (ok && n < 0)) {
                    QMessageBox::warning(this, "Wrong input", "The value in adjacency must be >= 0");
                    return;
                }
            }
            int count_edges = 0;
            int current_edge = 0;
            QVector<QPair<int, QPair<int, int>>> edge_plus_pos;
            for (int i = 0; i < ui->tableWidget_adj->rowCount(); ++i) {
                for (int j = 0; j < ui->tableWidget_adj->columnCount(); ++j) {
                    QTableWidgetItem *itm = ui->tableWidget_adj->item(i, j);
                    bool ok = false;
                    int num = itm->text().toInt(&ok, 10);
                    if (ok && num >= 0) {
                        while(num--) {
                            edge_plus_pos.push_back(QPair<int, QPair<int, int>>(current_edge++, QPair<int, int>(i, j)));
                            count_edges++;
                        }
                    }
                }
            }
            QVector<QVector<int>> matr_incid;
            for (int i = 0; i < ui->tableWidget_adj->rowCount(); ++i) { matr_incid.push_back(QVector<int>(count_edges, 0)); }
            // at least one edge ('1')
            if (edge_plus_pos.size() > 0) {
                int current_edge = 0;
                for (auto it : edge_plus_pos) {
                    // petlya
                    // it.second.first - node from which vertex emerges (from)
                    if (it.second.first == it.second.second) { matr_incid[it.second.first][current_edge++] = 2; }
                    else {
                        matr_incid[it.second.first][current_edge++] = 1;
                    }
                }
                for (auto it : edge_plus_pos) {
                    // it.first - edge. it.second.second - node to which vertex (it.first) enters
                    if (it.second.first != it.second.second) { matr_incid[it.second.second][it.first] = -1; }
                }
            }
            draw = true;
            matrix = matr_incid;
            make_matrix(matr_incid);
            matrix.clear();
            draw = false;
        }
    }
}

// FROM INCIDENCE MATRIX TO ADJACENCY
void MainWindow::on_pushButton_toAdj_clicked()
{
    // not directed graph
    if (ui->radioButton_undir->isChecked()) {
        for (int i = 0; i < ui->tableWidget_inc->rowCount(); ++i) {
            for (int j = 0; j < ui->tableWidget_inc->columnCount(); j++) {
                QTableWidgetItem *item = ui->tableWidget_inc->item(i, j);
                if (item->text() != '1' && item->text() != '0' && item->text() != '2') {
                    QMessageBox::warning(this, "Wrong input!", "The value in incidence matrix must be 0, 1 or 2!");
                    return;
                }
            }
        }
        int vertecies = ui->tableWidget_inc->rowCount();
        int edges = ui->tableWidget_inc->columnCount();
        QVector<QVector<int>> adj_matr;
        for (int i = 0; i < vertecies; ++i) { adj_matr.push_back(QVector<int>(vertecies, 0)); }
        QVector<QPair<int, int>> p;

        for (int i = 0; i < edges; ++i) {
            int a = -1, b = -1, vertex = 0;
            QTableWidgetItem *item;
            for ( ; vertex < vertecies && a == -1; ++vertex) {
                item = ui->tableWidget_inc->item(vertex, i);
                if (item->text() == '2') {
                    a = vertex, b = vertex;
                }
                else if (item->text() == '1') {
                    a = vertex;
                }
            }
            for ( ; vertex < vertecies && b == -1; ++vertex) {
                item = ui->tableWidget_inc->item(vertex, i);
                if (item->text() == '1') {
                    b = vertex;
                }
            }

            if (a != -1) {
                int add = 1;
                if (p.isEmpty()) {
                    p.push_back(QPair<int, int>(a, b));
                }
                else {
                    for (auto it : p) {
                        if (it.first == a && it.second == b) {
                            add++;
                        }
                    }
                    p.push_back(QPair<int, int>(a, b));
                    adj_matr[a][b] = adj_matr[b][a] = add;
                }
            }
           // QPaintEvent *p;
            draw = true;
            make_matrix(adj_matr);
            matrix = adj_matr;
            update();
            matrix.clear();
            draw = false;
        }
    }
    // directed graph
    else {
        for (int i = 0; i < ui->tableWidget_inc->rowCount(); ++i) {
            for (int j = 0; j < ui->tableWidget_inc->columnCount(); j++) {
                QTableWidgetItem *item = ui->tableWidget_inc->item(i, j);
                if (item->text() != '1' && item->text() != '0' && item->text() != "-1" && item->text() != '2') {
                    QMessageBox::warning(this, "Wrong input!", "The value in incidence matrix must be 0,1 or -1!");
                    return;
                }
            }
        }
        int vertecies = ui->tableWidget_inc->rowCount();
        int edges = ui->tableWidget_inc->columnCount();
        QVector<QVector<int>> adj_matr;
        for (int i = 0; i < vertecies; ++i) { adj_matr.push_back(QVector<int>(vertecies, 0)); }
        for (int i = 0; i < edges; ++i) {
            int a = -2, b = -2, vertex = 0;
            QTableWidgetItem *item;
            for ( ; vertex < vertecies && (a == -2 || b == -2); ++vertex) {
                item = ui->tableWidget_inc->item(vertex, i);
                // petlya
                if (item->text() == '2') { a = b = vertex; }
                else if (item->text() == '1') { a = vertex; }
                else if (item->text() == "-1") { b = vertex; }
            }
            if (a != -2 && b != -2) { adj_matr[a][b] = 1; }
        }
        draw = true;
        matrix = adj_matr;
        make_matrix(adj_matr);
        matrix.clear();
        draw = false;
    }
}
