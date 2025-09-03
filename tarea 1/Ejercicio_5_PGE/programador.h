#ifndef PROGRAMADOR_H
#define PROGRAMADOR_H

#include "empleado.h"

class Programador: public Empleado
{
private:
    QString Lenguaje;
    int horasExtra;
    float TarifaExtra = 50.0;

public:
   Programador(const QString &nombre, int id, float salarioBase, const QString &lenguaje, int horasExtra);

    float calcularSalario() const override;
    void mostrarDatos() const override;
};

#endif // PROGRAMADOR_H
