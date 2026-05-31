#pragma once
#include <iostream>
#include <string>
#include "ConexionSP.h"
#include <mysql.h>

using namespace std;

class Empleado {
private:
    int id_empleados = 0;
    string nombres;
    string apellidos;
    string direccion;
    string telefono;
    string cui;
    int genero = 0;
    string fecha_nacimiento;
    int id_puesto = 0;
    string fecha_inicio_labores;

public:
    Empleado() {}

    // Setters
    void setId_empleado(int id) { id_empleados = id; }
    void setNombres(string nom) { nombres = nom; }
    void setApellidos(string ape) { apellidos = ape; }
    void setDireccion(string dir) { direccion = dir; }
    void setTelefono(string tel) { telefono = tel; }
    void setCui(string c) { cui = c; }
    void setGenero(int gen) { genero = gen; }
    void setFecha_nacimiento(string fn) { fecha_nacimiento = fn; }
    void setId_puesto(int id_p) { id_puesto = id_p; }
    void setFecha_inicio_labores(string fil) { fecha_inicio_labores = fil; }

    void crear() {
        ConexionSP cn = ConexionSP();
        cn.abrirConexion();
        if (cn.getConexion()) {
            string id_p = to_string(id_puesto);
            string gen = to_string(genero);

            string consulta = "INSERT INTO empleados(nombres, apellidos, direccion, telefono, cui, genero, fecha_nacimiento, id_puesto, fecha_inicio_labores, fecha_ingreso) VALUES ('" + nombres + "','" + apellidos + "','" + direccion + "','" + telefono + "','" + cui + "'," + gen + ",'" + fecha_nacimiento + "'," + id_p + ",'" + fecha_inicio_labores + "', NOW());";

            if (!mysql_query(cn.getConexion(), consulta.c_str())) {
                cout << ">> Empleado creado exitosamente." << endl;
            }
            else { cout << "Error: " << mysql_error(cn.getConexion()) << endl; }
        }
        cn.cerrarConexion();
    }

    void leer() {
        ConexionSP cn = ConexionSP();
        cn.abrirConexion();
        if (cn.getConexion()) {
            cout << "\n============================== LISTADO DE EMPLEADOS ==============================" << endl;
            string consulta = "SELECT e.id_empleados, e.nombres, e.apellidos, e.cui, e.telefono, p.puesto, e.fecha_inicio_labores FROM empleados e INNER JOIN puestos p ON e.id_puesto = p.id_puestos;";

            if (!mysql_query(cn.getConexion(), consulta.c_str())) {
                MYSQL_RES* resultado = mysql_store_result(cn.getConexion());
                MYSQL_ROW fila;

                while ((fila = mysql_fetch_row(resultado))) {
                    cout << "ID: " << fila[0] << " | Nombre: " << fila[1] << " " << fila[2]
                        << " | CUI: " << fila[3] << " | Tel: " << fila[4]
                        << " | Puesto: " << fila[5] << " | Ingreso: " << fila[6] << endl;
                }
                mysql_free_result(resultado);
            }
            cout << "==================================================================================" << endl;
        }
        cn.cerrarConexion();
    }

    void actualizar() {
        ConexionSP cn = ConexionSP();
        cn.abrirConexion();
        if (cn.getConexion()) {
            string id_e = to_string(id_empleados);
            string id_p = to_string(id_puesto);
            string gen = to_string(genero);

            string consulta = "UPDATE empleados SET nombres='" + nombres + "', apellidos='" + apellidos + "', direccion='" + direccion + "', telefono='" + telefono + "', cui='" + cui + "', genero=" + gen + ", fecha_nacimiento='" + fecha_nacimiento + "', id_puesto=" + id_p + ", fecha_inicio_labores='" + fecha_inicio_labores + "' WHERE id_empleados=" + id_e + ";";

            if (!mysql_query(cn.getConexion(), consulta.c_str())) {
                cout << ">> Empleado actualizado exitosamente." << endl;
            }
            else { cout << "Error: " << mysql_error(cn.getConexion()) << endl; }
        }
        cn.cerrarConexion();
    }

    void borrar() {
        ConexionSP cn = ConexionSP();
        cn.abrirConexion();
        if (cn.getConexion()) {
            string id_e = to_string(id_empleados);
            string consulta = "DELETE FROM empleados WHERE id_empleados=" + id_e + ";";
            if (!mysql_query(cn.getConexion(), consulta.c_str())) {
                cout << ">> Empleado eliminado exitosamente." << endl;
            }
            else { cout << "Error: " << mysql_error(cn.getConexion()) << endl; }
        }
        cn.cerrarConexion();
    }
};