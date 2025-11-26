# Ejemplo: Sistema de iconos compartidos

## Introducción

Para ilustrar el patrón **Flyweight** en un contexto realista, construiremos un pequeño sistema de **iconos compartidos**.
En muchas aplicaciones gráficas (mapas, editores, paneles, dashboards,...) es habitual tener **miles de elementos** que comparten un mismo aspecto visual (iconos) pero cambian en su posición o información contextual.

El objetivo del sistema es:

* **Evitar crear miles de iconos idénticos**, ahorrando memoria.
* Compartir el **estado intrínseco** (la imagen/forma/identidad del icono).
* Pasar desde el exterior el **estado extrínseco** (posición, tamaño, metadatos).

Cada icono compartido se representa mediante un `Flyweight`, que guarda solo su estado intrínseco.
La clase `FlyweightFactory` se encarga de crear y gestionar estos iconos compartidos, devolviendo siempre la misma instancia para un mismo tipo.

El código cliente simula la creación de iconos en un mapa, solicitando repetidamente iconos con el mismo estado intrínseco (por ejemplo: *"árbol"*, *"casa"*, *"persona"*), pero con posiciones diferentes.

A continuación se muestra el código completo dividido en:

* **Flyweight.hpp** – interfaz y flyweights concretos
* **FlyweightFactory.hpp** – fábrica de flyweights
* **main.cpp** – código cliente

## Flyweight.hpp

```cpp
#pragma once
#include <iostream>
#include <string>

// ----------------------------------------
// Interfaz base del Flyweight
// ----------------------------------------
class Flyweight {
public:
    virtual ~Flyweight() = default;

    // Recibe el estado extrínseco
    virtual void mostrar(const std::string& posicion) const = 0;
};

// ----------------------------------------
// Flyweight concreto: almacena solo estado intrínseco
// ----------------------------------------
class IconoCompartido : public Flyweight {
private:
    std::string tipo_; // estado intrínseco: nombre del icono

public:
    explicit IconoCompartido(std::string tipo)
        : tipo_(std::move(tipo)) {}

    void mostrar(const std::string& posicion) const override {
        std::cout << "Mostrando icono [" << tipo_
                  << "] en posición " << posicion << "\n";
    }
};
```

## FlyweightFactory.hpp

```cpp
#pragma once
#include <memory>
#include <unordered_map>
#include <string>
#include "Flyweight.hpp"

// ----------------------------------------
// Fábrica de Flyweights
// ----------------------------------------
class FlyweightFactory {
private:
    std::unordered_map<std::string, std::shared_ptr<Flyweight>> pool_;

public:
    std::shared_ptr<Flyweight> obtener_icono(const std::string& tipo) {
        if (!pool_.contains(tipo)) {
            pool_[tipo] = std::make_shared<IconoCompartido>(tipo);
        }
        return pool_[tipo];
    }

    std::size_t total_iconos() const {
        return pool_.size();
    }
};
```

# main.cpp

```cpp
#include "FlyweightFactory.hpp"

int main() {
    FlyweightFactory fabrica;

    // Simulamos iconos repetidos con distinta posición
    auto arbol = fabrica.obtener_icono("Árbol");
    auto casa  = fabrica.obtener_icono("Casa");
    auto persona = fabrica.obtener_icono("Persona");

    arbol->mostrar("(10,10)");
    arbol->mostrar("(20,30)");
    arbol->mostrar("(50,60)");

    casa->mostrar("(100,200)");
    casa->mostrar("(120,240)");

    persona->mostrar("(5,8)");
    persona->mostrar("(6,15)");

    std::cout << "\nIconos realmente creados: " 
              << fabrica.total_iconos() << "\n";

    return 0;
}
```

## Añadir un nuevo tipo de icono

**No se modifica ninguna clase existente.**

Solo añadimos:

1. Un nuevo tipo en el cliente, o...
2. Un nuevo Flyweight concreto si deseamos un comportamiento distinto.

### Opción 1: solo añadir un nuevo tipo de icono

En `main.cpp`:

```cpp
auto coche = fabrica.obtener_icono("Coche");
coche->mostrar("(300,400)");
```

### Opción 2: añadir un Flyweight concreto adicional

En `Flyweight.hpp`:

```cpp
class IconoEspecial : public Flyweight {
public:
    void mostrar(const std::string& posicion) const override {
        std::cout << "[Especial] Icono destacado en " << posicion << "\n";
    }
};
```

En `FlyweightFactory.hpp`:

```cpp
if (tipo == "Especial") {
    pool_[tipo] = std::make_shared<IconoEspecial>();
}
```

