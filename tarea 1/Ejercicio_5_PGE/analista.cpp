#include "analista.h"

Analista::Analista( const QString &nombre, int id, float salarioBase, const QString &area):
    Empleado(nombre, id, salarioBase), Area(area){}

float  Analista::calcularSalario() const {
    return Salario;
}

void Analista::mostrarDatos() const {
    qDebug() << "--- Analista ---";
    Empleado::mostrarDatos();
    qDebug() << "Área de Especialización:" << Area;
    qDebug() << "Rol: Analista de Sistemas";
}
