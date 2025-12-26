# Implementación de Chain of Responsibility con C++

## Estructura general

La implementación del **Chain of Responsibility** en C++ moderno permite **procesar una petición a través de una cadena de objetos**, donde cada elemento decide si la gestiona o la delega al siguiente. El cliente envía la petición a la cadena sin conocer qué manejador concreto será responsable de procesarla.

Este enfoque desacopla el emisor de la petición de sus posibles receptores y permite añadir, eliminar o reordenar manejadores sin modificar el código cliente.

## Elementos de C++ moderno utilizados

* **Clases abstractas e interfaces puras** para definir un contrato común de manejo.
* **Métodos virtuales** para permitir especialización del comportamiento.
* **Polimorfismo dinámico** para tratar todos los manejadores de forma uniforme.
* **Destructores virtuales** para destrucción segura en jerarquías polimórficas.
* **Composición** para enlazar manejadores formando la cadena.
* **`std::unique_ptr`** para expresar propiedad exclusiva del siguiente manejador.
* **RAII** para garantizar gestión automática del ciclo de vida.
* **Movimiento de objetos (`std::move`)** para transferir la propiedad al construir la cadena.
* Uso explícito de **`override`** en manejadores concretos.


## Componentes del patrón y responsabilidades

### 1. Interfaz o clase base del **Manejador**

* Define la operación común para procesar o delegar una petición.
* Establece el punto de entrada de la cadena.
* Permite enlazar dinámicamente el siguiente manejador.
* Se utiliza de forma polimórfica mediante punteros o referencias.

### 2. **Manejadores concretos**

* Implementan la lógica específica para decidir si procesan la petición.
* Delegan la petición al siguiente manejador cuando no pueden gestionarla.
* Encapsulan las condiciones de manejo sin exponerlas al cliente.
* Mantienen el contrato definido por la interfaz base.

### 3. **Construcción de la cadena**

* Define el orden en el que se evaluarán los manejadores.
* Enlaza los manejadores mediante composición.
* Permite configurar la cadena de forma flexible y dinámica.
* Facilita la extensión del sistema sin modificar código existente.

### 4. **Código cliente**

* Envía la petición al primer manejador de la cadena.
* No conoce ni depende del número de manejadores existentes.
* Permanece desacoplado de la lógica de decisión.
* Gestiona los recursos de forma automática mediante RAII.

## Diagrama UML

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

