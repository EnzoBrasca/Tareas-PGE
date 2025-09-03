#include "objeto.h"

Objeto::Objeto(const QPointF &pos) : m_pos(pos)
{
}

QPointF Objeto::position() const
{
    return m_pos;
}


QRectF Objeto::boundingRect() const
{
    return QRectF(m_pos.x() * TILE_SIZE, m_pos.y() * TILE_SIZE, TILE_SIZE, TILE_SIZE);
}
