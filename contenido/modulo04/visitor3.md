# Ejemplo: Sistema de elementos visitables (inspección de objetos)

## Introducción

Para ilustrar el patrón **Visitor** en un contexto realista, construiremos un pequeño sistema formado por **elementos visitables** que representan distintos tipos de objetos dentro de una aplicación: por ejemplo, una *ParteA* y una *ParteB* de un sistema complejo.

El objetivo es permitir que el código cliente pueda aplicar **distintas operaciones**, como:

* mostrar información,
* obtener estadísticas,
* validar el estado interno de los objetos,

sin necesidad de **modificar** las clases de los elementos cada vez que añadimos una nueva operación.

Cada elemento concreto implementa un método `accept()` que delega la operación en un visitante concreto.
El cliente trabaja solo con las interfaces `Elemento` y `Visitante`, desconociendo los tipos específicos.

A continuación se muestra el código completo dividido en:

* **Elementos.hpp** – jerarquía de elementos y su interfaz
* **Visitantes.hpp** – interfaz visitante y visitantes concretos
* **main.cpp** – código cliente

## Elementos.hpp

```cpp
#pragma once
#include <iostream>
#include <memory>

// Declaración adelantada de Visitante
class Visitante;

// ----------------------------------------
// Interfaz base del elemento
// ----------------------------------------
class Elemento {
public:
    virtual ~Elemento() = default;
    virtual void accept(Visitante& v) = 0;
};

// ----------------------------------------
// Elemento concreto A
// ----------------------------------------
class ElementoA : public Elemento {
public:
    void accept(Visitante& v) override; // Implementación en Visitantes.hpp

    void operacion_especifica_A() const {
        std::cout << "ElementoA: realizando su lógica interna.\n";
    }
};

// ----------------------------------------
// Elemento concreto B
// ----------------------------------------
class ElementoB : public Elemento {
public:
    void accept(Visitante& v) override;

    void operacion_especifica_B() const {
        std::cout << "ElementoB: realizando su lógica interna.\n";
    }
};
```

## Visitantes.hpp

```cpp
#pragma once
#include "Elementos.hpp"

// ----------------------------------------
// Interfaz Visitante
// ----------------------------------------
class Visitante {
public:
    virtual ~Visitante() = default;

    virtual void visitar(ElementoA& e) = 0;
    virtual void visitar(ElementoB& e) = 0;
};

// ----------------------------------------
// Implementación de accept() (double dispatch)
// ----------------------------------------
inline void ElementoA::accept(Visitante& v) { v.visitar(*this); }
inline void ElementoB::accept(Visitante& v) { v.visitar(*this); }

// ----------------------------------------
// Visitante concreto 1: Mostrar información
// ----------------------------------------
class VisitanteMostrar : public Visitante {
public:
    void visitar(ElementoA& e) override {
        std::cout << "[Mostrar] Información de ElementoA → ";
        e.operacion_especifica_A();
    }

    void visitar(ElementoB& e) override {
        std::cout << "[Mostrar] Información de ElementoB → ";
        e.operacion_especifica_B();
    }
};

// ----------------------------------------
// Visitante concreto 2: Validación
// ----------------------------------------
class VisitanteValidar : public Visitante {
public:
    void visitar(ElementoA& e) override {
        std::cout << "[Validar] Comprobando ElementoA...\n";
    }

    void visitar(ElementoB& e) override {
        std::cout << "[Validar] Comprobando ElementoB...\n";
    }
};
```

## main.cpp

```cpp
#include <vector>
#include <memory>
#include "Visitantes.hpp"

// El cliente opera solo con Elemento y Visitante
void cliente(Elemento& elem, Visitante& visitante) {
    elem.accept(visitante);
}

int main() {
    // Colección heterogénea de elementos
    std::vector<std::unique_ptr<Elemento>> elementos;
    elementos.push_back(std::make_unique<ElementoA>());
    elementos.push_back(std::make_unique<ElementoB>());

    VisitanteMostrar mostrar;
    VisitanteValidar validar;

    for (auto& e : elementos) {
        cliente(*e, mostrar);
    }

    std::cout << "\n--- Validando ---\n";

    for (auto& e : elementos) {
        cliente(*e, validar);
    }

    return 0;
}
```

## Añadir un nuevo visitante

**Para añadir una nueva operación NO modificamos las clases de los elementos.**

Supongamos que queremos añadir un nuevo visitante con una operación de **exportación**.

### Añadir un nuevo visitante en `Visitantes.hpp`

Debajo de los otros visitantes, añadimos:

```cpp
class VisitanteExportar : public Visitante {
public:
    void visitar(ElementoA& e) override {
        std::cout << "[Exportar] Exportando ElementoA en formato JSON.\n";
    }

    void visitar(ElementoB& e) override {
        std::cout << "[Exportar] Exportando ElementoB en formato JSON.\n";
    }
};
```

### Usarlo desde el cliente (`main.cpp`)

```cpp
VisitanteExportar exportar;

for (auto& e : elementos) {
    cliente(*e, exportar);
}
```

### Qué no hemos modificado

* No hemos modificado la interfaz `Elemento`.
* No hemos modificado la interfaz `Visitante`.
* No hemos modificado la lógica interna de `ElementoA` ni `ElementoB`.
* No hemos modificado el código de `cliente`.

Solo hemos:

1. añadido un **nuevo visitante concreto** (`VisitanteExportar`),
2. y opcionalmente una línea en `main.cpp` para usarlo.

