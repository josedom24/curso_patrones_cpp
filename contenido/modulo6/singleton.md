Aquí tienes el material didáctico completo sobre el patrón de diseño **Singleton**, estructurado según tu esquema propuesto:

---

# 🧩 Patrón de Diseño: Singleton

## 1. Introducción y propósito

El patrón **Singleton** garantiza que **una clase tenga una única instancia** y proporciona un **punto de acceso global** a ella.

### Problema que resuelve

Evita que se creen múltiples instancias de una clase cuando solo debe existir una. Por ejemplo, en sistemas donde debe haber:

* Un único gestor de configuración
* Un único logger (registro de eventos)
* Un único acceso a base de datos o sistema de archivos

### Analogía simple

Piensa en un **presidente** de un país: solo debe haber **uno**. Todas las decisiones pasan por esa figura central, y no tiene sentido tener múltiples presidentes activos al mismo tiempo.

---

## 2. Motivación y casos de uso

### Escenarios donde es útil

* Controladores globales de recursos (logger, base de datos, configuración)
* Gestión centralizada de estado (modo debug, preferencias del usuario)
* Acceso compartido a hardware o servicios únicos (impresora, red)

### Problemas que ayuda a evitar

* Duplicación de recursos costosos
* Confusión o inconsistencias por múltiples instancias no sincronizadas
* Dependencia innecesaria de múltiples copias de un objeto que debería ser único

### Ámbitos de aplicación

* Interfaces gráficas (gestor de eventos)
* Motores de videojuegos (controlador de escenas)
* Sistemas embebidos (controladores de hardware únicos)

---

## 3. Relación con principios SOLID y buenas prácticas

| Principio                           | Relación                                                                           |
| ----------------------------------- | ---------------------------------------------------------------------------------- |
| **SRP** (Responsabilidad Única)     | La clase Singleton tiene una única responsabilidad: controlar su propia instancia. |
| **OCP** (Abierto/Cerrado)           | Se puede extender su comportamiento sin modificar cómo se accede a la instancia.   |
| **DIP** (Inversión de dependencias) | Puede romper DIP si se abusa del acceso global (ver desventajas).                  |

**Otros conceptos modernos relacionados:**

* RAII: La instancia puede gestionar recursos y liberar correctamente si se usa con `std::unique_ptr`.
* Smart pointers: permiten controlar el ciclo de vida de la instancia (lazy initialization).
* `std::function` y lambdas: se pueden usar para extender o modificar comportamiento del singleton.

---

## 4. Diagrama y estructura

### UML simplificado

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

---

## 5. Implementación en C++ moderno

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

### Explicación paso a paso

* `Logger()` es **privado**: evita que se creen instancias desde fuera.
* `instancia()` devuelve una referencia a una **instancia estática local**, creada la primera vez que se llama.
* Se eliminan la copia y la asignación (`= delete`) para evitar que otros dupliquen la instancia.

---

## 6. Ventajas, desventajas y consideraciones

### ✅ Ventajas

* Control total sobre la única instancia.
* Inicialización perezosa (`lazy initialization`).
* Thread-safe en C++11+ sin necesidad de mecanismos adicionales.

### ❌ Desventajas

* El acceso global puede fomentar **acoplamiento** innecesario (anti-patrón global).
* Dificulta pruebas unitarias si se accede directamente (no se puede inyectar una instancia falsa).
* Puede violar el principio de inversión de dependencias si se abusa del patrón.

### 🛠️ Consideraciones prácticas

* Usar solo cuando realmente se necesita **una única instancia**.
* Considerar pasar la instancia como dependencia si se necesita **flexibilidad y testeo**.
* Evitar el uso de Singleton como **almacén de estados globales no controlados**.

---

## 7. Ejemplos de aplicación real o mini-proyectos

### Mini-proyectos

* **Logger de eventos** con opción de niveles (`info`, `error`, `debug`)
* **Gestor de configuración** que se carga una vez desde un archivo
* **Controlador de acceso a base de datos** simulado

### Ejercicio propuesto

> Implementa una clase `Configuracion` como singleton, que cargue y exponga valores desde un archivo `.ini` simulado. Asegúrate de que no puede ser copiada ni instanciada directamente.

---

## 8. Resumen y puntos clave

* El patrón Singleton **garantiza una única instancia** de una clase.
* Controla la creación usando un **constructor privado** y un **método estático**.
* Útil para representar **recursos globales o compartidos**.
* Debe usarse con cuidado: el acceso global puede **romper principios de diseño** si se abusa.
* La implementación moderna en C++ es sencilla y segura gracias a las **variables locales estáticas** (C++11+).

---

¿Quieres que prepare ahora un esquema similar para otro patrón (como Factory Method, Observer, Decorator…)?
