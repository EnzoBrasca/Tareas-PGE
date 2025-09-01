#include <QCoreApplication>
#include <QList>
#include "gerente.h"
#include "programador.h"
#include "analista.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    // Usamos una lista de punteros a la clase base para demostrar polimorfismo.
    QList<Empleado*> listaEmpleados;

    // Creamos instancias de las clases derivadas y las añadimos a la lista.
    listaEmpleados.append(new Gerente("Enzo", 46373096, 15000.0, 7500.0));
    listaEmpleados.append(new Programador("Carlos Perez", 02, 50000.0, "C++ / Qt", 10));
    listaEmpleados.append(new Programador("Maria Rodriguez", 205, 52000.0, "Python", 5));
    listaEmpleados.append(new Analista("Luis Gomez", 301, 45000.0, "Bases de Datos"));

    // Iteramos sobre la lista y llamamos a los métodos de cada empleado.
    // Gracias al polimorfismo, se ejecutará la versión correcta de cada método
    // según el tipo real del objeto (Gerente, Desarrollador o Analista).
    for (Empleado* emp : listaEmpleados) {
        emp->mostrarDatos();
        double salarioTotal = emp->calcularSalario();
        qDebug() << "Salario Calculado Mensual: $" << QString::number(salarioTotal, 'f', 2);
        qDebug() << ""; // Línea en blanco para separar
    }

    // Liberamos la memoria de los objetos creados dinámicamente.
    qDeleteAll(listaEmpleados);
    listaEmpleados.clear();

    // En una aplicación sin bucle de eventos, puedes salir directamente.
    // return a.exec(); // No es necesario para una app de consola simple.
    return 0;
}
