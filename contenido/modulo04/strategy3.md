# Ejemplo: Sistema de cálculo flexible

## Introducción

Para ilustrar el patrón **Strategy** en un contexto realista, construiremos un pequeño sistema que permite realizar **distintos cálculos** sobre números enteros utilizando algoritmos intercambiables.
El objetivo del sistema es permitir que el código cliente ejecute una operación sin conocer la estrategia concreta utilizada.

Dependiendo de la estrategia seleccionada, el cálculo podrá ser:

* de **suma**,
* de **producto**,
* o un cálculo más complejo, como una **potencia**.

Cada cálculo es una estrategia concreta que implementa una interfaz común (`EstrategiaCalculo`).
El código cliente trabaja exclusivamente con la clase `ContextoCalculo`, que almacena una estrategia y delega el cálculo en ella.
Las estrategias concretas (`EstrategiaSuma`, `EstrategiaProducto`, `EstrategiaPotencia`) son responsables de implementar su propio algoritmo.

A continuación se muestra el código completo dividido en:

* **Estrategias.hpp** – interfaz común y estrategias concretas
* **Contexto.hpp** – clase que usa las estrategias
* **main.cpp** – código cliente


## Estrategias.hpp

```cpp
#pragma once
#include <iostream>
#include <memory>

// ----------------------------------------
// Interfaz base de la estrategia
// ----------------------------------------
class EstrategiaCalculo {
public:
    virtual ~EstrategiaCalculo() = default;
    virtual int calcular(int a, int b) const = 0;
};

// ----------------------------------------
// Estrategias concretas
// ----------------------------------------

// Estrategia: suma
class EstrategiaSuma : public EstrategiaCalculo {
public:
    int calcular(int a, int b) const override {
        return a + b;
    }
};

// Estrategia: producto
class EstrategiaProducto : public EstrategiaCalculo {
public:
    int calcular(int a, int b) const override {
        return a * b;
    }
};

// Estrategia: potencia (a^b)
class EstrategiaPotencia : public EstrategiaCalculo {
public:
    int calcular(int a, int b) const override {
        int resultado = 1;
        for (int i = 0; i < b; ++i) {
            resultado *= a;
        }
        return resultado;
    }
};
```


## Contexto.hpp

```cpp
#pragma once
#include <memory>
#include "Estrategias.hpp"

// ----------------------------------------
// Contexto que utiliza una estrategia de cálculo
// ----------------------------------------
class ContextoCalculo {
private:
    std::unique_ptr<EstrategiaCalculo> estrategia_;

public:
    explicit ContextoCalculo(std::unique_ptr<EstrategiaCalculo> estrategia)
        : estrategia_(std::move(estrategia)) {}

    void establecer_estrategia(std::unique_ptr<EstrategiaCalculo> nueva) {
        estrategia_ = std::move(nueva);
    }

    int ejecutar(int a, int b) const {
        return estrategia_->calcular(a, b);
    }
};
```


## main.cpp

```cpp
#include <iostream>
#include "Contexto.hpp"

void cliente(ContextoCalculo& contexto) {
    std::cout << "Resultado: " << contexto.ejecutar(3, 4) << "\n";
}

int main() {
    // Contexto con estrategia de suma
    ContextoCalculo contexto(std::make_unique<EstrategiaSuma>());
    cliente(contexto);

    // Cambiar estrategia a producto
    contexto.establecer_estrategia(std::make_unique<EstrategiaProducto>());
    cliente(contexto);

    // Cambiar estrategia a potencia
    contexto.establecer_estrategia(std::make_unique<EstrategiaPotencia>());
    cliente(contexto);

    return 0;
}
```


## Añadir una nueva estrategia

**Para añadir una nueva estrategia no tocamos ninguna clase existente**, solo añadimos una clase nueva y, opcionalmente, una línea en `main.cpp`.

### Añadir un nuevo cálculo: módulo (`a % b`)

En `Estrategias.hpp`:

```cpp
class EstrategiaModulo : public EstrategiaCalculo {
public:
    int calcular(int a, int b) const override {
        return a % b;
    }
};
```

### Usar la nueva estrategia en `main.cpp`

```cpp
contexto.establecer_estrategia(std::make_unique<EstrategiaModulo>());
cliente(contexto);
```

### Qué no hemos modificado

* No hemos modificado la interfaz `EstrategiaCalculo`.
* No hemos modificado la clase `ContextoCalculo`.
* No hemos modificado la lógica del cliente.

Solo hemos:

1. añadido una **nueva estrategia concreta** (`EstrategiaModulo`),
2. y opcionalmente una línea en `main.cpp` para usarla.


Si quieres, puedo generar además:

* el **yUML del ejemplo completo**,
* la **versión con carpetas**,
* una **explicación detallada del ciclo de vida**,
* o un **ejercicio guiado** para estudiantes.
