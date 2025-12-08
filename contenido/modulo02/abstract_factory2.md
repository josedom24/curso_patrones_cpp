# Implementación de Abstract Factory con C++

## Estructura y elementos modernos utilizados

La implementación del **Abstract Factory** en C++ moderno se organiza alrededor del concepto clave de **familias de productos**. Cada familia contiene varios productos relacionados que deben utilizarse de forma coherente. El patrón define fábricas abstractas capaces de producir todos los elementos de una misma familia.

A continuación se describen las clases principales y los elementos de C++ moderno asociados.

### 1. Interfaces base de los Productos

Cada tipo de producto de la familia posee su propia interfaz abstracta.
Por ejemplo, en una familia GUI pueden existir interfaces como `Button` y `Checkbox`.

**Elementos de C++ moderno utilizados:**

* **`std::unique_ptr`** para retornar productos sin fugas y con propiedad bien definida.
* **Destructores virtuales** para garantizar destrucción correcta de objetos polimórficos.
* **Herencia y polimorfismo dinámico**, que permiten a las variantes concretas cumplir la misma interfaz.

### 2. Productos concretos (por familia)

Cada familia proporciona sus propias implementaciones coherentes.
Ejemplo: `WinButton`, `WinCheckbox` para Windows; `LinuxButton`, `LinuxCheckbox` para Linux.

**Elementos de C++ moderno utilizados:**

* **Constructores modernos con listas de inicialización**.
* **Uso natural de RAII**, sin gestión manual de memoria.
* Integración con `std::unique_ptr` como forma estándar de manejar productos polimórficos.

### 3. Interfaz base de la Fábrica abstracta

Declara un conjunto de métodos capaces de crear **todos los productos de una familia**.
Cada método crea un tipo concreto de producto, pero el cliente solo conoce sus interfaces abstractas.

**Elementos de C++ moderno utilizados:**

* **Métodos fábrica que devuelven `std::unique_ptr<Producto>`**.
* Abstracción mediante interfaces puras.
* Posibilidad de que las fábricas se seleccionen dinámicamente (p.ej., según configuración).

### 4. Fábricas concretas

Implementan la creación de toda la familia coherente de productos.
Ejemplo: `WindowsFactory` crea *solo* productos estilo Windows.

**Elementos de C++ moderno utilizados:**

* **`std::make_unique<T>()`** para construir productos de la familia.
* **Encapsulación total** de las clases concretas dentro de la fábrica.
* Sustitución sin cambios en el código cliente gracias a polimorfismo y RAII.

### 5. Código cliente

Trabaja únicamente con la **fábrica abstracta** y las **interfaces de los productos**.
Nunca referencia productos concretos.

**Elementos de C++ moderno utilizados:**

* **Programación a interfaces**, sin dependencias fuertes.
* Gestión automática del ciclo de vida gracias a `std::unique_ptr`.
* **Alta extensibilidad**: el cliente no cambia al añadir una nueva familia.

## Diagrama UML

![uml](uml/abstract_factory.png)

## Ejemplo genérico


```cpp
#include <iostream>
#include <memory>

// ======================================================
//    Interfaces abstractas de los productos
// ======================================================

// Producto 1
class ProductoA {
public:
    virtual ~ProductoA() = default;
    virtual void operacionA() const = 0;
};

// Producto 2
class ProductoB {
public:
    virtual ~ProductoB() = default;
    virtual void operacionB() const = 0;
};


// ======================================================
//    Productos concretos de la Familia A
// ======================================================

class ProductoA_FamiliaA : public ProductoA {
public:
    void operacionA() const override {
        std::cout << "Ejecutando operación A en ProductoA_FamiliaA\n";
    }
};

class ProductoB_FamiliaA : public ProductoB {
public:
    void operacionB() const override {
        std::cout << "Ejecutando operación B en ProductoB_FamiliaA\n";
    }
};


// ======================================================
//    Productos concretos de la Familia B
// ======================================================

class ProductoA_FamiliaB : public ProductoA {
public:
    void operacionA() const override {
        std::cout << "Ejecutando operación A en ProductoA_FamiliaB\n";
    }
};

class ProductoB_FamiliaB : public ProductoB {
public:
    void operacionB() const override {
        std::cout << "Ejecutando operación B en ProductoB_FamiliaB\n";
    }
};


// ======================================================
//    Fábrica abstracta
// ======================================================

class FabricaAbstracta {
public:
    virtual ~FabricaAbstracta() = default;

    virtual std::unique_ptr<ProductoA> crearProductoA() const = 0;
    virtual std::unique_ptr<ProductoB> crearProductoB() const = 0;
};


// ======================================================
//    Fábricas concretas
// ======================================================

class FabricaFamiliaA : public FabricaAbstracta {
public:
    std::unique_ptr<ProductoA> crearProductoA() const override {
        return std::make_unique<ProductoA_FamiliaA>();
    }

    std::unique_ptr<ProductoB> crearProductoB() const override {
        return std::make_unique<ProductoB_FamiliaA>();
    }
};

class FabricaFamiliaB : public FabricaAbstracta {
public:
    std::unique_ptr<ProductoA> crearProductoA() const override {
        return std::make_unique<ProductoA_FamiliaB>();
    }

    std::unique_ptr<ProductoB> crearProductoB() const override {
        return std::make_unique<ProductoB_FamiliaB>();
    }
};


// ======================================================
//    Código cliente
// ======================================================

void cliente(const FabricaAbstracta& fabrica) {
    auto a = fabrica.crearProductoA();
    auto b = fabrica.crearProductoB();

    a->operacionA();
    b->operacionB();
}

int main() {
    FabricaFamiliaA fabricaA;
    FabricaFamiliaB fabricaB;

    cliente(fabricaA);
    cliente(fabricaB);
}
```

## Puntos clave del ejemplo genérico

* La **fábrica abstracta** define los métodos para crear todos los productos de una familia (crearProductoA, crearProductoB)
* Cada **fábrica concreta** produce versiones coherentes de toda su familia:

  * `FabricaFamiliaA` → productos *ProductoA_FamiliaA*, *ProductoB_FamiliaA*
  * `FabricaFamiliaB` → productos *ProductoA_FamiliaB*, *ProductoB_FamiliaB*
* El cliente trabaja solo con **interfaces abstractas** (`ProductoA`, `ProductoB`, `FabricaAbstracta`)
* `std::unique_ptr` garantiza seguridad, propiedad clara y ausencia de fugas
* Añadir una **nueva familia** solo requiere escribir otra fábrica concreta y sus productos
* Evita mezclar productos incompatibles (por ejemplo, ProductoA de FamiliaA con ProductoB de FamiliaB)

