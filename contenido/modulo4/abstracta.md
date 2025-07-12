# Clases abstractas y métodos virtuales

Las clases abstractas y los métodos virtuales permiten definir **acciones comunes** que pueden realizar distintos tipos de objetos, aunque cada uno las implemente de forma distinta. Esto hace posible escribir código que trabaje con objetos diferentes de manera uniforme, y al mismo tiempo mantener la flexibilidad para cambiar o extender el comportamiento sin modificar el código original.

## Clase abstracta

Una clase se considera **abstracta** si contiene al menos una función miembro declarada como `virtual` y con el sufijo `= 0`, conocida como **función virtual pura**. No se puede instanciar directamente una clase abstracta.

El `= 0` en la definición de un método virtual indica que esa función **no tiene implementación** en la clase donde se declara, y que **debe ser implementada** por cualquier clase derivada concreta. Ese método se llama **función virtual pura**, y su presencia convierte a la clase en una **clase abstracta**.

* La clase que contiene al menos una función `= 0` **no se puede instanciar** directamente.
* Obliga a las clases derivadas a proporcionar una implementación de ese método.
* Define una **interfaz obligatoria** que deben cumplir todas las subclases concretas.

Eejmplo:

```cpp
class Forma {
public:
    virtual void dibujar() const = 0; // Método virtual puro
};
```

## Método virtual

Un **método virtual** es una función miembro que puede ser redefinida por clases derivadas y cuya invocación se resuelve en **tiempo de ejecución** en función del **tipo dinámico** del objeto. Esta característica habilita el **polimorfismo dinámico**, es decir, la capacidad de utilizar una referencia o puntero a una clase base para invocar métodos que se comportan de forma diferente según la clase derivada concreta a la que pertenece el objeto. Esto permite diseñar sistemas flexibles donde el comportamiento puede variar sin cambiar el código que realiza la llamada.

Ejemplo:

```cpp
class Animal {
public:
    virtual void hablar() const {
        std::cout << "Sonido genérico\n";
    }
};
```

## Ejemplo: clase abstracta y derivación

```cpp
#include <iostream>
#include <memory>
#include <vector>

class Figura {
public:
    virtual void dibujar() const = 0; // Método virtual puro
    virtual ~Figura() = default;      // Destructor virtual
};

class Circulo : public Figura {
public:
    void dibujar() const override {
        std::cout << "Dibujando un círculo\n";
    }
};

class Rectangulo : public Figura {
public:
    void dibujar() const override {
        std::cout << "Dibujando un rectángulo\n";
    }
};

int main() {
    std::vector<std::unique_ptr<Figura>> figuras;

    figuras.push_back(std::make_unique<Circulo>());
    figuras.push_back(std::make_unique<Rectangulo>());

    for (const auto& figura : figuras)
        figura->dibujar();  // Llamada polimórfica
}
```

* **Clase abstracta `Figura`**: Declara un método virtual puro `dibujar() = 0`, lo que la convierte en **clase abstracta**, no se puede instanciar directamente. Solo sirve como **interfaz base**.
* **Uso de métodos virtuales**: La función `dibujar` es `virtual`, lo que permite que las clases derivadas implementen su propia versión. Se declara como `const` y `override` en las subclases para mayor claridad y seguridad.
* **Polimorfismo en tiempo de ejecución**:  En el bucle `for`, se llama a `figura->dibujar()` sin saber si el objeto es un `Circulo` o un `Rectangulo`. C++ resuelve dinámicamente cuál versión del método llamar según el **tipo real del objeto**.
* **Uso de punteros inteligentes (`std::unique_ptr`)**: Se usa `std::unique_ptr<Figura>` para manejar memoria automáticamente (RAII). Evita fugas de memoria y elimina la necesidad de llamar manualmente a `delete`.
* **Vector de punteros a la clase base (`Figura`)**: Permite almacenar distintos tipos derivados (`Circulo`, `Rectangulo`) en una misma colección. Esto es posible gracias al polimorfismo y al uso de punteros (o referencias) a la clase base.
* **Destructor virtual**: `Figura` tiene un destructor `virtual`, lo cual es **obligatorio** si se va a eliminar un objeto derivado a través de un puntero a la clase base. Asegura que se llame al destructor correcto al liberar recursos.

## Uso correcto de `override`

`override` es una **palabra clave** (especificador) introducida en C++11 que se utiliza para **marcar explícitamente que una función miembro está sobrescribiendo una función virtual heredada**.

El uso correcto de `override`:

* **Verifica en tiempo de compilación** que se está sobrescribiendo correctamente una función virtual de la clase base.
* **Previene errores sutiles** debidos a diferencias en la firma del método (por ejemplo, olvidar el `const` o un parámetro por referencia).
* Mejora la **legibilidad** y el **mantenimiento** del código, dejando claro al lector que la función forma parte de una jerarquía polimórfica.

Podemos usar `override` cuando:

* La función debe tener la **misma firma** que la versión virtual en la clase base (mismo nombre, parámetros y calificaciones como `const`).
* La función de la clase base debe ser **virtual**.

Veamos une ejemplo:


```cpp
class Figura {
public:
    virtual void dibujar() const = 0;  // Método virtual puro
    virtual ~Figura() = default;
};

class Circulo : public Figura {
public:
    void dibujar() const override {  // uso correcto de override
        std::cout << "Dibujando un círculo\n";
    }
};
```

Si escribieras mal la firma, como por ejemplo:

```cpp
void dibujar() override { ... }  //  Error: falta `const`
```

El compilador te mostraría un error gracias al uso de `override`.

Si no usamos `override`, ciertos errores pasan desapercibidos, pero en realidad estaríamos ocultando la función de la clase base en lugar de sobrescribirla correctamente, lo que impediría el funcionamiento del polimorfismo.

```cpp
class Circulo : public Figura {
public:
    void dibujar() {  //  No se sobrescribe realmente, solo se oculta
        std::cout << "Error: esto no se llama polimórficamente\n";
    }
};
```