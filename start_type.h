#ifndef START_TYPE_H
#define START_TYPE_H

#include <QMap>
#include <QPointF>

// ������� � ���i����� ������
typedef struct
{
    int clmns;
    int rows;
    bool dir;
    bool matr_adj;

} TStartM;

// �i����i��i��� ����� ���設� -- ���न���
typedef QMap <int,QPointF> VertexCoord;

#endif // START_TYPE_H
