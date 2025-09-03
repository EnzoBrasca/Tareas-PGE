#include <QCoreApplication>
#include <QDebug> // Para imprimir en consola de forma sencilla
#include <QDate>

// Incluimos las cabeceras de TODAS las clases que vamos a usar
#include "Vuelos.h" // Asumo que mantuviste el nombre Vuelos.h
#include "Pasajero.h"
#include "Reserva.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);



    Vuelos *vuelo1 = new Vuelos("AR1882", "Buenos Aires (EZE)", "Madrid (MAD)", QDateTime::currentDateTime().addDays(30), 150);
    Vuelos *vuelo2 = new Vuelos("LV3020", "Córdoba (COR)", "Bariloche (BRC)", QDateTime::currentDateTime().addDays(15), 90);

    Pasajero pasajero1("28.111.222", "Lionel", "Messi", QDate(1987, 6, 24));
    Pasajero pasajero2("35.333.444", "Emiliano", "Martinez", QDate(1992, 9, 2));

    qDebug() << ">>> Vuelos y pasajeros creados:";
    qDebug() << "Vuelo disponible:" << vuelo1->obtenerNumeroDeVuelo() << "con" << vuelo1->obtenerAsientosDisponibles() << "asientos.";
    qDebug() << "Vuelo disponible:" << vuelo2->obtenerNumeroDeVuelo() << "con" << vuelo2->obtenerAsientosDisponibles() << "asientos.";
    qDebug() << "Pasajero:" << pasajero1.obtenerNombreCompleto() << ", Edad:" << pasajero1.obtenerEdad();
    qDebug() << "Pasajero:" << pasajero2.obtenerNombreCompleto() << ", Edad:" << pasajero2.obtenerEdad();
    qDebug() << "";



    qDebug() << ">>> " << pasajero1.obtenerNombreCompleto() << " intenta reservar en el vuelo" << vuelo1->obtenerNumeroDeVuelo();


    Reserva *reserva1 = new Reserva(&pasajero1, vuelo1);
    reserva1->asignarAsiento("22A");

    if (vuelo1->agregarReserva(reserva1)) {
        qDebug() << "   Reserva exitosa!";
    } else {
        qDebug() << "   Fallo en la reserva.";
        delete reserva1;
    }


    qDebug() << ">>> " << pasajero2.obtenerNombreCompleto() << " intenta reservar en el vuelo" << vuelo2->obtenerNumeroDeVuelo();
    Reserva *reserva2 = new Reserva(&pasajero2, vuelo2);
    reserva2->asignarAsiento("10C");
    vuelo2->agregarReserva(reserva2);

    qDebug() << ">>> " << pasajero1.obtenerNombreCompleto() << " intenta reservar en el vuelo" << vuelo2->obtenerNumeroDeVuelo();
    Reserva *reserva3 = new Reserva(&pasajero1, vuelo2);
    reserva3->asignarAsiento("11B");
    vuelo2->agregarReserva(reserva3);
    qDebug() << "";



    qDebug() << "Asientos restantes en" << vuelo1->obtenerNumeroDeVuelo() << ":" << vuelo1->obtenerAsientosDisponibles();
    qDebug() << "Asientos restantes en" << vuelo2->obtenerNumeroDeVuelo() << ":" << vuelo2->obtenerAsientosDisponibles();
    qDebug() << "";
    qDebug() << ">>> Detalles de las reservas realizadas:";


    qDebug() << reserva1->obtenerDetalleReserva();
    qDebug() << reserva2->obtenerDetalleReserva();
    qDebug() << reserva3->obtenerDetalleReserva();
    qDebug() << "";



    delete vuelo1;
    delete vuelo2;

    return 0;
}
