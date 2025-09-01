#ifndef GERENTE_H
#define GERENTE_H

#include "empleado.h"

class Gerente : public Empleado
{
private:
    float bono;
public:
    Gerente(const QString &nombre, int id, float salarioBase, float bonoAnual);

    float calcularSalario() const override;

    void mostrarDatos() const override;

};

#endif // GERENTE_H
