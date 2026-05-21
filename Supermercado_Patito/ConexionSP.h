#pragma once
#include <mysql.h>
using namespace std;
class ConexionSP
{
private:
	MYSQL* Conexion;
public:
	void abrirConexion() {
		Conexion = mysql_init(0);
		Conexion = mysql_real_connect(Conexion, "localhost", "root", "Hunterxhunter.1", "supermercadopatito", 3306, NULL, 0);
	}
	MYSQL* getConexion() {
		return Conexion;
	}
	void cerrarConexion() {
		mysql_close(Conexion);
		Conexion = NULL;
	};
};