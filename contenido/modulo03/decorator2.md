# Implementación de Decorator con C++

## Estructura y elementos modernos utilizados

La implementación del **Decorator** en C++ moderno se organiza alrededor de una interfaz común y una serie de clases que permiten **envolver** objetos para añadir comportamiento dinámicamente.

### 1. Interfaz o clase base del **Componente**

Define la operación o conjunto de operaciones que pueden ejecutar tanto el componente base como los decoradores.
El cliente interactúa exclusivamente con esta interfaz.

**Elementos de C++ moderno utilizados:**

* **`std::unique_ptr`** para representar propiedad exclusiva del componente envuelto.
* **Destructores virtuales** para permitir una gestión segura mediante punteros polimórficos.
* **Polimorfismo dinámico** para que los decoradores puedan sustituir al componente de forma transparente.

### 2. **Componente concreto**

Implementa la funcionalidad principal. Es la entidad que puede ser decorada.

**Elementos de C++ moderno utilizados:**

* Diseño orientado a **RAII** y uso natural de punteros inteligentes en el cliente.
* Comportamiento simple y aislado, ideal para ser extendido por decoradores.

### 3. Clase base **Decorador**

Implementa la misma interfaz que el componente y contiene un puntero a otro componente.
Todas las llamadas son delegadas al componente envuelto, permitiendo agregar comportamiento antes o después.

**Elementos de C++ moderno utilizados:**

* **Composición mediante `std::unique_ptr<Componente>`**, lo que garantiza propiedad y facilita construcciones anidadas.
* **Delegación explícita** para extender el comportamiento sin modificar el componente original.
* **Uso de `explicit` y `std::move`** para recibir y almacenar el componente envuelto.

### 4. **Decoradores concretos**

Añaden funcionalidades específicas, cada uno representando una responsabilidad adicional que puede combinarse con otras.

**Elementos de C++ moderno utilizados:**

* **`override`** para asegurar una sobreescritura correcta de métodos virtuales.
* **Encapsulación estricta**: cada decorador opera independiente del resto.
* **Construcción mediante `std::make_unique`** para formar cadenas de decoradores de forma segura.

### 5. **Código cliente**

Trabaja únicamente con la interfaz del componente, sin distinguir entre componentes originales o decorados.

**Elementos de C++ moderno utilizados:**

* **Polimorfismo + RAII**: punteros inteligentes que gestionan automáticamente la cadena de decoradores.
* **Flexibilidad para construir combinaciones dinámicas** gracias a `std::move`.

## Diagrama UML (formato yUML)

![uml](uml/decorator.png)

## Ejemplo genérico

```cpp
#include <iostream>
#include <memory>

// ----------------------------------------
// Interfaz base del componente
// ----------------------------------------
class Componente {
public:
    virtual ~Componente() = default;
    virtual void operar() const = 0;
};

// ----------------------------------------
// Componente concreto
// ----------------------------------------
class ComponenteConcreto : public Componente {
public:
    void operar() const override {
        std::cout << "Operación del componente base.\n";
    }
};

// ----------------------------------------
// Clase base del decorador
// ----------------------------------------
class Decorador : public Componente {
protected:
    std::unique_ptr<Componente> componente_;

public:
    explicit Decorador(std::unique_ptr<Componente> componente)
        : componente_(std::move(componente)) {}

    void operar() const override {
        // Delegación al componente envuelto
        componente_->operar();
    }
};

// ----------------------------------------
// Decorador concreto A
// ----------------------------------------
class DecoradorA : public Decorador {
public:
    explicit DecoradorA(std::unique_ptr<Componente> componente)
        : Decorador(std::move(componente)) {}

    void operar() const override {
        std::cout << "[DecoradorA] Antes de operar.\n";
        Decorador::operar();
        std::cout << "[DecoradorA] Después de operar.\n";
    }
};

// ----------------------------------------
// Decorador concreto B
// ----------------------------------------
class DecoradorB : public Decorador {
public:
    explicit DecoradorB(std::unique_ptr<Componente> componente)
        : Decorador(std::move(componente)) {}

    void operar() const override {
        std::cout << "[DecoradorB] <<Extendiendo comportamiento>>\n";
        Decorador::operar();
    }
};

// ----------------------------------------
// Código cliente
// ----------------------------------------
int main() {
    // Componente base
    std::unique_ptr<Componente> componente =
        std::make_unique<ComponenteConcreto>();

    // Decoramos progresivamente
    componente = std::make_unique<DecoradorA>(std::move(componente));
    componente = std::make_unique<DecoradorB>(std::move(componente));

    // Uso final: el cliente no sabe que hay decoradores
    componente->operar();

    return 0;
}
```

## Puntos clave del ejemplo

* El decorador **no altera** el comportamiento del componente base: solo lo **extiende**.
* Las responsabilidades adicionales pueden **encadenarse** dinámicamente.
* `std::unique_ptr` garantiza una **gestión segura y automática del ciclo de vida** de toda la cadena.
* No se requiere modificar ninguna clase existente para añadir un nuevo comportamiento: basta con crear un nuevo decorador.
* El cliente siempre trabaja con la **interfaz común**, cumpliendo el principio *Programar a una interfaz, no a una implementación*.

