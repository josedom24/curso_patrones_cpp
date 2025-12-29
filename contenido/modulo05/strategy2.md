# Ejemplo: Sistema de cálculo flexible

## Introducción

Construiremos un pequeño sistema que permite realizar **distintos cálculos** sobre números enteros mediante **comportamientos inyectados dinámicamente**.
El sistema no conoce los algoritmos concretos: cada operación se proporciona como un **comportamiento intercambiable**.

Dependiendo del comportamiento inyectado, el cálculo podrá ser:

* una **suma**,
* un **producto**,
* o un cálculo más complejo, como una **potencia**.

El sistema utiliza **inyección de comportamiento basada en `std::function` y expresiones lambda**, lo que permite definir, sustituir o ampliar algoritmos **sin jerarquías de clases ni herencia**.

El código se organiza en:

* **Estrategias.hpp / Estrategias.cpp** – definición de las estrategias de cálculo
* **Contexto.hpp** – contexto que ejecuta el comportamiento inyectado
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
// Declaración de estrategias disponibles
// ----------------------------------------
extern EstrategiaCalculo estrategia_suma;
extern EstrategiaCalculo estrategia_producto;
extern EstrategiaCalculo estrategia_potencia;
```


## Estrategias.cpp

```cpp
#include "Estrategias.hpp"

// ----------------------------------------
// Definición de estrategias
// ----------------------------------------
EstrategiaCalculo estrategia_suma =
    [](int a, int b) {
        return a + b;
    };

EstrategiaCalculo estrategia_producto =
    [](int a, int b) {
        return a * b;
    };

EstrategiaCalculo estrategia_potencia =
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
    std::cout << "Resultado: "
              << contexto.ejecutar(3, 4)
              << "\n";
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


Recuerda que debemos realizar la compilación de la siguiente manera:

```bash
g++ main.cpp Estrategias.cpp -o calculadora
```


## Añadir una nueva estrategia

Para añadir una nueva operación **no es necesario modificar el contexto ni el código existente**.
Basta con definir una nueva estrategia que cumpla la firma esperada.

### Nueva operación: módulo (`a % b`)

#### En `Estrategias.hpp`

```cpp
extern EstrategiaCalculo estrategia_modulo;
```

#### En `Estrategias.cpp`

```cpp
EstrategiaCalculo estrategia_modulo =
    [](int a, int b) {
        return a % b;
    };
```


### Usarla desde `main.cpp`

```cpp
contexto.establecer_estrategia(estrategia_modulo);
cliente(contexto);
```


## Qué no se ha modificado

* No se ha modificado `ContextoCalculo`.
* No se ha cambiado la forma de ejecutar el cálculo.
* No se han añadido clases ni jerarquías.
* No se ha alterado el código cliente existente.

Solo hemos:

1. definido una **nueva estrategia de cálculo**,
2. implementado el comportamiento como una función intercambiable,
3. utilizado dicha estrategia desde el contexto.

