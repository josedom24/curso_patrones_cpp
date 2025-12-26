# Implementación de Abstract Factory con C++

## Estructura general

La implementación del **Abstract Factory** en C++ moderno permite crear **familias de productos relacionados** sin que el código cliente dependa de clases concretas. El patrón agrupa la creación de varios tipos de objetos bajo una única abstracción, garantizando que los productos creados sean coherentes entre sí.

Este enfoque desacopla la selección de una familia concreta del uso de los productos y permite sustituir una familia completa de objetos sin modificar el código cliente.

## Elementos de C++ moderno utilizados

* **Clases abstractas e interfaces puras** para definir contratos estables de productos y fábricas.
* **Métodos virtuales y virtuales puros** como puntos de extensión.
* **Herencia** para definir variantes concretas de productos y fábricas.
* **Polimorfismo dinámico** para trabajar con familias sin conocer tipos concretos.
* **Destructores virtuales** para destrucción segura de jerarquías polimórficas.
* **`std::unique_ptr`** para expresar propiedad exclusiva de los productos creados.
* **RAII** para garantizar liberación automática de recursos.
* Uso explícito de **`override`** en las implementaciones concretas.

## Componentes del patrón y responsabilidades

### 1. Interfaces base de los **Productos**

* Definen el comportamiento común de cada tipo de producto.
* Establecen contratos estables independientes de las implementaciones concretas.
* Permiten tratar productos de distintas familias de forma uniforme.
* No conocen ni dependen del proceso de creación

### 2. **Productos concretos** (por familia)

* Implementan las interfaces base de los productos.
* Representan variantes coherentes dentro de una misma familia.
* Encapsulan los detalles de implementación y los recursos internos.
* Garantizan compatibilidad entre los productos de la misma familia.

### 3. Interfaz base de la **Fábrica abstracta**

* Declara métodos de creación para todos los tipos de producto.
* Define el contrato común que deben cumplir todas las fábricas concretas.
* Centraliza la creación de familias completas de productos.
* Aísla al cliente de las clases concretas de los productos.

### 4. **Fábricas concretas**

* Implementan la creación de una familia completa y coherente de productos.
* Deciden qué clases concretas de producto se instancian.
* Conocen exclusivamente las implementaciones concretas de su familia.
* Aíslan la lógica de creación del resto del sistema.

### 5. **Código cliente**

* Trabaja únicamente con la fábrica abstracta y las interfaces de los productos.
* No conoce ni depende de las familias concretas.
* Utiliza los productos sin gestionar manualmente su ciclo de vida.
* Permanece estable ante la incorporación de nuevas familias.

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

