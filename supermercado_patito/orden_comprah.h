#pragma once
#include <iostream>
#include <string>
#include "ConexionSP.h"
#include <mysql.h>

using namespace std;

class Compra {
public:
    void nuevaCompra() {
        ConexionSP cn = ConexionSP();
        cn.abrirConexion();
        if (cn.getConexion()) {
            string nit_proveedor;
            string id_proveedor = "";
            int no_orden = 1;

            cout << "\n=========== NUEVA ORDEN DE COMPRA ===========" << endl;

            // --- 1. AUTO-INCREMENTAR NUMERO DE ORDEN ---
            string query_max = "SELECT MAX(no_orden_compras) FROM compras;";
            if (!mysql_query(cn.getConexion(), query_max.c_str())) {
                MYSQL_RES* res = mysql_store_result(cn.getConexion());
                MYSQL_ROW fila = mysql_fetch_row(res);
                if (fila && fila[0]) {
                    no_orden = stoi(fila[0]) + 1;
                }
                mysql_free_result(res);
            }

            cout << "No. Orden de Compra: " << no_orden << " (Generado automaticamente)" << endl;

            // --- 2. BUSQUEDA O CREACION DEL PROVEEDOR ---
            bool proveedor_valido = false;
            while (!proveedor_valido) {
                cout << "\nIngrese NIT del Proveedor: ";
                cin >> nit_proveedor;

                string query_proveedor = "SELECT id_proveedores, proveedor FROM proveedores WHERE nit = '" + nit_proveedor + "';";

                if (!mysql_query(cn.getConexion(), query_proveedor.c_str())) {
                    MYSQL_RES* res = mysql_store_result(cn.getConexion());
                    MYSQL_ROW fila = mysql_fetch_row(res);

                    if (fila) {
                        id_proveedor = fila[0];
                        cout << "   >> Proveedor encontrado: " << fila[1] << endl;
                        proveedor_valido = true;
                    }
                    else {
                        cout << "   xxxx Proveedor no registrado. Creando nuevo perfil... xxxx" << endl;
                        string empresa, direccion, telefono;

                        cout << "   Nombre Empresa: "; cin.ignore(); getline(cin, empresa);
                        cout << "   Direccion: "; getline(cin, direccion);
                        cout << "   Telefono: "; cin >> telefono;

                        string insert_prov = "INSERT INTO proveedores(proveedor, nit, direccion, telefono) VALUES ('" + empresa + "','" + nit_proveedor + "','" + direccion + "','" + telefono + "');";

                        if (!mysql_query(cn.getConexion(), insert_prov.c_str())) {
                            id_proveedor = to_string(mysql_insert_id(cn.getConexion()));
                            cout << "   >> Proveedor registrado exitosamente. Continuando..." << endl;
                            proveedor_valido = true;
                        }
                        else {
                            cout << "   xxxx Error al guardar el proveedor: " << mysql_error(cn.getConexion()) << " xxxx" << endl;
                        }
                    }
                    mysql_free_result(res);
                }
            }

            // --- 3. INSERTAR ENCABEZADO DE COMPRA ---
            // Usamos CURDATE() para poner la fecha automatica del sistema
            string insert_maestro = "INSERT INTO compras(no_orden_compras, id_proveedor, fecha_orden, fecha_ingreso) VALUES (" + to_string(no_orden) + "," + id_proveedor + ", CURDATE(), NOW());";

            if (!mysql_query(cn.getConexion(), insert_maestro.c_str())) {
                int id_compra_generado = mysql_insert_id(cn.getConexion());
                int agregar_mas = 1;

                // --- 4. CICLO DE DETALLES (INCREMENTO DE PRODUCTOS) ---
                while (agregar_mas == 1) {
                    string id_producto, cantidad, precio_costo;

                    cout << "\n--- AGREGAR PRODUCTO A INVENTARIO ---" << endl;
                    cout << "ID del Producto a comprar: "; cin >> id_producto;

                    // Buscamos el producto para confirmar que existe y mostrar la marca
                    string query_prod = "SELECT p.producto, m.marcas, p.precio_costo, p.existencia FROM productos p INNER JOIN marcas m ON p.id_marca = m.id_marcas WHERE p.id_productos = " + id_producto + ";";

                    if (!mysql_query(cn.getConexion(), query_prod.c_str())) {
                        MYSQL_RES* res = mysql_store_result(cn.getConexion());
                        MYSQL_ROW fila = mysql_fetch_row(res);

                        if (fila) {
                            string nombre_prod = fila[0];
                            string nombre_marca = fila[1];
                            string costo_actual = fila[2];
                            int stock_actual = stoi(fila[3]);

                            cout << "   >> Ingresando: " << nombre_marca << " - " << nombre_prod << " | Stock actual: " << stock_actual << endl;
                            cout << "   >> Ultimo Costo Registrado: Q" << costo_actual << endl;

                            cout << "Cantidad a ingresar: "; cin >> cantidad;
                            cout << "NUEVO Precio Costo Unitario: Q"; cin >> precio_costo;

                            string insert_detalle = "INSERT INTO compras_detalles(id_compra, id_producto, cantidad, precio_costo_unitario) VALUES (" + to_string(id_compra_generado) + "," + id_producto + "," + cantidad + "," + precio_costo + ");";

                            if (!mysql_query(cn.getConexion(), insert_detalle.c_str())) {

                                // ¡AQUÍ ESTÁ LA MAGIA DEL INCREMENTO! Sumamos la cantidad al stock existente
                                // Tambien aprovechamos a actualizar el nuevo precio_costo en el inventario
                                string update_stock = "UPDATE productos SET existencia = existencia + " + cantidad + ", precio_costo = " + precio_costo + " WHERE id_productos = " + id_producto + ";";
                                mysql_query(cn.getConexion(), update_stock.c_str());

                                cout << "   >> Mercaderia ingresada y stock actualizado exitosamente." << endl;
                            }
                            else {
                                cout << "   xxxx Error en detalle: " << mysql_error(cn.getConexion()) << " xxxx" << endl;
                            }
                        }
                        else {
                            cout << "   xxxx Error: El ID del producto no existe en el inventario. xxxx" << endl;
                        }
                        mysql_free_result(res);
                    }

                    cout << "\n¿Agregar otro producto a esta orden? (1 = Si, 0 = No): ";
                    cin >> agregar_mas;
                }

                // --- 5. MOSTRAR ORDEN DE COMPRA FINAL ---
                imprimirOrden(id_compra_generado, cn.getConexion());

            }
            else {
                cout << "Error al crear la orden: " << mysql_error(cn.getConexion()) << endl;
            }
        }
        cn.cerrarConexion();
    }

private:
    void imprimirOrden(int id_compra, MYSQL* conexion) {
        cout << "\n========================================================" << endl;
        cout << "                 ORDEN DE COMPRA GENERADA               " << endl;
        cout << "========================================================" << endl;

        string query_encabezado = "SELECT c.no_orden_compras, c.fecha_orden, p.proveedor, p.nit FROM compras c INNER JOIN proveedores p ON c.id_proveedor = p.id_proveedores WHERE c.id_compras = " + to_string(id_compra) + ";";

        if (!mysql_query(conexion, query_encabezado.c_str())) {
            MYSQL_RES* res = mysql_store_result(conexion);
            MYSQL_ROW fila = mysql_fetch_row(res);
            if (fila) {
                cout << "Orden No: " << fila[0] << "              Fecha: " << fila[1] << endl;
                cout << "Proveedor: " << fila[2] << "    NIT: " << fila[3] << endl;
            }
            mysql_free_result(res);
        }

        cout << "--------------------------------------------------------" << endl;
        cout << "CANT | PRODUCTO                     | P.COSTO | SUBTOTAL" << endl;
        cout << "--------------------------------------------------------" << endl;

        string query_detalle = "SELECT cd.cantidad, p.producto, cd.precio_costo_unitario, (cd.cantidad * cd.precio_costo_unitario) as subtotal FROM compras_detalles cd INNER JOIN productos p ON cd.id_producto = p.id_productos WHERE cd.id_compra = " + to_string(id_compra) + ";";

        double total_orden = 0.0;
        if (!mysql_query(conexion, query_detalle.c_str())) {
            MYSQL_RES* res = mysql_store_result(conexion);
            MYSQL_ROW fila;
            while ((fila = mysql_fetch_row(res))) {
                cout << fila[0] << "    | " << fila[1] << " | Q" << fila[2] << " | Q" << fila[3] << endl;
                total_orden += stod(fila[3]);
            }
            mysql_free_result(res);
        }

        cout << "--------------------------------------------------------" << endl;
        cout << "                                     TOTAL: Q" << total_orden << endl;
        cout << "========================================================" << endl;
    }
};
