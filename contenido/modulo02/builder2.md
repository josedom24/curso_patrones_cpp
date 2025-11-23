# Implementación del patrón Builder con C++ moderno

## Estructura y elementos modernos utilizados

La implementación del **Builder** en C++ moderno se centra en separar el **proceso de construcción** de la **representación final** del objeto.
El patrón encapsula todos los pasos necesarios para configurar un objeto complejo, permitiendo múltiples configuraciones sin sobrecargar la clase del producto.

A continuación se describen las clases principales y los elementos de C++ moderno asociados.

### 1. Producto: el objeto complejo a construir

El producto define la estructura final del objeto generado mediante el builder.
Suele poseer varios parámetros opcionales o configuraciones que se establecen paso a paso.

**Elementos de C++ moderno utilizados:**

* **Constructores privados** o protegidos para forzar el uso del builder.
* **Inicialización mediante listas de inicialización**.
* Uso natural de **RAII** sin gestión manual de memoria.

### 2. Interfaz base del Builder

Declara los métodos necesarios para configurar el producto paso a paso.
Cada método representa un aspecto o parte del producto que puede configurarse.

**Elementos de C++ moderno utilizados:**

* Uso de **fluidez de métodos** para permitir **interfaces fluidas** (`return *this;`).
* Métodos puros virtuales que definen los pasos de construcción.
* Separación del **qué construir** de **cómo se construye**.

### 3. Builders concretos

Implementan los pasos declarados por el builder abstracto.
Cada builder concreto puede crear una versión distinta del producto o una variante del mismo.

**Elementos de C++ moderno utilizados:**

* Implementaciones específicas sin exponer detalles al cliente.
* Uso de `std::unique_ptr` para devolver el producto construido.
* Posibilidad de validación interna antes de crear el producto final.

### 4. Director (opcional)

El *Director* define el **orden de los pasos**, especialmente cuando la construcción requiere una secuencia fija.
Suele utilizarse para productos complejos o para asegurar que el proceso siga un flujo apropiado.

**Elementos de C++ moderno utilizados:**

* Acoplamiento débil: el director solo conoce la interfaz del builder.
* Reutilización de la misma secuencia de pasos con distintos builders.

### 5. Código cliente

El cliente puede trabajar:

* directamente con el builder (en la versión sin Director), o
* delegando la secuencia en un Director (versión clásica del patrón).

**Elementos de C++ moderno utilizados:**

* **Fluidez de métodos** al construir objetos sin Director.
* **Polimorfismo** cuando se usan builders intercambiables.
* Gestión segura de memoria mediante `std::unique_ptr`.

## Diagrama UML (con Director)

```
                      Producto
               ------------------------
               + mostrar() : void

                      ▲
                      │
                 (creado por)
                      │

                <<abstract>>
                 Constructor
      -----------------------------------
      + reiniciar() : void
      + establecer_parteA() : void
      + establecer_parteB() : void
      + obtener_producto() : unique_ptr<Producto>
      + ~Constructor()

                      ▲
                      │
        --------------------------------------
        │                                    │
 ConstructorConcretoA               ConstructorConcretoB
 -----------------------            ----------------------
 + establecer_parteA()              + establecer_parteA()
 + establecer_parteB()              + establecer_parteB()
 + obtener_producto()               + obtener_producto()


                     Director
          ------------------------------
          + construir_minimo() : void
          + construir_completo() : void
          + ~Director()
```

## Ejemplo genérico en C++ moderno

### Variante 1 — Builder **con Director** (versión clásica)

```cpp
#include <iostream>
#include <memory>

// =====================================================
//                 Producto
// =====================================================

class Producto {
public:
    void establecer_parteA(const std::string& valor) { parteA_ = valor; }
    void establecer_parteB(const std::string& valor) { parteB_ = valor; }

    void mostrar() const {
        std::cout << "Producto: A=" << parteA_
                  << ", B=" << parteB_ << "\n";
    }

private:
    std::string parteA_;
    std::string parteB_;
};

// =====================================================
//                 Builder abstracto
// =====================================================

class Constructor {
public:
    virtual ~Constructor() = default;

    virtual void reiniciar() = 0;
    virtual void establecer_parteA() = 0;
    virtual void establecer_parteB() = 0;
    virtual std::unique_ptr<Producto> obtener_producto() = 0;
};

// =====================================================
//                 Builder concreto
// =====================================================

class ConstructorConcreto : public Constructor {
public:
    ConstructorConcreto() { reiniciar(); }

    void reiniciar() override {
        producto_ = std::make_unique<Producto>();
    }

    void establecer_parteA() override {
        producto_->establecer_parteA("Valor A estándar");
    }

    void establecer_parteB() override {
        producto_->establecer_parteB("Valor B estándar");
    }

    std::unique_ptr<Producto> obtener_producto() override {
        return std::move(producto_);
    }

private:
    std::unique_ptr<Producto> producto_;
};

// =====================================================
//                     Director
// =====================================================

class Director {
public:
    explicit Director(Constructor& ctor) : ctor_(ctor) {}

    std::unique_ptr<Producto> construir_minimo() {
        ctor_.reiniciar();
        ctor_.establecer_parteA();
        return ctor_.obtener_producto();
    }

    std::unique_ptr<Producto> construir_completo() {
        ctor_.reiniciar();
        ctor_.establecer_parteA();
        ctor_.establecer_parteB();
        return ctor_.obtener_producto();
    }

private:
    Constructor& ctor_;
};

// =====================================================
//                     Cliente
// =====================================================

int main() {
    ConstructorConcreto ctor;
    Director director(ctor);

    auto p1 = director.construir_minimo();
    p1->mostrar();

    auto p2 = director.construir_completo();
    p2->mostrar();
}
```

### Variante 2 — Builder **sin Director** (builder fluido moderno)

Esta variante es más idiomática en C++ actual:

* El builder y el cliente trabajan directamente.
* Los métodos devuelven `*this` para permitir **encadenamiento fluido**.
* El cliente decide libremente el orden de construcción.


```cpp
#include <iostream>
#include <memory>

class Producto {
public:
    Producto(const std::string& a, const std::string& b)
        : parteA_(a), parteB_(b) {}

    void mostrar() const {
        std::cout << "Producto: A=" << parteA_
                  << ", B=" << parteB_ << "\n";
    }

private:
    std::string parteA_;
    std::string parteB_;
};

class ConstructorFluido {
public:
    ConstructorFluido& parteA(const std::string& valor) {
        parteA_ = valor;
        return *this;
    }

    ConstructorFluido& parteB(const std::string& valor) {
        parteB_ = valor;
        return *this;
    }

    Producto construir() const {
        return Producto(parteA_, parteB_);
    }

private:
    std::string parteA_ = "A por defecto";
    std::string parteB_ = "B por defecto";
};

int main() {
    auto p = ConstructorFluido{}
                .parteA("A personalizada")
                .parteB("B personalizada")
                .construir();

    p.mostrar();
}
```


