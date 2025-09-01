#ifndef OBJETO_H
#define OBJETO_H

#include <QPainter>
#include <QPointF>
#include <QRectF>

const int TILE_SIZE = 20;

class Objeto
{
public:

    Objeto(const QPointF& pos);

    virtual ~Objeto() = default;


    virtual void paint(QPainter* painter) = 0;


    QPointF position() const;
    QRectF boundingRect() const;

protected:

    QPointF m_pos;
};

#endif // OBJETO_H
