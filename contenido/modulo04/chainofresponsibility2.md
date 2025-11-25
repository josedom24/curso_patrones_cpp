# Implementación de Chain of Responsibility con C++

## Estructura y elementos modernos utilizados

La implementación del **Chain of Responsibility** en C++ moderno se organiza alrededor de una jerarquía de manejadores que procesan peticiones de forma encadenada. Cada elemento de la estructura emplea mecanismos de C++ moderno orientados a la seguridad, claridad y extensibilidad.


### 1. Interfaz o clase base del **Manejador**

Define la operación que cada manejador debe ofrecer: procesar una petición o delegarla. Además, permite establecer el siguiente manejador en la cadena.

**Elementos de C++ moderno utilizados:**

* **`std::unique_ptr`** para expresar propiedad exclusiva del siguiente manejador.
* **Destructores virtuales** para garantizar liberación correcta en jerarquías polimórficas.
* **Polimorfismo dinámico** para que cada manejador concreto implemente su propia lógica.
* Método que recibe la petición por referencia constante o mediante tipos *value-like*.


### 2. **Manejadores concretos**

Implementan la lógica particular para determinar si deben procesar la petición o delegarla al siguiente manejador.

**Elementos de C++ moderno utilizados:**

* Construcción segura mediante inicialización moderna.
* Uso de **`override`** para indicar especialización de métodos virtuales.
* Encapsulación de condiciones de manejo sin exponer detalles al cliente.


### 3. **Construcción de la cadena**

El montaje de la cadena determina el flujo de responsabilidad. Cada manejador contiene un puntero al siguiente, permitiendo cadenas configurables dinámicamente.

**Elementos de C++ moderno utilizados:**

* Uso de `std::move` para transferir propiedad.
* Inicialización directa mediante objetos temporales y fábricas.
* Encadenamiento flexible que cumple el principio *Open/Closed*.


### 4. **Código cliente**

Envía peticiones a la cadena sin conocer cuántos manejadores existen ni cuál se hará cargo.

**Elementos de C++ moderno utilizados:**

* Programación a interfaz: solo conoce la clase base del manejador.
* Gestión de recursos automática mediante RAII y punteros inteligentes.


## Diagrama UML (formato yUML)

![uml](uml/chainofresponsibility.png)

## Ejemplo genérico

```cpp
#include <iostream>
#include <memory>
#include <string>

// ----------------------------------------
// Interfaz base del manejador
// ----------------------------------------
class Manejador {
public:
    virtual ~Manejador() = default;

    void establecer_siguiente(std::unique_ptr<Manejador> siguiente) {
        siguiente_ = std::move(siguiente);
    }

    void manejar(const std::string& peticion) const {
        if (!procesar(peticion) && siguiente_) {
            siguiente_->manejar(peticion);
        }
    }

protected:
    virtual bool procesar(const std::string& peticion) const = 0;

private:
    std::unique_ptr<Manejador> siguiente_;
};

// ----------------------------------------
// Manejador concreto A
// ----------------------------------------
class ManejadorConcretoA : public Manejador {
protected:
    bool procesar(const std::string& peticion) const override {
        if (peticion == "A") {
            std::cout << "ManejadorConcretoA procesó la petición.\n";
            return true;
        }
        return false;
    }
};

// Manejador concreto B
class ManejadorConcretoB : public Manejador {
protected:
    bool procesar(const std::string& peticion) const override {
        if (peticion == "B") {
            std::cout << "ManejadorConcretoB procesó la petición.\n";
            return true;
        }
        return false;
    }
};

// ----------------------------------------
// Código cliente
// ----------------------------------------
void cliente(const Manejador& manejador) {
    for (const auto& valor : {"A", "B", "C"}) {
        std::cout << "Enviando petición: " << valor << "\n";
        manejador.manejar(valor);
    }
}

int main() {
    // Construcción de la cadena
    auto manejadorA = std::make_unique<ManejadorConcretoA>();
    auto manejadorB = std::make_unique<ManejadorConcretoB>();

    // Encadenamiento: A -> B
    manejadorA->establecer_siguiente(std::move(manejadorB));

    // Uso del cliente
    cliente(*manejadorA);

    return 0;
}
```
## Puntos clave del ejemplo

* Los manejadores devuelven `bool` en su método `procesar` para indicar si la petición fue atendida.
* El uso de `std::unique_ptr` evita fugas y define claramente la propiedad de cada segmento de la cadena.
* El cliente desconoce cuántos manejadores forman la cadena o cuál procesará cada petición.
* Es sencillo insertar nuevos manejadores sin modificar código existente, cumpliendo *Open/Closed*.
* La separación entre *procesamiento* y *delegación* permite cadenas flexibles y configurables en tiempo de ejecución.

