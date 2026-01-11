# Implementación de Bridge con C++

## Estructura general

La implementación del **Bridge** en C++ moderno se basa en **separar una abstracción de su implementación**, permitiendo que ambas evolucionen de forma independiente. El patrón divide el diseño en dos jerarquías desacopladas que se comunican mediante composición.

Este enfoque permite combinar distintas abstracciones con distintas implementaciones sin generar explosión de clases y sin introducir dependencias rígidas entre niveles de diseño.

## Elementos de C++ moderno utilizados

* **Clases abstractas e interfaces puras** para definir contratos claros.
* **Métodos virtuales y virtuales puros** como puntos de extensión.
* **Herencia** para extender abstracciones e implementaciones.
* **Polimorfismo dinámico** para sustituir implementadores en tiempo de ejecución.
* **Destructores virtuales** para destrucción segura en jerarquías polimórficas.
* **`std::unique_ptr`** para expresar propiedad del implementador.
* **Composición** como mecanismo central del patrón.
* Uso explícito de **`override`** en las implementaciones concretas.
* **RAII** para una gestión correcta del ciclo de vida.

## Componentes del patrón y responsabilidades

### 1. Interfaz base del **Implementador**

* Define las operaciones primitivas que utilizará la abstracción.
* Establece un contrato estable para las implementaciones concretas.
* No conoce la abstracción de alto nivel.
* Se utiliza de forma polimórfica mediante punteros.

### 2. **Implementadores concretos**

* Implementan las operaciones primitivas definidas por el implementador base.
* Representan variantes independientes de la implementación técnica.
* Encapsulan detalles de bajo nivel.
* Gestionan correctamente sus propios recursos.

### 3. Interfaz o clase base de la **Abstracción**

* Define el comportamiento de alto nivel expuesto al cliente.
* Mantiene una referencia o puntero al implementador.
* Delega en el implementador las operaciones de bajo nivel.
* Aísla al cliente de los detalles de implementación.

### 4. **Abstracciones refinadas**

* Extienden el comportamiento de alto nivel.
* No modifican ni dependen de implementaciones concretas.
* Añaden funcionalidad sin romper el desacoplamiento.
* Pueden combinarse con cualquier implementador compatible.

### 5. **Código cliente**

* Trabaja exclusivamente con la abstracción.
* No conoce ni el tipo concreto de la abstracción ni del implementador.
* Puede cambiar implementaciones en tiempo de ejecución.
* Permanece estable ante nuevas abstracciones o implementaciones.


## Diagrama UML

![uml](uml/bridge.png)

## Ejemplo genérico

```cpp
#include <iostream>
#include <memory>
#include <string>

// ----------------------------------------
// Interfaz del Implementador
// ----------------------------------------
class Implementador {
public:
    virtual ~Implementador() = default;

    // Operación de bajo nivel que la abstracción utilizará
    virtual void operacion_implementacion(const std::string& contexto) const = 0;
};

// Implementador concreto A
class ImplementadorConcretoA : public Implementador {
public:
    void operacion_implementacion(const std::string& contexto) const override {
        std::cout << "[Implementador A] Procesando contexto: " << contexto << "\n";
    }
};

// Implementador concreto B
class ImplementadorConcretoB : public Implementador {
public:
    void operacion_implementacion(const std::string& contexto) const override {
        std::cout << "[Implementador B] Manejo alternativo de: " << contexto << "\n";
    }
};

// ----------------------------------------
// Abstracción
// ----------------------------------------
class Abstraccion {
protected:
    std::unique_ptr<Implementador> impl_;  // Bridge

public:
    explicit Abstraccion(std::unique_ptr<Implementador> impl)
        : impl_(std::move(impl)) {}

    virtual ~Abstraccion() = default;

    // Permite cambiar la implementación en tiempo de ejecución, si se desea
    void cambiar_implementador(std::unique_ptr<Implementador> nuevo_impl) {
        impl_ = std::move(nuevo_impl);
    }

    // Operación de alto nivel
    virtual void operacion(const std::string& datos) const = 0;
};

// Abstracción refinada A
class AbstraccionRefinadaA : public Abstraccion {
public:
    using Abstraccion::Abstraccion; // hereda el constructor

    void operacion(const std::string& datos) const override {
        std::cout << "[Abstracción A] Preparando datos...\n";
        std::string contexto = "A:" + datos;
        impl_->operacion_implementacion(contexto);
    }
};

// Abstracción refinada B
class AbstraccionRefinadaB : public Abstraccion {
public:
    using Abstraccion::Abstraccion; // hereda el constructor

    void operacion(const std::string& datos) const override {
        std::cout << "[Abstracción B] Validando y transformando datos...\n";
        std::string contexto = "B<" + datos + ">";
        impl_->operacion_implementacion(contexto);
    }
};

// ----------------------------------------
// Código cliente
// ----------------------------------------
int main() {
    // Abstracción A con Implementador A
    AbstraccionRefinadaA objetoA{
        std::make_unique<ImplementadorConcretoA>()
    };
    objetoA.operacion("petición 1");

    // Abstracción B con Implementador B
    AbstraccionRefinadaB objetoB{
        std::make_unique<ImplementadorConcretoB>()
    };
    objetoB.operacion("petición 2");

    // Cambiar implementación en tiempo de ejecución
    objetoB.cambiar_implementador(std::make_unique<ImplementadorConcretoA>());
    objetoB.operacion("petición 3 (reconfigurada)");

    return 0;
}
```

## Puntos claves del ejemplo

* `Implementador` y `Abstraccion` son **jerarquías independientes**.
* Las abstracciones refinadas (`AbstraccionRefinadaA/B`) no necesitan saber qué implementación concreta se usa.
* Los implementadores concretos (`ImplementadorConcretoA/B`) no saben qué tipo de abstracción los utiliza.
* El cliente puede **combinar libremente** cualquier abstracción refinada con cualquier implementador concreto.
* El método `cambiar_implementador` muestra cómo se puede **reconfigurar el puente en tiempo de ejecución**.


