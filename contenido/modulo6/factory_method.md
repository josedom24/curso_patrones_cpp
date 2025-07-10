Aquí tienes el material didáctico completo sobre el patrón de diseño **Factory Method**, estructurado según tu propuesta:

---

# 🏭 Patrón de Diseño: Factory Method

## 1. Introducción y propósito

El patrón **Factory Method** es un patrón creacional que permite **delegar la creación de objetos a subclases**, en lugar de instanciarlos directamente con `new`. Su propósito es **desacoplar la lógica de creación del uso** del objeto, facilitando así la extensión y reutilización del código.

🔧 **Problema resuelto:** ¿Qué ocurre si el código que usa objetos también debe conocer todos sus constructores y detalles internos? Se produce un fuerte acoplamiento y una menor flexibilidad. Factory Method evita esto.

🎯 **Situaciones típicas de uso:**

* Cuando una clase necesita crear objetos, pero **no sabe de antemano qué tipo exacto necesita**.
* Cuando se necesita **una familia de productos relacionados**, pero con la posibilidad de variar el tipo en tiempo de ejecución.

📦 **Analogía simple:** Pedir una pizza a una cadena de restaurantes. Desde tu punto de vista, haces un pedido (creas un objeto), pero no decides los ingredientes ni la receta interna. Cada sucursal (subclase) prepara la pizza de forma distinta.

---

## 2. Motivación y casos de uso

### 👨‍💻 Escenarios comunes:

* Interfaces gráficas que deben crear botones o ventanas dependiendo del sistema operativo.
* Motores de juegos que generan enemigos o elementos distintos por nivel.
* Frameworks que permiten a terceros definir sus propias clases derivadas y delegan en ellas la creación de instancias.

### 🧩 Problemas resueltos:

* Evita el uso extensivo de `if` o `switch` para determinar qué clase instanciar.
* Reduce el acoplamiento entre la lógica del cliente y las clases concretas.
* Facilita la extensibilidad: nuevas variantes de productos se integran sin modificar el código base.

---

## 3. Relación con principios SOLID y buenas prácticas

✅ **Open/Closed Principle (OCP):** Puedes extender el sistema añadiendo nuevas subclases que implementen el método de creación, **sin modificar** las clases existentes.

✅ **Single Responsibility Principle (SRP):** La clase base define el algoritmo general, mientras que la responsabilidad de instanciar los productos se delega a las subclases.

🔗 **Relación con RAII y smart pointers:** Es común retornar punteros inteligentes (`std::unique_ptr`) en las fábricas para **garantizar la gestión automática del recurso**.

---

## 4. Diagrama y estructura

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
```

---

## 5. Implementación en C++ moderno

### ✅ Paso 1: Definir la interfaz del producto

```cpp
class Producto {
public:
    virtual void usar() const = 0;
    virtual ~Producto() = default;
};
```

### ✅ Paso 2: Implementar productos concretos

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

### ✅ Paso 3: Definir la interfaz del creador

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

### ✅ Paso 4: Crear fábricas concretas

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

### ✅ Paso 5: Usar el patrón

```cpp
int main() {
    std::unique_ptr<Creador> creador = std::make_unique<CreadorA>();
    creador->operacion();  // Usando Producto A

    creador = std::make_unique<CreadorB>();
    creador->operacion();  // Usando Producto B
}
```

---

## 6. Ventajas, desventajas y consideraciones

### ✅ Ventajas

* Permite **crear productos sin conocer sus clases concretas**.
* Favorece la extensión mediante nuevas subclases.
* Facilita el testing y el desacoplamiento.

### ⚠️ Desventajas

* Introduce **más clases y abstracciones**, lo que puede dificultar la lectura si el patrón no se justifica.
* Puede ser **innecesario** en casos simples donde basta con `new`.

### 💡 Buenas prácticas

* Devuelve objetos mediante `std::unique_ptr` o `std::shared_ptr`.
* Aplica este patrón cuando la creación es variable, no si hay solo un tipo de producto.
* Úsalo junto a otros patrones como Singleton (para la fábrica) o Prototype (para clones).

---

## 7. Ejemplos de aplicación real o mini-proyectos

### 💼 Ejercicio 1: Gestor de reportes

Define una clase `Reporte` con variantes `PDFReporte`, `CSVReporte`, etc. Usa `Factory Method` para que una interfaz `ReporteCreador` cree el formato correcto según configuración.

### 🎮 Ejercicio 2: Juego de cartas

Crea una clase `Carta` con variantes `CartaAtaque`, `CartaDefensa`, etc. Usa una fábrica `FábricaCartas` que genera cartas distintas en cada nivel.

---

## 8. Resumen y puntos clave

* El patrón Factory Method **desacopla la creación de objetos de su uso**.
* Se basa en delegar en subclases la decisión de qué clase instanciar.
* Refuerza los principios **OCP** y **SRP**.
* Es ideal para **crear familias de objetos** con estructuras extensibles.
* Debe usarse cuando el tipo de producto puede cambiar o crecer.

📚 **Para profundizar**:

* *Design Patterns* - GoF, capítulo sobre Factory Method.
* cppreference.com sobre [`std::unique_ptr`](https://en.cppreference.com/w/cpp/memory/unique_ptr).

---

¿Quieres que te prepare una versión con ejercicios guiados o autoevaluación tipo test para este patrón?
