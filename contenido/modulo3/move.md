# Semántica de copia y movimiento

En C++ moderno, la eficiencia en la gestión de recursos es una prioridad. Para lograrlo, el lenguaje introduce mecanismos que permiten **copiar** o **mover** objetos de manera explícita o implícita. Estos mecanismos se conocen como **semántica de copia** y **semántica de movimiento**, respectivamente. Entender estos conceptos es esencial para escribir código eficiente, seguro y conforme a los principios de la **gestión de recursos (RAII)**.

## Valores lvalue y rvalue

Antes de abordar directamente la semántica de copia y movimiento, es necesario comprender dos categorías fundamentales de expresiones en C++:

* **lvalue (left value):** Expresiones que hacen referencia a una ubicación identificable en memoria y que pueden aparecer en el lado izquierdo de una asignación. Pueden ser referenciadas con `&`.

  Ejemplo:

  ```cpp
  int x = 42;    // x es un lvalue
  int* p = &x;   // se puede tomar la dirección de x
  ```

* **rvalue (right value):** Expresiones temporales que no tienen nombre ni dirección permanente. No se les puede tomar la dirección (en general), y se usan típicamente en el lado derecho de una asignación.

  Ejemplo:

  ```cpp
  int y = x + 1; // x + 1 es un rvalue
  ```

Con la llegada de C++11, se introdujo una nueva categoría de referencias, las **referencias a rvalue (`T&&`)**, que permiten capturar estos valores temporales y explotarlos para evitar copias innecesarias.

## Semántica de copia

Cuando se realiza una copia de un objeto, se crea una nueva instancia que contiene el mismo valor (o estado) que el objeto original. Esta operación puede ser costosa si el objeto contiene recursos dinámicos, como memoria, archivos o conexiones.

C++ define dos formas para realizar copias:

* **Constructor de copia:**

  ```cpp
  ClassName(const ClassName& other);
  ```

* **Operador de asignación por copia:**

  ```cpp
  ClassName& operator=(const ClassName& other);
  ```

Ejemplo:

```cpp
#include <iostream>
#include <vector>

class Buffer {
private:
    std::vector<int> data;

public:

    // Constructor de copia
    Buffer(const Buffer& other) : data(other.data) {
        std::cout << "Copia\n";
    }

    // Operador de asignación por copia
    Buffer& operator=(const Buffer& other) {
        data = other.data;
        std::cout << "Asignación por copia\n";
        return *this;
    }
    // Constructor por defecto
    Buffer() = default;

    // Constructor con datos
    Buffer(std::initializer_list<int> list) : data(list) {}
};
int main() {
    Buffer b1{1, 2, 3};
    Buffer b2(b1);  // Copia: llama al constructor de Copia
                    //También se podría inicializar: Buffer b2 = b1;
                    //También se podría inicializar: Buffer b2 {b1};
    Buffer b3{4, 5, 6};
    b3 = b2;  // Copia: llama al operador de asignación por copia

    return 0;
}

```

## Semántica de movimiento

La semántica de movimiento permite **transferir** recursos de un objeto a otro **sin duplicarlos**, lo que puede ser mucho más eficiente que copiar. 

* El concepto de **mover un objeto** se refiere a **transferir la propiedad de sus recursos** (como memoria, punteros, etc.) de un objeto a otro, sin hacer una copia de los mismos. Esto es especialmente útil cuando un objeto tiene recursos costosos, como memoria dinámica (por ejemplo, un `std::vector` o un `std::string`). 
* En vez de copiar todos los datos del objeto, **se transfiere** la "propiedad" de esos recursos a otro objeto. Este proceso es mucho más eficiente que una **copia profunda**.

Este mecanismo se apoya en:

* **Constructor de movimiento:**

  ```cpp
  ClassName(ClassName&& other);
  ```

* **Operador de asignación por movimiento:**

  ```cpp
  ClassName& operator=(ClassName&& other);
  ```

Estos métodos se activan cuando el objeto origen es un rvalue, es decir, un valor temporal que está a punto de destruirse. Para invocar explícitamente la semántica de movimiento, se debe convertir un lvalue en rvalue utilizando el operador de movimiento `std::move`. 

