# Implementación de Mediator con C++

## Estructura general

La implementación del **Mediator** en C++ moderno permite **centralizar la comunicación entre un conjunto de objetos**, evitando dependencias directas entre ellos. Los objetos participantes, denominados colegas, delegan la coordinación de sus interacciones en un mediador común.

Este enfoque reduce el acoplamiento entre componentes, concentra la lógica de interacción en un único punto y facilita la modificación o extensión de las reglas de comunicación sin alterar a los colegas.

## Elementos de C++ moderno utilizados

* **Clases abstractas e interfaces puras** para definir el contrato del mediador.
* **Métodos virtuales** para permitir mediadores concretos intercambiables.
* **Polimorfismo dinámico** para desacoplar colegas y mediador.
* **`std::shared_ptr`** para gestionar la propiedad compartida de los colegas.
* **`std::weak_ptr`** para evitar ciclos de referencia entre mediador y colegas.
* **RAII** para gestionar automáticamente el ciclo de vida de los objetos.
* **Contenedores estándar** para almacenar y gestionar los colegas registrados.

## Componentes del patrón y responsabilidades

### 1. Interfaz o clase base del **Mediador**

* Define las operaciones que permiten coordinar la comunicación entre colegas.
* Establece un punto central de interacción.
* Conoce a los colegas participantes.
* Se utiliza de forma polimórfica mediante punteros inteligentes.

### 2. Interfaz o clase base de los **Colegiales** (componentes)

* Representa a los objetos que participan en la comunicación.
* Mantiene una referencia al mediador en lugar de a otros colegas.
* Notifica al mediador cuando ocurre un evento relevante.
* Encapsula su comportamiento propio sin conocer la lógica global.

### 3. **Mediador concreto**

* Implementa las reglas de interacción entre los colegas.
* Coordina explícitamente el flujo de comunicación.
* Decide qué acciones deben ejecutarse en respuesta a los eventos.
* Aísla completamente a los colegas entre sí.

### 4. **Colegiales concretos**

* Implementan el comportamiento específico de cada componente.
* Generan eventos o solicitudes hacia el mediador.
* Reaccionan a las instrucciones recibidas desde el mediador.
* No mantienen referencias directas a otros colegas.

### 5. **Código cliente**

* Crea y configura el mediador y los colegas concretos.
* Registra los colegas en el mediador.
* Inicia las operaciones del sistema.
* No implementa ni conoce las reglas de comunicación internas.

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
