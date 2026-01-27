# Ejemplo: Sistema de gestión de tareas

## Introducción

Para ilustrar el patrón **Facade** en un contexto realista, construiremos un pequeño **sistema de gestión de tareas** que coordina varios subsistemas internos que realizan operaciones específicas:

* **Subsistema de validación**
* **Subsistema de almacenamiento**
* **Subsistema de notificación**

El cliente solo quiere ejecutar operaciones de alto nivel como:

* **crear una tarea**,
* **completar una tarea**,
* **notificar cambios**,
* **obtener un resumen del sistema**.

Sin embargo, cada una de estas operaciones implica múltiples pasos dentro de los subsistemas, los cuales no deberían ser visibles para el código cliente.

El patrón **Facade** permite crear una clase fachada (`GestorTareas`) que ofrezca una **API simple y coherente**, mientras oculta la complejidad de los subsistemas internos.

A continuación se muestra el código completo dividido en:

* **Subsistemas.hpp** – subsistemas y su lógica individual
* **Fachada.hpp** – implementación de la fachada
* **main.cpp** – código cliente

## Subsistemas.hpp

```cpp
#pragma once
#include <iostream>
#include <string>
#include <vector>

// ----------------------------------------
// Subsistema A: Validación de tareas
// ----------------------------------------
class ValidadorTareas {
public:
    bool validar_creacion(const std::string& nombre) const {
        if (nombre.empty()) {
            std::cout << "[Validador] Error: el nombre no puede estar vacío.\n";
            return false;
        }
        std::cout << "[Validador] Tarea válida.\n";
        return true;
    }

    bool validar_completado(int id) const {
        std::cout << "[Validador] Validando id " << id << "...\n";
        return id >= 0;
    }
};

// ----------------------------------------
// Subsistema B: Almacenamiento
// ----------------------------------------
class AlmacenTareas {
private:
    std::vector<std::string> tareas_;

public:
    int guardar(const std::string& nombre) {
        tareas_.push_back(nombre);
        std::cout << "[Almacén] Tarea '" << nombre << "' guardada.\n";
        return static_cast<int>(tareas_.size() - 1);
    }

    void completar(int id) {
        if (id >= 0 && id < static_cast<int>(tareas_.size())) {
            std::cout << "[Almacén] Tarea '" << tareas_[id] 
                      << "' marcada como completada.\n";
        }
    }

    std::size_t total() const {
        return tareas_.size();
    }
};

// ----------------------------------------
// Subsistema C: Notificaciones
// ----------------------------------------
class Notificador {
public:
    void enviar(const std::string& mensaje) const {
        std::cout << "[Notificador] Enviando notificación: " 
                  << mensaje << "\n";
    }
};
```

## Fachada.hpp

```cpp
#pragma once
#include "Subsistemas.hpp"

// ----------------------------------------
// Clase Fachada: interfaz simplificada
// ----------------------------------------
class GestorTareas {
private:
    ValidadorTareas validador_;
    AlmacenTareas almacen_;
    Notificador notificador_;

public:
    // Operación de alto nivel: creación de tarea
    void crear_tarea(const std::string& nombre) {
        std::cout << "=== Creación de tarea ===\n";
        if (!validador_.validar_creacion(nombre)) {
            return;
        }
        int id = almacen_.guardar(nombre);
        notificador_.enviar("Nueva tarea creada con id " + std::to_string(id));
    }

    // Operación de alto nivel: completar una tarea
    void completar_tarea(int id) {
        std::cout << "=== Completando tarea ===\n";
        if (!validador_.validar_completado(id)) {
            return;
        }
        almacen_.completar(id);
        notificador_.enviar("La tarea " + std::to_string(id) + " ha sido completada.");
    }

    // Operación de alto nivel: resumen del sistema
    void mostrar_resumen() const {
        std::cout << "=== Resumen del sistema ===\n";
        std::cout << "Total de tareas: " << almacen_.total() << "\n";
        notificador_.enviar("Resumen consultado.");
    }
};
```

## main.cpp

```cpp
#include "Fachada.hpp"

int main() {
    GestorTareas gestor;

    gestor.crear_tarea("Aprender C++");
    gestor.crear_tarea("Preparar presentación");
    gestor.completar_tarea(0);
    gestor.mostrar_resumen();

    return 0;
}
```

## Añadir un nuevo subsistema

Supongamos que queremos añadir un **Subsistema de registro histórico** para almacenar un log cronológico de cambios.

### Añadir el nuevo subsistema en `Subsistemas.hpp`

```cpp
class RegistroHistorico {
public:
    void registrar(const std::string& evento) {
        std::cout << "[Histórico] " << evento << "\n";
    }
};
```

### Integrar el subsistema en la fachada (`Fachada.hpp`)

```cpp
private:
    RegistroHistorico historico_;   // NUEVO miembro
```

Y actualizar métodos relevantes:

```cpp
void crear_tarea(const std::string& nombre) {
    ...
    historico_.registrar("Tarea creada: " + nombre);
}
```
### Qué no hemos modificado

Al añadir el nuevo subsistema **RegistroHistorico**:

* No se ha modificado el código cliente (`main.cpp`).
* No se ha modificado el contrato público de la clase `GestorTareas`.
* No se han modificado las interfaces ni el comportamiento de los subsistemas existentes.
* No se ha alterado la forma en la que el cliente utiliza el sistema.

Solo hemos añadido:

* Un nuevo subsistema interno (`RegistroHistorico`).
* Lógica adicional dentro de la fachada para coordinar su uso.


