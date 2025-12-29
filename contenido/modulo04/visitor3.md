# Ejemplo: Sistema de elementos visitables (inspección de objetos)

## Introducción

Para ilustrar el patrón **Visitor**, construiremos un pequeño sistema formado por **elementos visitables** que representan distintos tipos de objetos dentro de una aplicación (por ejemplo, `ElementoA` y `ElementoB`).

El objetivo es permitir añadir **nuevas operaciones** (mostrar información, validar, exportar, etc.) **sin modificar las clases de los elementos**, delegando dichas operaciones en objetos visitante.

El ejemplo se organiza en:

* **Elementos.hpp / Elementos.cpp** – jerarquía de elementos visitables
* **Visitantes.hpp / Visitantes.cpp** – interfaz visitante y visitantes concretos
* **main.cpp** – código cliente


## Elementos.hpp

```cpp
#pragma once

// Declaración anticipada
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
    void accept(Visitante& v) override;
    void operacion_especifica_A() const;
};

// ----------------------------------------
// Elemento concreto B
// ----------------------------------------
class ElementoB : public Elemento {
public:
    void accept(Visitante& v) override;
    void operacion_especifica_B() const;
};
```


## Elementos.cpp

```cpp
#include <iostream>
#include "Elementos.hpp"
#include "Visitantes.hpp"

// ----------------------------------------
// Implementación de accept (double dispatch)
// ----------------------------------------
void ElementoA::accept(Visitante& v) {
    v.visitar(*this);
}

void ElementoB::accept(Visitante& v) {
    v.visitar(*this);
}

// ----------------------------------------
// Lógica propia de los elementos
// ----------------------------------------
void ElementoA::operacion_especifica_A() const {
    std::cout << "ElementoA: realizando su lógica interna.\n";
}

void ElementoB::operacion_especifica_B() const {
    std::cout << "ElementoB: realizando su lógica interna.\n";
}
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

    virtual void visitar(ElementoA&) = 0;
    virtual void visitar(ElementoB&) = 0;
};

// ----------------------------------------
// Visitante concreto: Mostrar información
// ----------------------------------------
class VisitanteMostrar : public Visitante {
public:
    void visitar(ElementoA&) override;
    void visitar(ElementoB&) override;
};

// ----------------------------------------
// Visitante concreto: Validar
// ----------------------------------------
class VisitanteValidar : public Visitante {
public:
    void visitar(ElementoA&) override;
    void visitar(ElementoB&) override;
};
```


## Visitantes.cpp

```cpp
#include <iostream>
#include "Visitantes.hpp"

// ----------------------------------------
// VisitanteMostrar
// ----------------------------------------
void VisitanteMostrar::visitar(ElementoA& e) {
    std::cout << "[Mostrar] Información de ElementoA → ";
    e.operacion_especifica_A();
}

void VisitanteMostrar::visitar(ElementoB& e) {
    std::cout << "[Mostrar] Información de ElementoB → ";
    e.operacion_especifica_B();
}

// ----------------------------------------
// VisitanteValidar
// ----------------------------------------
void VisitanteValidar::visitar(ElementoA&) {
    std::cout << "[Validar] Comprobando ElementoA...\n";
}

void VisitanteValidar::visitar(ElementoB&) {
    std::cout << "[Validar] Comprobando ElementoB...\n";
}
```


## main.cpp

```cpp
#include <iostream>
#include <vector>
#include <memory>
#include "Visitantes.hpp"

// El cliente opera solo con Elemento y Visitante
void cliente(Elemento& elem, Visitante& visitante) {
    elem.accept(visitante);
}

int main() {
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

Recuerda que debemos realizar la compilación de la siguiente manera:

```bash
g++ main.cpp Elementos.cpp Visitantes.cpp -o visitor
```

## Añadir un nuevo visitante

Para añadir una **nueva operación**, **no se modifican los elementos**.

### Nuevo visitante: `VisitanteExportar`

#### Declaración (`Visitantes.hpp`)

```cpp
// ----------------------------------------
// Nuevo Visitante concreto: Exportar
// ----------------------------------------

class VisitanteExportar : public Visitante {
public:
    void visitar(ElementoA&) override;
    void visitar(ElementoB&) override;
};
```

#### Implementación (`Visitantes.cpp`)

```cpp
// ----------------------------------------
// VisitanteExportar
// ----------------------------------------

void VisitanteExportar::visitar(ElementoA&) {
    std::cout << "[Exportar] Exportando ElementoA en formato JSON.\n";
}

void VisitanteExportar::visitar(ElementoB&) {
    std::cout << "[Exportar] Exportando ElementoB en formato JSON.\n";
}
```

#### Uso desde `main.cpp`

```cpp
VisitanteExportar exportar;

std::cout << "\n--- Exportando ---\n";
for (auto& e : elementos) {
    cliente(*e, exportar);
}
```

## Qué no hemos modificado

* No se ha modificado la interfaz `Elemento`.
* No se ha modificado la interfaz `Visitante`.
* No se ha modificado la lógica interna de `ElementoA` ni `ElementoB`.
* No se ha modificado la función `cliente`.

Solo hemos:

1. añadido un **nuevo visitante concreto** (`VisitanteExportar`),
2. definido su comportamiento específico para cada tipo de elemento,
3. utilizado el nuevo visitante desde el código cliente.

