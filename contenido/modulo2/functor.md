# Clases functoras y lambdas como objetos de primera clase

En C++ moderno, las funciones pueden tratarse como **objetos de primera clase**, es decir, pueden ser **almacenadas, pasadas como argumentos, devueltas desde funciones, y manipuladas** como cualquier otro objeto.

Dos herramientas fundamentales para representar funciones como objetos de primera clase son:

* **Clases functoras (o funtors)**: objetos que sobrecargan el operador de llamada `operator()`.
* **Lambdas**: funciones anónimas, generalmente más concisas, que también se comportan como objetos invocables.


## Clases functoras

Una **functora** es una clase que implementa el operador de llamada `()` como miembro, lo que le permite comportarse como una función.

Veamos un ejemplo:

```cpp
#include <iostream>

class MostrarCuadrado {
public:
    void operator()(int x) const {
        std::cout << "Cuadrado: " << x * x << '\n';
    }
};

int main() {
    MostrarCuadrado f;
    f(5);  // Cuadrado: 25
}
```

`MostrarCuadrado` es una clase que se comporta como una función, gracias al operador `()`. Este patrón se usa para encapsular comportamiento configurable en un objeto.

## Lambdas como objetos de primera clase

Las **expresiones lambda** también son objetos invocables, aunque de tipos anónimos. Se comportan como clases functoras generadas automáticamente por el compilador.

Veamos un ejemplo:

```cpp
auto f = [](int x) {
    std::cout << "Cubo: " << x * x * x << '\n';
};

f(3);  // Cubo: 27
```

Aquí `f` es un objeto que puede invocarse como una función. Esto permite:

* Almacenarlo en variables.
* Pasarlo como parámetro a otras funciones.
* Devolverlo desde funciones.
* Usarlo en contenedores funcionales (`std::function`, etc.).

## Uso de lambdas o clases functoras

Esta lambda:

```cpp
auto f = [](int x) { return x + 1; };
```

Es conceptualmente equivalente a esta clase:

```cpp
class Incrementar {
public:
    int operator()(int x) const {
        return x + 1;
    }
};

Incrementar f;
```

El compilador genera una clase similar automáticamente para cada lambda.


## Ejemplo final

```cpp
#include <iostream>
#include <vector>
#include <functional>

class Multiplicar {
public:
    explicit Multiplicar(int factor) : factor_(factor) {}
    void operator()(int x) const {
        std::cout << x << " * " << factor_ << " = " << x * factor_ << '\n';
    }

private:
    int factor_;
};

void aplicar(std::function<void(int)> f, const std::vector<int>& datos) {
    for (int x : datos)
        f(x);
}

int main() {
    std::vector<int> datos = {1, 2, 3};

    aplicar(Multiplicar(3), datos);  // Usa functor
    aplicar([](int x) { std::cout << "Cuadrado: " << x * x << '\n'; }, datos);  // Usa lambda
}
```

* **Clases functoras** como `Multiplicar` permiten definir objetos que se comportan como funciones (`operator()`).
* **Lambdas** son funciones anónimas y compactas, útiles para definir comportamiento directamente en línea.
* **`std::function`** permite aceptar cualquier tipo de función o callable (functor, lambda, puntero a función) con una firma específica (`void(int)` en este caso).
* La función `aplicar` demuestra cómo abstraer comportamiento y aplicarlo de forma genérica a una colección de datos (`std::vector`).

Para terminar este aprtado tenemos que tener en cuenta:

* Las **functoras** son más adecuadas cuando se necesita mantener **estado complejo**, extender comportamiento mediante **herencia**, o reutilizar el tipo.
* Las **lambdas** son preferibles cuando se necesita una **definición local, breve y sin reutilización**.
* Ambos mecanismos se comportan como **objetos invocables** y pueden utilizarse con `std::function`, algoritmos estándar o funciones personalizadas.


### Ejercicio sugerido

**Enunciado:**
Implemente una clase `FiltroMultiplo` que sea una functora que filtre e imprima solo los valores múltiplos de un número dado. Luego, utilice una lambda equivalente para hacer lo mismo.

**Ejemplo de uso:**

```cpp
FiltroMultiplo filtro(3);
filtro(6);  // Imprime 6
filtro(7);  // No imprime

auto lambda = [](int x) { if (x % 3 == 0) std::cout << x << '\n'; };
lambda(9);  // Imprime 9
```

---

¿Deseas que te proporcione la solución de este ejercicio o seguimos con el último apartado: **Ejercicios simples que simulan estrategias o filtros**?
