#include "dgraph_draw.h"
#include "ui_dgraph_draw.h"
#include "start_type.h"
#include <QPen>
#include <QPainter>
#include <QDebug>

const int CIRCLE_W = 20;    // �i����� ����

// ���設� i �� ���न���
VertexCoord vertex = {
                      {0, QPointF(300, 510)},
                      {1, QPointF(418.001, 126.288)},
                      {2, QPointF(115, 399.373)},
                      {3, QPointF(510, 300)},
                      {4, QPointF(181.999, 126.288)},
                      {5, QPointF(418.001, 473.712)},
                      {6, QPointF(300, 90)},
                      {7, QPointF(182, 473.712)},
                      {8, QPointF(485, 200.627)},
                      {9, QPointF(90, 300)},
                      {10, QPointF(485, 399.373)},
                      {11, QPointF(115, 200.627)}
                     };

DGraph_draw::DGraph_draw(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DGraph_draw)
{
    ui->setupUi(this);
    this->setWindowTitle("Your Graph");
    connect(parent, SIGNAL(draw_graph(QTableWidget *, bool)), this, SLOT(when_draw_graph(QTableWidget *, bool)));
}

DGraph_draw::~DGraph_draw()
{
    delete ui;
}

// �਩��� ���i �� ���, 直� �ॡ� ��㢠�
void DGraph_draw::when_draw_graph(QTableWidget *tab, bool isDir)
{
    Dtab = tab;
    isDir___ = isDir;
}

// �㭪�i� ��㢠��� ��?��� �?���
void DGraph_draw::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QPen blackP(Qt::black); // ���i� ॡ��
    blackP.setWidth(2);
    painter.setPen(blackP);

    // ��� ����
    if (!isDir___)
    {
        // ��ॣ�鸞� ������� ��� �� �i�������� � �����? ��i�����i
        for (int i = 0; i < Dtab->rowCount(); ++i)
        {
            for (int j = i; j < Dtab->columnCount(); ++j)
            {
                if (Dtab->item(i, j)->text() != "0")
                {
                    // ��� ����
                    if (i==j)
                    {
                        painter.drawEllipse(vertex[i].x()-CIRCLE_W, vertex[i].y()-CIRCLE_W, CIRCLE_W+20, CIRCLE_W+20);
                    }
                    else
                    {
                        // ������� �i�i��
                        painter.drawLine(vertex[i].x()+CIRCLE_W/2, vertex[i].y()+CIRCLE_W/2, vertex[j].x()+CIRCLE_W/2, vertex[j].y()+CIRCLE_W/2);
                        bool ok;
                        // ��ਬ�� �᫮ ॡ��
                        int countE = Dtab->item(i,j)->text().toInt(&ok, 10);
                        --countE;

                        int h = 50;
                        // ���i ॡ� ���� �ਢ���
                        while (countE > 0)
                        {
                            QPainterPath path;
                            path.moveTo(vertex[i].x()+CIRCLE_W/2, vertex[i].y()+CIRCLE_W/2);
                            double midlX = (vertex[i].x() + vertex[j].x()) / 2 + h;
                            double midlY = (vertex[i].y() + vertex[j].y()) / 2 - h;
                            path.cubicTo(QPointF(midlX, midlY), QPointF(midlX, midlY), QPointF(vertex[j].x()+CIRCLE_W/2, vertex[j].y()+CIRCLE_W/2));

                            painter.drawPath(path);
                            h += 50;
                            --countE;
                        }
                    }
                }
            }
        }
    }
    // ��� ��
    else
    {
        // ��ॣ�鸞� ��? �������
        for (int i = 0; i < Dtab->rowCount(); ++i)
        {
            for (int j = 0; j < Dtab->columnCount(); ++j)
            {
                if (Dtab->item(i, j)->text() != "0")
                {
                    if (i==j)
                    {
                        painter.drawEllipse(vertex[i].x()-CIRCLE_W, vertex[i].y()-CIRCLE_W, CIRCLE_W+20, CIRCLE_W+20);
                    }
                    else
                    {
                        painter.drawLine(vertex[i].x()+CIRCLE_W/2, vertex[i].y()+CIRCLE_W/2, vertex[j].x()+CIRCLE_W/2, vertex[j].y()+CIRCLE_W/2);
                    }
                }
            }
        }
    }

    QPen magP(Qt::magenta);     // ������ ���設
    QBrush cyanB(Qt::cyan);     // ���i� ���設
    magP.setWidth(4);

    painter.setPen(magP);
    painter.setBrush(cyanB);

    // ���㢠��� ���設
    for(int i = 0; i < Dtab->rowCount(); ++i)
    {
        painter.drawEllipse(vertex[i].x(), vertex[i].y(), CIRCLE_W, CIRCLE_W);
    }

    // ���㢠��� ����שׁ�
    if (isDir___)
    {
        // ���i� ���i��箪
        QBrush arrB(Qt::black);
        painter.setPen(Qt::black);
        painter.setBrush(arrB);
        // ��ॣ鸞� ��? �������
        for (int i = 0; i < Dtab->rowCount(); ++i)
        {
            for (int j = 0; j < Dtab->columnCount(); ++j)
            {
                if (i==j)
                {
                    continue;
                }
                if (Dtab->item(i, j)->text() != "0")
                {
                    // ����� �ਪ�⭨�
                    const QPointF points[3] =
                    {
                        QPointF(vertex[j].x()+CIRCLE_W/2+5, vertex[j].y()+CIRCLE_W/2),
                        QPointF(vertex[j].x()+CIRCLE_W/2+5, vertex[j].y()+CIRCLE_W/2+5),
                        QPointF(vertex[j].x()+CIRCLE_W/2-5, vertex[j].y()+CIRCLE_W/2+5)
                    };

                    painter.drawPolygon(points, 3);
                }
            }
        }
    }
}
