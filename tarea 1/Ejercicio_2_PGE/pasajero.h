#ifndef PASAJERO_H
#define PASAJERO_H

#include <QString>
#include <QTime>
#include <QDate>

class Pasajero{
private:
    QString Nombre;
    QString Apellido;
    QString DNI;
    QDate Nacimiento;
    QString Mail;
public:
    Pasajero(const QString &dni, const QString &nombre, const QString &apellido, const QDate &fechaNacimiento);

    QString obtenerNombreCompleto();
    int obtenerEdad();
    void actualizarContacto(const QString &nuevoContacto);
};
#endif // PASAJERO_H
