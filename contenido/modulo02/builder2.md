# Implementación del patrón Builder con C++ moderno

## Estructura general

La implementación del **Builder** en C++ moderno separa el **proceso de construcción** de un objeto complejo de su **representación final**. El patrón permite construir un mismo tipo de objeto mediante distintos pasos o configuraciones, sin sobrecargar constructores ni exponer detalles internos al código cliente.

Este enfoque facilita la creación progresiva de objetos, garantiza estados válidos durante la construcción y permite reutilizar el proceso de construcción en distintos contextos.

## Elementos de C++ moderno utilizados

* **Clases abstractas e interfaces puras** para definir el proceso de construcción.
* **Métodos virtuales** para representar pasos configurables.
* **Herencia** para definir distintos builders concretos.
* **Fluidez de métodos** para permitir configuraciones encadenadas.
* **Constructores no públicos** para controlar la creación del producto.
* **`std::unique_ptr`** para expresar propiedad del objeto construido.
* **RAII** para garantizar liberación automática de recursos.
* Uso explícito de **`override`** en builders concretos.

## Componentes del patrón y responsabilidades

### 1. **Producto**

* Representa el objeto complejo que se desea construir.
* Define la estructura y el estado final del objeto.
* No expone el proceso de construcción al exterior.
* Garantiza sus invariantes una vez finalizada la construcción.

### 2. Interfaz base del **Builder**

* Declara los pasos necesarios para construir el producto.
* Define una interfaz común para distintas estrategias de construcción.
* Permite configurar el producto de forma progresiva.
* No expone detalles de la representación final.

### 3. **Builders concretos**

* Implementan los pasos de construcción definidos por la interfaz.
* Construyen variantes específicas del producto.
* Encapsulan la lógica de construcción concreta.
* Deciden cuándo el producto está listo para ser devuelto.

### 4. **Director** (opcional)

* Define el orden en el que se ejecutan los pasos de construcción.
* Encapsula secuencias de construcción reutilizables.
* Trabaja únicamente con la interfaz del builder.
* No conoce la representación concreta del producto.

### 5. **Código cliente**

* Decide qué builder utilizar según el contexto.
* Puede construir directamente el producto o delegar en un director.
* No conoce los detalles internos de la construcción.
* Utiliza el producto final ya construido y válido.

## Diagrama UML (con Director)

![uml](uml/builder.png)

## Diagrama UML (sin Director)

![uml](uml/builder2.png)

## Ejemplo genérico

### Variante 1: Builder **con Director** (versión clásica)

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

### Variante 2: Builder **sin Director** (builder fluido moderno)

Esta variante es más idiomática en C++ actual:

* El builder y el cliente trabajan directamente.
* Los métodos devuelven `*this` para permitir **encadenamiento fluido**.
* El cliente decide libremente el orden de construcción.


```cpp
#include <iostream>
#include <memory>
#include <string>

// =====================================================
//                 Producto
// =====================================================

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

// =====================================================
//                 Builder concreto (fluido)
// =====================================================

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

    std::unique_ptr<Producto> construir() const {
        return std::make_unique<Producto>(parteA_, parteB_);
    }

private:
    std::string parteA_ = "A por defecto";
    std::string parteB_ = "B por defecto";
};

// =====================================================
//                     Cliente
// =====================================================

int main() {
    auto p = ConstructorFluido{}
                .parteA("A personalizada")
                .parteB("B personalizada")
                .construir();

    p->mostrar();
}

```


