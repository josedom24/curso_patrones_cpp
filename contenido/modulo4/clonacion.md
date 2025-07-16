# Clonación de objetos: copias superficiales y profundas

En el diseño e implementación de software orientado a objetos, es común la necesidad de **duplicar un objeto** para preservar su estado o generar una variante sin modificar el original. Este proceso se conoce como **clonación**. En C++ moderno, esta tarea se ve reflejada en la implementación de constructores y operadores de copia, así como en la definición explícita de métodos de clonación.

Una clonación puede ser:

* **Superficial (shallow copy):** se copian los valores de los miembros, incluidos los punteros, sin crear copias independientes de los recursos dinámicos.
* **Profunda (deep copy):** se copian recursivamente los datos, creando nuevas instancias de los recursos apuntados, de forma que el objeto clonado sea completamente independiente del original.

Esta distinción es fundamental cuando un objeto gestiona recursos dinámicos (memoria, archivos, sockets, etc.), ya que una copia superficial puede provocar errores como **double delete**, acceso a memoria liberada o comportamiento inesperado.

## Ejemplo de clonación superficial y profunda

Queremos copiar un objeto que contiene un `std::vector<int>`. Vamos a ilustrar:

* Qué ocurre si dos objetos comparten un mismo vector (copia superficial).
* Qué ocurre si cada objeto tiene una copia independiente del vector (copia profunda).

```cpp
#include <iostream>
#include <vector>
#include <memory> // Para std::unique_ptr

// Copia superficial: comparte el mismo vector (mismo puntero)
class ContenedorSuperficial {
public:
    std::vector<int>* datos;  // Apunta a un vector externo (NO es dueño)

    // Constructor que recibe un puntero al vector compartido
    ContenedorSuperficial(std::vector<int>* ptr) : datos(ptr) {}

    // Método de clonación superficial: copia el puntero
    std::unique_ptr<ContenedorSuperficial> clone() const {
        return std::make_unique<ContenedorSuperficial>(datos);
    }

    void mostrar() const {
        for (int i : *datos)
            std::cout << i << " ";
        std::cout << "\n";
    }
};

// Copia profunda: crea su propia copia del vector
class ContenedorProfundo {
public:
    std::vector<int> datos;  // Propiedad interna del objeto

    // Constructor que copia el vector (deep copy)
    ContenedorProfundo(const std::vector<int>& v) : datos(v) {}

    // Método de clonación profunda: copia los datos
    std::unique_ptr<ContenedorProfundo> clone() const {
        return std::make_unique<ContenedorProfundo>(datos);
    }

    void mostrar() const {
        for (int i : datos)
            std::cout << i << " ";
        std::cout << "\n";
    }
};
int main() {
    std::vector<int> base = {1, 2, 3};

    std::cout << "== Copia superficial ==\n";
    ContenedorSuperficial s1(&base);
    auto s2 = s1.clone();  // Ambos apuntan al mismo vector

    base[1] = 99;  // Se modifica desde fuera

    std::cout << "s1: "; s1.mostrar();  // 1 99 3
    std::cout << "s2: "; s2->mostrar(); // 1 99 3

    std::cout << "\n== Copia profunda ==\n";
    ContenedorProfundo p1(base);
    auto p2 = p1.clone();  // Se crea un nuevo vector copiado

    base[1] = 42; // Solo afecta al vector original (no al de p1 ni p2)

    std::cout << "p1: "; p1.mostrar(); // 1 99 3
    std::cout << "p2: "; p2->mostrar(); // 1 99 3
    std::cout << "base: ";
    for (int i : base) std::cout << i << " "; // 1 42 3
    std::cout << "\n";
}
```

* En la **copia superficial**, los objetos apuntan al **mismo recurso** (el vector). Un cambio en uno afecta a todos.
* En la **copia profunda**, cada objeto contiene una **copia independiente** del recurso. Los cambios son locales.
* Se usan **`std::unique_ptr`** para manejar la clonación de forma segura y moderna, sin `new` manual.
* El método `clone()`:

  * En el superficial, **copia el puntero** (comparten datos).
  * En el profundo, **copia los datos** (cada uno tiene su propio vector).
* Este diseño prepara el terreno para jerarquías polimórficas, donde `clone()` se declara como `virtual` y permite duplicar objetos derivados desde punteros a clase base (como en el patrón Prototype).

## Clonación en clases con herencia

En el desarrollo de software orientado a objetos, es común manipular objetos mediante punteros o referencias a clases base, sin conocer su tipo derivado exacto. En estos casos, cuando se desea **duplicar** dichos objetos, no es suficiente con realizar una copia superficial o una llamada directa al constructor de copia, pues:

* El tipo concreto puede no conocerse en tiempo de compilación.
* La lógica de copia puede depender de detalles específicos de la subclase.

Por ello, se necesita un mecanismo que permita **clonar polimórficamente** un objeto desde un puntero o referencia a clase base. Este mecanismo es esencial para implementar el patrón Prototype y se logra mediante un método `clone()` declarado como `virtual`.

Vamos a permitir la duplicación de objetos derivados a través de una interfaz común, sin que el código cliente tenga que conocer la clase concreta del objeto que está clonando.

Veamos un ejemplo:

```cpp
class Clonable {
public:
    virtual std::unique_ptr<Clonable> clone() const = 0;
    virtual ~Clonable() = default;
};
```

* Se declara `clone()` como **función virtual pura**.
* Se devuelve un `std::unique_ptr` para garantizar **gestión segura de memoria**.
* Se define un **destructor virtual** para asegurar destrucción adecuada en jerarquías.


Cada clase derivada implementa su propia lógica de clonación:

```cpp
class DerivadoA : public Clonable {
public:
    int dato;
    DerivadoA(int d) : dato(d) {}

    std::unique_ptr<Clonable> clone() const override {
        return std::make_unique<DerivadoA>(*this); // Copia por valor
    }
};

class DerivadoB : public Clonable {
public:
    std::vector<int> datos;
    DerivadoB(const std::vector<int>& v) : datos(v) {}

    std::unique_ptr<Clonable> clone() const override {
        return std::make_unique<DerivadoB>(*this); // Copia profunda
    }
};
```

Y se usa en el programa principal:

```cpp
#include <iostream>
#include <memory>
#include <vector>

void imprimir(const Clonable& obj) {
    auto copia = obj.clone();  // Clonación polimórfica
    // Se podría hacer algo más útil aquí, según la interfaz
    std::cout << "Objeto clonado con éxito.\n";
}

int main() {
    DerivadoA a(42);
    DerivadoB b({1, 2, 3});

    imprimir(a);
    imprimir(b);
}
```

* El método `clone()` requiere implementar correctamente el constructor de copia o lógica personalizada para cada clase derivada.
* Si la jerarquía es profunda, puede haber sobrecoste en mantenimiento.
