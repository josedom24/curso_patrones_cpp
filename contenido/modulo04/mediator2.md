# Implementación de Mediator con C++

## Estructura y elementos modernos utilizados

La implementación del **Mediator** en C++ moderno se organiza en un conjunto de clases que encapsulan y separan claramente responsabilidades. A continuación se describen los elementos esenciales y los mecanismos modernos empleados.

### 1. Interfaz o clase base del **Mediador**

Define el conjunto de operaciones que permiten la comunicación entre los objetos colegas (componentes).
El mediador conoce a los colegas y centraliza la lógica de coordinación.

**Elementos de C++ moderno utilizados:**

* **`std::shared_ptr` y `std::weak_ptr`** para evitar ciclos de referencia entre mediador y colegas.
* **Métodos virtuales** para permitir implementaciones concretas del mediador.
* **Polimorfismo dinámico** para permitir sustituir el mediador por versiones más complejas sin cambiar el cliente.

### 2. Interfaz o clase base de los **Colegiales** (componentes)

Cada colega representa un componente que participa en la comunicación.
En lugar de comunicarse entre sí, notifican al mediador.

**Elementos utilizados:**

* Cada colega mantiene una **referencia débil (`std::weak_ptr`) al mediador**.
* Se definen métodos como `enviar_evento(...)` o `notificar(...)`.
* El comportamiento propio se mantiene encapsulado en el colega.

### 3. Implementación concreta del **Mediador**

Coordina explícitamente la comunicación entre los colegas.
Contiene reglas de interacción y lógica orquestada.

**Elementos utilizados:**

* **Containers de punteros inteligentes** para almacenar colegas.
* **Expresiones modernas** para encapsular flujos de comunicación.
* **Separación completa entre los colegas**, que no tienen referencias directas entre sí.

### 4. **Colegiales concretos**

Implementan el comportamiento propio y comunican eventos al mediador.

**Elementos utilizados:**

* **`std::enable_shared_from_this`** cuando un colega necesita obtener un `shared_ptr` a sí mismo para enviarse como parámetro.
* **Métodos de acción específicos** que desencadenan notificaciones al mediador.

### 5. **Código cliente**

Configura los objetos concretos, vincula el mediador con los colegas y ejecuta las operaciones.
El cliente nunca implementa reglas de comunicación entre colegas.


## Diagrama UML

![uml](uml/mediator.png)

## Ejemplo genérico en C++

```cpp
#include <iostream>
#include <memory>
#include <string>

// ------------------------------------------------------
// Interfaz del Mediador
// ------------------------------------------------------
class InterfazMediador {
public:
    virtual ~InterfazMediador() = default;

    virtual void notificar(const std::string& emisor,
                           const std::string& evento) = 0;
};

// ------------------------------------------------------
// Clase base Colega
// ------------------------------------------------------
class Colega {
public:
    virtual ~Colega() = default;

    void establecer_mediador(std::weak_ptr<InterfazMediador> mediador) {
        mediador_ = mediador;
    }

protected:
    void notificar_mediador(const std::string& evento) {
        if (auto m = mediador_.lock()) {
            m->notificar(nombre(), evento);
        }
    }

    virtual std::string nombre() const = 0;

private:
    std::weak_ptr<InterfazMediador> mediador_;
};

// ------------------------------------------------------
// Colega concreto A
// ------------------------------------------------------
class ColegaConcretoA : public Colega {
public:
    void accionA() {
        std::cout << "A realiza accionA().\n";
        notificar_mediador("accionA");
    }

private:
    std::string nombre() const override {
        return "ColegaA";
    }
};

// ------------------------------------------------------
// Colega concreto B
// ------------------------------------------------------
class ColegaConcretoB : public Colega {
public:
    void accionB() {
        std::cout << "B realiza accionB().\n";
        notificar_mediador("accionB");
    }

private:
    std::string nombre() const override {
        return "ColegaB";
    }
};

// ------------------------------------------------------
// Mediador concreto
// ------------------------------------------------------
class MediadorConcreto : public InterfazMediador {
public:
    void registrar_colegaA(std::shared_ptr<ColegaConcretoA> a) {
        colegaA_ = std::move(a);
    }

    void registrar_colegaB(std::shared_ptr<ColegaConcretoB> b) {
        colegaB_ = std::move(b);
    }

    void notificar(const std::string& emisor,
                   const std::string& evento) override 
    {
        std::cout << "[Mediador] Evento '" << evento
                  << "' recibido de " << emisor << ".\n";

        if (emisor == "ColegaA" && evento == "accionA") {
            if (colegaB_) {
                std::cout << "[Mediador] -> Indicando a B que actúe.\n";
                colegaB_->accionB();
            }
        } 
        else if (emisor == "ColegaB" && evento == "accionB") {
            if (colegaA_) {
                std::cout << "[Mediador] -> Indicando a A que actúe.\n";
                colegaA_->accionA();
            }
        }
    }

private:
    std::shared_ptr<ColegaConcretoA> colegaA_;
    std::shared_ptr<ColegaConcretoB> colegaB_;
};

// ------------------------------------------------------
// Código cliente
// ------------------------------------------------------
int main() {
    auto mediador = std::make_shared<MediadorConcreto>();

    auto colegaA = std::make_shared<ColegaConcretoA>();
    auto colegaB = std::make_shared<ColegaConcretoB>();

    colegaA->establecer_mediador(mediador);
    colegaB->establecer_mediador(mediador);

    mediador->registrar_colegaA(colegaA);
    mediador->registrar_colegaB(colegaB);

    // Interacciones:
    colegaA->accionA();
    std::cout << "\n";
    colegaB->accionB();

    return 0;
}
```
## Puntos clave del ejemplo

* Los colegas **no se comunican directamente** entre ellos, sino a través del mediador.
* Se usan **`std::shared_ptr`** y **`std::weak_ptr`** para evitar ciclos de referencia y gestionar fácilmente el ciclo de vida.
* El mediador contiene **todas las reglas de coordinación**, lo que simplifica mucho el comportamiento de los colegas.
* El cliente solo **registra vínculos** y ejecuta operaciones, sin involucrarse en la lógica de interacción.
* Cambiar las reglas del sistema solo requiere **modificar o sustituir el mediador**, sin tocar los colegas.
