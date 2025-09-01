#include "gerente.h"
#include <qDebug>
Gerente::Gerente(const QString &nombre, int id, float salarioBase, float bonoAnual)
    : Empleado(nombre, id, salarioBase), bono(bonoAnual) {}

float Gerente::calcularSalario() const {
    return Salario + (bono / 12);
}

void Gerente::mostrarDatos() const {
    qDebug() << "--Gerente--";
    Empleado::mostrarDatos();
    qDebug() << "Bono Anual: $" << QString::number(bono, 'f', 2);
}
