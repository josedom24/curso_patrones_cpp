# Ejemplo: Sistema de cálculo flexible

## Introducción

Construiremos un pequeño sistema que permite realizar **distintos cálculos** sobre números enteros mediante **comportamientos inyectados dinámicamente**.
El sistema no conoce los algoritmos concretos: cada operación se proporciona como una función intercambiable.

Dependiendo del comportamiento inyectado, el cálculo podrá ser:

* una **suma**,
* un **producto**,
* o un cálculo más complejo, como una **potencia**.

El sistema utiliza **inyección de comportamiento basada en `std::function` y expresiones lambda**, lo que permite que el algoritmo se defina, sustituya o amplíe sin necesidad de jerarquías de clases.

A continuación se muestra el código dividido en:

* **Estrategias.hpp** – conjunto de estrategias implementadas como funciones y lambdas
* **Contexto.hpp** – clase que acepta y ejecuta un comportamiento inyectado
* **main.cpp** – código cliente que selecciona y cambia estrategias

## Estrategias.hpp

```cpp
#pragma once
#include <functional>

// ----------------------------------------
// Definición de la firma común
// ----------------------------------------
using EstrategiaCalculo = std::function<int(int, int)>;

// ----------------------------------------
// Estrategias disponibles
// ----------------------------------------

inline EstrategiaCalculo estrategia_suma = 
    [](int a, int b) { return a + b; };

inline EstrategiaCalculo estrategia_producto = 
    [](int a, int b) { return a * b; };

inline EstrategiaCalculo estrategia_potencia = 
    [](int a, int b) {
        int resultado = 1;
        for (int i = 0; i < b; ++i) {
            resultado *= a;
        }
        return resultado;
    };
```

## Contexto.hpp

```cpp
#pragma once
#include "Estrategias.hpp"

class ContextoCalculo {
private:
    EstrategiaCalculo estrategia_;

public:
    explicit ContextoCalculo(EstrategiaCalculo estrategia)
        : estrategia_(std::move(estrategia)) {}

    void establecer_estrategia(EstrategiaCalculo nueva) {
        estrategia_ = std::move(nueva);
    }

    int ejecutar(int a, int b) const {
        return estrategia_(a, b);
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
    ContextoCalculo contexto(estrategia_suma);
    cliente(contexto);

    // Cambiar estrategia a producto
    contexto.establecer_estrategia(estrategia_producto);
    cliente(contexto);

    // Cambiar estrategia a potencia
    contexto.establecer_estrategia(estrategia_potencia);
    cliente(contexto);

    return 0;
}
```

## Añadir una nueva estrategia

### Nueva operación: módulo (`a % b`)

En `Estrategias.hpp`:

```cpp
inline EstrategiaCalculo estrategia_modulo =
    [](int a, int b) { return a % b; };
```

### Usarla en `main.cpp`

```cpp
contexto.establecer_estrategia(estrategia_modulo);
cliente(contexto);
```

### Qué no se ha modificado

* No se ha modificado `ContextoCalculo`.
* No se ha modificado código existente.
* No se han añadido clases.

Solo:

1. se ha definido una nueva función/lambda,
2. y opcionalmente se usa desde `main.cpp`.

