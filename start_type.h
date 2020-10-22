#ifndef START_TYPE_H
#define START_TYPE_H

#include <QMap>
#include <QPointF>

// Структура з вихiдними даними
typedef struct
{
    int clmns;
    int rows;
    bool dir;
    bool matr_adj;

} TStartM;

// Вiдповiднiсть номер вершини -- координати
typedef QMap <int,QPointF> VertexCoord;

#endif // START_TYPE_H
