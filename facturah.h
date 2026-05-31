#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib> 
#include "ConexionSP.h"
#include <mysql.h>

using namespace std;

class Venta {
public:
    void nuevaVenta() {
        ConexionSP cn = ConexionSP();
        cn.abrirConexion();
        if (cn.getConexion()) {
            string nit_cliente, id_empleado;
            string id_cliente = "";
            string serie = "A";
            int no_factura = 1;

            cout << "\n=========== NUEVA FACTURA DE VENTA ===========" << endl;

            string query_max = "SELECT MAX(no_factura) FROM ventas WHERE serie = '" + serie + "';";
            if (!mysql_query(cn.getConexion(), query_max.c_str())) {
                MYSQL_RES* res = mysql_store_result(cn.getConexion());
                MYSQL_ROW fila = mysql_fetch_row(res);
                if (fila && fila[0]) {
                    no_factura = stoi(fila[0]) + 1;
                }
                mysql_free_result(res);
            }

            cout << "Serie: " << serie << " (Asignada automaticamente)" << endl;
            cout << "No. Factura: " << no_factura << " (Generado automaticamente)" << endl;

            bool cliente_valido = false;
            while (!cliente_valido) {
                cout << "\nIngrese NIT del Cliente (Ej. CF o 123456-7): ";
                cin >> nit_cliente;

                string query_cliente = "SELECT id_clientes, nombres, apellidos FROM clientes WHERE nit = '" + nit_cliente + "';";

                if (!mysql_query(cn.getConexion(), query_cliente.c_str())) {
                    MYSQL_RES* res = mysql_store_result(cn.getConexion());
                    MYSQL_ROW fila = mysql_fetch_row(res);

                    if (fila) {
                        id_cliente = fila[0];
                        cout << "   >> Cliente encontrado: " << fila[1] << " " << fila[2] << endl;
                        cliente_valido = true;
                    }
                    else {
                        cout << "   xxxx Cliente no registrado. Creando nuevo perfil... xxxx" << endl;
                        string nom, ape, tel, correo;
                        int gen;

                        cout << "   Nombres: "; cin.ignore(); getline(cin, nom);
                        cout << "   Apellidos: "; getline(cin, ape);
                        cout << "   Genero (1=Masc, 0=Fem): "; cin >> gen;
                        cout << "   Telefono: "; cin >> tel;
                        cout << "   Correo Electronico: "; cin >> correo;

                        string insert_cli = "INSERT INTO clientes(nombres, apellidos, nit, genero, telefono, correo_electronico, fecha_ingreso) VALUES ('" + nom + "','" + ape + "','" + nit_cliente + "'," + to_string(gen) + ",'" + tel + "','" + correo + "', NOW());";

                        if (!mysql_query(cn.getConexion(), insert_cli.c_str())) {
                            id_cliente = to_string(mysql_insert_id(cn.getConexion()));
                            cout << "   >> Cliente registrado exitosamente. Continuando con la factura..." << endl;
                            cliente_valido = true;
                        }
                        else {
                            cout << "   xxxx Error al guardar el cliente: " << mysql_error(cn.getConexion()) << " xxxx" << endl;
                        }
                    }
                    mysql_free_result(res);
                }
            }

            bool empleado_valido = false;
            while (!empleado_valido) {
                cout << "\nID del Empleado (Cajero): ";
                cin >> id_empleado;

                string query_empleado = "SELECT nombres, apellidos FROM empleados WHERE id_empleados = " + id_empleado + ";";

                if (!mysql_query(cn.getConexion(), query_empleado.c_str())) {
                    MYSQL_RES* res = mysql_store_result(cn.getConexion());
                    MYSQL_ROW fila = mysql_fetch_row(res);

                    if (fila) {
                        cout << "   >> Cajero actual: " << fila[0] << " " << fila[1] << endl;
                        empleado_valido = true;
                    }
                    else {
                        cout << "   xxxx Error: El ID del empleado no existe. Intente de nuevo. xxxx" << endl;
                    }
                    mysql_free_result(res);
                }
            }

            string insert_maestro = "INSERT INTO ventas(no_factura, serie, fecha_factura, id_cliente, id_empleado, fecha_ingreso) VALUES (" + to_string(no_factura) + ",'" + serie + "', CURDATE()," + id_cliente + "," + id_empleado + ", NOW());";

            if (!mysql_query(cn.getConexion(), insert_maestro.c_str())) {
                int id_venta_generado = mysql_insert_id(cn.getConexion());
                int agregar_mas = 1;

                while (agregar_mas == 1) {
                    string id_producto, cantidad;

                    cout << "\n--- AGREGAR PRODUCTO ---" << endl;
                    cout << "ID del Producto: "; cin >> id_producto;

                    string query_prod = "SELECT p.producto, m.marcas, p.precio_venta, p.existencia FROM productos p INNER JOIN marcas m ON p.id_marca = m.id_marcas WHERE p.id_productos = " + id_producto + ";";

                    if (!mysql_query(cn.getConexion(), query_prod.c_str())) {
                        MYSQL_RES* res = mysql_store_result(cn.getConexion());
                        MYSQL_ROW fila = mysql_fetch_row(res);

                        if (fila) {
                            string nombre_prod = fila[0];
                            string nombre_marca = fila[1];
                            string precio_unitario = fila[2];
                            int stock_actual = stoi(fila[3]);

                            cout << "   >> Producto: " << nombre_marca << " - " << nombre_prod << " | Precio: Q" << precio_unitario << " | Stock actual: " << stock_actual << endl;

                            cout << "Cantidad a vender: "; cin >> cantidad;

                            if (stoi(cantidad) > stock_actual) {
                                cout << "   xxxx Error: No hay suficiente producto en inventario. Venta cancelada. xxxx" << endl;
                            }
                            else {
                                string insert_detalle = "INSERT INTO ventas_detalle(id_venta, id_producto, cantidad, precio_unitario) VALUES (" + to_string(id_venta_generado) + "," + id_producto + "," + cantidad + "," + precio_unitario + ");";

                                if (!mysql_query(cn.getConexion(), insert_detalle.c_str())) {
                                    string update_stock = "UPDATE productos SET existencia = existencia - " + cantidad + " WHERE id_productos = " + id_producto + ";";
                                    mysql_query(cn.getConexion(), update_stock.c_str());

                                    cout << "   >> Producto agregado a la factura exitosamente." << endl;
                                }
                                else {
                                    cout << "   xxxx Error en detalle: " << mysql_error(cn.getConexion()) << " xxxx" << endl;
                                }
                            }
                        }
                        else {
                            cout << "   xxxx Error: El ID del producto no existe. Intente con otro. xxxx" << endl;
                        }
                        mysql_free_result(res);
                    }

                    cout << "\n¿Agregar otro producto? (1 = Si, 0 = No): ";
                    cin >> agregar_mas;
                }


                imprimirFactura(id_venta_generado, cn.getConexion());

            }
            else {
                cout << "Error al crear la factura: " << mysql_error(cn.getConexion()) << endl;
            }
        }
        cn.cerrarConexion();
    }

private:
    void imprimirFactura(int id_venta, MYSQL* conexion) {
        string query_encabezado = "SELECT v.no_factura, v.serie, v.fecha_factura, c.nombres, c.apellidos, c.nit FROM ventas v INNER JOIN clientes c ON v.id_cliente = c.id_clientes WHERE v.id_venta = " + to_string(id_venta) + ";";

        if (!mysql_query(conexion, query_encabezado.c_str())) {
            MYSQL_RES* res = mysql_store_result(conexion);
            MYSQL_ROW fila = mysql_fetch_row(res);

            if (fila) {
                string no_fact = fila[0];
                string serie = fila[1];
                string fecha = fila[2];
                string cliente = string(fila[3]) + " " + string(fila[4]);
                string nit = fila[5];


                string nombre_archivo = "Factura_" + serie + "-" + no_fact + ".html";
                ofstream ticket(nombre_archivo);


                ticket << "<!DOCTYPE html>\n<html>\n<head>\n";
                ticket << "<meta charset='UTF-8'>\n";
                ticket << "<title>Factura " << serie << "-" << no_fact << "</title>\n";
                ticket << "<style>\n";
                ticket << "  body { font-family: 'Courier New', Courier, monospace; background-color: #f4f4f4; padding: 20px; }\n";
                ticket << "  .factura-container { background-color: white; width: 600px; margin: 0 auto; padding: 20px; border-radius: 8px; box-shadow: 0px 0px 10px rgba(0,0,0,0.1); }\n";
                ticket << "  h1 { text-align: center; color: #333; }\n";
                ticket << "  table { width: 100%; border-collapse: collapse; margin-top: 20px; }\n";
                ticket << "  th, td { border-bottom: 1px solid #ddd; padding: 10px; text-align: left; }\n";
                ticket << "  th { background-color: #f2f2f2; }\n";
                ticket << "  .total { text-align: right; font-size: 20px; font-weight: bold; margin-top: 20px; }\n";
                ticket << "</style>\n";
                ticket << "</head>\n<body>\n";

                ticket << "<div class='factura-container'>\n";
                ticket << "  <h1>🏪 SUPERMERCADO PATITO</h1>\n";
                ticket << "  <hr>\n";
                ticket << "  <p><b>Factura No:</b> " << serie << "-" << no_fact << " <span style='float:right;'><b>Fecha:</b> " << fecha << "</span></p>\n";
                ticket << "  <p><b>Cliente:</b> " << cliente << " <span style='float:right;'><b>NIT:</b> " << nit << "</span></p>\n";

                ticket << "  <table>\n";
                ticket << "    <tr><th>CANT</th><th>PRODUCTO</th><th>PRECIO</th><th>SUBTOTAL</th></tr>\n";

                mysql_free_result(res);


                string query_detalle = "SELECT vd.cantidad, p.producto, vd.precio_unitario, (vd.cantidad * vd.precio_unitario) as subtotal FROM ventas_detalle vd INNER JOIN productos p ON vd.id_producto = p.id_productos WHERE vd.id_venta = " + to_string(id_venta) + ";";

                double total_factura = 0.0;
                if (!mysql_query(conexion, query_detalle.c_str())) {
                    MYSQL_RES* res_det = mysql_store_result(conexion);
                    MYSQL_ROW fila_det;
                    while ((fila_det = mysql_fetch_row(res_det))) {
                        ticket << "    <tr>";
                        ticket << "<td>" << fila_det[0] << "</td>";
                        ticket << "<td>" << fila_det[1] << "</td>";
                        ticket << "<td>Q" << fila_det[2] << "</td>";
                        ticket << "<td>Q" << fila_det[3] << "</td>";
                        ticket << "</tr>\n";

                        total_factura += stod(fila_det[3]);
                    }
                    mysql_free_result(res_det);
                }

                ticket << "  </table>\n";
                ticket << "  <div class='total'>TOTAL A PAGAR: Q" << total_factura << "</div>\n";
                ticket << "  <p style='text-align:center; margin-top:30px; color:#777;'>¡Gracias por su compra!</p>\n";
                ticket << "</div>\n";

                ticket << "</body>\n</html>";
                ticket.close();

                cout << "\n>> Factura generada exitosamente en formato WEB: " << nombre_archivo << endl;
                cout << ">> Abriendo factura en el navegador para imprimir/guardar como PDF..." << endl;


                string comando = "start " + nombre_archivo;
                system(comando.c_str());

            }
            else {
                mysql_free_result(res);
            }
        }
    }
};
