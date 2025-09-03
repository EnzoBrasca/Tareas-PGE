#ifndef OBJETOS_H
#define OBJETOS_H

#include <iostream>
#include <QString>
#include <QTime>
#include <QDate>

class Reserva;

class Vuelos
{
private:
    QString NumeroDeVuelo;
    QString Origen;
    QString Destino;
    QDateTime fecha;
    int CapacidadMaxima;
    QString estado;

    QList<Reserva*> m_listaReservas;
public:
    Vuelos(const QString &numeroVuelo, const QString &origen, const QString &destino, const QDateTime &salida, int capacidad);

    int obtenerAsientosDisponibles();
    bool agregarReserva(Reserva *resreva);
    void cambiarEstado(const QString &nuevoEstado);

    QString obtenerNumeroDeVuelo();
};



#endif // OBJETOS_H
