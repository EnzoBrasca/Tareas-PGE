#ifndef CLASES_H
#define CLASES_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Materia{
    string materia = "";
    int Nota = 0;
};

class Persona
{
protected:
    int Edad = 0;
    string Nombre;
    string Apellido;
    string DNI;
};

class Estudiante: public Persona
{

public:
    vector<Materia> Materias;
    void Registrar(string nombre, string apellido, string dni, int edad, vector<Materia> materias);
    void Consultar();
};

#endif



