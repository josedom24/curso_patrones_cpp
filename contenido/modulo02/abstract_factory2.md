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

## Ejemplo genérico en C++

```cpp
#include <iostream>
#include <memory>

// ======================================================
//    Interfaces de la familia de productos
// ======================================================

// Producto 1: Button
class Button {
public:
    virtual ~Button() = default;
    virtual void paint() const = 0;
};

// Producto 2: Checkbox
class Checkbox {
public:
    virtual ~Checkbox() = default;
    virtual void toggle() const = 0;
};


// ======================================================
//    Productos concretos de la familia Windows
// ======================================================

class WinButton : public Button {
public:
    void paint() const override {
        std::cout << "[Windows] Pintando botón.\n";
    }
};

class WinCheckbox : public Checkbox {
public:
    void toggle() const override {
        std::cout << "[Windows] Alternando checkbox.\n";
    }
};


// ======================================================
//    Productos concretos de la familia Linux
// ======================================================

class LinuxButton : public Button {
public:
    void paint() const override {
        std::cout << "[Linux] Pintando botón.\n";
    }
};

class LinuxCheckbox : public Checkbox {
public:
    void toggle() const override {
        std::cout << "[Linux] Alternando checkbox.\n";
    }
};


// ======================================================
//    Fábrica abstracta
// ======================================================

class AbstractGUIFactory {
public:
    virtual ~AbstractGUIFactory() = default;

    virtual std::unique_ptr<Button> create_button() const = 0;
    virtual std::unique_ptr<Checkbox> create_checkbox() const = 0;
};


// ======================================================
//    Fábricas concretas
// ======================================================

class WindowsFactory : public AbstractGUIFactory {
public:
    std::unique_ptr<Button> create_button() const override {
        return std::make_unique<WinButton>();
    }

    std::unique_ptr<Checkbox> create_checkbox() const override {
        return std::make_unique<WinCheckbox>();
    }
};

class LinuxFactory : public AbstractGUIFactory {
public:
    std::unique_ptr<Button> create_button() const override {
        return std::make_unique<LinuxButton>();
    }

    std::unique_ptr<Checkbox> create_checkbox() const override {
        return std::make_unique<LinuxCheckbox>();
    }
};


// ======================================================
//    Código cliente
// ======================================================

void cliente(const AbstractGUIFactory& factory) {
    auto button   = factory.create_button();
    auto checkbox = factory.create_checkbox();

    button->paint();
    checkbox->toggle();
}

int main() {
    WindowsFactory winFactory;
    LinuxFactory   linuxFactory;

    cliente(winFactory);
    cliente(linuxFactory);
}
```

## Puntos clave del ejemplo

* La **fábrica abstracta** declara métodos para crear todos los productos de la **familia**.
* Cada fábrica concreta produce **variantes coherentes**:
  *WindowsFactory → productos Windows*,
  *LinuxFactory → productos Linux*.
* El cliente trabaja únicamente con **interfaces (`Button`, `Checkbox`)** y **no conoce las clases concretas**.
* `std::unique_ptr` garantiza seguridad, propiedad clara y ausencia de fugas.
* Añadir una nueva familia (por ejemplo, *macOS*) solo requiere implementar una nueva fábrica y sus productos, sin modificar el cliente.
* El patrón evita mezclar productos incompatibles entre sí.

