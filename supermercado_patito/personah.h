#pragma once
#include <iostream>
#include <string>

using namespace std;

class Persona {
    // 'protected' permite que las clases que heredan (Cliente, Empleado) puedan usar estas variables
protected:
    string nombres;
    string apellidos;
    string direccion;
    int telefono;
    string fecha_nacimiento;

public:
    // Constructor vacio
    Persona() {}

    // Constructor 1: Para entidades que NO requieren fecha de nacimiento (Ej: Cliente)
    Persona(string nom, string ape, string dir, int tel) {
        nombres = nom;
        apellidos = ape;
        direccion = dir;
        telefono = tel;
        fecha_nacimiento = ""; // Queda en blanco por defecto
    }

    // Constructor 2: Para entidades que SI requieren fecha de nacimiento (Ej: Empleado)
    Persona(string nom, string ape, string dir, int tel, string fn) {
        nombres = nom;
        apellidos = ape;
        direccion = dir;
        telefono = tel;
        fecha_nacimiento = fn;
    }

    // Metodos SET (Modificar atributos)
    void setNombres(string n) { nombres = n; }
    void setApellidos(string a) { apellidos = a; }
    void setDireccion(string d) { direccion = d; }
    void setTelefono(int t) { telefono = t; }
    void setFecha_Nacimiento(string fn) { fecha_nacimiento = fn; }

    // Metodos GET (Mostrar atributos)
    string getNombres() { return nombres; }
    string getApellidos() { return apellidos; }
    string getDireccion() { return direccion; }
    int getTelefono() { return telefono; }
    string getFecha_Nacimiento() { return fecha_nacimiento; }
};

