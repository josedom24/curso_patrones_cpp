# Devolución de interfaces mediante punteros inteligentes

En la programación orientada a objetos (POO), uno de los principios fundamentales es el uso de **interfaces abstractas** para lograr la **desacoplamiento** entre componentes. Esto permite que los clientes de una clase no dependan de implementaciones concretas, sino de contratos bien definidos. En C++ moderno, una práctica recomendada es devolver estas interfaces a través de **punteros inteligentes**, en lugar de punteros sin gestión (`raw pointers`) o referencias, para asegurar una correcta gestión de recursos y facilitar el uso del polimorfismo.

Cuando una función produce una instancia de un objeto cuya clase concreta está oculta al cliente y solo se expone su interfaz abstracta, es necesario devolver ese objeto de una forma que:

* **Preserve el polimorfismo**.
* **Evite fugas de memoria**.
* Permita **transferir la propiedad** del objeto creado.
* Respete los principios de diseño como *programar contra interfaces* y *responsabilidad única*.

Esto no puede lograrse eficazmente devolviendo objetos por valor ni por referencia. Por ello, se emplean punteros inteligentes como `std::unique_ptr` o `std::shared_ptr`. Ya que'como sabemos, el uso de punteros (`raw pointer`) delega la responsabilidad de liberar memoria al cliente, lo que es propenso a errores.


## Ejemplo de interface

Una interfaz en C++ se implementa como una clase abstracta que contiene al menos un método virtual puro:

```cpp
class Shape {
public:
    virtual void draw() const = 0;
    virtual ~Shape() = default;
};
```

Las clases que implementan esta interfaz deben sobrescribir todos los métodos puros:

```cpp
class Circle : public Shape {
public:
    void draw() const override {
        // Implementación específica
    }
};
```

## Uso de punteros inteligentes para devolver la interface

El uso de `std::unique_ptr` o `std::shared_ptr` resuelve los problemas de delegar al cliente la liberación de memoria.

### `std::unique_ptr<T>`: transferencia de propiedad única

Es la opción preferida cuando el objeto creado no necesita ser compartido:

```cpp
std::unique_ptr<Shape> createShape() {
    return std::make_unique<Circle>();
}
```

Ventajas:

* Garantiza destrucción automática del objeto.
* No se puede copiar, solo mover.
* Reduce ambigüedades de ownership.

### `std::shared_ptr<T>`: propiedad compartida

Se utiliza si múltiples componentes necesitan compartir la propiedad del objeto:

```cpp
std::shared_ptr<Shape> createShape() {
    return std::make_shared<Circle>();
}
```

Ventajas:

* Gestión automática con conteo de referencias.
* Adecuado para estructuras de datos compartidas.

## Ejemplo completo: Devolución de interfaces mediante `std::unique_ptr`

```cpp
#include <iostream>
#include <memory>
#include <string>

// Interfaz abstracta
class Shape {
public:
    virtual void draw() const = 0;
    virtual ~Shape() = default;
};

// Implementación concreta: Circle
class Circle : public Shape {
public:
    void draw() const override {
        std::cout << "Dibujando un círculo.\n";
    }
};

// Implementación concreta: Square
class Square : public Shape {
public:
    void draw() const override {
        std::cout << "Dibujando un cuadrado.\n";
    }
};

// Fábrica abstracta
class ShapeFactory {
public:
    virtual std::unique_ptr<Shape> createShape() const = 0;
    virtual ~ShapeFactory() = default;
};

// Fábrica concreta para Circle
class CircleFactory : public ShapeFactory {
public:
    std::unique_ptr<Shape> createShape() const override {
        return std::make_unique<Circle>();
    }
};

// Fábrica concreta para Square
class SquareFactory : public ShapeFactory {
public:
    std::unique_ptr<Shape> createShape() const override {
        return std::make_unique<Square>();
    }
};

// Cliente
void clientCode(const ShapeFactory& factory) {
    std::unique_ptr<Shape> shape = factory.createShape();
    shape->draw();  // Llama a la implementación concreta a través de la interfaz
}

// Programa principal
int main() {
    CircleFactory circleFactory;
    SquareFactory squareFactory;

    std::cout << "Usando CircleFactory:\n";
    clientCode(circleFactory);

    std::cout << "\nUsando SquareFactory:\n";
    clientCode(squareFactory);

    return 0;
}
```

