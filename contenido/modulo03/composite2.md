# Implementación de Composite en C++

## Estructura general

La implementación del **Composite** en C++ moderno permite **tratar de forma uniforme objetos simples y objetos compuestos** mediante una interfaz común. El patrón organiza los elementos en una **estructura jerárquica**, normalmente en forma de árbol, donde tanto las hojas como los compuestos se manipulan de la misma manera.

Este enfoque simplifica el código cliente, elimina distinciones artificiales entre tipos de objetos y facilita la construcción de estructuras recursivas complejas.

## Elementos de C++ moderno utilizados

* **Clases abstractas e interfaces puras** para definir el componente común.
* **Métodos virtuales y virtuales puros** para unificar el comportamiento.
* **Polimorfismo dinámico** para tratar hojas y compuestos de forma uniforme.
* **Destructores virtuales** para destrucción segura de jerarquías.
* **Composición** para construir estructuras jerárquicas.
* **`std::unique_ptr`** para expresar propiedad exclusiva de los componentes.
* **Contenedores estándar** como `std::vector` para almacenar hijos.
* **RAII** para garantizar liberación automática de recursos.
* Uso explícito de **`override`** en implementaciones concretas.

## Componentes del patrón y responsabilidades

### 1. **Interfaz base Componente**

* Define las operaciones comunes a todos los elementos de la jerarquía.
* Establece un contrato único para hojas y compuestos.
* Permite al cliente interactuar sin conocer la estructura interna.
* Se utiliza de forma polimórfica mediante punteros o referencias.

### 2. **Componente hoja**

* Representa elementos indivisibles de la estructura.
* Implementa directamente las operaciones del componente base.
* No contiene otros componentes.
* Encapsula comportamiento simple y autónomo.

### 3. **Componente compuesto**

* Representa elementos que contienen otros componentes.
* Mantiene una colección de componentes hijos.
* Implementa las operaciones delegando recursivamente en sus hijos.
* Permite construir estructuras jerárquicas arbitrarias.

### 4. **Código cliente**

* Trabaja exclusivamente con la interfaz del componente.
* No distingue entre hojas y compuestos.
* Manipula estructuras completas de forma uniforme.
* Gestiona la memoria de forma automática mediante RAII.


## Diagrama UML

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

