#pragma once
#include <iostream>
#include <string>
#include "ConexionSP.h"
#include <mysql.h>

using namespace std;

class Puesto {
private:
    int id_puestos = 0;
    string puesto;

public:
    Puesto() {}
    Puesto(int id, string p) {
        id_puestos = id;
        puesto = p;
    }

    void setId_puesto(int id) { id_puestos = id; }
    void setPuesto(string p) { puesto = p; }

    int getId_puesto() { return id_puestos; }
    string getPuesto() { return puesto; }

    void crear() {
        ConexionSP cn = ConexionSP();
        cn.abrirConexion();
        if (cn.getConexion()) {
            string consulta = "INSERT INTO puestos(puesto) VALUES ('" + puesto + "');";
            if (!mysql_query(cn.getConexion(), consulta.c_str())) {
                id_puestos = mysql_insert_id(cn.getConexion());
                cout << ">> Puesto ingresado exitosamente con ID: " << id_puestos << endl;
            }
            else { cout << "Error: " << mysql_error(cn.getConexion()) << endl; }
        }
        cn.cerrarConexion();
    }

    void leer() {
        ConexionSP cn = ConexionSP();
        cn.abrirConexion();
        if (cn.getConexion()) {
            cout << "\n--- LISTADO DE PUESTOS ---" << endl;
            string consulta = "SELECT id_puestos, puesto FROM puestos;";
            if (!mysql_query(cn.getConexion(), consulta.c_str())) {
                MYSQL_RES* resultado = mysql_store_result(cn.getConexion());
                MYSQL_ROW fila;
                while ((fila = mysql_fetch_row(resultado))) {
                    cout << "ID: " << fila[0] << " | Puesto: " << fila[1] << endl;
                }
                mysql_free_result(resultado);
            }
        }
        cn.cerrarConexion();
    }

    void actualizar() {
        ConexionSP cn = ConexionSP();
        cn.abrirConexion();
        if (cn.getConexion()) {
            string id_p = to_string(id_puestos);
            string consulta = "UPDATE puestos SET puesto='" + puesto + "' WHERE id_puestos=" + id_p + ";";
            if (!mysql_query(cn.getConexion(), consulta.c_str())) {
                cout << ">> Puesto actualizado exitosamente." << endl;
            }
            else { cout << "Error: " << mysql_error(cn.getConexion()) << endl; }
        }
        cn.cerrarConexion();
    }

    void borrar() {
        ConexionSP cn = ConexionSP();
        cn.abrirConexion();
        if (cn.getConexion()) {
            string id_p = to_string(id_puestos);
            string consulta = "DELETE FROM puestos WHERE id_puestos=" + id_p + ";";
            if (!mysql_query(cn.getConexion(), consulta.c_str())) {
                cout << ">> Puesto eliminado exitosamente." << endl;
            }
            else { cout << "Error (Posiblemente en uso): " << mysql_error(cn.getConexion()) << endl; }
        }
        cn.cerrarConexion();
    }
};
