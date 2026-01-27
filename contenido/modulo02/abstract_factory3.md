# Ejemplo: Interfaz gráfica multiplataforma

## Introducción

Para ilustrar el patrón **Abstract Factory** en un escenario realista, construiremos un pequeño sistema de componentes gráficos (*widgets*).

El objetivo es permitir que el código cliente construya y utilice componentes de interfaz gráfica, botones, casillas de verificación, etc., **sin conocer la plataforma concreta** para la que están diseñados.

Dependiendo de la fábrica seleccionada, los widgets serán:

* de estilo **Windows**, o
* de estilo **Linux**.

Cada familia contiene sus propios productos coherentes:

* **Familia Windows:** `WinButton`, `WinCheckbox`
* **Familia Linux:** `LinuxButton`, `LinuxCheckbox`

El código cliente interactúa únicamente con la fábrica abstracta `AbstractGUIFactory`, que proporciona los métodos `create_button()` y `create_checkbox()`.
Las fábricas concretas (`WindowsFactory`, `LinuxFactory`) se encargan de producir todos los componentes coherentes dentro de una misma familia.

A continuación se muestra el código completo dividido en:

* **Productos.hpp**: productos e interfaces.
* **Fabricas.hpp**: fábricas y sus implementaciones.
* **main.cpp**: código cliente.

## Productos.hpp

```cpp
#pragma once
#include <iostream>
#include <memory>

// ----------------------------------------
// Interfaces de los productos
// ----------------------------------------

class Button {
public:
    virtual ~Button() = default;
    virtual void paint() const = 0;
};

class Checkbox {
public:
    virtual ~Checkbox() = default;
    virtual void toggle() const = 0;
};


// ----------------------------------------
// Productos concretos: FAMILIA WINDOWS
// ----------------------------------------

class WinButton : public Button {
public:
    void paint() const override {
        std::cout << "[Windows] Dibujando botón.\n";
    }
};

class WinCheckbox : public Checkbox {
public:
    void toggle() const override {
        std::cout << "[Windows] Alternando checkbox.\n";
    }
};


// ----------------------------------------
// Productos concretos: FAMILIA LINUX
// ----------------------------------------

class LinuxButton : public Button {
public:
    void paint() const override {
        std::cout << "[Linux] Dibujando botón.\n";
    }
};

class LinuxCheckbox : public Checkbox {
public:
    void toggle() const override {
        std::cout << "[Linux] Alternando checkbox.\n";
    }
};
```

## Fabricas.hpp

```cpp
#pragma once
#include <memory>
#include "Productos.hpp"

// ----------------------------------------
// Fábrica abstracta
// ----------------------------------------
class AbstractGUIFactory {
public:
    virtual ~AbstractGUIFactory() = default;

    virtual std::unique_ptr<Button>   create_button() const = 0;
    virtual std::unique_ptr<Checkbox> create_checkbox() const = 0;
};


// ----------------------------------------
// Fábrica concreta: FAMILIA WINDOWS
// ----------------------------------------

class WindowsFactory : public AbstractGUIFactory {
public:
    std::unique_ptr<Button> create_button() const override {
        return std::make_unique<WinButton>();
    }
    
    std::unique_ptr<Checkbox> create_checkbox() const override {
        return std::make_unique<WinCheckbox>();
    }
};


// ----------------------------------------
// Fábrica concreta: FAMILIA LINUX
// ----------------------------------------

class LinuxFactory : public AbstractGUIFactory {
public:
    std::unique_ptr<Button> create_button() const override {
        return std::make_unique<LinuxButton>();
    }
    
    std::unique_ptr<Checkbox> create_checkbox() const override {
        return std::make_unique<LinuxCheckbox>();
    }
};
```

## main.cpp

```cpp
#include "Fabricas.hpp"

void cliente(const AbstractGUIFactory& fabrica) {
    auto boton = fabrica.create_button();
    auto checkbox = fabrica.create_checkbox();

    boton->paint();
    checkbox->toggle();
}

int main() {
    WindowsFactory winUI;
    LinuxFactory   linuxUI;

    cliente(winUI);
    cliente(linuxUI);

    return 0;
}
```

## Añadir una nueva familia de productos

**Para añadir una nueva familia solo hay que crear nuevos productos concretos y una nueva fábrica concreta. No se modifica ninguna interfaz existente.**

Veamos cómo añadir la **familia macOS**.

### Añadir los nuevos productos en `Productos.hpp`

```cpp
// ----------------------------------------
// Productos concretos: FAMILIA macOS
// ----------------------------------------

class MacButton : public Button {
public:
    void paint() const override {
        std::cout << "[macOS] Dibujando botón con estilo macOS.\n";
    }
};

class MacCheckbox : public Checkbox {
public:
    void toggle() const override {
        std::cout << "[macOS] Alternando checkbox con estilo macOS.\n";
    }
};
```

### Añadir la nueva fábrica en `Fabricas.hpp`

```cpp

// ----------------------------------------
// Fábrica concreta: FAMILIA macOS
// ----------------------------------------

class MacFactory : public AbstractGUIFactory {
public:
    std::unique_ptr<Button> create_button() const override {
        return std::make_unique<MacButton>();
    }

    std::unique_ptr<Checkbox> create_checkbox() const override {
        return std::make_unique<MacCheckbox>();
    }
};
```

### Usar la nueva familia en `main.cpp`

```cpp
MacFactory macUI;
cliente(macUI);
```

### Qué no hemos modificado

* La interfaz `Button`.
* La interfaz `Checkbox`.
* La interfaz `AbstractGUIFactory`.
* La función `cliente`.

Solo hemos añadido:

* Una **familia completa de productos** (MacButton, MacCheckbox),
* Una **fábrica concreta** (MacFactory),
* Opcionalmente, una línea en `main.cpp` para usarla.

