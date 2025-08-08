# Ejemplo de patrón Factory Method con C++

## Cómo implementar el patrón

La implementación del patrón Factory Method en C++ moderno sigue estos pasos:

1. **Definir una interfaz base o clase abstracta** para los productos que se desean crear.
2. Crear **múltiples clases concretas** que implementen esa interfaz.
3. Definir una **clase base (abstracta o no)** que declare un método `crearObjeto()`, cuyo tipo de retorno es un puntero (preferiblemente `std::unique_ptr`) a la interfaz del producto.
4. Implementar **subclases concretas del creador**, que sobrescriban el método `crearObjeto()` y devuelvan instancias concretas del producto.
5. El **código cliente** interactúa con el producto a través de su interfaz y con el creador mediante su clase base, sin necesidad de conocer las clases concretas involucradas.

En C++ moderno se recomienda:

* Usar **punteros inteligentes** (`std::unique_ptr`) para la gestión automática de memoria.
* Aprovechar **`override`** para mayor claridad y seguridad en la herencia.
* Emplear **`std::make_unique`** para instanciar objetos.

## Implementación en C++ moderno

Para ilustrar el patrón, se desarrollará el siguiente mini-proyecto: **Simulador de logística**:

* Interfaz: `Transporte` con un método `entregar()`.
* Clases concretas: `Camion`, `Barco`, `Avion`.
* Clase base `Logistica`, con método virtual `crearTransporte()`.
* Subclases: `LogisticaTerrestre`, `LogisticaMaritima`, `LogisticaAerea`.
* Cliente: función `procesarEntrega()` que utiliza objetos de tipo `Transporte` sin conocer su tipo concreto.

## Código de ejemplo

```cpp
#include <iostream>
#include <memory>
#include <string>

// === Interfaz del producto ===
class Transporte {
public:
    virtual void entregar() const = 0;
    virtual ~Transporte() = default;
};

// === Productos concretos ===
class Camion : public Transporte {
public:
    void entregar() const override {
        std::cout << "Entrega realizada por camión.\n";
    }
};

class Barco : public Transporte {
public:
    void entregar() const override {
        std::cout << "Entrega realizada por barco.\n";
    }
};

class Avion : public Transporte {
public:
    void entregar() const override {
        std::cout << "Entrega realizada por avión.\n";
    }
};

// === Creador abstracto ===
class Logistica {
public:
    virtual std::unique_ptr<Transporte> crearTransporte() const = 0;

    void planificarEntrega() const {
        auto transporte = crearTransporte();
        // Lógica común para todas las logísticas
        std::cout << "Iniciando planificación de entrega...\n";
        transporte->entregar();
    }

    virtual ~Logistica() = default;
};

// === Creadores concretos ===
class LogisticaTerrestre : public Logistica {
public:
    std::unique_ptr<Transporte> crearTransporte() const override {
        return std::make_unique<Camion>();
    }
};

class LogisticaMaritima : public Logistica {
public:
    std::unique_ptr<Transporte> crearTransporte() const override {
        return std::make_unique<Barco>();
    }
};

class LogisticaAerea : public Logistica {
public:
    std::unique_ptr<Transporte> crearTransporte() const override {
        return std::make_unique<Avion>();
    }
};

// === Código cliente ===
void procesarEntrega(const Logistica& logistica) {
    logistica.planificarEntrega();
}

int main() {
    LogisticaTerrestre terrestre;
    LogisticaMaritima maritima;
    LogisticaAerea aerea;

    std::cout << "=== Entrega terrestre ===\n";
    procesarEntrega(terrestre);

    std::cout << "\n=== Entrega marítima ===\n";
    procesarEntrega(maritima);

    std::cout << "\n=== Entrega aérea ===\n";
    procesarEntrega(aerea);

    return 0;
}
```

Explicación del código:

* La clase `Transporte` define la interfaz común para todos los medios de entrega.
* Las clases `Camion`, `Barco` y `Avion` implementan diferentes formas de entrega.
* `Logistica` es el creador base que define el método `crearTransporte()` y encapsula una lógica común de planificación (`planificarEntrega()`).
* Las clases `LogisticaTerrestre`, `LogisticaMaritima` y `LogisticaAerea` sobrescriben el método fábrica y devuelven productos concretos.
* La función `procesarEntrega()` actúa como cliente que opera sobre el creador abstracto sin conocer los detalles internos.

## Observaciones finales

* Esta implementación es fácilmente extensible: agregar un nuevo tipo de transporte solo requiere una nueva clase concreta y una subclase de `Logistica`.
* Gracias al uso de punteros inteligentes, se evita la gestión manual de memoria.
* La separación entre creación de objetos y uso de objetos se mantiene clara y modular.
