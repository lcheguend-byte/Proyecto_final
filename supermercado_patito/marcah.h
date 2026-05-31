#pragma once
#include <iostream>
#include <string>
#include "ConexionSP.h"
#include <mysql.h>

using namespace std;

class Marca {
private:
    int id_marcas = 0;
    string marcas;

public:
    Marca() {}
    Marca(int id_m, string m) {
        id_marcas = id_m;
        marcas = m;
    }

    void setId_marca(int id) { id_marcas = id; }
    void setMarca(string m) { marcas = m; }

    int getId_marca() { return id_marcas; }
    string getMarca() { return marcas; }

    void crear() {
        ConexionSP cn = ConexionSP();
        cn.abrirConexion();
        if (cn.getConexion()) {
            string consulta = "INSERT INTO marcas(marcas) VALUES ('" + marcas + "');";
            int q_estado = mysql_query(cn.getConexion(), consulta.c_str());
            if (!q_estado) {
                cout << ">> Marca ingresada exitosamente." << endl;
            }
            else {
                cout << "Error al ingresar: " << mysql_error(cn.getConexion()) << endl;
            }
        }
        cn.cerrarConexion();
    }

    void leer() {
        int q_estado = 0;
        ConexionSP cn = ConexionSP();
        MYSQL_ROW fila;
        MYSQL_RES* resultado;
        cn.abrirConexion();
        if (cn.getConexion()) {
            cout << "___________ Marcas REGISTRADAS ___________" << endl;
            string consulta = "select * from marcas;";
            const char* c = consulta.c_str();
            q_estado = mysql_query(cn.getConexion(), c);
            if (!q_estado) {
                resultado = mysql_store_result(cn.getConexion());
                while (fila = mysql_fetch_row(resultado)) {
                    cout << fila[0] << "," << fila[1] << "," << endl;
                }
            }
            else {
                cout << " xxx Consulta Fallida xxx" << endl;
            }
        }
        cn.cerrarConexion();
    }
    void actualizar() {
        ConexionSP cn = ConexionSP();
        cn.abrirConexion();
        if (cn.getConexion()) {
            string id_m = to_string(id_marcas);

            string consulta = "UPDATE marcas SET marcas='" + marcas + "' WHERE id_marcas=" + id_m + ";";
            if (!mysql_query(cn.getConexion(), consulta.c_str())) {
                cout << ">> Marca actualizada." << endl;
            }
            else { cout << "Error: " << mysql_error(cn.getConexion()) << endl; }
        }
        cn.cerrarConexion();
    }

    void borrar() {
        ConexionSP cn = ConexionSP();
        cn.abrirConexion();
        if (cn.getConexion()) {
            string id_m = to_string(id_marcas);
            string consulta = "DELETE FROM marcas WHERE id_marcas=" + id_m + ";";
            if (!mysql_query(cn.getConexion(), consulta.c_str())) {
                cout << ">> Marca eliminada." << endl;
            }
            else { cout << "Error (Posiblemente en uso): " << mysql_error(cn.getConexion()) << endl; }
        }
        cn.cerrarConexion();
    }
};
