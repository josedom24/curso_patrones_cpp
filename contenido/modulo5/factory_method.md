# Factory Method

## Introducción y propósito

El patrón **Factory Method** es un patrón creacional que permite **delegar la creación de objetos a subclases**, en lugar de instanciarlos directamente con `new`. Su propósito es **desacoplar la lógica de creación del uso** del objeto, facilitando así la extensión y reutilización del código.

## Problema que resuelve

* ¿Qué ocurre si el código que usa objetos también debe conocer todos sus constructores y detalles internos? Se produce un fuerte acoplamiento y una menor flexibilidad. Factory Method evita esto.

* Cuando una clase necesita crear objetos, pero **no sabe de antemano qué tipo exacto necesita**.
* Cuando se necesita **una familia de productos relacionados**, pero con la posibilidad de variar el tipo en tiempo de ejecución.

Algunos escenarios donde es útil:

* Interfaces gráficas que deben crear botones o ventanas dependiendo del sistema operativo.
* Motores de juegos que generan enemigos o elementos distintos por nivel.
* Frameworks que permiten a terceros definir sus propias clases derivadas y delegan en ellas la creación de instancias.

## Diagrama UML y estructura

```
        +------------------+
        |  Product         |<---------------------+
        +------------------+                      |
        | +operation()     |                      |
        +------------------+                      |
                 ^                                 |
                 |                                 |
     +---------------------+           +----------------------+
     | ConcreteProductA     |           | ConcreteProductB     |
     +---------------------+           +----------------------+

        +---------------------+
        | Creator             |
        +---------------------+
        | +createProduct()    |<--------------------+
        +---------------------+                     |
                 ^                                   |
                 |                                   |
     +-------------------------+         +---------------------------+
     | ConcreteCreatorA        |         | ConcreteCreatorB          |
     +-------------------------+         +---------------------------+
     | +createProduct()        |         | +createProduct()          |
     +-------------------------+         +---------------------------+
```


* **Product**: Es una clase abstracta, interfaz pura que define la interfaz común para los objetos que serán creados por el método fábrica.
* **ConcreteProductA** y **ConcreteProductB**: Son clases concretas, que implementan la interfaz `Product`. Son las clases reales que se instancian. Sobrescriben `operation()` con lógica específica.
* **Creator**: Es una clase abstracta, interfaz pura (*Interfaz de factoría*) que declara el método fábrica `createProduct()`, que devuelve un `Product`. Usa de **punteros inteligentes** (`std::unique_ptr`) para retorno de objetos polimórficos.
* **ConcreteCreatorA** y **ConcreteCreatorB**: Son clases concretas que implementan el método fábrica `createProduct()` y devuelven instancias concretas (`ConcreteProductA` o `ConcreteProductB`).

Relación entre las clases:

* `ConcreteProductA` y `ConcreteProductB` **heredan** de `Product`.
* `ConcreteCreatorA` y `ConcreteCreatorB` **heredan** de `Creator`.
* `Creator` tiene un método `createProduct()` que será **implementado por sus subclases** para devolver distintos `ConcreteProduct`.


## Implementación en C++ moderno

### Paso 1: Definir la interfaz del producto

```cpp
class Producto {
public:
    virtual void usar() const = 0;
    virtual ~Producto() = default;
};
```

### Paso 2: Implementar productos concretos

```cpp
class ProductoA : public Producto {
public:
    void usar() const override {
        std::cout << "Usando Producto A\n";
    }
};

class ProductoB : public Producto {
public:
    void usar() const override {
        std::cout << "Usando Producto B\n";
    }
};
```

### Paso 3: Definir la interfaz del creador

```cpp
class Creador {
public:
    virtual std::unique_ptr<Producto> crearProducto() const = 0;
    virtual ~Creador() = default;

    void operacion() const {
        auto producto = crearProducto(); // fábrica
        producto->usar();                // uso del producto
    }
};
```

### Paso 4: Crear fábricas concretas

```cpp
class CreadorA : public Creador {
public:
    std::unique_ptr<Producto> crearProducto() const override {
        return std::make_unique<ProductoA>();
    }
};

class CreadorB : public Creador {
public:
    std::unique_ptr<Producto> crearProducto() const override {
        return std::make_unique<ProductoB>();
    }
};
```

### Paso 5: Usar el patrón

```cpp
int main() {
    std::unique_ptr<Creador> creador = std::make_unique<CreadorA>();
    creador->operacion();  // Usando Producto A

    creador = std::make_unique<CreadorB>();
    creador->operacion();  // Usando Producto B
}
```

## Ventajas

* Permite **crear productos sin conocer sus clases concretas**.
* Favorece la extensión mediante nuevas subclases.
* Facilita el testing y el desacoplamiento.

## Desventajas

* Introduce **más clases y abstracciones**, lo que puede dificultar la lectura si el patrón no se justifica.
* Puede ser **innecesario** en casos simples donde basta con `new`.

## Buenas prácticas

* Devuelve objetos mediante `std::unique_ptr` o `std::shared_ptr`.
* Aplica este patrón cuando la creación es variable, no si hay solo un tipo de producto.
* Úsalo junto a otros patrones como Singleton (para la fábrica) o Prototype (para clones).

## Ejercicio propuesto

Crea una clase `Carta` con variantes `CartaAtaque`, `CartaDefensa`, etc. Usa una fábrica `FábricaCartas` que genera cartas distintas en cada nivel.

