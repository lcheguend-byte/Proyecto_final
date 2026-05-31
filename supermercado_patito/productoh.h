#pragma once
#include <iostream>
#include <string>
#include "ConexionSP.h"
#include <mysql.h>

using namespace std;

class Producto {
private:
    int id_productos = 0;
    string producto;
    int id_marca = 0;
    string descripcion;
    string imagen;
    double precio_costo = 0.0;
    double precio_venta = 0.0;
    int existencia = 0;

public:
    // Constructor Vacio
    Producto() {}

    // Constructor con parametros
    Producto(int id_p, string prod, int id_m, string desc, string img, double pc, double pv, int ex) {
        id_productos = id_p;
        producto = prod;
        id_marca = id_m;
        descripcion = desc;
        imagen = img;
        precio_costo = pc;
        precio_venta = pv;
        existencia = ex;
    }

    // ==============================================
    // METODOS SET (Modificar atributos)
    // ==============================================
    void setId_producto(int id_p) { id_productos = id_p; }
    void setProducto(string prod) { producto = prod; }
    void setId_marca(int id_m) { id_marca = id_m; }
    void setDescripcion(string desc) { descripcion = desc; }
    void setImagen(string img) { imagen = img; }
    void setPrecio_costo(double pc) { precio_costo = pc; }
    void setPrecio_venta(double pv) { precio_venta = pv; }
    void setExistencia(int ex) { existencia = ex; }

    // ==============================================
    // METODOS GET (Obtener atributos)
    // ==============================================
    int getId_producto() { return id_productos; }
    string getProducto() { return producto; }
    int getId_marca() { return id_marca; }
    string getDescripcion() { return descripcion; }
    string getImagen() { return imagen; }
    double getPrecio_costo() { return precio_costo; }
    double getPrecio_venta() { return precio_venta; }
    int getExistencia() { return existencia; }

    // ==============================================
    // METODOS CRUD (Base de Datos)
    // ==============================================

    void crear() {
        ConexionSP cn = ConexionSP();
        cn.abrirConexion();
        if (cn.getConexion()) {
            string id_m = to_string(id_marca);
            string pc = to_string(precio_costo);
            string pv = to_string(precio_venta);
            string ex = to_string(existencia);

            // NOW() para ingresar automaticamente la fecha y hora del sistema
            string consulta = "INSERT INTO productos(producto, id_marca, descripcion, imagen, precio_costo, precio_venta, existencia, fecha_ingreso) VALUES ('" + producto + "'," + id_m + ",'" + descripcion + "','" + imagen + "'," + pc + "," + pv + "," + ex + ", NOW());";

            int q_estado = mysql_query(cn.getConexion(), consulta.c_str());
            if (!q_estado) {
                id_productos = mysql_insert_id(cn.getConexion());
                cout << ">> Producto ingresado exitosamente con el ID: " << id_productos << endl;
            }
            else {
                cout << "xxxx Error al ingresar el producto xxxx" << endl;
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
            cout << "\n========================================= INVENTARIO DE PRODUCTOS =========================================" << endl;
            // Utilizamos INNER JOIN para mostrar el nombre de la marca en lugar del numero de id_marca
            string consulta = "SELECT p.id_productos, p.producto, m.marcas, p.descripcion, p.precio_costo, p.precio_venta, p.existencia, p.fecha_ingreso FROM productos p INNER JOIN marcas m ON p.id_marca = m.id_marcas;";

            int q_estado = mysql_query(cn.getConexion(), consulta.c_str());
            if (!q_estado) {
                MYSQL_RES* resultado = mysql_store_result(cn.getConexion());
                MYSQL_ROW fila;

                while ((fila = mysql_fetch_row(resultado))) {
                    cout << "ID: " << fila[0] << " | Producto: " << fila[1]
                        << " | Marca: " << fila[2]
                        << " | Desc: " << fila[3]
                        << " | Costo: Q" << fila[4]
                        << " | Venta: Q" << fila[5]
                        << " | Stock: " << fila[6]
                        << " | Ingreso: " << fila[7] << endl;
                }
                mysql_free_result(resultado);
                cout << "===========================================================================================================" << endl;
            }
            else {
                cout << "xxxx Error al leer el inventario xxxx" << endl;
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
            string id_p = to_string(id_productos);
            string id_m = to_string(id_marca);
            string pc = to_string(precio_costo);
            string pv = to_string(precio_venta);
            string ex = to_string(existencia);

            // La fecha_ingreso no se actualiza
            string consulta = "UPDATE productos SET producto='" + producto + "', id_marca=" + id_m + ", descripcion='" + descripcion + "', imagen='" + imagen + "', precio_costo=" + pc + ", precio_venta=" + pv + ", existencia=" + ex + " WHERE id_productos=" + id_p + ";";

            int q_estado = mysql_query(cn.getConexion(), consulta.c_str());
            if (!q_estado) {
                cout << ">> Producto con ID " << id_productos << " actualizado exitosamente." << endl;
            }
            else {
                cout << "xxxx Error al actualizar el producto xxxx" << endl;
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
            string id_p = to_string(id_productos);
            string consulta = "DELETE FROM productos WHERE id_productos=" + id_p + ";";

            int q_estado = mysql_query(cn.getConexion(), consulta.c_str());
            if (!q_estado) {
                cout << ">> Producto con ID " << id_productos << " eliminado exitosamente." << endl;
            }
            else {
                cout << "xxxx Error al eliminar el producto xxxx" << endl;
                cout << "Detalle: " << mysql_error(cn.getConexion()) << endl;
            }
        }
        else {
            cout << "xxxx Error de conexion a la base de datos xxxx" << endl;
        }
        cn.cerrarConexion();
    }
};