# Ejemplo: Logger global del sistema

## Introducción

Para ilustrar el patrón **Singleton** en un contexto realista, construiremos un **logger global** que centraliza la escritura de mensajes de diagnóstico de toda la aplicación.

El objetivo es asegurar que exista **una única instancia del logger**, lo que garantiza:

* una fuente única y coherente de mensajes,
* una configuración compartida,
* un acceso global y controlado,
* y la ausencia de múltiples flujos o archivos abiertos simultáneamente.

El Singleton es adecuado para este escenario porque proporciona un punto de acceso centralizado y evita la creación accidental de múltiples instancias.

Se presenta el código dividido en:

* **LoggerSingleton.hpp** — definición de la clase Singleton
* **main.cpp** — código cliente

## LoggerSingleton.hpp

```cpp
#pragma once
#include <iostream>
#include <string>

class LoggerSingleton {
public:
    // Punto de acceso único al singleton
    static LoggerSingleton& instance() {
        static LoggerSingleton instancia; // Inicialización perezosa y segura
        return instancia;
    }

    // ----------------------------------------
    // Operaciones ofrecidas por el Singleton
    // ----------------------------------------

    // 1. Registrar un mensaje general
    void log(const std::string& mensaje) {
        std::cout << "[LOG] " << mensaje << "\n";
    }

    // 2. Registrar un aviso
    void warning(const std::string& mensaje) {
        std::cout << "[WARNING] " << mensaje << "\n";
    }

    // 3. Registrar un error
    void error(const std::string& mensaje) {
        std::cout << "[ERROR] " << mensaje << "\n";
    }

private:
    // Constructor privado para impedir creación directa
    LoggerSingleton() = default;

    // Destructor privado o protegido (no accesible desde fuera)
    ~LoggerSingleton() = default;

    // Evitar copia y asignación
    LoggerSingleton(const LoggerSingleton&) = delete;
    LoggerSingleton& operator=(const LoggerSingleton&) = delete;

    // Evitar movimiento (opcional pero recomendado)
    LoggerSingleton(LoggerSingleton&&) = delete;
    LoggerSingleton& operator=(LoggerSingleton&&) = delete;
};
```

## main.cpp

```cpp
#include "LoggerSingleton.hpp"

void inicializar() {
    LoggerSingleton::instance().log("Iniciando el sistema...");
}

void procesar() {
    LoggerSingleton::instance().warning("El rendimiento está por debajo del esperado.");
}

void finalizar() {
    LoggerSingleton::instance().error("Finalización inesperada detectada.");
}

int main() {
    inicializar();
    procesar();
    finalizar();

    return 0;
}
```

