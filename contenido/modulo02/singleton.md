# Singleton

## Introducción y propósito

El patrón **Singleton** garantiza que **una clase tenga una única instancia** y proporciona un **punto de acceso global** a ella.

## Problema que resuelve

Evita que se creen múltiples instancias de una clase cuando solo debe existir una. Por ejemplo, en sistemas donde debe haber:

* Un único gestor de configuración.
* Un único logger (registro de eventos).
* Un único acceso a base de datos o sistema de archivos.

Algunos escenarios donde es útil:

* Controladores globales de recursos (logger, base de datos, configuración).
* Gestión centralizada de estado (modo debug, preferencias del usuario).
* Acceso compartido a hardware o servicios únicos (impresora, red).

Nos ayuda a evitar:

* Duplicación de recursos costosos.
* Confusión o inconsistencias por múltiples instancias no sincronizadas.
* Dependencia innecesaria de múltiples copias de un objeto que debería ser único.

## Diagrama UML y estructura

```
┌──────────────────────┐
│      Singleton       │
├──────────────────────┤
│ - instancia : T*     │
├──────────────────────┤
│ + instancia() : T&   │
│ + operacion()        │
└──────────────────────┘
```

* `instancia()` es un método estático que devuelve una referencia a la instancia única.
* El constructor es privado para impedir otras construcciones.

## Implementación en C++ moderno

```cpp
#include <iostream>

class Logger {
private:
    Logger() {
        std::cout << "Logger creado.\n";
    }

    // Eliminar copia y asignación
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

public:
    static Logger& instancia() {
        static Logger unica_instancia; // Se crea una vez (lazy, thread-safe en C++11+)
        return unica_instancia;
    }

    void log(const std::string& mensaje) {
        std::cout << "[LOG] " << mensaje << '\n';
    }
};

int main() {
    Logger::instancia().log("Inicio del sistema.");
    Logger::instancia().log("Cargando configuración.");
}
```

* `Logger()` es **privado**: evita que se creen instancias desde fuera.
* `instancia()` devuelve una referencia a una **instancia estática local**, con eso conseguimos dos propiedades importantes:
    * **Lazy Initialization (Inicialización perezosa)**: El objeto se crea solo cuando se necesita por primera vez, en lugar de hacerlo al inicio del programa.
    * **Thread-safe (Seguro para múltiples hilos)**: El código puede ejecutarse correctamente en un entorno con múltiples hilos sin riesgo **de condiciones de carrera (race conditions)**. Si varios hilos llaman a `getInstance()` al mismo tiempo, solo uno de ellos debe crear la instancia, y los demás deben obtener la misma instancia sin errores.
* Se eliminan la copia y la asignación (`= delete`) para evitar que otros dupliquen la instancia.

## Ventajas

* Control total sobre la única instancia.
* Inicialización perezosa (`lazy initialization`).
* Thread-safe en C++11+ sin necesidad de mecanismos adicionales.

## Desventajas

* El acceso global puede fomentar **acoplamiento** innecesario (anti-patrón global). Debido a que se comporta como una variable global disfrazada, y el uso de variables globales es considerado un **anti-patrón**.
* Dificulta pruebas unitarias si se accede directamente (no se puede inyectar una instancia falsa que simule su comportamiento).
* Puede violar el principio de inversión de dependencias si se abusa del patrón, ya que acceder al objeto está acoplándose directamente a una implementación concreta , lo cual viola el principio.

## Configuración del comportamiento

A veces no queremos que el Singleton tenga un comportamiento fijo. En su lugar, puede ser útil permitir que el usuario **inyecte o registre comportamiento personalizado** en tiempo de ejecución, como funciones de procesamiento, filtros, callbacks, etc.

Usando `std::function` como atributo del Singleton, puedes permitir que se le asigne cualquier función o lambda que respete una cierta firma. Veamos un ejemplo donde vamos a construir  un logger siguiendo el aptrón Singleton, que permita al usuario definir **cómo se imprime cada mensaje**:

```cpp
#include <iostream>
#include <functional>
#include <string>

class Logger {
private:
    Logger() = default;

    std::function<void(const std::string&)> estrategia_log = 
        [](const std::string& mensaje) {
            std::cout << "[DEFAULT] " << mensaje << '\n';
        };

public:
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    static Logger& instancia() {
        static Logger instancia_unica;
        return instancia_unica;
    }

    void log(const std::string& mensaje) {
        estrategia_log(mensaje); // uso del std::function
    }

    void establecerEstrategia(std::function<void(const std::string&)> nueva_funcion) {
        estrategia_log = nueva_funcion;
    }
};

int main() {
    // Uso por defecto
    Logger::instancia().log("Mensaje normal");

    // Cambiar el comportamiento del log con una lambda
    Logger::instancia().establecerEstrategia([](const std::string& msg) {
        std::cerr << "[ERROR] " << msg << '\n';
    });

    Logger::instancia().log("Este mensaje va a std::cerr");
}
```
