#include <iostream>
#include <string>

// Incluir tus clases
#include "Marca.h"
#include "Cliente.h"
#include "Producto.h"
#include "Empleado.h"
#include "Proveedor.h"
#include "Puesto.h"

using namespace std;

// Prototipos de funciones para los submenus
void menuMarcas();
void menuClientes();
void menuProductos();
void menuProveedores();
void menuPuestos();
void menuEmpleados();

int main() {
    int opcion;

    do {
        cout << "\n==========================================" << endl;
        cout << "        SUPERMERCADO PATITO - SISTEMA      " << endl;
        cout << "==========================================" << endl;
        cout << "1. Gestionar Marcas" << endl;
        cout << "2. Gestionar Clientes" << endl;
        cout << "3. Gestionar Productos " << endl;
        cout << "4. Gestionar Proveedores" << endl;
        cout << "5. Gestionar Puestos" << endl;
        cout << "6. Gestionar Empleados" << endl;
        cout << "0. Salir" << endl;
        cout << "------------------------------------------" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: menuMarcas(); break;
        case 2: menuClientes(); break;
        case 3: menuProductos(); break;
        case 4: menuProveedores(); break;
        case 5: menuPuestos(); break;   // <-- CORREGIDO: Opción 5 va a Puestos
        case 6: menuEmpleados(); break; // <-- CORREGIDO: Opción 6 va a Empleados
        case 0: cout << "Saliendo del sistema..." << endl; break;
        default: cout << "Opcion invalida." << endl; break;
        }
    } while (opcion != 0);

    return 0;
}

// =========================================================
//                  SUBMENU DE MARCAS
// =========================================================
void menuMarcas() {
    int op;
    Marca m; // Instancia de la clase Marca
    string nombre_marca;
    int id;

    do {
        cout << "\n--- MODULO DE MARCAS ---" << endl;
        cout << "1. Ingresar Marca\n2. Ver Marcas\n3. Actualizar Marca\n4. Eliminar Marca\n0. Regresar al Menu Principal" << endl;
        cout << "Opcion: ";
        cin >> op;
        cin.ignore(); // Limpiamos el buffer justo después de leer el número de opción

        switch (op) {
        case 1: // CREAR
            cout << "Ingrese el nombre de la nueva marca: ";
            getline(cin, nombre_marca); // Ahora sí va a leer el texto limpio y completo

            m.setMarca(nombre_marca);
            m.crear();
            break;

        case 2: // LEER
            m.leer();
            break;

        case 3: // ACTUALIZAR
            m.leer();
            cout << "\nIngrese el ID de la marca que desea modificar: ";
            cin >> id;
            cin.ignore();
            cout << "Ingrese el NUEVO nombre para la marca: ";
            getline(cin, nombre_marca);

            m.setId_marca(id);
            m.setMarca(nombre_marca);
            m.actualizar();
            break;

        case 4: // BORRAR
            m.leer();
            cout << "\nIngrese el ID de la marca que desea ELIMINAR: ";
            cin >> id;

            m.setId_marca(id);
            m.borrar();
            break;
        }
    } while (op != 0);
}

