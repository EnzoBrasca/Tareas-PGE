#ifndef COMIDA_H
#define COMIDA_H

#include "objeto.h"

class Comida : public Objeto
{
public:
    Comida(const QPointF& pos);

    void paint(QPainter* painter) override;
};

#endif // COMIDA_H
