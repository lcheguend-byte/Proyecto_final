#pragma once
#include <iostream>
#include <string>
#include "ConexionSP.h"
#include <mysql.h>

using namespace std;

class Cliente {
private:
    int id_clientes = 0;
    string nombres;
    string apellidos;
    string nit;
    int genero; 
    string telefono;
    string correo_electronico;

public:
    // Constructor Vacio
    Cliente() {}

    // Constructor con parametros
    Cliente(int id, string nom, string ape, string n, int gen, string tel, string correo) {
        id_clientes = id;
        nombres = nom;
        apellidos = ape;
        nit = n;
        genero = gen;
        telefono = tel;
        correo_electronico = correo;
    }

    // ==============================================
    // METODOS SET (Modificar atributos)
    // ==============================================
    void setId_cliente(int id) { id_clientes = id; }
    void setNombres(string nom) { nombres = nom; }
    void setApellidos(string ape) { apellidos = ape; }
    void setNit(string n) { nit = n; }
    void setGenero(int gen) { genero = gen; }
    void setTelefono(string tel) { telefono = tel; }
    void setCorreoElectronico(string correo) { correo_electronico = correo; }

    // ==============================================
    // METODOS GET (Obtener atributos)
    // ==============================================
    int getId_cliente() { return id_clientes; }
    string getNombres() { return nombres; }
    string getApellidos() { return apellidos; }
    string getNit() { return nit; }
    int getGenero() { return genero; }
    string getTelefono() { return telefono; }
    string getCorreoElectronico() { return correo_electronico; }

    // ===================================================
    // RESTRICCIONES DE SEGURIDAD (MANUEL REYES.)
    // ===================================================
    void validarDatos() {
        if (nit.empty()) {
            cout << "\n[RESTRICCION]: El NIT del cliente no puede estar vacio.\n";
        }
        if (nombres.empty()) {
            cout << "\n[RESTRICCION]: El nombre del cliente no puede estar vacio.\n";
        }
        if (telefono.empty()) {
            cout << "\n[RESTRICCION]: El telefono del cliente no puede estar vacio.\n";
        }
    }

    // ==============================================
    // METODOS CRUD (Base de Datos)
    // ==============================================

    void crear() {
        validarDatos();
        ConexionSP cn = ConexionSP();
        cn.abrirConexion();
        if (cn.getConexion()) {
            string gen = to_string(genero);
            
            string consulta = "INSERT INTO clientes(nombres, apellidos, nit, genero, telefono, correo_electronico, fecha_ingreso) VALUES ('" + nombres + "','" + apellidos + "','" + nit + "'," + gen + ",'" + telefono + "','" + correo_electronico + "', NOW());";

            int q_estado = mysql_query(cn.getConexion(), consulta.c_str());
            if (!q_estado) {
                id_clientes = mysql_insert_id(cn.getConexion());
                cout << ">> Cliente creado exitosamente con el ID: " << id_clientes << endl;
            }
            else {
                cout << "xxxx Error al crear el cliente xxxx" << endl;
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
            cout << "\n======================== LISTADO DE CLIENTES ========================" << endl;
            
            string consulta = "SELECT id_clientes, nit, nombres, apellidos, genero, telefono, correo_electronico, fecha_ingreso FROM clientes;";

            int q_estado = mysql_query(cn.getConexion(), consulta.c_str());
            if (!q_estado) {
                MYSQL_RES* resultado = mysql_store_result(cn.getConexion());
                MYSQL_ROW fila;

                while ((fila = mysql_fetch_row(resultado))) {
                   
                    string sexo = (fila[4][0] == '1' || fila[4][0] == 1) ? "Masculino" : "Femenino";

                    cout << "ID: " << fila[0] << " | NIT: " << fila[1]
                        << " | Nombre: " << fila[2] << " " << fila[3]
                        << " | Genero: " << sexo
                        << " | Tel: " << fila[5]
                        << " | Correo: " << fila[6]
                        << " | Ingreso: " << fila[7] << endl;
                }
                mysql_free_result(resultado);
                cout << "=====================================================================" << endl;
            }
            else {
                cout << "xxxx Error al leer los clientes xxxx" << endl;
                cout << "Detalle: " << mysql_error(cn.getConexion()) << endl;
            }
        }
        else {
            cout << "xxxx Error de conexion a la base de datos xxxx" << endl;
        }
        cn.cerrarConexion();
    }

    void actualizar() {
        validarDatos();
        ConexionSP cn = ConexionSP();
        cn.abrirConexion();
        if (cn.getConexion()) {
            string id_c = to_string(id_clientes);
            string gen = to_string(genero);

            // Nota: No actualizamos 'fecha_ingreso' porque es un dato historico de creacion
            string consulta = "UPDATE clientes SET nombres='" + nombres + "', apellidos='" + apellidos + "', nit='" + nit + "', genero=" + gen + ", telefono='" + telefono + "', correo_electronico='" + correo_electronico + "' WHERE id_clientes=" + id_c + ";";

            int q_estado = mysql_query(cn.getConexion(), consulta.c_str());
            if (!q_estado) {
                cout << ">> Cliente con ID " << id_clientes << " actualizado exitosamente." << endl;
            }
            else {
                cout << "xxxx Error al actualizar el cliente xxxx" << endl;
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
            string id_c = to_string(id_clientes);
            string consulta = "DELETE FROM clientes WHERE id_clientes=" + id_c + ";";

            int q_estado = mysql_query(cn.getConexion(), consulta.c_str());
            if (!q_estado) {
                cout << ">> Cliente con ID " << id_clientes << " eliminado exitosamente." << endl;
            }
            else {
                cout << "xxxx Error al eliminar el cliente xxxx" << endl;
             
                cout << "Detalle: " << mysql_error(cn.getConexion()) << endl;
            }
        }
        else {
            cout << "xxxx Error de conexion a la base de datos xxxx" << endl;
        }
        cn.cerrarConexion();
    }
};