// =========================================================
//                  SUBMENU DE CLIENTES
// =========================================================
void menuClientes() {
    int op;
    Cliente c;
    string nit, nombres, apellidos, telefono, correo;
    int genero, id;

    do {
        cout << "\n--- MODULO DE CLIENTES ---" << endl;
        cout << "1. Ingresar Cliente\n2. Ver Clientes\n3. Actualizar Cliente\n4. Eliminar Cliente\n0. Regresar al Menu Principal" << endl;
        cout << "Opcion: ";
        cin >> op;
        cin.ignore();

        switch (op) {
        case 1: // CREAR
            cout << "Ingrese NIT: ";
            cin >> nit;
            cin.ignore();

            cout << "Ingrese Nombres: ";
            getline(cin, nombres);

            cout << "Ingrese Apellidos: ";
            getline(cin, apellidos);

            cout << "Ingrese Genero (1 = Masculino, 0 = Femenino): ";
            cin >> genero;

            cout << "Ingrese Telefono: ";
            cin >> telefono;

            cout << "Ingrese Correo Electronico: ";
            cin >> correo;

            c.setNit(nit);
            c.setNombres(nombres);
            c.setApellidos(apellidos);
            c.setGenero(genero);
            c.setTelefono(telefono);
            c.setCorreoElectronico(correo);

            c.crear();
            break;

        case 2: // LEER
            c.leer();
            break;

        case 3: // ACTUALIZAR
            c.leer();
            cout << "\nIngrese el ID del cliente que desea modificar: ";
            cin >> id;

            cout << "Ingrese NUEVO NIT: ";
            cin >> nit;
            cin.ignore();

            cout << "Ingrese NUEVOS Nombres: ";
            getline(cin, nombres);

            cout << "Ingrese NUEVOS Apellidos: ";
            getline(cin, apellidos);

            cout << "Ingrese NUEVO Genero (1 = Masc, 0 = Fem): ";
            cin >> genero;

            cout << "Ingrese NUEVO Telefono: ";
            cin >> telefono;

            cout << "Ingrese NUEVO Correo: ";
            cin >> correo;

            c.setId_cliente(id);
            c.setNit(nit);
            c.setNombres(nombres);
            c.setApellidos(apellidos);
            c.setGenero(genero);
            c.setTelefono(telefono);
            c.setCorreoElectronico(correo);

            c.actualizar();
            break;

        case 4: // BORRAR
            c.leer();
            cout << "\nIngrese el ID del cliente que desea ELIMINAR: ";
            cin >> id;

            c.setId_cliente(id);
            c.borrar();
            break;
        }
    } while (op != 0);
}

// =========================================================
//                  SUBMENU DE PRODUCTOS
// =========================================================
void menuProductos() {
    int op;
    Producto p;
    Marca m;

    int id, id_marca, existencia;
    double precio_costo, precio_venta;
    string nombre_producto, descripcion, imagen;

    do {
        cout << "\n--- MODULO DE PRODUCTOS ---" << endl;
        cout << "1. Ingresar Producto\n2. Ver Productos\n3. Actualizar Producto\n4. Eliminar Producto\n0. Regresar al Menu Principal" << endl;
        cout << "Opcion: ";
        cin >> op;
        cin.ignore();

        switch (op) {
        case 1: // CREAR
            cout << "Ingrese nombre del Producto: ";
            getline(cin, nombre_producto);

            cout << "\n-- Marcas Disponibles en el Sistema --" << endl;
            m.leer(); // Si tu método se llama leer() o read(), asegúrate que coincida. En tu código original decía m.leer();
            cout << "Ingrese el ID de la Marca para este producto: ";
            cin >> id_marca;
            cin.ignore();

            cout << "Ingrese Descripcion del Producto: ";
            getline(cin, descripcion);

            cout << "Ingrese ruta de la Imagen (Ej. C:/img/prod.jpg): ";
            getline(cin, imagen);

            cout << "Ingrese Precio de Costo (Ej. 10.50): ";
            cin >> precio_costo;

            cout << "Ingrese Precio de Venta (Ej. 15.00): ";
            cin >> precio_venta;

            cout << "Ingrese Existencia actual (Stock): ";
            cin >> existencia;

            p.setProducto(nombre_producto);
            p.setId_marca(id_marca);
            p.setDescripcion(descripcion);// Asegúrate que tu setter se llame setDescripcion
            p.setImagen(imagen);
            p.setPrecio_costo(precio_costo);
            p.setPrecio_venta(precio_venta);
            p.setExistencia(existencia);

            p.crear();
            break;

        case 2: // LEER
            p.leer();
            break;

        case 3: // ACTUALIZAR
            p.leer();
            cout << "\nIngrese el ID del Producto que desea modificar: ";
            cin >> id;
            cin.ignore();

            cout << "Ingrese NUEVO nombre del Producto: ";
            getline(cin, nombre_producto);

            cout << "\n-- Marcas Disponibles --" << endl;
            m.leer();
            cout << "Ingrese NUEVO ID de la Marca: ";
            cin >> id_marca;
            cin.ignore();

            cout << "Ingrese NUEVA Descripcion: ";
            getline(cin, descripcion);

            cout << "Ingrese NUEVA ruta de la Imagen: ";
            getline(cin, imagen);

            cout << "Ingrese NUEVO Precio de Costo: ";
            cin >> precio_costo;

            cout << "Ingrese NUEVO Precio de Venta: ";
            cin >> precio_venta;

            cout << "Ingrese NUEVA Existencia: ";
            cin >> existencia;

            p.setId_producto(id);
            p.setProducto(nombre_producto);
            p.setId_marca(id_marca);
            p.setImagen(imagen);
            p.setPrecio_costo(precio_costo);
            p.setPrecio_venta(precio_venta);
            p.setExistencia(existencia);

            p.actualizar();
            break;

        case 4: // BORRAR
            p.leer();
            cout << "\nIngrese el ID del producto que desea ELIMINAR: ";
            cin >> id;

            p.setId_producto(id);
            p.borrar();
            break;
        }
    } while (op != 0);
}

