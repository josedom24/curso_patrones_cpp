# Ejemplo: Logger global del sistema

## Introducción

Para ilustrar el uso del patrón Singleton en un contexto realista, construiremos un componente centralizado (**Logger global**) que gestiona la escritura de mensajes de diagnóstico de toda la aplicación.
El objetivo es asegurar que exista **una única instancia del logger**, lo que garantiza:

* Una fuente única y coherente de mensajes.
* Una configuración compartida.
* Un acceso centralizado y consistente.
* La ausencia de múltiples flujos o archivos abiertos simultáneamente.

El código se presenta dividido en:

* **Logger.hpp**: interfaz y clase concreta del logger.
* **main.cpp**: código cliente.

## Versión clásica

En esta variante, implementamos el logger como un **Singleton clásico**, es decir, una clase que:

* Impide la creación de instancias desde el exterior.
* Proporciona un único punto de acceso global.
* Garantiza que solo exista una instancia durante toda la ejecución del programa.

Aunque esta solución es habitual, es importante comprender sus consecuencias arquitectónicas, que analizaremos al final.


## Logger.hpp

```cpp
#pragma once
#include <iostream>
#include <string>

// ----------------------------------------
// Interfaz del logger
// ----------------------------------------
class ILogger {
public:
    virtual ~ILogger() = default;

    virtual void log(const std::string& msg) = 0;
    virtual void warning(const std::string& msg) = 0;
    virtual void error(const std::string& msg) = 0;
};

// ----------------------------------------
// Implementación Singleton
// ----------------------------------------
class ConsoleLogger : public ILogger {
public:
    // Punto de acceso global
    static ConsoleLogger& instance() {
        static ConsoleLogger instance; // Inicialización segura desde C++11
        return instance;
    }

    // Eliminamos copia y asignación
    ConsoleLogger(const ConsoleLogger&) = delete;
    ConsoleLogger& operator=(const ConsoleLogger&) = delete;

    // Implementación de ILogger
    void log(const std::string& msg) override {
        std::cout << "[LOG] " << msg << "\n";
    }

    void warning(const std::string& msg) override {
        std::cout << "[WARNING] " << msg << "\n";
    }

    void error(const std::string& msg) override {
        std::cout << "[ERROR] " << msg << "\n";
    }

private:
    // Constructor privado: impide creación externa
    ConsoleLogger() = default;
};
```


## main.cpp

```cpp
#include "Logger.hpp"

// ----------------------------
// Funciones que utilizan el logger
// ----------------------------

void inicializar() {
    ConsoleLogger::instance().log("Iniciando el sistema...");
}

void procesar() {
    ConsoleLogger::instance().warning("El rendimiento está por debajo del esperado.");
}

void finalizar() {
    ConsoleLogger::instance().error("Finalización inesperada detectada.");
}

// ----------------------------
// Punto de entrada
// ----------------------------

int main() {
    inicializar();
    procesar();
    finalizar();

    return 0;
}
```
Aunque funcional, este diseño introduce varias limitaciones importantes:

* **Actúa como una variable global encubierta**: `ConsoleLogger::instance()` puede usarse desde cualquier parte sin declararlo, manteniendo estado compartido durante toda la ejecución.
* **Introduce dependencias ocultas difíciles de rastrear**: funciones como `procesar()` dependen de `ConsoleLogger` sin indicarlo en sus parámetros.
* **Complica la sustitución en pruebas**: no permite reemplazar `ConsoleLogger` por otra implementación de `ILogger`, obligando a usar siempre la instancia real.
* **Hace menos explícito el flujo de creación y uso**: `ConsoleLogger` se crea automáticamente en el primer acceso y no existe un punto claro que controle su ciclo de vida.

## Versión moderna

En esta variante, el logger deja de ser un punto de acceso global y pasa a ser un **objeto explícito dentro del diseño del programa**. En lugar de ocultar su existencia detrás de una clase con acceso global, se crea en un punto central (`main`) y se proporciona a las funciones que lo necesitan.

Este enfoque se basa en la **inyección de dependencias**, donde las funciones reciben un `ILogger&` en lugar de obtener el logger por sí mismas. De este modo, las dependencias quedan visibles en las interfaces y el flujo de uso del objeto resulta claro y controlado.

Aunque sigue existiendo una única instancia (`ConsoleLogger logger;`), su unicidad no está impuesta por la clase, sino por cómo se organiza el programa. Esto permite un diseño más flexible, desacoplado y fácil de mantener.


## Logger.hpp

```cpp
#pragma once
#include <iostream>
#include <string>

// ----------------------------------------
// Interfaz del logger
// ----------------------------------------
class ILogger {
public:
    virtual ~ILogger() = default;

    virtual void log(const std::string& msg) = 0;
    virtual void warning(const std::string& msg) = 0;
    virtual void error(const std::string& msg) = 0;
};

// ----------------------------------------
// Implementación concreta del logger
// ----------------------------------------
class ConsoleLogger : public ILogger {
public:
    void log(const std::string& msg) override {
        std::cout << "[LOG] " << msg << "\n";
    }

    void warning(const std::string& msg) override {
        std::cout << "[WARNING] " << msg << "\n";
    }

    void error(const std::string& msg) override {
        std::cout << "[ERROR] " << msg << "\n";
    }
};
```

## main.cpp

```cpp
#include "Logger.hpp"

// ----------------------------
// Funciones que utilizan el logger
// ----------------------------

void inicializar(ILogger& logger) {
    logger.log("Iniciando el sistema...");
}

void procesar(ILogger& logger) {
    logger.warning("El rendimiento está por debajo del esperado.");
}

void finalizar(ILogger& logger) {
    logger.error("Finalización inesperada detectada.");
}

// ----------------------------
// Punto central del programa
// ----------------------------

int main() {
    // Única instancia del logger, gestionada explícitamente
    ConsoleLogger logger;

    inicializar(logger);
    procesar(logger);
    finalizar(logger);

    return 0;
}
```

* **No actúa como una variable global encubierta**: `ConsoleLogger` se crea explícitamente en `main` y se pasa a las funciones, evitando estado global implícito.
* **Hace explícitas las dependencias**: funciones como `procesar(ILogger& logger)` declaran claramente que dependen de un logger en su interfaz.
* **Facilita la sustitución en pruebas**: permite usar otras implementaciones de `ILogger` (por ejemplo, mocks) sin modificar el código cliente.
* **Hace explícito el flujo de creación y uso**: el objeto `ConsoleLogger logger;` se crea en un punto central y su ciclo de vida es visible y controlado.


