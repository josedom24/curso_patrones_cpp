# Abstract Factory

## Introducción y propósito

El patrón **Abstract Factory** proporciona una interfaz para crear **familias de objetos relacionados** sin especificar sus clases concretas.

## Problemas que resuelve

Evita que el código cliente conozca las clases concretas que debe instanciar. Así se promueve el **principio de inversión de dependencias**: el cliente depende de abstracciones, no de implementaciones.

Algunos escenario reales donde lo podemos utilizar:

* **Interfaces gráficas** con temas o estilos (Windows, macOS, Linux).
* **Drivers multiplataforma** o acceso a distintos motores de base de datos.
* **Juegos** donde hay familias de enemigos, terrenos y objetos por cada mundo o nivel.

## Diagrama UML y estructura

```
           +----------------------+
           | AbstractFactory      |
           +----------------------+
           | +createChair()       |
           | +createSofa()        |
           +----------------------+
                   /\
                  /  \
      +----------------------+     +----------------------+
      | ModernFactory        |     | ClassicFactory       |
      +----------------------+     +----------------------+
      | +createChair()       |     | +createChair()       |
      | +createSofa()        |     | +createSofa()        |
      +----------------------+     +----------------------+

           +---------------------+
           | AbstractChair       |
           +---------------------+
           | +sitOn()            |
           +---------------------+
                   /\
                  /  \
      +----------------------+     +----------------------+
      | ModernChair           |     | ClassicChair         |
      +----------------------+     +----------------------+

(Idem para Sofa)
```


* `AbstractFactory`: Declara los métodos para crear productos abstractos.                          |
* `ConcreteFactory`: Implementa la creación de una familia concreta de productos.                  |
* `AbstractProduct`: Interfaz común para una familia de productos (ej. `Chair`, `Sofa`).           |
* `ConcreteProduct`: Implementación específica de un producto (ej. `ModernChair`, `ClassicChair`). |
* El cliente usa solo la interfaz abstracta para crear y usar productos.                   |


## Implementación en C++ moderno

Veamos un ejemplo: Muebles modernos y clásicos

```cpp
#include <iostream>
#include <memory>

// Productos abstractos
struct Chair {
    virtual void sitOn() const = 0;
    virtual ~Chair() = default;
};

struct Sofa {
    virtual void lieOn() const = 0;
    virtual ~Sofa() = default;
};

// Productos concretos - Modernos
struct ModernChair : public Chair {
    void sitOn() const override { std::cout << "Sitting on a modern chair.\n"; }
};

struct ModernSofa : public Sofa {
    void lieOn() const override { std::cout << "Lying on a modern sofa.\n"; }
};

// Productos concretos - Clásicos
struct ClassicChair : public Chair {
    void sitOn() const override { std::cout << "Sitting on a classic chair.\n"; }
};

struct ClassicSofa : public Sofa {
    void lieOn() const override { std::cout << "Lying on a classic sofa.\n"; }
};

// Fábrica abstracta
struct FurnitureFactory {
    virtual std::unique_ptr<Chair> createChair() const = 0;
    virtual std::unique_ptr<Sofa> createSofa() const = 0;
    virtual ~FurnitureFactory() = default;
};

// Fábricas concretas
struct ModernFurnitureFactory : public FurnitureFactory {
    std::unique_ptr<Chair> createChair() const override {
        return std::make_unique<ModernChair>();
    }

    std::unique_ptr<Sofa> createSofa() const override {
        return std::make_unique<ModernSofa>();
    }
};

struct ClassicFurnitureFactory : public FurnitureFactory {
    std::unique_ptr<Chair> createChair() const override {
        return std::make_unique<ClassicChair>();
    }

    std::unique_ptr<Sofa> createSofa() const override {
        return std::make_unique<ClassicSofa>();
    }
};

// Cliente
void clientCode(const FurnitureFactory& factory) {
    auto chair = factory.createChair();
    auto sofa = factory.createSofa();
    chair->sitOn();
    sofa->lieOn();
}

int main() {
    ModernFurnitureFactory modernFactory;
    ClassicFurnitureFactory classicFactory;

    std::cout << "Cliente con muebles modernos:\n";
    clientCode(modernFactory);

    std::cout << "\nCliente con muebles clásicos:\n";
    clientCode(classicFactory);
}
```

* `Chair` y `Sofa` son interfaces base (clases abstractas).
* `ModernChair` y `ClassicChair` son implementaciones concretas.
* `FurnitureFactory` es la interfaz de la fábrica.
* Cada fábrica concreta devuelve objetos que **pertenecen a una misma familia**.
* El cliente (`clientCode`) usa solo la interfaz abstracta, sin conocer detalles concretos.

## Ventajas

* Alto nivel de **desacoplamiento**.
* Facilita añadir nuevas familias de productos (nuevos estilos).
* Favorece la **consistencia entre productos** de una misma familia.
* Ideal para sistemas extensibles y configurables.
* Facilita el reemplazo de familias de objetos.

## Desventajas

* Puede generar **muchas clases** (una por cada producto y fábrica).
* Añadir un nuevo tipo de producto requiere cambios en todas las fábricas existentes.
* A veces, **sobreingeniería** si solo se necesita una fábrica simple (usar Factory Method en ese caso).

## Buenas prácticas

* Usar `std::unique_ptr` para gestión automática de memoria.
* Separar claramente productos abstractos y concretos.
* Documentar bien las familias de productos.

