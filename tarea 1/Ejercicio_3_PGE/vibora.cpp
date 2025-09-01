#include "vibora.h"

Vibora::Vibora(const QPointF &startPos)
    : m_direction(Direction::Right),
    m_lastMovedDirection(Direction::Right),
    m_pendingGrowth(0)
{


    m_body.append(new ViboraSegment(startPos));
    m_body.append(new ViboraSegment(QPointF(startPos.x() - 1, startPos.y())));
    m_body.append(new ViboraSegment(QPointF(startPos.x() - 2, startPos.y())));
}

Vibora::~Vibora()
{

    qDeleteAll(m_body);
    m_body.clear();
}

void Vibora::setDirection(Direction dir)
{

    if (m_lastMovedDirection == Direction::Up && dir == Direction::Down) return;
    if (m_lastMovedDirection == Direction::Down && dir == Direction::Up) return;
    if (m_lastMovedDirection == Direction::Left && dir == Direction::Right) return;
    if (m_lastMovedDirection == Direction::Right && dir == Direction::Left) return;

    m_direction = dir;
}

Direction Vibora::direction() const
{
    return m_direction;
}

void Vibora::move()
{
    QPointF newHeadPos = headPosition();
    switch (m_direction) {
    case Direction::Up:    newHeadPos.ry()--; break;
    case Direction::Down:  newHeadPos.ry()++; break;
    case Direction::Left:  newHeadPos.rx()--; break;
    case Direction::Right: newHeadPos.rx()++; break;
    case Direction::None:  return;
    }
    m_lastMovedDirection = m_direction;


    m_body.prepend(new ViboraSegment(newHeadPos));


    if (m_pendingGrowth > 0) {
        m_pendingGrowth--;
    } else {
        delete m_body.last();
        m_body.removeLast();
    }
}

void Vibora::grow()
{
    m_pendingGrowth++;
}

void Vibora::paint(QPainter *painter)
{

    for (Objeto* segment : m_body) {
        segment->paint(painter);
    }

    if (!m_body.isEmpty()) {
        painter->save();
        painter->setBrush(QBrush(QColor(0, 180, 0)));
        painter->drawRect(m_body.first()->boundingRect());
        painter->restore();
    }
}

QPointF Vibora::headPosition() const
{
    return m_body.isEmpty() ? QPointF(0, 0) : m_body.first()->position();
}

bool Vibora::checkSelfCollision() const
{
    if (m_body.size() < 2) {
        return false;
    }
    const QPointF headPos = headPosition();

    for (int i = 1; i < m_body.size(); ++i) {
        if (m_body.at(i)->position() == headPos) {
            return true;
        }
    }
    return false;
}

bool Vibora::occupies(const QPointF &pos) const
{
    for(const auto& segment : m_body) {
        if (segment->position() == pos) {
            return true;
        }
    }
    return false;
}
