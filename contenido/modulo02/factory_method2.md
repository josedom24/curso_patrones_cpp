# Implementación de Factory Method con C++

## Estructura general 

La implementación del **Factory Method** en C++ moderno se apoya en un conjunto reducido de mecanismos del lenguaje que permiten desacoplar la creación de objetos de su uso, garantizando seguridad, extensibilidad y una gestión correcta de recursos.

## Elementos de C++ moderno utilizados

* **Clases abstractas e interfaces puras** para definir contratos estables.
* **Métodos virtuales y virtuales puros** como puntos de extensión.
* **Herencia** para especializar el proceso de creación.
* **Polimorfismo dinámico** para trabajar con objetos sin conocer su tipo concreto.
* **Destructores virtuales** para destrucción segura a través de punteros base.
* **`std::unique_ptr`** para expresar propiedad exclusiva de los objetos creados.
* **RAII** para garantizar liberación automática de recursos.
* Uso explícito de **`override`** en las redefiniciones.

## Componentes del patrón y responsabilidades

### 1. Interfaz o clase base del **Producto**

* Define el comportamiento común que deben ofrecer todos los productos.
* Establece un contrato estable independiente de las implementaciones concretas.
* Permite que el código cliente trate todos los productos de forma uniforme.
* No conoce ni controla el proceso de creación de las instancias.

### 2. **Productos concretos**

* Implementan el comportamiento definido por la interfaz del producto.
* Representan variantes específicas dentro de la misma familia de productos.
* Encapsulan los detalles de implementación y los recursos internos.
* Cumplen las invariantes definidas por la abstracción base.

### 3. Interfaz o clase base **Creador**

* Declara el método de creación que devuelve un producto abstracto.
* Define el punto de extensión donde se decide el tipo concreto del producto.
* Puede, opcionalmente, definir operaciones que trabajan con el producto sin conocer su implementación concreta.
* Desacopla al cliente de las clases concretas que se instancian.

### 4. **Creadores concretos**

* Especializan el proceso de creación definido por el creador base.
* Deciden qué tipo concreto de producto se instancia.
* Centralizan el conocimiento sobre las clases concretas del producto.
* Aíslan la lógica de creación del resto del sistema.

### 5. **Código cliente**

* Trabaja exclusivamente con las abstracciones del creador y del producto.
* No conoce ni depende de los tipos concretos creados.
* Utiliza los objetos obtenidos sin gestionar manualmente su ciclo de vida.
* Permanece estable frente a la introducción de nuevos productos o creadores.

## Diagrama UML

![uml](uml/factory_method.png)

## Ejemplo genérico


```cpp
#include <iostream>
#include <memory>

// ----------------------------------------
// Interfaz base del producto
// ----------------------------------------
class Producto {
public:
    virtual ~Producto() = default;
    virtual void operar() const = 0;
};

// Producto concreto A
class ProductoConcretoA : public Producto {
public:
    void operar() const override {
        std::cout << "Operación del ProductoConcretoA\n";
    }
};

// Producto concreto B
class ProductoConcretoB : public Producto {
public:
    void operar() const override {
        std::cout << "Operación del ProductoConcretoB\n";
    }
};

// ----------------------------------------
// Interfaz base del creador
// ----------------------------------------
class Creador {
public:
    virtual ~Creador() = default;

    // Factory Method
    virtual std::unique_ptr<Producto> crear_producto() const = 0;
};

// Creador concreto A
class CreadorConcretoA : public Creador {
public:
    std::unique_ptr<Producto> crear_producto() const override {
        return std::make_unique<ProductoConcretoA>();
    }
};

// Creador concreto B
class CreadorConcretoB : public Creador {
public:
    std::unique_ptr<Producto> crear_producto() const override {
        return std::make_unique<ProductoConcretoB>();
    }
};

// ----------------------------------------
// Código cliente
// ----------------------------------------
void cliente(const Creador& creador) {
    auto producto = creador.crear_producto();  // creación delegada
    producto->operar();                        // uso del producto
}

int main() {
    CreadorConcretoA fabricaA;
    CreadorConcretoB fabricaB;

    cliente(fabricaA);
    cliente(fabricaB);

    return 0;
}

```

## Puntos clave del ejemplo

* El cliente **trabaja con la abstracción `Creador`**, permitiendo sustituir distintos creadores concretos sin modificar el código cliente.
* El método fábrica `crear_producto()` **encapsula la decisión de qué producto concreto se instancia dentro del creador concreto**, no en el cliente.
* El cliente **recibe y utiliza un `Producto` a través de su abstracción**, sin conocer su tipo concreto.
* El polimorfismo se manifiesta tanto en el **creador** como en el **producto**, reforzando la separación entre creación y uso.
* El cliente depende únicamente de **abstracciones**, no de implementaciones concretas.