// =========================================================
//                  SUBMENU DE PROVEEDORES
// =========================================================
void menuProveedores() {
    int op;
    Proveedor p;
    int id;
    string empresa, nit, direccion, telefono;

    do {
        cout << "\n--- MODULO DE PROVEEDORES ---" << endl;
        cout << "1. Ingresar Proveedor\n2. Ver Proveedores\n3. Actualizar Proveedor\n4. Eliminar Proveedor\n0. Regresar al Menu Principal" << endl;
        cout << "Opcion: ";
        cin >> op;
        cin.ignore();

        switch (op) {
        case 1: // CREAR
            cout << "Ingrese el nombre del Proveedor / Empresa: ";
            getline(cin, empresa);

            cout << "Ingrese NIT (Ej. 123456-7 o CF): ";
            getline(cin, nit);

            cout << "Ingrese Direccion: ";
            getline(cin, direccion);

            cout << "Ingrese Telefono: ";
            getline(cin, telefono);

            p.setProveedor(empresa);
            p.setNit(nit);
            p.setDireccion(direccion);
            p.setTelefono(telefono);

            p.crear();
            break;

        case 2: // LEER
            p.leer();
            break;

        case 3: // ACTUALIZAR
            p.leer();
            cout << "\nIngrese el ID del Proveedor que desea modificar: ";
            cin >> id;
            cin.ignore();

            cout << "Ingrese NUEVO nombre del Proveedor: ";
            getline(cin, empresa);

            cout << "Ingrese NUEVO NIT: ";
            getline(cin, nit);

            cout << "Ingrese NUEVA Direccion: ";
            getline(cin, direccion);

            cout << "Ingrese NUEVO Telefono: ";
            getline(cin, telefono);

            p.setId_proveedor(id);
            p.setProveedor(empresa);
            p.setNit(nit);
            p.setDireccion(direccion);
            p.setTelefono(telefono);

            p.actualizar();
            break;

        case 4: // BORRAR
            p.leer();
            cout << "\nIngrese el ID del Proveedor que desea ELIMINAR: ";
            cin >> id;

            p.setId_proveedor(id);
            p.borrar();
            break;
        }
    } while (op != 0);
}

