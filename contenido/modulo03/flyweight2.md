# Implementación de Flyweight con C++

## Estructura y elementos modernos utilizados

La implementación del **Flyweight** en C++ moderno se organiza en torno a la distinción entre **estado intrínseco** (compartido) y **estado extrínseco** (externo y variable). Se apoya en el uso de `std::shared_ptr`, contenedores hash modernos y la separación clara entre los objetos ligeros compartidos (*flyweights*) y la fábrica responsable de gestionarlos.

### 1. Interfaz o clase base del **Flyweight**

Define el comportamiento común que los objetos flyweight deben ofrecer. La interfaz recibe el **estado extrínseco** desde el exterior, mientras que el estado intrínseco permanece dentro del objeto compartido.

**Elementos de C++ moderno utilizados:**

* **Destructores virtuales** para garantizar la gestión segura del polimorfismo.
* **Parámetros de entrada inmutables** para proteger el estado intrínseco.
* **Separación estricta entre intrínseco/extrínseco**, facilitando el ahorro de memoria.

### 2. **Flyweights concretos**

Representan objetos compartidos que almacenan únicamente el estado intrínseco.
Todos los datos que varían entre instancias se pasan como argumentos a los métodos.

**Elementos de C++ moderno utilizados:**

* **Inicialización uniforme** y propiedades constantes (`const`) para el estado intrínseco.
* **Uso de referencias constantes** para el estado extrínseco.

### 3. **FlyweightFactory**

Es la responsable de:

* Mantener una tabla de objetos flyweight ya creados.
* Buscar un flyweight existente con el estado intrínseco solicitado.
* Crear uno nuevo solo si es necesario.

**Elementos de C++ moderno utilizados:**

* **`std::unordered_map`** para búsquedas rápidas por clave.
* **`std::shared_ptr`** para compartir objetos sin copiar su estado intrínseco.
* **`std::make_shared<T>()`** para asignación eficiente y agrupada.

### 4. **Código cliente**

Trabaja con flyweights a través de la fábrica y proporciona siempre el estado extrínseco.

**Elementos de C++ moderno utilizados:**

* **Programación a interfaces**, independizando al cliente de cómo se gestionan los objetos.
* **Objetos ligeros efímeros** (estado extrínseco) que no saturan la memoria.

## Diagrama UML (formato yUML)

![uml](uml/flyweight.png)

## Ejemplo genérico

```cpp
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

// ----------------------------------------
// Interfaz base del Flyweight
// ----------------------------------------
class Flyweight {
public:
    virtual ~Flyweight() = default;

    // Recibe el estado extrínseco
    virtual void operar(const std::string& estado_extrinseco) const = 0;
};

// ----------------------------------------
// Flyweight concreto (estado intrínseco compartido)
// ----------------------------------------
class FlyweightConcreto : public Flyweight {
    std::string estado_intrinseco_;

public:
    explicit FlyweightConcreto(std::string estado_intrinseco)
        : estado_intrinseco_(std::move(estado_intrinseco)) {}

    void operar(const std::string& estado_extrinseco) const override {
        std::cout << "Flyweight compartido [" << estado_intrinseco_
                  << "] operando con estado extrínseco [" 
                  << estado_extrinseco << "].\n";
    }
};

// ----------------------------------------
// Fábrica de flyweights (gestiona la compartición)
// ----------------------------------------
class FlyweightFactory {
    std::unordered_map<std::string, std::shared_ptr<Flyweight>> pool_;

public:
    std::shared_ptr<Flyweight> obtener_flyweight(const std::string& clave) {
        if (pool_.find(clave) == pool_.end()) {
            // Crear solo si no existe
            pool_[clave] = std::make_shared<FlyweightConcreto>(clave);
        }
        return pool_[clave];
    }

    std::size_t cantidad_flyweights() const {
        return pool_.size();
    }
};

// ----------------------------------------
// Código cliente
// ----------------------------------------
void cliente(FlyweightFactory& fabrica,
             const std::string& estado_intrinseco,
             const std::string& estado_extrinseco)
{
    auto flyweight = fabrica.obtener_flyweight(estado_intrinseco);
    flyweight->operar(estado_extrinseco);
}

// ----------------------------------------
// Programa principal
// ----------------------------------------
int main() {
    FlyweightFactory fabrica;

    cliente(fabrica, "TipoA", "Posición (10,20)");
    cliente(fabrica, "TipoA", "Posición (30,40)");
    cliente(fabrica, "TipoB", "Posición (50,60)");
    cliente(fabrica, "TipoA", "Posición (15,25)");

    std::cout << "Flyweights creados realmente: "
              << fabrica.cantidad_flyweights() << "\n";

    return 0;
}
```
## Puntos clave del ejemplo

* El estado **intrínseco** se almacena dentro del flyweight concreto y se comparte mediante `std::shared_ptr`.
* El estado **extrínseco** se pasa a cada llamada de `operar()`, evitando duplicarlo en cada instancia.
* La fábrica garantiza que solo se cree **un objeto por clave intrínseca**, reduciendo el consumo de memoria.
* La separación clara entre creación (fábrica), uso (cliente) y almacenamiento del estado intrínseco respeta el patrón y ayuda a mantener un código limpio, eficiente y mantenible.

