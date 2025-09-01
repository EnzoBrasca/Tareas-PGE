#include "comida.h"

Comida::Comida(const QPointF &pos) : Objeto(pos)
{
}

void Comida::paint(QPainter *painter)
{
    painter->save();
    painter->setBrush(QBrush(Qt::red));
    painter->drawEllipse(boundingRect());
    painter->restore();
}
