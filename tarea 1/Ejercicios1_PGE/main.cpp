#include "clases.h"

int main()
{
    Estudiante un_alumno;
    un_alumno.Registrar("Enzo", "Brasca", "46.373.096", 20, {{"Matematica", 9},{"Programacion", 10}});

    un_alumno.Consultar();

    return 0;
}