// =========================================================
//                  SUBMENU DE EMPLEADOS
// =========================================================
void menuEmpleados() {
    int op, id, genero, id_puesto;
    string nombres, apellidos, direccion, telefono, cui, fn, fil;
    Empleado e;
    Puesto p;

    do {
        cout << "\n--- MODULO DE EMPLEADOS ---" << endl;
        cout << "1. Ingresar Empleado\n2. Ver Empleados\n3. Actualizar Empleado\n4. Eliminar Empleado\n0. Regresar" << endl;
        cout << "Opcion: ";
        cin >> op;
        cin.ignore();

        switch (op) {
        case 1:
            cout << "Ingrese Nombres: "; getline(cin, nombres);
            cout << "Ingrese Apellidos: "; getline(cin, apellidos);
            cout << "Ingrese Direccion: "; getline(cin, direccion);
            cout << "Ingrese Telefono: "; getline(cin, telefono);
            cout << "Ingrese CUI (DPI): "; getline(cin, cui);
            cout << "Ingrese Genero (1=Masc, 0=Fem): "; cin >> genero;
            cout << "Fecha de Nacimiento (YYYY-MM-DD): "; cin >> fn;

            cout << "\n-- Puestos Disponibles --\n";
            p.leer();
            cout << "Ingrese el ID del Puesto: "; cin >> id_puesto;

            cout << "Fecha Inicio de Labores (YYYY-MM-DD): "; cin >> fil;

            e.setNombres(nombres); e.setApellidos(apellidos); e.setDireccion(direccion);
            e.setTelefono(telefono); e.setCui(cui); e.setGenero(genero);
            e.setFecha_nacimiento(fn); e.setId_puesto(id_puesto); e.setFecha_inicio_labores(fil);
            e.crear();
            break;
        case 2: e.leer(); break;
        case 3:
            e.leer();
            cout << "\nID del Empleado a modificar: "; cin >> id;
            cout << "NUEVOS Nombres: "; cin.ignore(); getline(cin, nombres);
            cout << "NUEVOS Apellidos: "; getline(cin, apellidos);
            cout << "NUEVA Direccion: "; getline(cin, direccion);
            cout << "NUEVO Telefono: "; getline(cin, telefono);
            cout << "NUEVO CUI: "; getline(cin, cui);
            cout << "NUEVO Genero (1=Masc, 0=Fem): "; cin >> genero;
            cout << "NUEVA Fecha Nacimiento: "; cin >> fn;
            p.leer();
            cout << "NUEVO ID de Puesto: "; cin >> id_puesto;
            cout << "NUEVA Fecha Inicio Labores: "; cin >> fil;

            e.setId_empleado(id); e.setNombres(nombres); e.setApellidos(apellidos);
            e.setDireccion(direccion); e.setTelefono(telefono); e.setCui(cui);
            e.setGenero(genero); e.setFecha_nacimiento(fn);
            e.setId_puesto(id_puesto); e.setFecha_inicio_labores(fil);
            e.actualizar();
            break;
        case 4:
            e.leer();
            cout << "\nID del Empleado a eliminar: "; cin >> id;
            e.setId_empleado(id); e.borrar();
            break;
        }
    } while (op != 0);
}

// =========================================================
//                  SUBMENU DE PUESTOS
// =========================================================
void menuPuestos() {
    int op, id;
    string nom_puesto;
    Puesto p;

    do {
        cout << "\n--- MODULO DE PUESTOS ---" << endl;
        cout << "1. Ingresar Puesto\n2. Ver Puestos\n3. Actualizar Puesto\n4. Eliminar Puesto\n0. Regresar" << endl;
        cout << "Opcion: ";
        cin >> op;
        cin.ignore(); // Agregado para limpiar el buffer antes del getline de abajo

        switch (op) {
        case 1:
            cout << "Ingrese el nombre del Puesto: ";
            getline(cin, nom_puesto);
            p.setPuesto(nom_puesto);
            p.crear();
            break;
        case 2: p.leer(); break;
        case 3:
            p.leer();
            cout << "ID del Puesto a modificar: "; cin >> id;
            cout << "NUEVO nombre del Puesto: "; cin.ignore(); getline(cin, nom_puesto);
            p.setId_puesto(id); p.setPuesto(nom_puesto); p.actualizar();
            break;
        case 4:
            p.leer();
            cout << "ID del Puesto a eliminar: "; cin >> id;
            p.setId_puesto(id); p.borrar();
            break;
        }
    } while (op != 0);
}