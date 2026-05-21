#pragma once
#include <iostream>
#include <string>
#include "ConexionSP.h"
#include <mysql.h>

using namespace std;

class Proveedor {
private:
    int id_proveedores = 0;
    string proveedor;
    string nit;
    string direccion;
    string telefono;

public:
    // Constructor Vacio
    Proveedor() {}

    // Constructor con parametros
    Proveedor(int id, string prov, string n, string dir, string tel) {
        id_proveedores = id;
        proveedor = prov;
        nit = n;
        direccion = dir;
        telefono = tel;
    }

    // ==============================================
    // METODOS SET (Modificar atributos)
    // ==============================================
    void setId_proveedor(int id) { id_proveedores = id; }
    void setProveedor(string prov) { proveedor = prov; }
    void setNit(string n) { nit = n; }
    void setDireccion(string dir) { direccion = dir; }
    void setTelefono(string tel) { telefono = tel; }

    // ==============================================
    // METODOS GET (Obtener atributos)
    // ==============================================
    int getId_proveedor() { return id_proveedores; }
    string getProveedor() { return proveedor; }
    string getNit() { return nit; }
    string getDireccion() { return direccion; }
    string getTelefono() { return telefono; }

    // ==============================================
    // METODOS CRUD (Base de Datos)
    // ==============================================

    void crear() {
        ConexionSP cn = ConexionSP();
        cn.abrirConexion();
        if (cn.getConexion()) {
            string consulta = "INSERT INTO proveedores(proveedor, nit, direccion, telefono) VALUES ('" + proveedor + "','" + nit + "','" + direccion + "','" + telefono + "');";

            int q_estado = mysql_query(cn.getConexion(), consulta.c_str());
            if (!q_estado) {
                id_proveedores = mysql_insert_id(cn.getConexion());
                cout << ">> Proveedor ingresado exitosamente con el ID: " << id_proveedores << endl;
            }
            else {
                cout << "xxxx Error al ingresar el proveedor xxxx" << endl;
                cout << "Detalle: " << mysql_error(cn.getConexion()) << endl;
            }
        }
        else {
            cout << "xxxx Error de conexion a la base de datos xxxx" << endl;
        }
        cn.cerrarConexion();
    }

    void leer() {
        ConexionSP cn = ConexionSP();
        cn.abrirConexion();
        if (cn.getConexion()) {
            cout << "\n==================== LISTADO DE PROVEEDORES ====================" << endl;
            string consulta = "SELECT id_proveedores, proveedor, nit, direccion, telefono FROM proveedores;";

            int q_estado = mysql_query(cn.getConexion(), consulta.c_str());
            if (!q_estado) {
                MYSQL_RES* resultado = mysql_store_result(cn.getConexion());
                MYSQL_ROW fila;

                while ((fila = mysql_fetch_row(resultado))) {
                    cout << "ID: " << fila[0] << " | Empresa: " << fila[1]
                        << " | NIT: " << fila[2]
                        << " | Dir: " << fila[3]
                        << " | Tel: " << fila[4] << endl;
                }
                mysql_free_result(resultado);
                cout << "================================================================" << endl;
            }
            else {
                cout << "xxxx Error al leer los proveedores xxxx" << endl;
                cout << "Detalle: " << mysql_error(cn.getConexion()) << endl;
            }
        }
        else {
            cout << "xxxx Error de conexion a la base de datos xxxx" << endl;
        }
        cn.cerrarConexion();
    }

    void actualizar() {
        ConexionSP cn = ConexionSP();
        cn.abrirConexion();
        if (cn.getConexion()) {
            string id_prov = to_string(id_proveedores);

            string consulta = "UPDATE proveedores SET proveedor='" + proveedor + "', nit='" + nit + "', direccion='" + direccion + "', telefono='" + telefono + "' WHERE id_proveedores=" + id_prov + ";";

            int q_estado = mysql_query(cn.getConexion(), consulta.c_str());
            if (!q_estado) {
                cout << ">> Proveedor con ID " << id_proveedores << " actualizado exitosamente." << endl;
            }
            else {
                cout << "xxxx Error al actualizar el proveedor xxxx" << endl;
                cout << "Detalle: " << mysql_error(cn.getConexion()) << endl;
            }
        }
        else {
            cout << "xxxx Error de conexion a la base de datos xxxx" << endl;
        }
        cn.cerrarConexion();
    }

    void borrar() {
        ConexionSP cn = ConexionSP();
        cn.abrirConexion();
        if (cn.getConexion()) {
            string id_prov = to_string(id_proveedores);
            string consulta = "DELETE FROM proveedores WHERE id_proveedores=" + id_prov + ";";

            int q_estado = mysql_query(cn.getConexion(), consulta.c_str());
            if (!q_estado) {
                cout << ">> Proveedor con ID " << id_proveedores << " eliminado exitosamente." << endl;
            }
            else {
                cout << "xxxx Error al eliminar el proveedor xxxx" << endl;
                cout << "Detalle: " << mysql_error(cn.getConexion()) << endl;
            }
        }
        else {
            cout << "xxxx Error de conexion a la base de datos xxxx" << endl;
        }
        cn.cerrarConexion();
    }
};