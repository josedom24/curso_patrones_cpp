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



A continuación se resumen los aspectos más relevantes del ejemplo, tanto desde el punto de vista del patrón Factory Method como del uso de C++ moderno.

### ✔ Separación entre *producto* y *creador*

* La clase `Logger` define la interfaz común para todos los productos.
* Los productos concretos (`LoggerConsola`, `LoggerArchivo`, `LoggerRed`) implementan distintos comportamientos sin afectar al cliente.

### ✔ Uso de punteros inteligentes (`std::unique_ptr`)

* El método fábrica devuelve `std::unique_ptr<Logger>`, lo que garantiza:

  * propiedad exclusiva del objeto creado,
  * gestión automática de memoria,
  * ausencia de fugas incluso ante excepciones.

### ✔ Construcción segura con `std::make_unique`

* Las clases creadoras concretas usan `std::make_unique`, que unifica construcción y asignación del puntero en una única operación segura.

### ✔ Desacoplamiento total del cliente

* El cliente solo conoce `CreadorLogger`, no los productos concretos.
* Llamar a `registrar()` desencadena la creación del logger adecuado sin que el cliente tenga que decidir qué logger usar.

### ✔ Extensibilidad

* Para añadir un nuevo tipo de logger (por ejemplo, `LoggerBD`):

  * se crea una clase de producto nueva,
  * se implementa un nuevo creador concreto.
* El cliente no cambia en absoluto (*Open/Closed Principle*).

## Añadir un nuevo producto

La respuesta corta: **para añadir un nuevo producto no tocas las interfaces base, solo añades clases nuevas y, como mucho, una línea en `main.cpp`.**

Te lo detallo paso a paso suponiendo que quieres un nuevo logger, por ejemplo `LoggerBD` (base de datos):

---

## 1. Añadir el nuevo producto en `Productos.hpp`

Debajo de los otros productos, añades una nueva clase que herede de `Logger`:

```cpp
// Logger que simula escribir en una base de datos
class LoggerBD : public Logger {
public:
    void log(const std::string& mensaje) override {
        std::cout << "[BD] INSERT INTO logs VALUES ('" << mensaje << "');\n";
    }
};
```

✅ Cambios en `Productos.hpp`

* **No modificas** la interfaz `Logger`.
* **Solo añades** una nueva clase concreta (`LoggerBD`).

---

## 2. Añadir el nuevo creador en `Creadores.hpp`

Debajo de los otros creadores concretos, añades uno nuevo para este producto:

```cpp
class CreadorLoggerBD : public CreadorLogger {
public:
    std::unique_ptr<Logger> crear_logger() const override {
        return std::make_unique<LoggerBD>();
    }
};
```

✅ Cambios en `Creadores.hpp`

* **No modificas** `CreadorLogger`.
* **Solo añades** una nueva subclase (`CreadorLoggerBD`) que sabe crear `LoggerBD`.

---

## 3. Usar el nuevo producto desde el cliente (`main.cpp`)

En `main.cpp`, si quieres probarlo, solo añades:

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

✅ Cambios en `main.cpp`

* Creas una instancia de `CreadorLoggerBD`.
* Llamas a `cliente(fabricaBD);`.

---

## 4. Qué NO has tenido que cambiar (y eso es lo importante)

Fíjate en lo que **ha permanecido intacto**:

* No has modificado la interfaz `Logger`.
* No has modificado la interfaz `CreadorLogger`.
* No has modificado el código de `cliente`.

Solo has:

1. añadido un **nuevo producto concreto** (`LoggerBD`),
2. añadido un **nuevo creador concreto** (`CreadorLoggerBD`),
3. y opcionalmente una línea en `main.cpp` para usarlo.

Eso es exactamente lo que quieres enseñar al hablar de **Open/Closed** con Factory Method.

Si quieres, te puedo escribir el código completo actualizado con `LoggerBD` ya integrado, para que lo copies tal cual en tus transparencias o apuntes.
