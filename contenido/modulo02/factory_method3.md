# Ejemplo: Sistema de registros

## Introducción

Para ilustrar el patrón **Factory Method** en un contexto realista, construiremos un pequeño sistema de registros (loggers).
El objetivo del sistema es permitir que el código cliente genere mensajes de log **sin conocer el tipo concreto de logger** que los procesa.
Dependiendo del creador elegido, los mensajes podrán enviarse:

* a la **consola**,
* a un **archivo**, o
* a un destino simulado de **red**.

Cada logger es un producto concreto que implementa una interfaz común (`Logger`).
El código cliente trabaja exclusivamente con la clase abstracta `CreadorLogger`, que define el método fábrica `crear_logger()`.
Las clases creadoras concretas (`CreadorLoggerConsola`, `CreadorLoggerArchivo`, `CreadorLoggerRed`) son las responsables de decidir qué tipo de logger construir.

A continuación se muestra el código completo dividido en:

* **Productos.hpp** – productos y su interfaz
* **Creadores.hpp** – fábricas y sus implementaciones
* **main.cpp** – código cliente


## Productos.hpp

```cpp
#pragma once
#include <iostream>
#include <fstream>
#include <memory>
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

    // Método que utiliza el logger sin conocer su tipo concreto
    void registrar(const std::string& mensaje) const {
        auto logger = crear_logger();
        logger->log(mensaje);
    }
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
    fabrica.registrar("Mensaje de prueba");
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

La respuesta corta: **para añadir un nuevo producto no tocamos las interfaces base, solo añadimos clases nuevas y, como mucho, una línea en `main.cpp`.**
Veamos los cambios para añadir un nuevo logger, por ejemplo `LoggerBD` (base de datos):

### Añadir el nuevo producto en `Productos.hpp`

Debajo de los otros productos, añadimos una nueva clase que herede de `Logger`:

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

Debajo de los otros creadores concretos, añadimos uno nuevo para este producto:

```cpp
class CreadorLoggerBD : public CreadorLogger {
public:
    std::unique_ptr<Logger> crear_logger() const override {
        return std::make_unique<LoggerBD>();
    }
};
```

### Usar el nuevo producto desde el cliente (`main.cpp`)

En `main.cpp`, añadimos:

```cpp
#include "Creadores.hpp"

void cliente(const CreadorLogger& fabrica) {
    fabrica.registrar("Mensaje de prueba");
}

int main() {
    CreadorLoggerConsola fabricaConsola;
    CreadorLoggerArchivo fabricaArchivo("log.txt");
    CreadorLoggerRed fabricaRed;
    CreadorLoggerBD fabricaBD;         // <-- NUEVO

    cliente(fabricaConsola);
    cliente(fabricaArchivo);
    cliente(fabricaRed);
    cliente(fabricaBD);                // <-- NUEVO

    return 0;
}
```

### Qué no hemos cambiado

* No hemos modificado la interfaz `Logger`.
* No hemos modificado la interfaz `CreadorLogger`.
* No hemos modificado el código de `cliente`.

Solo hemos:

1. añadido un **nuevo producto concreto** (`LoggerBD`),
2. añadido un **nuevo creador concreto** (`CreadorLoggerBD`),
3. y opcionalmente una línea en `main.cpp` para usarlo.

