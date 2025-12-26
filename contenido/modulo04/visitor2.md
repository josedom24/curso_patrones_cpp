# Implementación de Visitor con C++

## Estructura general

La implementación del **Visitor** en C++ moderno permite **definir nuevas operaciones sobre una estructura de objetos sin modificar las clases de dichos objetos**. El patrón separa la estructura de datos de las operaciones que se aplican sobre ella, organizando estas últimas en una jerarquía independiente.

Este enfoque resulta especialmente útil cuando la estructura de elementos es estable, pero las operaciones que deben aplicarse sobre ella evolucionan con frecuencia.

## Elementos de C++ moderno utilizados

* **Clases abstractas e interfaces puras** para definir contratos de elementos y visitantes.
* **Métodos virtuales** para habilitar el doble despacho.
* **Polimorfismo dinámico** para seleccionar la operación adecuada en tiempo de ejecución.
* **Destructores virtuales** para destrucción segura en jerarquías polimórficas.
* **RAII** para la gestión automática de recursos en visitantes con estado.
* **Contenedores de la STL** para almacenar colecciones heterogéneas de elementos.
* **`std::unique_ptr`** para gestionar elementos polimórficos de forma segura.

## Componentes del patrón y responsabilidades

### 1. Interfaz base de **Elemento**

* Define el método `accept` que recibe un visitante.
* Establece el punto de entrada para el doble despacho.
* Permite aplicar operaciones externas sin modificar la clase.
* Se utiliza de forma polimórfica mediante punteros o referencias.

### 2. **Elementos concretos**

* Representan los distintos tipos de la estructura de objetos.
* Implementan el método `accept` delegando en el visitante.
* Encapsulan sus propios datos y estado.
* No contienen la lógica de las operaciones externas.

### 3. Interfaz base del **Visitante**

* Declara un método de visita por cada tipo concreto de elemento.
* Define el conjunto de operaciones aplicables a la estructura.
* Permite añadir nuevas operaciones sin modificar los elementos.
* Se utiliza de forma polimórfica.

### 4. **Visitantes concretos**

* Implementan operaciones específicas sobre cada tipo de elemento.
* Agrupan lógica relacionada dentro de un mismo visitante.
* Pueden mantener estado interno durante el recorrido.
* Aplican algoritmos sin alterar la estructura visitada.

### 5. **Código cliente**

* Crea y gestiona la estructura de elementos.
* Aplica uno o varios visitantes a dicha estructura.
* No modifica ni conoce la lógica interna de las operaciones.
* Gestiona la memoria de forma automática mediante RAII.

## Diagrama UML

![uml](uml/visitor.png)

## Ejemplo genérico en C++

```cpp
#include <iostream>
#include <memory>
#include <vector>

// ----------------------------------------
// Interfaz base del Visitante
// ----------------------------------------
class ElementoA;
class ElementoB;

class Visitante {
public:
    virtual ~Visitante() = default;
    virtual void visitar(ElementoA& elem) = 0;
    virtual void visitar(ElementoB& elem) = 0;
};

// ----------------------------------------
// Interfaz base del Elemento
// ----------------------------------------
class Elemento {
public:
    virtual ~Elemento() = default;
    virtual void accept(Visitante& v) = 0;
};

// ----------------------------------------
// Elementos concretos
// ----------------------------------------
class ElementoA : public Elemento {
public:
    void accept(Visitante& v) override {
        v.visitar(*this); // double dispatch
    }

    void accion_especifica_A() const {
        std::cout << "Acción específica de ElementoA.\n";
    }
};

class ElementoB : public Elemento {
public:
    void accept(Visitante& v) override {
        v.visitar(*this); // double dispatch
    }

    void accion_especifica_B() const {
        std::cout << "Acción específica de ElementoB.\n";
    }
};

// ----------------------------------------
// Visitantes concretos
// ----------------------------------------
class VisitanteConcreto1 : public Visitante {
public:
    void visitar(ElementoA& elem) override {
        std::cout << "VisitanteConcreto1 procesa ElementoA → ";
        elem.accion_especifica_A();
    }

    void visitar(ElementoB& elem) override {
        std::cout << "VisitanteConcreto1 procesa ElementoB → ";
        elem.accion_especifica_B();
    }
};

class VisitanteConcreto2 : public Visitante {
public:
    void visitar(ElementoA& elem) override {
        std::cout << "VisitanteConcreto2 analiza ElementoA.\n";
    }

    void visitar(ElementoB& elem) override {
        std::cout << "VisitanteConcreto2 analiza ElementoB.\n";
    }
};

// ----------------------------------------
// Código cliente
// ----------------------------------------
int main() {
    std::vector<std::unique_ptr<Elemento>> elementos;
    elementos.push_back(std::make_unique<ElementoA>());
    elementos.push_back(std::make_unique<ElementoB>());

    VisitanteConcreto1 v1;
    VisitanteConcreto2 v2;

    std::cout << "--- Aplicando VisitanteConcreto1 ---\n";
    for (auto& e : elementos) {
        e->accept(v1);
    }

    std::cout << "\n--- Aplicando VisitanteConcreto2 ---\n";
    for (auto& e : elementos) {
        e->accept(v2);
    }

    return 0;
}
```

## Puntos clave del ejemplo

* El método `accept` implementa la primera parte del doble despacho llamando al método `visitar` correspondiente.
* Cada `visitar(ElementoX&)` constituye la segunda parte del doble despacho.
* Para añadir una nueva operación, basta con crear un nuevo visitante sin modificar las clases `ElementoA` y `ElementoB`.
* Para añadir un nuevo tipo de elemento, se debe modificar la interfaz del visitante (trade-off del patrón).
* El uso de `std::unique_ptr` y contenedores estándar permite almacenar elementos polimórficos de forma segura.
* La lógica de negocio está completamente separada de la estructura de datos.

Si quieres, puedo añadir una sección final con **qué no hemos modificado**, en el estilo que usas para Factory Method.
