# Implementación de Adapter con C++ moderno

## Estructura general

La implementación del **patrón Adapter** en C++ moderno permite **compatibilizar interfaces incompatibles** sin modificar el código existente. El patrón introduce una capa intermedia que traduce la interfaz que el cliente espera a la interfaz real de una clase ya existente.

Este enfoque facilita la reutilización de código legado o externo y desacopla al cliente de detalles concretos de implementación, manteniendo estable el diseño del sistema.

## Elementos de C++ moderno utilizados

* **Clases abstractas e interfaces puras** para definir la interfaz objetivo.
* **Métodos virtuales y virtuales puros** como contrato estable para el cliente.
* **Polimorfismo dinámico** para permitir el uso transparente del adaptador.
* **Destructores virtuales** para destrucción segura a través de interfaces.
* **Composición** para encapsular el objeto adaptado.
* **`std::unique_ptr` o referencias** para expresar propiedad o dependencia.
* **Constructores explícitos** para evitar conversiones implícitas no deseadas.
* Uso explícito de **`override`** en los métodos adaptados.
* **RAII** para garantizar una gestión correcta del ciclo de vida.

## Componentes del patrón y responsabilidades

### 1. **Interfaz objetivo (Target)**

* Define la interfaz que el cliente espera utilizar.
* Establece un contrato estable independiente de las implementaciones concretas.
* Permite tratar adaptadores y posibles implementaciones nativas de forma uniforme.
* Se utiliza de forma polimórfica mediante punteros o referencias.

### 2. **Clase adaptada (Adaptee)**

* Representa una clase existente con una interfaz incompatible.
* No se modifica para adaptarse al nuevo sistema.
* Puede ser código legado, externo o ajeno al diseño actual.
* Proporciona la funcionalidad real que se desea reutilizar.

### 3. **Adaptador (Adapter)**

* Implementa la interfaz objetivo esperada por el cliente.
* Contiene internamente una instancia del adaptado, normalmente mediante composición, aunque la forma concreta de propiedad depende del diseño.
* Traduce las llamadas del cliente a operaciones del adaptado.
* Encapsula la lógica de conversión entre interfaces.

### 4. **Código cliente**

* Trabaja exclusivamente con la interfaz objetivo.
* No conoce ni depende de la clase adaptada.
* Utiliza el adaptador de forma transparente.
* Permanece estable ante cambios o sustituciones del adaptado.


## Diagrama UML

![uml](uml/adapter.png)

## Ejemplo genérico

```cpp
#include <iostream>
#include <memory>

// ----------------------------------------
// Interfaz objetivo (Target)
// ----------------------------------------
class InterfazObjetivo {
public:
    virtual ~InterfazObjetivo() = default;
    virtual void operacion() const = 0;
};

// ----------------------------------------
// Clase adaptada (Adaptee) con una interfaz incompatible
// ----------------------------------------
class Adaptado {
public:
    void operacion_especifica() const {
        std::cout << "Ejecutando operacion_especifica del Adaptado.\n";
    }
};

// ----------------------------------------
// Adaptador (Adapter)
// ----------------------------------------
class Adaptador : public InterfazObjetivo {
public:
    explicit Adaptador(std::unique_ptr<Adaptado> adaptado)
        : adaptado_(std::move(adaptado)) {}

    void operacion() const override {
        // Traducción de la llamada
        adaptado_->operacion_especifica();
    }

private:
    // El adaptador posee al objeto adaptado en este ejemplo
    std::unique_ptr<Adaptado> adaptado_;
};

// ----------------------------------------
// Código cliente
// ----------------------------------------
void cliente(const InterfazObjetivo& objetivo) {
    objetivo.operacion();
}

int main() {
    auto adaptado = std::make_unique<Adaptado>();
    auto adaptador = std::make_unique<Adaptador>(std::move(adaptado));

    cliente(*adaptador);

    return 0;
}
```

## Puntos clave del ejemplo

* La interfaz objetivo define lo que el cliente espera sin conocer detalles del adaptado.
* El adaptador implementa la interfaz objetivo y encapsula un objeto adaptado mediante composición.
* La llamada del cliente se traduce directamente en una llamada compatible con el adaptado.
* El cliente permanece completamente desacoplado de la implementación real, reforzando la extensibilidad y el principio *Open/Closed*.
* El uso de `std::unique_ptr` garantiza que la propiedad del objeto adaptado quede claramente definida y se gestione de forma automática mediante RAII.
