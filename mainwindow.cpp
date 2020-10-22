#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "start_dialog.h"

#include <stdlib.h>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Lab -1- Hyzha & Denkin");

    // Виклик дiалогу для початкових даних
    Start_Dialog p;
    if (p.exec() == QDialog::Accepted)
    {
        // Отримуємо данi у змiнну класу
        data = p.retData();

        if (data->matr_adj)
        {
            // Якщо будуємо сумiжнiсть, то у сумiжнiсть перетворювати не будемо
            ui->pushButton_toAdj->setEnabled(false);
            MakeAdjMatrix(data);
        }
        else
        {
            // Якщо будуємо iнцидентнiсть, то в iнц перетворювати не будемо
            ui->pushButton_toInc->setEnabled(false);
            MakeIncMatrix(data);
        }
    }
    else
    {
        exit(0);
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

// Рисування матрицi Сумiжностi
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

    // Створення порожнiх елементiв. Необiхдно для подальшої перевiрки введення
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < clmns; ++j)
        {
            ui->tableWidget_adj->setItem(i, j, new QTableWidgetItem);
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

    // Створення порожнiх елементiв. Необiхдно для подальшої перевiрки введення
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < clmns; ++j)
        {
            ui->tableWidget_inc->setItem(i, j, new QTableWidgetItem);
        }
    }
}

// Ф-цiя перевiрки на симетричнiсть матрицi сумiж для неорграфа
bool MainWindow::CheckFillSym()
{
    int rows = ui->tableWidget_adj->rowCount();
    int clmns = ui->tableWidget_adj->columnCount();
    for (int i = 0; i < rows; ++i)
    {
        for (int j = i; j < clmns; ++j)
        {
            // Отримуємо симетричнi елементи матрицi
            QTableWidgetItem *itm = ui->tableWidget_adj->item(i, j);
            QTableWidgetItem *itmS = ui->tableWidget_adj->item(j, i);
            // Якщо порожнi клiтинки
            if (itm->text().isEmpty() || itmS->text().isEmpty())
            {
                QMessageBox::critical(this, "Wrong filling", QString("No input in x%1x%2").arg(j+1).arg(i+1));
                return false;
            }
            bool ok;
            bool okS;
            itm->text().toUInt(&ok, 10);
            itmS->text().toUInt(&okS, 10);
            if (ok == false || okS == false)
            {
                QMessageBox::critical(this, "Wrong filling", "Only numbers are allowed");
                return false;
            }

            // Якщо не однаковi
            if ( itm->text() != itmS->text() )
            {
                // TODO: выделять ячейки цветом, но тогда перед нажатием toInc убирать цвет ячейки
                QMessageBox::information(this, "Wrong filling", QString("The matrix must be Symmetric. Check x%1x%2").arg(j+1).arg(i+1));
                return false;
            }

        }
    }
    return true;
}

// Перевiрка коректностi матрицi iнцидентностi
bool MainWindow::CheckFillInc()
{
    int rows = ui->tableWidget_inc->rowCount();
    int clmns = ui->tableWidget_inc->columnCount();
    // Цикл проходження кожного стовпчика
    for (int j = 0; j < clmns; ++j)
    {
        int sum = 0;        // поточна сума у стовпцi
        // Цикл проходження по кожного рядка у кожному стовпчику
        for (int i = 0; i < rows; ++i)
        {
            QTableWidgetItem *itm = ui->tableWidget_inc->item(i, j);
            if (itm->text().isEmpty())
            {
                QMessageBox::critical(this, "Wrong filling", QString("No input in x%1y%2").arg(j+1).arg(i+1));
                return false;
            }
            bool ok;
            // Елементи матрицi беремо за модулем, а потiм додаємо
            sum += abs(itm->text().toInt(&ok, 10));

            if (!ok)
            {
                QMessageBox::critical(this, "Wrong filling", "Only numbers are allowed");
                return false;
            }
        }
        // Сума у кожному стовпчику повинна бути менше або дорiвнювати 2
        if (sum != 2)
        {
            QMessageBox::information(this, "Wrong filling", QString("The sum in each column must be 2. Check y%1").arg(j + 1));
            return false;
        }
    }
    return true;
}

