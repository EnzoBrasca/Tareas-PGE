#include "pasajero.h" // Incluye su propia cabecera

// Constructor y métodos permanecen idénticos a la versión anterior.
Pasajero::Pasajero(const QString &dni, const QString &nombre, const QString &apellido, const QDate &fechaNacimiento)
    : DNI(dni), Nombre(nombre), Apellido(apellido), Nacimiento(fechaNacimiento)
{
}

QString Pasajero::obtenerNombreCompleto()
{
    return Nombre + " " + Apellido;
}

int Pasajero::obtenerEdad()
{
    if (!Nacimiento.isValid()) {
        return 0;
    }
    return Nacimiento.daysTo(QDate::currentDate()) / 365;
}

void Pasajero::actualizarContacto(const QString &nuevoContacto)
{
    Mail = nuevoContacto;
}
