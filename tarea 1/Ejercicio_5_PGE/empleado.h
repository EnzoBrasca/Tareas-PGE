#ifndef EMPLEADO_H
#define EMPLEADO_H

#include <QString>
#include <qDebug>
class Empleado
{
protected:
    QString Nombre;
    int DNI;
    float Salario;
public:
    Empleado(const QString &nombre, int id, double salarioBase)
        : Nombre(nombre), DNI(id), Salario(salarioBase) {};
    virtual ~Empleado();

    virtual float calcularSalario() const = 0;

    virtual void mostrarDatos() const{
        qDebug() << "ID:" << DNI;
        qDebug() << "Nombre:" << Nombre;
        qDebug() << "Salario Base: $" << QString::number(Salario, 'f', 2);
    };
};

#endif // EMPLEADO_H
