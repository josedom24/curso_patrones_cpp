# Ejemplo: Sistema de cálculo flexible

## Introducción

Construimos un pequeño sistema que permite realizar **distintos cálculos** sobre números enteros mediante **comportamientos inyectados dinámicamente**.
El sistema no conoce los algoritmos concretos: cada operación se proporciona como un **comportamiento intercambiable**.

Dependiendo del comportamiento inyectado, el cálculo podrá ser:

* una **suma**,
* un **producto**,
* una **potencia**,
* u otras operaciones añadidas posteriormente.

El sistema utiliza **inyección de comportamiento basada en `std::function` y expresiones lambda**, lo que permite definir, sustituir o ampliar algoritmos **sin jerarquías de clases ni herencia**, y sin modificar el contexto.

El código se organiza en:

* **Estrategias.hpp** – definición de la firma común y fábricas de estrategias
* **Contexto.hpp** – contexto que ejecuta el comportamiento inyectado
* **main.cpp** – código cliente


## Estrategias.hpp

```cpp
#pragma once
#include <functional>

// ----------------------------------------
// Firma común de las estrategias
// ----------------------------------------
using EstrategiaCalculo = std::function<int(int, int)>;

// ----------------------------------------
// Fábricas de estrategias
// ----------------------------------------
EstrategiaCalculo estrategia_suma();
EstrategiaCalculo estrategia_producto();
EstrategiaCalculo estrategia_potencia();
```


## Estrategias.cpp

```cpp
#include "Estrategias.hpp"

// ----------------------------------------
// Implementación de estrategias
// ----------------------------------------
EstrategiaCalculo estrategia_suma() {
    return [](int a, int b) {
        return a + b;
    };
}

EstrategiaCalculo estrategia_producto() {
    return [](int a, int b) {
        return a * b;
    };
}

EstrategiaCalculo estrategia_potencia() {
    return [](int a, int b) {
        int resultado = 1;
        for (int i = 0; i < b; ++i) {
            resultado *= a;
        }
        return resultado;
    };
}
```


## Contexto.hpp

```cpp
#pragma once
#include <utility>
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
    std::cout << "Resultado: "
              << contexto.ejecutar(3, 4)
              << "\n";
}

int main() {
    // Contexto con estrategia de suma
    ContextoCalculo contexto(estrategia_suma());
    cliente(contexto);

    // Cambiar estrategia a producto
    contexto.establecer_estrategia(estrategia_producto());
    cliente(contexto);

    // Cambiar estrategia a potencia
    contexto.establecer_estrategia(estrategia_potencia());
    cliente(contexto);

    return 0;
}
```


## Compilación

```bash
g++ main.cpp Estrategias.cpp -o calculadora
```


## Añadir una nueva estrategia

Para añadir una nueva operación **no es necesario modificar el contexto**.
Basta con definir una nueva estrategia que cumpla la firma esperada y usarla desde el cliente.

### Nueva operación: módulo (`a % b`)

Vamos a considerar que `b != 0`.

#### En `Estrategias.hpp`

```cpp
EstrategiaCalculo estrategia_modulo();
```

#### En `Estrategias.cpp`

```cpp
EstrategiaCalculo estrategia_modulo() {
    return [](int a, int b) {
        // Se asume b != 0
        return a % b;
    };
}
```

#### Uso desde `main.cpp`

```cpp
contexto.establecer_estrategia(estrategia_modulo());
cliente(contexto);
```


## Qué no se ha modificado

* No se ha modificado `ContextoCalculo`.
* No se ha cambiado la forma de ejecutar el cálculo.
* No se han añadido clases ni jerarquías.
* No se ha alterado la lógica existente del contexto.

Solo hemos añadido:

* La definición de una **nueva estrategia de cálculo**.
* La implementación del algoritmo como un comportamiento intercambiable.
* El uso de dicha estrategia desde el código cliente.

