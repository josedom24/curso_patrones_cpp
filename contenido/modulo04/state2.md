# Implementación de State con C++

## Estructura y elementos modernos utilizados

La implementación del **State** en C++ moderno se organiza en torno a un conjunto de clases que encapsulan estados y comportamientos. Cada estado se modela como un objeto distinto, y el *contexto* delega en ellos la lógica según corresponda.

### 1. Interfaz o clase base del **Estado**

Define todas las operaciones que pueden variar según el estado. El *contexto* delega su comportamiento en esta interfaz sin conocer la clase concreta del estado activo.

**Elementos de C++ moderno utilizados:**

* **Destructores virtuales** para permitir manipular estados mediante punteros inteligentes.
* **Polimorfismo dinámico** para delegar la operación al estado activo.
* **`std::unique_ptr`** para modelar el estado como propiedad exclusiva del contexto.

### 2. **Estados concretos**

Representan los diferentes estados posibles del sistema. Cada estado implementa la interfaz base y decide qué hacer en cada operación, incluyendo transiciones a otros estados.

**Elementos de C++ moderno utilizados:**

* **`std::make_unique`** para crear estados de manera segura.
* **Transiciones explícitas** mediante reemplazo del `std::unique_ptr` almacenado en el contexto.
* **Responsabilidad clara**: cada clase gestiona únicamente su propio comportamiento.

### 3. **Contexto**

Es el objeto que utiliza el patrón. Mantiene un puntero al estado actual y delega en él todas las operaciones dependientes del estado.

**Elementos de C++ moderno utilizados:**

* **`std::unique_ptr<Estado>`** para almacenar el estado actual.
* **Métodos públicos que delegan** internamente en el estado.
* **Setters internos del estado** llamados desde los propios estados concretos.

### 4. **Código cliente**

El cliente interactúa con el contexto y no conoce nada acerca de los estados concretos o las transiciones internas.

**Elementos de C++ moderno utilizados:**

* Programación a interfaz a través del contexto.
* Delegación completa del comportamiento relacionada con el estado.

## Diagrama UML

![uml](uml/state.png)

## Ejemplo genérico

```cpp
#include <iostream>
#include <memory>

// ----------------------------------------
// Declaración anticipada
// ----------------------------------------
class Estado;

// ----------------------------------------
// Contexto
// ----------------------------------------
class Contexto {
public:
    explicit Contexto(std::unique_ptr<Estado> estado_inicial)
        : estado(std::move(estado_inicial)) {}

    void cambiar_estado(std::unique_ptr<Estado> nuevo_estado) {
        estado = std::move(nuevo_estado);
    }

    void accion() {
        estado->accion(*this);
    }

private:
    std::unique_ptr<Estado> estado;
};

// ----------------------------------------
// Interfaz base del estado
// ----------------------------------------
class Estado {
public:
    virtual ~Estado() = default;
    virtual void accion(Contexto& contexto) = 0;
};

// ----------------------------------------
// Estado concreto A
// ----------------------------------------
class EstadoConcretoA : public Estado {
public:
    void accion(Contexto& contexto) override {
        std::cout << "Estado A: ejecutando acción...\n";
        std::cout << "Transición de A → B.\n";
        contexto.cambiar_estado(std::make_unique<EstadoConcretoB>());
    }
};

// ----------------------------------------
// Estado concreto B
// ----------------------------------------
class EstadoConcretoB : public Estado {
public:
    void accion(Contexto& contexto) override {
        std::cout << "Estado B: ejecutando acción...\n";
        std::cout << "Transición de B → A.\n";
        contexto.cambiar_estado(std::make_unique<EstadoConcretoA>());
    }
};

// ----------------------------------------
// Función cliente
// ----------------------------------------
int main() {
    Contexto contexto(std::make_unique<EstadoConcretoA>());

    contexto.accion(); // A → B
    contexto.accion(); // B → A
    contexto.accion(); // A → B

    return 0;
}
```

## Puntos clave del ejemplo

* Se utiliza una declaración anticipada de `Estado` porque `Contexto` necesita almacenar un `std::unique_ptr<Estado>` antes de que la clase `Estado` esté completamente definida, evitando así una dependencia circular entre ambas clases.
* El estado actual se almacena como `std::unique_ptr<Estado>`, lo que encapsula completamente su ciclo de vida.
* Cada estado define su comportamiento particular y las posibles transiciones.
* El contexto desconoce los detalles internos de cada estado y solo delega operaciones.
* Las clases de estado manejan explícitamente las transiciones, eliminando condicionales externos.
* El diseño es totalmente extensible: basta con añadir nuevas clases de estado sin modificar el código existente, cumpliendo el principio *Open/Closed*.


