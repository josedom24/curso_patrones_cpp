# Ejemplo: Colección de tareas pendientes (To-Do List)

## Introducción

Para ilustrar el patrón **Iterator** en un contexto realista, construiremos un pequeño sistema de **gestión de tareas pendientes**.

El objetivo es permitir que el código cliente **recorra una colección de tareas sin conocer su representación interna**.
Dependiendo de la colección elegida, las tareas podrán almacenarse:

* en memoria usando un `std::vector`,
* con tareas añadidas dinámicamente,
* o incluso en futuras extensiones: ordenadas por prioridad, filtradas o agrupadas.

Cada iterador concreto sabe cómo recorrer la colección, mientras el código cliente trabaja únicamente con la interfaz `Iterador`.

La colección concreta (`ColeccionTareas`) proporciona un método `crear_iterador()`, encargado de construir un iterador sincronizado con sus datos.

El cliente solo recibirá un iterador y lo usará para leer las tareas secuencialmente sin acceder a la estructura interna ni a los detalles de almacenamiento.

A continuación se muestra el código dividido en:

* **Iterador.hpp** – interfaz del iterador e iterador concreto
* **Coleccion.hpp** – interfaz de la colección y colección concreta
* **main.cpp** – código cliente que recorre las tareas

## Iterador.hpp

```cpp
#pragma once
#include <string>
#include <vector>
#include <memory>

// ----------------------------------------
// Interfaz del iterador
// ----------------------------------------
class Iterador {
public:
    virtual ~Iterador() = default;

    virtual const std::string& actual() const = 0;
    virtual void avanzar() = 0;
    virtual bool fin() const = 0;
};

// ----------------------------------------
// Iterador concreto para una colección de tareas
// ----------------------------------------
class IteradorTareas : public Iterador {
private:
    const std::vector<std::string>& tareas_;
    std::size_t indice_ = 0;

public:
    explicit IteradorTareas(const std::vector<std::string>& tareas)
        : tareas_(tareas) {}

    const std::string& actual() const override {
        return tareas_.at(indice_);
    }

    void avanzar() override {
        ++indice_;
    }

    bool fin() const override {
        return indice_ >= tareas_.size();
    }
};
```

## Coleccion.hpp

```cpp
#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Iterador.hpp"

// ----------------------------------------
// Interfaz de la colección
// ----------------------------------------
class Coleccion {
public:
    virtual ~Coleccion() = default;

    virtual std::unique_ptr<Iterador> crear_iterador() const = 0;
};

// ----------------------------------------
// Colección concreta de tareas
// ----------------------------------------
class ColeccionTareas : public Coleccion {
private:
    std::vector<std::string> tareas_;

public:
    void agregar_tarea(const std::string& tarea) {
        tareas_.push_back(tarea);
    }

    std::unique_ptr<Iterador> crear_iterador() const override {
        return std::make_unique<IteradorTareas>(tareas_);
    }
};
```

## main.cpp

```cpp
#include <iostream>
#include "Coleccion.hpp"

// ----------------------------------------
// Función cliente
// ----------------------------------------
void mostrar_tareas(const Coleccion& coleccion) {
    auto it = coleccion.crear_iterador();

    while (!it->fin()) {
        std::cout << "• " << it->actual() << "\n";
        it->avanzar();
    }
}

int main() {
    ColeccionTareas tareas;

    tareas.agregar_tarea("Comprar leche");
    tareas.agregar_tarea("Preparar presentación");
    tareas.agregar_tarea("Enviar informe semanal");

    std::cout << "Lista de tareas:\n";
    mostrar_tareas(tareas);

    return 0;
}
```

## Añadir un nuevo tipo de iteración

Supongamos que queremos **ordenar las tareas alfabéticamente antes de recorrerlas**, sin modificar ni la interfaz `Iterador` ni `Coleccion`.

Esto se hace añadiendo:

1. **Un nuevo iterador concreto**
2. **Una nueva colección concreta o método específico que lo devuelva**

### Ejemplo: Iterador que recorre las tareas ordenadas

```cpp
class IteradorTareasOrdenadas : public Iterador {
private:
    std::vector<std::string> tareas_ordenadas_;
    std::size_t indice_ = 0;

public:
    explicit IteradorTareasOrdenadas(const std::vector<std::string>& tareas)
        : tareas_ordenadas_(tareas) {
        std::sort(tareas_ordenadas_.begin(), tareas_ordenadas_.end());
    }

    const std::string& actual() const override {
        return tareas_ordenadas_.at(indice_);
    }

    void avanzar() override {
        ++indice_;
    }

    bool fin() const override {
        return indice_ >= tareas_ordenadas_.size();
    }
};
```

### Nueva colección concreta:

```cpp
class ColeccionTareasOrdenadas : public ColeccionTareas {
public:
    std::unique_ptr<Iterador> crear_iterador() const override {
        // Reutilizamos el almacenamiento pero con un iterador distinto
        return std::make_unique<IteradorTareasOrdenadas>(obtener_todas());
    }

private:
    const std::vector<std::string>& obtener_todas() const {
        return ColeccionTareas::tareas_; // debería hacerse con getter protegido
    }
};
```
### Qué no hemos modificado

* No hemos modificado la interfaz `Iterador`.
* No hemos modificado la interfaz `Coleccion`.
* No hemos modificado el código del cliente (`mostrar_tareas`).

Solo hemos:

1. añadido un **nuevo iterador concreto** (`IteradorTareasOrdenadas`),
2. añadido una **nueva colección concreta** o un método alternativo que lo construye (`ColeccionTareasOrdenadas`),
3. y opcionalmente una línea en `main.cpp` para usarlo.
