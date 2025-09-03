#include "clases.h"

using namespace std;
void Estudiante::Registrar(string nombre, string apellido, string dni, int edad, vector<Materia> materias ){
    Nombre = nombre;
    Apellido = apellido;
    DNI = dni;
    Edad = edad;
    Materias = materias;
}

void Estudiante::Consultar(){
    cout << "\n--- Datos del Alumno ---" << std::endl;

    cout << "Nombre completo: " << Nombre << " " << Apellido << std::endl;

    cout << "Edad: " << Edad << std::endl;
    cout << "Legajo: " << DNI << std::endl;
    cout << "--- Materias y Notas ---" << std::endl;
    for (const auto& materia : Materias) {

        cout << "Materia: " << materia.materia << " - Nota: " << materia.Nota << std::endl;
    }
}
