#ifndef RESERVA_H
#define RESERVA_H
#include <QString>
#include <QTime>
#include <QDate>
#include "Vuelos.h"
#include "pasajero.h"

class Reserva{
private:
    QString Codigo;
    QDateTime Fecha;
    QString Asiento;
    QString Estado;

    Pasajero * pasajero;
    Vuelos *vuelos;
public:
    // El constructor necesita los objetos con los que se asocia
    Reserva(Pasajero *pasajero, Vuelos *vuelo);

    // Métodos públicos
    void confirmarReserva();
    void cancelarReserva();
    QString obtenerDetalleReserva() const;
    void asignarAsiento(const QString &asiento);

    // Getters para acceder a los objetos asociados
    Pasajero* getPasajero() const;
    Vuelos* getVuelo() const;
    QString getCodigoReserva() const;
};

#endif // RESERVA_H
