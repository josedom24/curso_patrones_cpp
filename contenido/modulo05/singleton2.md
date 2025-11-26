# Ejemplo: Logger global del sistema

## Introducción

Para ilustrar el uso de un **logger global** en un contexto realista, construiremos un componente centralizado que gestiona la escritura de mensajes de diagnóstico de toda la aplicación.

El objetivo es asegurar que exista **una única instancia del logger**, lo que garantiza:

* una fuente única y coherente de mensajes,
* una configuración compartida,
* un acceso centralizado y consistente,
* y la ausencia de múltiples flujos o archivos abiertos simultáneamente.

Para conseguirlo de forma clara y flexible, el logger se crea en un punto bien definido del programa y se proporciona a los módulos que lo necesitan mediante **inyección de dependencias**. Esta técnica permite mantener una única instancia, controlar su ciclo de vida y evitar dependencias globales implícitas.

El código se presenta dividido en:

* **Logger.hpp** — interfaz y clase concreta del logger
* **main.cpp** — código cliente

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

1. **La unicidad no la garantiza la clase ni el lenguaje**, sino la arquitectura del programa: se crea un único logger en un punto central y se reutiliza en todas partes.
2. **La inyección de dependencias consiste en recibir el logger desde fuera**, en lugar de crearlo dentro de cada módulo o función.
3. **Las funciones consumidoras no instancian loggers**, solo usan el que reciben, lo que mantiene la coherencia y evita duplicaciones accidentales.
4. **La inyección de dependencias no busca garantizar unicidad**, sino reducir acoplamiento, hacer el diseño más claro y facilitar el reemplazo del logger.
5. **Este enfoque evita estado global oculto**, hace explícito el ciclo de vida del objeto y mejora notablemente la testabilidad.
6. **La unicidad se controla mediante diseño**, no mediante restricciones técnicas como en el patrón Singleton.

