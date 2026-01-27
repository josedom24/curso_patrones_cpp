# Ejemplo: Editor de formas gráficas

## Introducción

Para ilustrar el patrón **Prototype** en un contexto realista, construiremos un pequeño **editor de formas gráficas**.
El objetivo del sistema es permitir que el código cliente pueda **duplicar formas** sin conocer sus clases concretas, recurriendo al método `clonar()` definido en una interfaz común (`Forma`).

Cada forma es un **prototipo** capaz de generar copias de sí misma. Esto permite:

* Clonar objetos complejos sin reconstruirlos desde cero.
* Evitar dependencias con clases concretas.
* Añadir nuevas formas sin modificar el código existente.
* Demostrar el uso práctico del polimorfismo con `std::unique_ptr`.

El ejemplo se divide en:

* **Formas.hpp**: interfaz base y prototipos concretos.
* **main.cpp**: código cliente.

## Formas.hpp

```cpp
#pragma once
#include <iostream>
#include <memory>
#include <string>

// ----------------------------------------
// Interfaz base del prototipo: Forma
// ----------------------------------------
class Forma {
public:
    virtual ~Forma() = default;
    virtual std::unique_ptr<Forma> clonar() const = 0;
    virtual void dibujar() const = 0;
};

// ----------------------------------------
// Prototipo concreto: Rectángulo
// ----------------------------------------
class Rectangulo : public Forma {
private:
    int ancho_;
    int alto_;

public:
    Rectangulo(int ancho, int alto)
        : ancho_(ancho), alto_(alto) {}

    std::unique_ptr<Forma> clonar() const override {
        // Copia superficial (suficiente para tipos primitivos)
        return std::make_unique<Rectangulo>(*this);
    }

    void dibujar() const override {
        std::cout << "Rectángulo [" << ancho_
                  << "x" << alto_ << "]\n";
    }
};

// ----------------------------------------
// Prototipo concreto: Círculo
// ----------------------------------------
class Circulo : public Forma {
private:
    int radio_;

public:
    explicit Circulo(int radio)
        : radio_(radio) {}

    std::unique_ptr<Forma> clonar() const override {
        return std::make_unique<Circulo>(*this);
    }

    void dibujar() const override {
        std::cout << "Círculo (radio=" << radio_ << ")\n";
    }
};
```

## main.cpp

```cpp
#include "Formas.hpp"

// Función cliente que recibe cualquier forma y la clona
void cliente(const Forma& prototipo) {
    auto copia = prototipo.clonar();
    copia->dibujar();
}

int main() {
    Rectangulo rect(120, 60);
    Circulo circ(40);

    cliente(rect);   // Clona y dibuja un rectángulo
    cliente(circ);   // Clona y dibuja un círculo

    return 0;
}
```

## Añadir un nuevo prototipo

Añadir un nuevo prototipo es **muy sencillo** y no requiere modificar el código existente.
Los prototipos anteriores utilizaban **copia por valor**, suficiente al no gestionar recursos dinámicos. En este caso, vamos a añadir un nuevo prototipo que **sí contiene un atributo dinámico**, por lo que necesita implementar una **copia profunda**.

Supongamos que queremos añadir una nueva forma: **Rectángulo con estilo**.

### Añadir el nuevo prototipo en `Formas.hpp`

Debajo de las demás formas, añadimos:

```cpp
// ----------------------------------------
// Prototipo concreto: Rectángulo con estilo
// ----------------------------------------

class RectanguloConEstilo : public Forma {
private:
    int ancho_;
    int alto_;
    std::unique_ptr<std::string> color_;  // atributo dinámico

public:
    RectanguloConEstilo(int ancho, int alto, std::string color)
        : ancho_(ancho),
          alto_(alto),
          color_(std::make_unique<std::string>(std::move(color))) {}

    // Clonación profunda: se duplica el recurso dinámico
    std::unique_ptr<Forma> clonar() const override {
        return std::make_unique<RectanguloConEstilo>(
            ancho_,
            alto_,
            *color_
        );
    }

    void dibujar() const override {
        std::cout << "Rectángulo [" << ancho_
                  << "x" << alto_
                  << "] color=" << *color_ << "\n";
    }
};
```

### Usar el nuevo prototipo en `main.cpp`

Simplemente añadimos un objeto `RectanguloConEstilo` y usamos `cliente()`:

```cpp
RectanguloConEstilo rectEstilado(100, 50, "rojo");
cliente(rectEstilado);
```

### Qué no hemos modificado

* No hemos cambiado la interfaz `Forma`.
* No hemos cambiado ninguna de las formas existentes.
* No hemos cambiado el código del cliente.

Solo hemos añadido:

* Una **nueva clase prototipo** (`RectanguloConEstilo`),
* Una **línea en `main.cpp`** para probarlo.

