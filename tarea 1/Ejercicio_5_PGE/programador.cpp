#include "programador.h"

Programador::Programador(const  QString &nombre, int id, float salarioBase, const QString &lenguaje, int horasExtra)
    : Empleado(nombre, id, salarioBase), Lenguaje(lenguaje), TarifaExtra(horasExtra) {}

float Programador::calcularSalario() const {
    return Salario + (horasExtra * TarifaExtra);
}

void Programador::mostrarDatos() const {
    qDebug() << "--- Desarrollador ---";
    Empleado::mostrarDatos();
    qDebug() << "Lenguaje Principal:" << Lenguaje;
    qDebug() << "Horas Extra:" << horasExtra;
    qDebug() << "Rol: Desarrollador de Software";
}
