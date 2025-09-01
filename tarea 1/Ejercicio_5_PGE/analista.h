#ifndef ANALISTA_H
#define ANALISTA_H

#include "empleado.h"

class Analista : public Empleado
{
private:
    QString Area;

public:
    Analista( const QString &nombre, int id, float salarioBase, const QString &area);

    float calcularSalario() const  override;

    void mostrarDatos() const override;
};

#endif // ANALISTA_H
