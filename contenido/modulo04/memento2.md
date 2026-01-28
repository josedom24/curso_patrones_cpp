# Implementación de Memento con C++

## Estructura general

La implementación del **Memento** se basa en:

* Un **Originador** que contiene el estado y define operaciones para guardar y restaurar dicho estado.
* Un **Memento** que almacena una instantánea del estado del originador.
* Una relación donde el **Originador crea Mementos** y también **restaura su estado** a partir de un memento.
* Un **Cuidador (Caretaker)** que mantiene y gestiona una colección de mementos sin interpretarlos.
* Un **código cliente** que interactúa con originador y cuidador para solicitar guardados y restauraciones.

## Componentes del patrón y responsabilidades

* **Originador:** crea mementos a partir de su estado actual y restaura su estado a partir de un memento.
* **Memento:** almacena el estado capturado del originador para que pueda ser utilizado posteriormente en una restauración.
* **Cuidador (Caretaker):** almacena y recupera mementos, gestionando el historial de estados.
* **Código cliente:** solicita operaciones de guardado y restauración utilizando originador y cuidador.


## Diagrama UML

![uml](uml/memento.png)

## Ejemplo genérico

```cpp
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// ------------------------------------------------------------
// Clase Memento
// ------------------------------------------------------------
class Memento {
private:
    std::string estado_;

    // Solo el Originador puede construir mementos
    friend class Originador;

    explicit Memento(std::string estado)
        : estado_(std::move(estado)) {}

public:
    // No se exponen getters públicos para mantener encapsulación
};

// ------------------------------------------------------------
// Clase Originador (crea y restaura mementos)
// ------------------------------------------------------------
class Originador {
private:
    std::string estado_;

public:
    explicit Originador(std::string estado_inicial)
        : estado_(std::move(estado_inicial)) {}

    void establecer_estado(std::string nuevo_estado) {
        estado_ = std::move(nuevo_estado);
    }

    void mostrar_estado() const {
        std::cout << "Estado actual: " << estado_ << "\n";
    }

    // Crear un memento con el estado actual
    std::unique_ptr<Memento> crear_memento() const {
        return std::unique_ptr<Memento>(new Memento(estado_));
    }

    // Restaurar el estado desde un memento
    void restaurar_desde(const Memento& m) {
        estado_ = m.estado_;
    }
};

// ------------------------------------------------------------
// Clase Cuidador (gestiona los mementos)
// ------------------------------------------------------------
class Cuidador {
private:
    std::vector<std::unique_ptr<Memento>> historial_;

public:
    void guardar(std::unique_ptr<Memento> m) {
        historial_.push_back(std::move(m));
    }

    const Memento* obtener(std::size_t indice) const {
        if (indice < historial_.size())
            return historial_[indice].get();
        return nullptr;
    }
};

// ------------------------------------------------------------
// Código cliente
// ------------------------------------------------------------
int main() {
    Originador originador{"Estado inicial"};
    Cuidador cuidador;

    originador.mostrar_estado();

    // Guardamos un memento
    cuidador.guardar(originador.crear_memento());

    // Cambiamos estado
    originador.establecer_estado("Estado modificado");
    originador.mostrar_estado();

    // Restauramos estado previo
    if (const Memento* m = cuidador.obtener(0)) {
        originador.restaurar_desde(*m);
    }

    originador.mostrar_estado();

    return 0;
}
```


## Puntos clave del ejemplo

* El **Originador** es el único que accede al contenido del memento gracias a `friend`, preservando el encapsulamiento.
* El **Memento** no expone su estado: solo guarda los datos y permite que el originador los restaure.
* El **Cuidador** almacena mementos sin conocer su estructura interna, cumpliendo el principio de responsabilidad única.
* El uso de **`std::unique_ptr`** garantiza que cada memento tenga un propietario claro y evita fugas de memoria.
* La implementación soporta un historial completo de estados con un mecanismo simple y seguro.
* No se utiliza `std::make_unique` en el método `crear_memento()` para crear el memento porque su constructor es no público y solo es accesible desde el originador, reforzando así el control de creación y el encapsulamiento del estado.