* En C++, el operador de movimiento solo se puede invocar sobre **rvalues**, porque el propósito del movimiento es **transferir los recursos de un objeto que ya no será usado**. 
* Si intentaras mover un **lvalue** (una referencia a un objeto que aún se va a seguir utilizando), podrías terminar con un objeto en un estado indefinido.
* El **truco** es que un lvalue (una referencia a un objeto existente) **no puede ser tratado como un rvalue directamente**. Para poder invocar la semántica de movimiento (es decir, usar el **constructor de movimiento** o el **operador de asignación de movimiento**), tenemos que **convertir explícitamente el lvalue en un rvalue**, lo que se hace utilizando `std::move`.
* `std::move` es simplemente una **función de casting** que convierte un lvalue en un rvalue. En realidad, no realiza ninguna operación de movimiento ni de copia, solo **cambia el tipo** de la expresión a rvalue, permitiendo que el compilador lo maneje como un objeto temporal.
* Cuando usas `std::move`, en realidad **estás diciendo al compilador**: "Este objeto ya no lo necesito, puedes transferir sus recursos". Después de usar `std::move`, el objeto original generalmente queda en un estado válido pero indefinido, por lo que no deberías intentar usarlo.

Ejemplo:

```cpp
#include <iostream>
#include <vector>

struct Buffer {
    std::vector<int> data;

    // Constructor de movimiento
    Buffer(Buffer&& other) noexcept : data(std::move(other.data)) {
        std::cout << "Movimiento\n";
    }

    // Operador de asignación por movimiento
    Buffer& operator=(Buffer&& other) noexcept {
        if (this != &other) {  // Evitar la autoasignación
            data = std::move(other.data);
            std::cout << "Asignación por movimiento\n";
        }
        return *this;
    }

    // Constructor por defecto
    Buffer() = default;

    // Constructor con datos
    Buffer(std::initializer_list<int> list) : data(list) {}
};

int main() {
    Buffer b1{1, 2, 3};
    Buffer b2 (std::move(b1));  // Movimiento: llama al constructor de movimiento
                                //También se podría inicializar: Buffer b2 = std::move(b1);
                                //También se podría inicializar:  Buffer b2 {std::move(b1)}
    Buffer b3{4, 5, 6};
    b3 = std::move(b2);  // Movimiento: llama al operador de asignación por movimiento

    return 0;
}

```

* Hemos marcado los constructor y el los operadores como `noexcept`, que significa que el compilador asume que no lanzará excepciones durante su ejecución. Esto tiene implicaciones importantes para la optimización del código, especialmente en contenedores estándar como `std::vector` o `std::map`, donde las operaciones de mover o copiar pueden ser optimizadas si se garantiza que no se lanzarán excepciones.
* En el código, `std::move(b1)` convierte el **lvalue** `b1` en un **rvalue**, lo que permite que el constructor de movimiento sea invocado en lugar del constructor de copia.
* Después de mover, `b1` puede estar en un **estado indefinido**, pero `b2` ahora tiene los datos de `b1`.
* **`std::move` no realiza el movimiento en sí**, solo lo hace posible al convertir el lvalue en un rvalue.

## Regla de cinco  y de cero


* **Regla de Cinco**: Si quieres gestionar los recursos manualmente (como la memoria de un arreglo dinámico), necesitas implementar las cinco operaciones: constructor de copia, operador de asignación por copia, constructor por movimiento, operador de asignación por movimiento y destructor.
* **Regla de Cero**: Si usas tipos que gestionan automáticamente los recursos, como `std::vector`, `std::unique_ptr` o `std::shared_ptr`, puedes evitar la necesidad de escribir código manual para estas operaciones, porque el propio tipo se encarga de gestionarlas. Esto hace que el código sea más seguro, más limpio y más fácil de mantener.

## Ejemplo comparativo

### Utilizando la regla del cinco 

Supongamos que estamos creando una clase Buffer que gestiona un arreglo dinámico de enteros. Como estamos manejando memoria de forma manual, necesitamos implementar las cinco operaciones: Constructor de copia, operador de asignación por copia, constructor por movimiento, operador de asignación por movimiento y destructor. Aquí te dejo el ejemplo:

