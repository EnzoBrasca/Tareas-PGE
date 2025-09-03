#include "Vuelos.h"
#include "reserva.h"

#include <QDebug>

Vuelos::Vuelos(const QString &numeroVuelo, const QString &origen, const QString &destino, const QDateTime &salida, int capacidad):
      NumeroDeVuelo(numeroVuelo),
      Origen(origen),
      Destino(destino),
      fecha(salida),
      CapacidadMaxima(capacidad),
      estado("confimado")
{

}

int Vuelos::obtenerAsientosDisponibles()
{
    return CapacidadMaxima - m_listaReservas.count();
}

bool Vuelos::agregarReserva(Reserva *reserva)
{
    if (obtenerAsientosDisponibles() > 0) {
        m_listaReservas.append(reserva);
        return true;
    } else {
        qDebug() << "Error: No hay asientos disponibles en el vuelo" << NumeroDeVuelo;
        return false;
    }
}

void Vuelos::cambiarEstado(const QString &nuevoEstado)
{
    estado = nuevoEstado;
}

QString Vuelos::obtenerNumeroDeVuelo()
{
    return NumeroDeVuelo;
}
