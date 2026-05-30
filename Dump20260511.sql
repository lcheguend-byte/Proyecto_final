CREATE DATABASE IF NOT EXISTS `supermercadopatito`;
USE `supermercadopatito`;

CREATE TABLE `puestos` (
  `id_puestos` SMALLINT NOT NULL AUTO_INCREMENT,
  `puesto` VARCHAR(50) NOT NULL,
  PRIMARY KEY (`id_puestos`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

CREATE TABLE `marcas` (
  `id_marcas` SMALLINT NOT NULL AUTO_INCREMENT,
  `marcas` VARCHAR(50) NOT NULL,
  PRIMARY KEY (`id_marcas`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

CREATE TABLE `clientes` (
  `id_clientes` INT NOT NULL AUTO_INCREMENT,
  `nombres` VARCHAR(60) NOT NULL,
  `apellidos` VARCHAR(60) NOT NULL,
  `nit` VARCHAR(12) NOT NULL,
  `genero` BIT(1) NOT NULL,
  `telefono` VARCHAR(25) NOT NULL,
  `correo_electronico` VARCHAR(45) NOT NULL,
  `fecha_ingreso` DATETIME NOT NULL,
  PRIMARY KEY (`id_clientes`),
  UNIQUE (`nit`),
  UNIQUE (`correo_electronico`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

CREATE TABLE `proveedores` (
  `id_proveedores` INT NOT NULL AUTO_INCREMENT,
  `proveedor` VARCHAR(60) NOT NULL,
  `nit` VARCHAR(12) NOT NULL,
  `direccion` VARCHAR(80) NOT NULL,
  `telefono` VARCHAR(25) NOT NULL,
  PRIMARY KEY (`id_proveedores`),
  UNIQUE (`nit`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

CREATE TABLE `empleados` (
  `id_empleados` INT NOT NULL AUTO_INCREMENT,
  `nombres` VARCHAR(60) NOT NULL,
  `apellidos` VARCHAR(60) NOT NULL,
  `direccion` VARCHAR(80) NOT NULL,
  `telefono` VARCHAR(25) NOT NULL,
  `cui` VARCHAR(15) NOT NULL,
  `genero` BIT(1) NOT NULL,
  `fecha_nacimiento` DATE NOT NULL,
  `id_puesto` SMALLINT NOT NULL,
  `fecha_inicio_labores` DATE NOT NULL,
  `fecha_ingreso` DATETIME(6) NOT NULL,
  PRIMARY KEY (`id_empleados`),
  UNIQUE (`cui`),
  CONSTRAINT `fk_empleados_puestos`
    FOREIGN KEY (`id_puesto`)
    REFERENCES `puestos` (`id_puestos`)
    ON DELETE RESTRICT
    ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

CREATE TABLE `productos` (
  `id_productos` INT NOT NULL AUTO_INCREMENT,
  `producto` VARCHAR(50) NOT NULL,
  `id_marca` SMALLINT NOT NULL,
  `descripcion` VARCHAR(100) NOT NULL,
  `imagen` VARCHAR(255) NOT NULL,
  `precio_costo` DECIMAL(8,2) NOT NULL,
  `precio_venta` DECIMAL(8,2) NOT NULL,
  `existencia` INT NOT NULL,
  `fecha_ingreso` DATETIME NOT NULL,
  PRIMARY KEY (`id_productos`),
  CONSTRAINT `fk_productos_marcas`
    FOREIGN KEY (`id_marca`)
    REFERENCES `marcas` (`id_marcas`)
    ON DELETE RESTRICT
    ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

CREATE TABLE `compras` (
  `id_compras` INT NOT NULL AUTO_INCREMENT,
  `no_orden_compras` INT NOT NULL,
  `id_proveedor` INT NOT NULL,
  `fecha_orden` DATE NOT NULL,
  `fecha_ingreso` DATETIME(6) NOT NULL,
  PRIMARY KEY (`id_compras`),
  UNIQUE (`no_orden_compras`),
  CONSTRAINT `fk_compras_proveedores`
    FOREIGN KEY (`id_proveedor`)
    REFERENCES `proveedores` (`id_proveedores`)
    ON DELETE RESTRICT
    ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

CREATE TABLE `ventas` (
  `id_venta` INT NOT NULL AUTO_INCREMENT,
  `no_factura` INT NOT NULL,
  `serie` CHAR(1) NOT NULL,
  `fecha_factura` DATE NOT NULL,
  `id_cliente` INT NOT NULL,
  `id_empleado` INT NOT NULL,
  `fecha_ingreso` DATETIME(6) NOT NULL,
  PRIMARY KEY (`id_venta`),
  UNIQUE (`no_factura`),
  CONSTRAINT `fk_ventas_clientes`
    FOREIGN KEY (`id_cliente`)
    REFERENCES `clientes` (`id_clientes`)
    ON DELETE RESTRICT
    ON UPDATE CASCADE,
  CONSTRAINT `fk_ventas_empleados`
    FOREIGN KEY (`id_empleado`)
    REFERENCES `empleados` (`id_empleados`)
    ON DELETE RESTRICT
    ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

CREATE TABLE `compras_detalles` (
  `id_compra_detalle` BIGINT NOT NULL AUTO_INCREMENT,
  `id_compra` INT NOT NULL,
  `id_producto` INT NOT NULL,
  `cantidad` INT NOT NULL,
  `precio_costo_unitario` DECIMAL(8,2) NOT NULL,
  PRIMARY KEY (`id_compra_detalle`),
  CONSTRAINT `fk_compras_detalles_compras`
    FOREIGN KEY (`id_compra`)
    REFERENCES `compras` (`id_compras`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_compras_detalles_productos`
    FOREIGN KEY (`id_producto`)
    REFERENCES `productos` (`id_productos`)
    ON DELETE RESTRICT
    ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

CREATE TABLE `ventas_detalle` (
  `id_venta_detalle` BIGINT NOT NULL AUTO_INCREMENT,
  `id_venta` INT NOT NULL,
  `id_producto` INT NOT NULL,
  `cantidad` INT NOT NULL,
  `precio_unitario` DECIMAL(8,2) NOT NULL,
  PRIMARY KEY (`id_venta_detalle`),
  CONSTRAINT `fk_ventas_detalle_ventas`
    FOREIGN KEY (`id_venta`)
    REFERENCES `ventas` (`id_venta`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_ventas_detalle_productos`
    FOREIGN KEY (`id_producto`)
    REFERENCES `productos` (`id_productos`)
    ON DELETE RESTRICT
    ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;