# Uso de lambdas para comportamiento flexible

En C++ moderno, las **expresiones lambda** permiten definir funciones **de forma concisa**, **en línea** y **flexible**. Este mecanismo forma parte de un conjunto de herramientas que permiten **abstraer comportamiento**, es decir, **parametrizar el *qué hacer*** sin necesidad de crear nuevas clases o funciones independientes.

## Funciones lambda

Una **expresión lambda** es una forma de definir una función anónima (sin nombre) que puede capturar variables del entorno en el que se define. Su sintaxis general es:

```cpp
[captura](parámetros) -> tipo_retorno {
    cuerpo;
};
```

Donde:

* `captura` indica qué variables externas se usan dentro de la lambda.
* `parámetros` son los argumentos que acepta la lambda.
* `tipo_retorno` es opcional si puede deducirse.
* `cuerpo` es el bloque de código que se ejecuta al invocar la lambda.

Veamos un ejemplo simple:

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> datos = {1, 2, 3, 4, 5};

    std::for_each(datos.begin(), datos.end(), [](int x) {
        std::cout << x * 2 << ' ';
    });
}
```

* Recordamos que `std::for_each` nos permite recorrer  y aplicar una función a cada elemento del iterador.
* La lambda `[](int x) { std::cout << x * 2 << ' '; }` actúa como una función que se aplica a cada elemento del vector. Este enfoque evita declarar una función externa y hace el código más compacto y local.

## Captura de variables

Las lambdas pueden capturar variables del entorno mediante:

* Captura por valor (`[=]`): copia las variables externas utilizadas.
* Captura por referencia (`[&]`): utiliza referencias a las variables externas.
* Captura explícita: se puede especificar individualmente qué capturar y cómo (`[x, &y]`).

Veamos un ejemplo:

```cpp
int a = 10, b = 20;

auto lambda = [a, &b]() {
    std::cout << "a: " << a << ", b: " << b << '\n';
    // a es copia; b es referencia
};

b = 99;
lambda();  // a: 10, b: 99
```

## Uso en funciones y algoritmos

Las lambdas se utilizan ampliamente con algoritmos estándar:

```cpp
#include <algorithm>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> valores = {1, 3, 5, 7, 9};
    
    // Buscar el primer valor mayor que 4
    auto it = std::find_if(valores.begin(), valores.end(), [](int x) {
        return x > 4;
    });

    if (it != valores.end())
        std::cout << "Encontrado: " << *it << '\n';
}
```

* Recuerda que `std::find_if` nos permite buscar un elemento que cumpla una condición.
* La condición se establece por una función lambda.
* El uso de lambdas nos aporta varias ventajas:
    * Eliminan la necesidad de funciones auxiliares triviales.
    * Permiten escribir código más expresivo y localizado.
    * Facilitan la programación funcional y el paso de comportamiento como argumento.
    * Pueden capturar el contexto (estado externo) cuando se necesita.