```cpp
#include <iostream>
#include <cstring>  // Para la copia de memoria

class Buffer {
private:
    size_t size;
    int* data;

public:
    // Constructor normal
    explicit Buffer(size_t s) : size(s), data(new int[s]) {
        std::cout << "Constructor normal\n";
    }

    // Destructor
    ~Buffer() {
        delete[] data;  // Liberamos la memoria
        std::cout << "Destructor\n";
    }

    // Constructor de copia (Copia profunda)
    Buffer(const Buffer& other) : size(other.size), data(new int[other.size]) {
        std::memcpy(data, other.data, size * sizeof(int));  // Copia profunda
        std::cout << "Constructor de copia\n";
    }

    // Operador de asignación por copia (Copia profunda)
    Buffer& operator=(const Buffer& other) {
        if (this == &other) return *this;  // Verificamos auto-asignación

        // Liberamos el recurso anterior
        delete[] data;

        size = other.size;
        data = new int[other.size];
        std::memcpy(data, other.data, size * sizeof(int));  // Copia profunda
        std::cout << "Operador de asignación por copia\n";

        return *this;
    }

    // Constructor por movimiento
    Buffer(Buffer&& other) noexcept : size(other.size), data(other.data) {
        other.data = nullptr;  // Dejamos el objeto original en un estado válido
        std::cout << "Constructor de movimiento\n";
    }

    // Operador de asignación por movimiento
    Buffer& operator=(Buffer&& other) noexcept {
        if (this == &other) return *this;  // Verificamos auto-asignación

        // Liberamos el recurso anterior
        delete[] data;

        size = other.size;
        data = other.data;
        other.data = nullptr;  // Dejamos el objeto original en un estado válido
        std::cout << "Operador de asignación por movimiento\n";

        return *this;
    }

    // Método para añadir datos (simplemente asignamos un valor)
    void add_data(size_t index, int value) {
        if (index < size) {
            data[index] = value;
        }
    }

    // Método para imprimir los datos
    void print() const {
        for (size_t i = 0; i < size; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << "\n";
    }
};

int main() {
    Buffer b1(5);  // Llamamos al constructor normal
    b1.add_data(0, 10);
    b1.add_data(1, 20);
    b1.print();

    // Usamos el constructor de copia
    Buffer b2 = b1;  // Llama al constructor de copia
    b2.print();

    // Usamos el operador de asignación por copia
    Buffer b3(3);
    b3 = b1;  // Llama al operador de asignación por copia
    b3.print();

    // Usamos el constructor por movimiento
    Buffer b4 = std::move(b1);  // Llama al constructor por movimiento
    b4.print();

    // Usamos el operador de asignación por movimiento
    Buffer b5(2);
    b5 = std::move(b4);  // Llama al operador de asignación por movimiento
    b5.print();

    return 0;
}

```

* **Constructor por copia**: Hace una **copia profunda** de los datos, para que `b2` tenga su propia copia del arreglo de `b1`.
* **Operador de asignación por copia**: Hace lo mismo que el constructor de copia, pero para el caso en que ya existe un objeto `b3` y queremos asignarle los datos de `b1`.
* **Constructor por movimiento**: Toma la propiedad de los datos de `b1`, dejándolo en un estado válido pero vacío. Después de mover los datos, `b1` ya no debe ser utilizado.
* **Operador de asignación por movimiento**: Similar al constructor de movimiento, pero en este caso, se asigna el recurso de `b4` a `b5`.
* **Destructor**: Se asegura de liberar la memoria asignada cuando el objeto es destruido.


### Utilizando la regla del cero con punteros inteligentes

Ahora vamos a simplificar este código usando la **Regla de Cero**. En lugar de gestionar la memoria manualmente, usaremos un **smart pointer** (`std::unique_ptr`), que se encarga automáticamente de la memoria y recursos asociados.

