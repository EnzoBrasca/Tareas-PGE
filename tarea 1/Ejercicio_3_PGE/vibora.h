#ifndef VIBORA_H
#define VIBORA_H

#include "objeto.h"
#include <QList>
#include <QPointF>

enum class Direction { None, Up, Down, Left, Right };

class ViboraSegment : public Objeto{
public:
    ViboraSegment(const QPointF& pos) : Objeto(pos) {}
    void paint(QPainter* painter) override {
        painter->save();
        painter->setBrush(QBrush(Qt::green));
        painter->drawRect(boundingRect());
        painter->restore();
    }
};

class Vibora
{
public:
    Vibora(const QPointF& startPos);
    ~Vibora();

    void move();
    void grow();
    void setDirection(Direction dir);
    Direction direction() const;

    void paint(QPainter* painter);

    QPointF headPosition() const;
    bool checkSelfCollision() const;
    bool occupies(const QPointF& pos) const;

private:
    QList<Objeto*> m_body;
    Direction m_direction;
    Direction m_lastMovedDirection;
    int m_pendingGrowth;
};

#endif
