#include "reserva.h"

// ¡IMPORTANTE! Aquí incluimos las definiciones completas de Pasajero y Vuelo
// porque necesitamos llamar a sus métodos (ej: obtenerNombreCompleto()).
#include "pasajero.h"
#include "Vuelos.h"

#include <QRandomGenerator>

Reserva::Reserva(Pasajero *pasajero, Vuelos *vuelo)
    : pasajero(pasajero),
    vuelos(vuelo),
    Fecha(QDateTime::currentDateTime()),
    Estado("Confirmada")
{
    const QString posiblesCaracteres = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (int i = 0; i < 6; ++i) {
        int index = QRandomGenerator::global()->bounded(posiblesCaracteres.length());
        QChar nextChar = posiblesCaracteres.at(index);
        Codigo.append(nextChar);
    }
}

void Reserva::confirmarReserva()
{
    Estado = "Confirmada";
}

void Reserva::cancelarReserva()
{
    Estado = "Cancelada";
}

void Reserva::asignarAsiento(const QString &asiento)
{
    Asiento = asiento;
}

QString Reserva::obtenerDetalleReserva() const
{
    if (!pasajero || !vuelos) {
        return "Error: Datos de la reserva incompletos.";
    }

    return QString("Reserva %1 - Pasajero: %2 - Vuelo: %3 - Asiento: %4")
        .arg(Codigo)
        .arg(pasajero->obtenerNombreCompleto())
        .arg(vuelos->obtenerNumeroDeVuelo())
        .arg(Asiento.isEmpty() ? "No asignado" : Asiento);
}

Pasajero* Reserva::getPasajero() const
{
    return pasajero;
}

Vuelos* Reserva::getVuelo() const
{
    return vuelos;
}

QString Reserva::getCodigoReserva() const
{
    return Codigo;
}