```cpp
#include <iostream>
#include <memory>  // Para std::unique_ptr

class Buffer {
private:
    size_t size;
    std::unique_ptr<int[]> data;  // Usamos un unique_ptr para gestionar el arreglo

public:
    // Constructor normal
    explicit Buffer(size_t s) : size(s), data(std::make_unique<int[]>(s)) {
        std::cout << "Constructor normal\n";
    }

    // Método para añadir datos
    void add_data(size_t index, int value) {
        if (index < size) {
            data[index] = value;
        }
    }

    // Método para imprimir los datos
    void print() const {
        for (size_t i = 0; i < size; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << "\n";
    }
};

int main() {
    Buffer b1(5);  // Llamamos al constructor normal
    b1.add_data(0, 10);
    b1.add_data(1, 20);
    b1.print();

    // Usamos el constructor de copia
    Buffer b2 = b1;  // Llama al constructor de copia (automáticamente usa el constructor por copia de std::unique_ptr)
    b2.print();

    // Usamos el operador de asignación por copia
    Buffer b3(3);
    b3 = b1;  // Llama al operador de asignación por copia (automáticamente usa el operador de asignación por copia de std::unique_ptr)
    b3.print();

    return 0;
}
```
* **`std::make_unique`** es una función que facilita la creación de punteros inteligentes de tipo `std::unique_ptr`. Es una forma más segura y concisa de crear un `unique_ptr` sin tener que usar el operador `new` directamente.
* **`std::unique_ptr`** maneja automáticamente la memoria. Esto significa que no tenemos que preocuparnos por liberar la memoria en el destructor ni gestionar las copias o los movimientos de manera manual.
* Cuando **`Buffer` es copiado o movido**, **`std::unique_ptr` se encarga de copiar o mover el puntero automáticamente**:
    * Si copiamos el objeto, el **`unique_ptr` realiza una copia del recurso** (esto generalmente no es posible con `unique_ptr` sin transferir la propiedad, pero la STL tiene un comportamiento específico para este caso).
    * Si movemos el objeto, **el `unique_ptr` transfiere la propiedad del recurso** de un objeto a otro.


### Utilizando la regla del cero con `std::vector`

En el último ejemplo volvemos a utilizar la **Regla de Cero**, pero en este caso utilizando la clase `std::vector` directamente sin escribir ninguno de los constructores, operadores o destructores manualmente.

**Lo bueno de `std::vector` es que ya gestiona automáticamente los recursos (como la memoria dinámica) sin que tengamos que preocuparnos por nada**. Esto hace que el código sea mucho más limpio y seguro.

```cpp
#include <iostream>
#include <vector>

class Buffer {
private:
    std::vector<int> data;  // Usamos std::vector que gestiona automáticamente la memoria

public:
    // Constructor normal
    explicit Buffer(size_t s) : data(s) {
        std::cout << "Constructor normal\n";
    }

    // Método para añadir datos
    void add_data(size_t index, int value) {
        if (index < data.size()) {
            data[index] = value;
        }
    }

    // Método para imprimir los datos
    void print() const {
        for (auto val : data) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }
};

int main() {
    Buffer b1(5);  // Llamamos al constructor normal
    b1.add_data(0, 10);
    b1.add_data(1, 20);
    b1.print();

    // Usamos el constructor de copia
    Buffer b2 = b1;  // Llama automáticamente al constructor de copia de std::vector
    b2.print();

    // Usamos el operador de asignación por copia
    Buffer b3(3);
    b3 = b1;  // Llama automáticamente al operador de asignación por copia de std::vector
    b3.print();

    // Usamos el constructor por movimiento
    Buffer b4 = std::move(b1);  // Llama automáticamente al constructor por movimiento de std::vector
    b4.print();

    // Usamos el operador de asignación por movimiento
    Buffer b5(2);
    b5 = std::move(b4);  // Llama automáticamente al operador de asignación por movimiento de std::vector
    b5.print();

    return 0;
}
```

* **`std::vector`**: El `std::vector` gestiona automáticamente su memoria (como el arreglo dinámico interno). No necesitamos escribir código para copiar, mover ni liberar los recursos.
* **Copias y movimientos automáticos**: Cuando copiamos o movemos un `Buffer`, el `std::vector` se encarga de realizar una **copia profunda** o **movimiento de recursos** de manera automática.
* **Destructor**: El `std::vector` se encarga de liberar la memoria cuando el objeto se destruye, así que no necesitamos escribir un destructor.

