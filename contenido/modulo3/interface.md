# Interfaces puras

En programación orientada a objetos, una **interfaz** es un conjunto de funciones públicas que una clase expone y que define **qué puede hacer** un objeto, sin especificar **cómo lo hace**. En C++, no existe un tipo especial llamado `interface` como en otros lenguajes (Java, C#), pero se puede representar mediante **clases abstractas puras**, es decir, clases que contienen exclusivamente **métodos virtuales puros**.

Estas clases proporcionan una forma robusta de diseñar software flexible, extensible y desacoplado, favoreciendo principios como **programar contra interfaces y no contra implementaciones**.

## Interfaz pura

Una **interfaz pura** en C++ es una clase abstracta que cumple las siguientes condiciones:

* Contiene **solo funciones miembro virtuales puras**, es decir, declaradas con `= 0`.
* No proporciona implementación funcional (salvo, opcionalmente, un destructor virtual).
* Su propósito es **definir un contrato** que deben cumplir todas las clases derivadas.

Ejemplo:

```cpp
class Dibujable {
public:
    virtual void dibujar() const = 0;   // Método virtual puro
    virtual ~Dibujable() = default;     // Destructor virtual necesario
};
```

Una **interfaz pura**:

* **No se puede instanciar**: al contener al menos un método virtual puro, la clase es abstracta y no puede usarse para crear objetos directamente.
* **Define una interfaz, no una implementación**: las clases derivadas deben proporcionar su propia implementación de todos los métodos virtuales puros.
* **Soporte para polimorfismo**: permite escribir código que trabaje con objetos a través de referencias o punteros a la interfaz, sin conocer su tipo concreto en tiempo de compilación.
* **Favorece la extensibilidad**: nuevas clases pueden adherirse a la interfaz sin modificar el código existente, cumpliendo con el **principio abierto/cerrado (OCP)**.
* **Consigue el desacoplamiento** entre definición y uso.

## Ejemplo 

```cpp
#include <iostream>
#include <vector>
#include <memory>

// Definimos la interfaz pura
class Dibujable {
public:
    virtual void dibujar() const = 0;
    virtual ~Dibujable() = default;
};

// Clases concretas que implementan la interfaz
class Circulo : public Dibujable {
public:
    void dibujar() const override {
        std::cout << "Dibujando un círculo\n";
    }
};

class Rectangulo : public Dibujable {
public:
    void dibujar() const override {
        std::cout << "Dibujando un rectángulo\n";
    }
};

// Función que trabaja con la interfaz
void renderizar(const std::vector<std::unique_ptr<Dibujable>>& objetos) {
    for (const auto& obj : objetos)
        obj->dibujar();  // Llamada polimórfica
}

int main() {
    std::vector<std::unique_ptr<Dibujable>> figuras;
    figuras.push_back(std::make_unique<Circulo>());
    figuras.push_back(std::make_unique<Rectangulo>());

    renderizar(figuras);
}
```

* `Dibujable` es una interfaz pura.
* `Circulo` y `Rectangulo` la implementan.
* `renderizar` puede operar sobre cualquier objeto que implemente `Dibujable`, sin conocer su tipo real.

---