// Перетворення з сумiжностi в iнцидентнiсть
void MainWindow::on_pushButton_toInc_clicked()
{
    // Неорiнт
    if (!data->dir)
    {
        // Перевiрка на симетричнiсть
        if(CheckFillSym())
        {
            // Алгоритм перетворення
            // Створюємо матрицю, к-сть рядкiв -- к-сть вершин
            ui->tableWidget_inc->setRowCount(data->rows);

            int rowA = ui->tableWidget_adj->rowCount();
            int clmnA = ui->tableWidget_adj->columnCount();
            // Цикл проходження кожного рядка
            for (int i = 0; i < rowA; ++i)
            {
                // Цикл проходження кожного стовпчика у кожному рядку
                for (int j = i; j < clmnA; ++j)
                {
                    // Отримуємо елемент
                    QTableWidgetItem *itm = ui->tableWidget_adj->item(i, j);
                    bool ok;
                    int CellNum = itm->text().toInt(&ok, 10);
                    int rowInc1 = i;
                    int rowInc2 = j;

                    // Цикл, поки число ребер, що з'єднують поточну вершини, бiльше нуля
                    while (CellNum > 0)
                    {
                        // Додаємо стовпчик до матрицi iнц
                        ui->tableWidget_inc->insertColumn(ui->tableWidget_inc->columnCount());

                        // Заповнюємо новий стовпчик нулями
                        for (int k = 0; k < rowA; ++k)
                        {
                            QTableWidgetItem *zero = new QTableWidgetItem("0", 0);
                            ui->tableWidget_inc->setItem(k, ui->tableWidget_inc->columnCount() - 1, zero);
                        }
                        QTableWidgetItem *inInc = new QTableWidgetItem();
                        // Якщо ряд=стовп, ребро -- петля
                        if (i == j)
                        {
                            inInc->setText("2");
                        }
                        else
                        {
                            inInc->setText("1");
                        }

                        ui->tableWidget_inc->setItem(rowInc1, ui->tableWidget_inc->columnCount() - 1, inInc);
                        QTableWidgetItem *clon = inInc->clone();
                        ui->tableWidget_inc->setItem(rowInc2, ui->tableWidget_inc->columnCount() - 1, clon);
                        // Вiдмiтили одне ребро, зменишили к-сть, що залишилася
                        --CellNum;
                    }
                }
            }

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

            int rows = ui->tableWidget_inc->rowCount();
            int clmns = ui->tableWidget_inc->columnCount();
            QStringList headersA, headersB;
            for (int i = 1; i <= rows; ++i)
            {
                ui->tableWidget_inc->setVerticalHeaderLabels(headersA << ("x" + QString::number(i)));
            }

            for (int j = 1; j <= clmns; ++j)
            {
                ui->tableWidget_inc->setHorizontalHeaderLabels(headersB << ("y" + QString::number(j)));
            }

            // Рисування графа
            dGraph = new DGraph_draw(this);
            emit draw_graph(ui->tableWidget_adj, false);
            dGraph->show();
        }
    }
    // Орiнт
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
            make_matrix(matr_incid);
        }

        /// Рисування графа ///
        dGraph = new DGraph_draw(this);
        emit draw_graph(ui->tableWidget_adj, true);
        dGraph->show();
    }
}

void MainWindow::make_matrix(const QVector<QVector<int> > &v) {
    // if adjacency, then need to draw incidence
    //if (ui->radioButton_adj->isChecked()) {
    if(data->matr_adj) {
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
        // ????????? ?????????????? ??????? ???????
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
            //if (ui->radioButton_adj->isChecked()) {
            if(data->matr_adj) {
                ui->tableWidget_inc->setItem(i, j, itm);
            }
            else {
                ui->tableWidget_adj->setItem(i, j, itm);
            }
        }
    }
}

