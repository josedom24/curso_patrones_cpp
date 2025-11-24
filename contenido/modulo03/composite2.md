# Implementación de Composite en C++

## Estructura y elementos modernos utilizados

La implementación del **Composite** en C++ moderno se organiza en torno a una jerarquía que representa elementos simples y elementos compuestos mediante una interfaz común. A continuación se describen los elementos principales y los mecanismos relevantes de C++ moderno.

### 1. **Interfaz base Componente**

Define las operaciones comunes que todos los elementos de la jerarquía deben ofrecer, tanto simples como compuestos. El cliente interactúa exclusivamente con esta interfaz.

**Elementos de C++ moderno utilizados:**

* **Destructor virtual** para gestionar objetos polimórficos con seguridad.
* **Métodos virtuales puros** que unifican el comportamiento.
* **Programación a interfaces**, ocultando si un objeto es hoja o compuesto.

### 2. **Componente hoja**

Representa los elementos indivisibles de la estructura. Implementa las operaciones definidas en la interfaz base.

**Elementos de C++ moderno utilizados:**

* Implementación directa y simple orientada a RAII.
* No almacena otros componentes.

### 3. **Componente compuesto**

Representa objetos que contienen otros componentes, permitiendo formar estructuras jerárquicas recursivas.

**Elementos de C++ moderno utilizados:**

* **`std::vector<std::unique_ptr<Componente>>`** como contenedor de hijos.
* **`std::unique_ptr`** para propiedad exclusiva de los componentes agregados.
* **Métodos `agregar`, `eliminar` y recorridos recursivos**.
* Delegación recursiva en las operaciones comunes.

### 4. **Código cliente**

Interactúa únicamente con la interfaz `Componente`, ignorando si se trata de una hoja o un compuesto.

**Elementos de C++ moderno utilizados:**

* Gestión de memoria completamente automática mediante punteros inteligentes.
* Manipulación uniforme de la jerarquía gracias al polimorfismo.

## Diagrama UML (yUML)

![uml](uml/composite.png)


## Ejemplo genérico

```cpp
#include <iostream>
#include <memory>
#include <vector>

// ----------------------------------------
// Interfaz base del componente
// ----------------------------------------
class Componente {
public:
    virtual ~Componente() = default;
    virtual void operar() const = 0;
};

// ----------------------------------------
// Componente hoja
// ----------------------------------------
class Hoja : public Componente {
private:
    std::string nombre_;

public:
    explicit Hoja(std::string nombre)
        : nombre_(std::move(nombre)) {}

    void operar() const override {
        std::cout << "Hoja: " << nombre_ << "\n";
    }
};

// ----------------------------------------
// Componente compuesto
// ----------------------------------------
class Compuesto : public Componente {
private:
    std::string nombre_;
    std::vector<std::unique_ptr<Componente>> hijos_;

public:
    explicit Compuesto(std::string nombre)
        : nombre_(std::move(nombre)) {}

    void agregar(std::unique_ptr<Componente> componente) {
        hijos_.push_back(std::move(componente));
    }

    void operar() const override {
        std::cout << "Compuesto: " << nombre_ << "\n";
        for (const auto& hijo : hijos_) {
            hijo->operar();  // llamada recursiva
        }
    }
};

// ----------------------------------------
// Función cliente
// ----------------------------------------
void cliente(const Componente& componente) {
    componente.operar();
}

// ----------------------------------------
// Ejecución demostrativa
// ----------------------------------------
int main() {
    auto raiz = std::make_unique<Compuesto>("Raíz");

    raiz->agregar(std::make_unique<Hoja>("Hoja A"));
    raiz->agregar(std::make_unique<Hoja>("Hoja B"));

    auto subarbol = std::make_unique<Compuesto>("Subárbol 1");
    subarbol->agregar(std::make_unique<Hoja>("Hoja 1.1"));
    subarbol->agregar(std::make_unique<Hoja>("Hoja 1.2"));

    raiz->agregar(std::move(subarbol));

    cliente(*raiz);

    return 0;
}
```

## Puntos clave del ejemplo

* **Uniformidad:** El cliente desconoce qué elementos son hojas o compuestos, gracias a la interfaz común.
* **Recursividad natural:** Los compuestos delegan operaciones a sus hijos sin lógica adicional.
* **Seguridad en la gestión de memoria:** El uso de `std::unique_ptr` garantiza propiedad y destrucción automática de toda la jerarquía.
* **Extensibilidad:** Se pueden añadir nuevos tipos de componentes sin modificar el código cliente ni la estructura general.
* **Estructura clara:** La distinción entre hojas y compuestos permite modelar estructuras de tipo árbol de forma directa.

