# Implementación de Factory Method con C++

## Estructura y elementos modernos utilizados

La implementación del **Factory Method** en C++ moderno se organiza en torno a un conjunto de clases con responsabilidades bien definidas. A continuación se describen estas clases y, para cada una, los mecanismos de C++ moderno que resultan relevantes.

### 1. Interfaz o clase base del **Producto**

Define el comportamiento común que todos los productos deben ofrecer. El código cliente trabaja exclusivamente a través de esta interfaz, sin conocer los tipos concretos.

**Elementos de C++ moderno utilizados:**

* **`std::unique_ptr`** como tipo de retorno y de uso en toda la jerarquía, garantizando propiedad clara y destrucción automática.
* **Destructores virtuales** para permitir una gestión segura de objetos polimórficos mediante punteros inteligentes.
* **Polimorfismo dinámico** para permitir que distintos productos se utilicen de forma uniforme.

### 2. **Productos concretos**

Implementan el comportamiento definido por la interfaz base. Cada clase concreta representa una variante específica del producto.

**Elementos de C++ moderno utilizados:**

* **Construcción segura** mediante inicialización moderna de objetos (lista de inicialización, tipos fuertes, reglas de RAII apropiadas).
* Uso natural de **`std::unique_ptr`** como forma esperada de gestionar instancias polimórficas.

### 3. Interfaz o clase base **Creador**

Declara el **factory method**, que define cómo se obtiene un producto. También puede contener operaciones que utilizan el producto creado sin necesidad de conocer su tipo concreto.

**Elementos de C++ moderno utilizados:**

* **Métodos que devuelven `std::unique_ptr<Producto>`**, separando claramente propiedad y responsabilidad.
* **Separación entre creación y uso**, apoyada por punteros inteligentes que evitan fugas y simplifican el ciclo de vida de los objetos creados.
* **Polimorfismo** para permitir que el creador delegue la decisión del tipo concreto a las subclases.

### 4. **Creadores concretos**

Implementan el método fábrica y crean instancias de productos concretos. Son los únicos lugares del sistema donde se conoce el tipo específico del producto.

**Elementos de C++ moderno utilizados:**

* **`std::make_unique<T>()`** para construir el producto de forma segura.
* **Encapsulación estricta** que evita exponer detalles de los tipos concretos al resto del sistema.

### 5. **Código cliente**

Interactúa únicamente con la interfaz del creador y nunca con productos concretos. Obtiene productos ya configurados y listos para su uso.

**Elementos de C++ moderno utilizados:**

* **Programación a interfaces**, apoyada por punteros inteligentes para gestionar productos polimórficos sin preocuparse por el ciclo de vida.
* **Dependencia explícitamente reducida** gracias a la combinación de polimorfismo y RAII moderno.
* **Uso natural de objetos temporales** que contienen productos creados por la fábrica sin necesidad de gestión manual.

## Diagrama UML

![uml](uml/factory_method.png)

## Ejemplo genérico


```cpp
#include <iostream>
#include <memory>

// ----------------------------------------
// Interfaz base del producto
// ----------------------------------------
class Producto {
public:
    virtual ~Producto() = default;
    virtual void operar() const = 0;
};

// Producto concreto A
class ProductoConcretoA : public Producto {
public:
    void operar() const override {
        std::cout << "Operación del ProductoConcretoA.\n";
    }
};

// Producto concreto B
class ProductoConcretoB : public Producto {
public:
    void operar() const override {
        std::cout << "Operación del ProductoConcretoB.\n";
    }
};

// ----------------------------------------
// Interfaz base del creador
// ----------------------------------------
class Creador {
public:
    virtual ~Creador() = default;

    // Factory Method
    virtual std::unique_ptr<Producto> crear_producto() const = 0;

    // Operación que utiliza el producto
    void ejecutar() const {
        auto producto = crear_producto();
        producto->operar();
    }
};

// Creador concreto A
class CreadorConcretoA : public Creador {
public:
    std::unique_ptr<Producto> crear_producto() const override {
        return std::make_unique<ProductoConcretoA>();
    }
};

// Creador concreto B
class CreadorConcretoB : public Creador {
public:
    std::unique_ptr<Producto> crear_producto() const override {
        return std::make_unique<ProductoConcretoB>();
    }
};

// ----------------------------------------
// Función cliente
// ----------------------------------------
void cliente(const Creador& creador) {
    creador.ejecutar();
}

int main() {
    CreadorConcretoA fabricaA;
    CreadorConcretoB fabricaB;

    cliente(fabricaA);
    cliente(fabricaB);

    return 0;
}
```

## Puntos clave del ejemplo

* El método fábrica `crear_producto()` encapsula la decisión de qué producto concreto se instancia.
* El uso de `std::unique_ptr` garantiza una gestión automática y segura de la memoria.
* La clase `Creador` define una operación (`ejecutar`) que trabaja con el producto sin conocer su tipo concreto, reforzando la separación entre creación y uso.
* El cliente depende únicamente de la interfaz del creador, no de los productos concretos.