// Перетворення з Iнцидентностi в Сумiжнiсть
void MainWindow::on_pushButton_toAdj_clicked()
{
    // Орiнт
    if (data->dir)
    {
        if (CheckFillInc())
        {
            ui->tableWidget_adj->setRowCount(data->rows);
            ui->tableWidget_adj->setColumnCount(data->rows);

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

            int r = ui->tableWidget_adj->rowCount();
            int c = ui->tableWidget_adj->columnCount();

            QStringList headersA, headersB;

            for (int i = 1; i <= r; ++i)
            {
                ui->tableWidget_adj->setHorizontalHeaderLabels(headersA << ("x" + QString::number(i)));
            }

            for (int j = 1; j <= c; ++j)
            {
                ui->tableWidget_adj->setVerticalHeaderLabels(headersB << ("x" + QString::number(j)));
            }


            int rowsA = ui->tableWidget_adj->rowCount();
            int clmnsA = ui->tableWidget_adj->columnCount();

            // Заповнюємо матрицю сумiжностi нулями
            for (int k = 0; k < rowsA; ++k)
            {
                for (int j = 0; j < clmnsA; ++j)
                {
                    QTableWidgetItem *zero = new QTableWidgetItem("0", 0);
                    ui->tableWidget_adj->setItem(k, j, zero);
                    QTableWidgetItem *clon = zero->clone();
                    ui->tableWidget_adj->setItem(j, k, clon);
                }
            }

            // Алгоритм
            int rowsI = ui->tableWidget_inc->rowCount();
            int clmnsI = ui->tableWidget_inc->columnCount();
            for (int j = 0; j < clmnsI; ++j)
            {
                bool suc = false;
                for (int i = 0; i < rowsI; ++i)
                {
                    int forAdj_r = 0, forAdj_c = 0;
                    QTableWidgetItem *itm = ui->tableWidget_inc->item(i, j);
                    bool ok;
                    int fnum = itm->text().toInt(&ok, 10);
                    if (fnum == 1)
                    {
                        forAdj_r = i;
                    }
                    else if (fnum == -1)
                    {
                        forAdj_c = i;
                    }
                    else if (fnum == 2)
                    {
                        QTableWidgetItem *fromAdj = ui->tableWidget_adj->item(i, i);
                        bool ok;
                        int numAdj = fromAdj->text().toInt(&ok, 10);
                        ++numAdj;
                        QTableWidgetItem *clon = fromAdj->clone();
                        clon->setText(QString::number(numAdj));
                        ui->tableWidget_adj->setItem(i, i, clon);
                        suc = true;
                        break;
                    }
                    else
                    {
                        continue;
                    }

                    for (int k = i + 1; k < rowsI; ++k)
                    {
                        QTableWidgetItem *item = ui->tableWidget_inc->item(k, j);
                        bool ok;
                        int snum = item->text().toInt(&ok, 10);

                        if (snum == 1)
                        {
                            forAdj_r = k;
                        }
                        else if (snum == -1)
                        {
                            forAdj_c = k;
                        }
                        else
                        {
                            continue;
                        }

                        QTableWidgetItem *fromAdj = ui->tableWidget_adj->item(forAdj_r, forAdj_c);
                        bool ok2;
                        int numAdj = fromAdj->text().toInt(&ok2, 10);
                        ++numAdj;
                        QTableWidgetItem *clon = fromAdj->clone();
                        clon->setText(QString::number(numAdj));
                        ui->tableWidget_adj->setItem(forAdj_r, forAdj_c, clon);
                        suc = true;
                        break;
                    }
                    if(suc)
                    {
                        break;
                    }
                }
            }

            // Paint
            dGraph = new DGraph_draw(this);
            emit draw_graph(ui->tableWidget_adj, true);
            dGraph->show();
        }
    }
    // not directed graph
    //if (ui->radioButton_undir->isChecked()) {
    //if (!data->dir) {
    else {
        for (int i = 0; i < ui->tableWidget_inc->rowCount(); ++i) {
            for (int j = 0; j < ui->tableWidget_inc->columnCount(); j++) {
                QTableWidgetItem *item = ui->tableWidget_inc->item(i, j);
                if (item->text() != '1' && item->text() != '0' && item->text() != '2') {
                    QMessageBox::warning(this, "Wrong input!", "The value in incidence matrix must be 0, 1 or 2!");
                    return;
                }
            }
        }

        for (int i = 0; i < ui->tableWidget_inc->columnCount(); ++i) {
            for (int j = 0; j < ui->tableWidget_inc->rowCount(); ++j) {
                QTableWidgetItem *item = ui->tableWidget_inc->item(j, i);
                if (item->text() == '1') {
                    int count = 0;
                    for (int k = j + 1; k < ui->tableWidget_inc->rowCount(); ++k) {
                        QTableWidgetItem *itm = ui->tableWidget_inc->item(k, i);
                        if (itm->text() == '1') {
                            count++;
                        }
                    }
                    if (count > 1 || count == 0) {
                        QMessageBox::warning(this, "Wrong input!", "Wrong matrix filling!");
                        return;
                    }
                    else { break; }
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
                    adj_matr[a][b] = adj_matr[b][a] = add;
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
            make_matrix(adj_matr);
        }

        /// Paint ///
        dGraph = new DGraph_draw(this);
        emit draw_graph(ui->tableWidget_adj, false);
        dGraph->show();
    }
}

// Оновлення даних
void MainWindow::on_pushButton_rel_clicked()
{
    this->close();
    MainWindow *w = new MainWindow();
    w->show();
}
