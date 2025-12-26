# Implementación de Memento con C++

## Estructura general

La implementación del **Memento** en C++ moderno permite **capturar y restaurar el estado interno de un objeto** sin violar su encapsulamiento. El patrón separa claramente la responsabilidad de guardar el estado, restaurarlo y gestionarlo externamente.

Este enfoque es habitual en funcionalidades como deshacer/rehacer, históricos de estado o recuperación ante errores, manteniendo ocultos los detalles internos del objeto original.

## Elementos de C++ moderno utilizados

* **Encapsulación estricta** mediante atributos privados.
* **Constructores privados** para restringir la creación de mementos.
* Uso controlado de **`friend`** para permitir acceso exclusivo al originador.
* **`std::unique_ptr`** para expresar propiedad exclusiva del estado guardado.
* **RAII** para garantizar la gestión automática del ciclo de vida.
* **Contenedores de la STL** como `std::vector` para almacenar historiales de estado.
* **Tipos estándar** como `std::string` y tipos integrales para representar el estado.

## Componentes del patrón y responsabilidades

### 1. **Originador**

* Representa el objeto cuyo estado debe guardarse y restaurarse.
* Define el estado interno que se desea preservar.
* Crea mementos que capturan su estado actual.
* Restaura su estado a partir de un memento válido.

### 2. **Memento**

* Almacena una instantánea del estado del originador.
* Tiene **constructores privados** para impedir su creación desde el exterior.
* No expone información interna ni operaciones de modificación.
* Solo es accesible por el originador mediante `friend`.

### 3. **Cuidador (Caretaker)**

* Gestiona los mementos creados por el originador.
* Almacena historiales de estado usando **contenedores de la STL**.
* No accede ni modifica el contenido interno de los mementos.
* Proporciona mementos cuando se solicita una restauración.

### 4. **Código cliente**

* Interactúa con el originador y el cuidador.
* No conoce ni manipula el estado interno almacenado.
* Dispara operaciones de guardado y restauración.
* Permanece desacoplado de la representación del estado.

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
        return std::make_unique<Memento>(estado_);
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

