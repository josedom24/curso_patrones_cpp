# Ejemplo: Sistema de registros

## Introducción

Para ilustrar el patrón **Factory Method** en un contexto realista, construiremos un pequeño sistema de registros (*loggers*).
El objetivo del sistema es permitir que el código cliente genere mensajes de log **sin conocer el tipo concreto de logger** que los procesa.

Dependiendo del creador elegido, los mensajes podrán enviarse:

* a la **consola**,
* a un **archivo**, o
* a un destino simulado de **red**.

Cada logger es un **producto concreto** que implementa una interfaz común (`Logger`).
El código cliente trabaja exclusivamente con la **abstracción del creador**, que define el método fábrica `crear_logger()`, y con la **abstracción del producto**, que define la operación de registro.

Las clases creadoras concretas son las responsables de decidir **qué tipo de logger construir**, mientras que el **uso del logger queda en manos del cliente**, reforzando la separación entre creación y uso de objetos .

A continuación se muestra el código completo dividido en:

* **Productos.hpp** – productos y su interfaz
* **Creadores.hpp** – fábricas y sus implementaciones
* **main.cpp** – código cliente

## Productos.hpp

```cpp
#pragma once
#include <iostream>
#include <fstream>
#include <string>

// ----------------------------------------
// Interfaz base del producto: Logger
// ----------------------------------------
class Logger {
public:
    virtual ~Logger() = default;
    virtual void log(const std::string& mensaje) = 0;
};

// ----------------------------------------
// Productos concretos
// ----------------------------------------

// Logger que escribe en consola
class LoggerConsola : public Logger {
public:
    void log(const std::string& mensaje) override {
        std::cout << "[Consola] " << mensaje << "\n";
    }
};

// Logger que escribe en un archivo
class LoggerArchivo : public Logger {
private:
    std::ofstream archivo_;

public:
    explicit LoggerArchivo(const std::string& ruta)
        : archivo_(ruta, std::ios::app) {}

    void log(const std::string& mensaje) override {
        if (archivo_.is_open()) {
            archivo_ << "[Archivo] " << mensaje << "\n";
        }
    }
};

// Logger que simula envío por red
class LoggerRed : public Logger {
public:
    void log(const std::string& mensaje) override {
        std::cout << "[Red -> servidor] " << mensaje << "\n";
    }
};
```

## Creadores.hpp

```cpp
#pragma once
#include <memory>
#include <string>
#include "Productos.hpp"

// ----------------------------------------
// Interfaz base del creador
// ----------------------------------------
class CreadorLogger {
public:
    virtual ~CreadorLogger() = default;

    // Factory Method
    virtual std::unique_ptr<Logger> crear_logger() const = 0;
};

// ----------------------------------------
// Creadores concretos
// ----------------------------------------

class CreadorLoggerConsola : public CreadorLogger {
public:
    std::unique_ptr<Logger> crear_logger() const override {
        return std::make_unique<LoggerConsola>();
    }
};

class CreadorLoggerArchivo : public CreadorLogger {
private:
    std::string ruta_;

public:
    explicit CreadorLoggerArchivo(const std::string& ruta)
        : ruta_(ruta) {}

    std::unique_ptr<Logger> crear_logger() const override {
        return std::make_unique<LoggerArchivo>(ruta_);
    }
};

class CreadorLoggerRed : public CreadorLogger {
public:
    std::unique_ptr<Logger> crear_logger() const override {
        return std::make_unique<LoggerRed>();
    }
};
```

## main.cpp

```cpp
#include "Creadores.hpp"

void cliente(const CreadorLogger& fabrica) {
    auto logger = fabrica.crear_logger();   // creación delegada
    logger->log("Mensaje de prueba");        // uso explícito del producto
}

int main() {
    CreadorLoggerConsola fabricaConsola;
    CreadorLoggerArchivo fabricaArchivo("log.txt");
    CreadorLoggerRed fabricaRed;

    cliente(fabricaConsola);
    cliente(fabricaArchivo);
    cliente(fabricaRed);

    return 0;
}
```

## Añadir un nuevo producto

Para añadir un nuevo tipo de logger **no es necesario modificar las abstracciones existentes** ni el código cliente.
Basta con introducir nuevas clases concretas.

### Añadir el nuevo producto en `Productos.hpp`

```cpp
// Logger que simula escribir en una base de datos
class LoggerBD : public Logger {
public:
    void log(const std::string& mensaje) override {
        std::cout << "[BD] INSERT INTO logs VALUES ('" << mensaje << "');\n";
    }
};
```

### Añadir el nuevo creador en `Creadores.hpp`

```cpp
class CreadorLoggerBD : public CreadorLogger {
public:
    std::unique_ptr<Logger> crear_logger() const override {
        return std::make_unique<LoggerBD>();
    }
};
```

### Usar el nuevo producto desde el cliente (`main.cpp`)

```cpp
int main() {
    CreadorLoggerConsola fabricaConsola;
    CreadorLoggerArchivo fabricaArchivo("log.txt");
    CreadorLoggerRed fabricaRed;
    CreadorLoggerBD fabricaBD;  //NUEVO

    cliente(fabricaConsola);
    cliente(fabricaArchivo);
    cliente(fabricaRed);
    cliente(fabricaBD); //NUEVO

    return 0;
}
```

## Qué no hemos modificado

* No se ha modificado la interfaz `Logger`.
* No se ha modificado la interfaz `CreadorLogger`.
* No se ha modificado el código del cliente.

Solo se han añadido:

1. un **nuevo producto concreto** (`LoggerBD`),
2. un **nuevo creador concreto** (`CreadorLoggerBD`).
3. y opcionalmente una línea en `main.cpp` para usarlo.