* **`Shape`** es la interfaz abstracta que define el método `draw()`.
* **`Circle` y `Square`** son implementaciones concretas que derivan de `Shape`.
* **`ShapeFactory`** es la interfaz de fábrica abstracta que expone `createShape()`.
* **`CircleFactory` y `SquareFactory`** implementan la creación concreta de `Circle` y `Square`, respectivamente.
* La función **`clientCode`** recibe una referencia a `ShapeFactory`, solicita un objeto a través de la interfaz, y lo usa sin conocer su tipo concreto.
* Se utiliza **`std::unique_ptr`** para garantizar que el recurso dinámico sea destruido automáticamente sin necesidad de intervención manual del cliente.*

Conseguimos las siguientes ventajas:

* **Encapsulamiento**: el cliente nunca conoce las clases concretas.
* **Polimorfismo seguro**: se trabaja siempre con punteros a la interfaz.
* **RAII**: la gestión de memoria está garantizada sin llamadas a `delete`.
* **Flexibilidad**: se pueden añadir nuevas formas fácilmente creando nuevas fábricas concretas sin cambiar el código del cliente.

## Ejemplo completo: Devolución de interfaces mediante `std::shared_ptr`

```cpp
#include <iostream>
#include <memory>
#include <string>

// Interfaz abstracta
class Shape {
public:
    virtual void draw() const = 0;
    virtual ~Shape() = default;
};

// Implementación concreta: Circle
class Circle : public Shape {
public:
    void draw() const override {
        std::cout << "Dibujando un círculo.\n";
    }
};

// Implementación concreta: Square
class Square : public Shape {
public:
    void draw() const override {
        std::cout << "Dibujando un cuadrado.\n";
    }
};

// Fábrica abstracta
class ShapeFactory {
public:
    virtual std::shared_ptr<Shape> createShape() const = 0;
    virtual ~ShapeFactory() = default;
};

// Fábrica concreta para Circle
class CircleFactory : public ShapeFactory {
public:
    std::shared_ptr<Shape> createShape() const override {
        return std::make_shared<Circle>();
    }
};

// Fábrica concreta para Square
class SquareFactory : public ShapeFactory {
public:
    std::shared_ptr<Shape> createShape() const override {
        return std::make_shared<Square>();
    }
};

// Cliente
void clientCode(const ShapeFactory& factory) {
    std::shared_ptr<Shape> shape = factory.createShape();
    shape->draw();

    // Otra referencia compartida al mismo objeto
    std::shared_ptr<Shape> shapeCopy = shape;
    std::cout << "Referencias compartidas: "
              << shape.use_count() << "\n";

    shapeCopy->draw();
}

// Programa principal
int main() {
    CircleFactory circleFactory;
    SquareFactory squareFactory;

    std::cout << "Usando CircleFactory:\n";
    clientCode(circleFactory);

    std::cout << "\nUsando SquareFactory:\n";
    clientCode(squareFactory);

    return 0;
}
```

* Se reemplaza `std::unique_ptr` por `std::shared_ptr` en toda la jerarquía.
* Los objetos creados pueden tener **múltiples propietarios**, como se observa en `shapeCopy`.
* Se utiliza `use_count()` para mostrar cuántas referencias comparten el objeto.


Usa `std::shared_ptr` cuando:

* El objeto debe **persistir mientras haya referencias vivas**.
* Hay **múltiples componentes** que usan el mismo objeto sin que uno tenga la responsabilidad exclusiva de destruirlo.
* Se almacena en **contenedores compartidos** como `std::vector<std::shared_ptr<Shape>>`.

