# Implementación de Prototype en C++

## Estructura general

La implementación del **Prototype** en C++ moderno se basa en la **creación de nuevos objetos a partir de instancias existentes**, delegando el proceso de copia en el propio objeto. El patrón permite duplicar objetos sin conocer su tipo concreto ni los detalles internos de su construcción.

Este enfoque resulta especialmente útil cuando la creación de objetos es costosa o compleja, y cuando es necesario preservar configuraciones ya existentes en nuevas instancias.

Recuerda los diferentes tipos de copia:

* **Copia superficial**: se copian los valores de los miembros, pero los recursos dinámicos gestionados manualmente o mediante punteros quedan compartidos entre el objeto original y la copia. Cualquier modificación del recurso afecta a ambas instancias.
* **Copia profunda**: además de copiar los valores, se crean copias independientes de los recursos dinámicos, garantizando que el objeto clonado no comparte estado interno con el original.

## Elementos de C++ moderno utilizados

La implementación del patrón Prototype se apoya en mecanismos de C++ moderno que permiten expresar clonación segura, control del ciclo de vida y copias correctas de objetos complejos.

* **Clases abstractas e interfaces puras** para definir el contrato de clonación.
* **Métodos virtuales puros**, en particular el método `clone()`.
* **Polimorfismo dinámico** para clonar objetos sin conocer su tipo concreto.
* **Destructores virtuales** para destrucción segura a través de interfaces.
* **`std::unique_ptr`** para expresar propiedad exclusiva de la copia creada.
* **Constructores de copia** para implementar copias superficiales o profundas.
* **RAII** para garantizar gestión correcta de recursos durante la clonación.
* Uso explícito de **`override`** en las implementaciones concretas.

## Componentes del patrón y responsabilidades

### 1. Interfaz o clase base del **Prototipo**

* Define el contrato común que deben cumplir todos los objetos clonables.
* Declara el método `clone()` como operación fundamental del patrón.
* Permite crear nuevas instancias sin conocer el tipo dinámico concreto.
* Garantiza un uso polimórfico seguro mediante un destructor virtual.

### 2. **Prototipos concretos**

* Implementan el método `clone()` devolviendo una nueva instancia del mismo tipo.
* Deciden si la clonación se realiza mediante copia superficial o copia profunda.
* Encapsulan la lógica necesaria para duplicar recursos internos.
* Mantienen las invariantes del objeto original en la copia creada.

### 3. **Código cliente**

* Trabaja exclusivamente con la interfaz del prototipo.
* Solicita nuevas instancias mediante la operación `clone()`.
* No conoce la clase concreta ni la lógica interna de copia.
* Gestiona el ciclo de vida de los objetos clonados de forma segura mediante RAII.



## Diagrama UML

![uml](uml/prototype.png)

## Ejemplo genérico

```cpp
#include <iostream>
#include <memory>
#include <string>

// ----------------------------------------
// Interfaz base del prototipo
// ----------------------------------------
class Prototipo {
public:
    virtual ~Prototipo() = default;

    // Método de clonación
    virtual std::unique_ptr<Prototipo> clone() const = 0;

    virtual void mostrar() const = 0;
};

// ----------------------------------------
// Prototipo concreto A (copia superficial)
// ----------------------------------------
class PrototipoConcretoA : public Prototipo {
public:
    PrototipoConcretoA(std::string nombre, int valor)
        : nombre_(std::move(nombre)), valor_(valor) {}

    std::unique_ptr<Prototipo> clone() const override {
        return std::make_unique<PrototipoConcretoA>(*this); //Copia superficial, sin recursos compartidos
    }

    void mostrar() const override {
        std::cout << "PrototipoConcretoA { nombre = " << nombre_
                  << ", valor = " << valor_ << " }\n";
    }

private:
    std::string nombre_;
    int valor_;
};

// ----------------------------------------
// Prototipo concreto B (copia profunda)
// ----------------------------------------
class PrototipoConcretoB : public Prototipo {
public:
    PrototipoConcretoB(std::string etiqueta, std::unique_ptr<int> dato)
        : etiqueta_(std::move(etiqueta)), dato_(std::move(dato)) {}

    // Clonación profunda: duplicamos el recurso dinámico
    std::unique_ptr<Prototipo> clone() const override {
        return std::make_unique<PrototipoConcretoB>(
            etiqueta_, std::make_unique<int>(*dato_));
    }

    void mostrar() const override {
        std::cout << "PrototipoConcretoB { etiqueta = " << etiqueta_
                  << ", dato = " << *dato_ << " }\n";
    }

private:
    std::string etiqueta_;
    std::unique_ptr<int> dato_; // requiere copia profunda
};

// ----------------------------------------
// Función cliente
// ----------------------------------------
void cliente(const Prototipo& prototipo) {
    auto copia = prototipo.clone();
    copia->mostrar();
}

int main() {
    PrototipoConcretoA protA("Ejemplo A", 42);
    PrototipoConcretoB protB("Ejemplo B", std::make_unique<int>(100));

    cliente(protA);
    cliente(protB);

    return 0;
}
```

## Puntos clave del ejemplo

* El método `clone()` encapsula completamente el proceso de copia, permitiendo que cada clase concrete copia superficial o profunda según sus necesidades.
* El uso de **`std::unique_ptr`** garantiza la gestión automática de los objetos clonados.
* El cliente trabaja exclusivamente con la **interfaz del prototipo**, sin conocer cómo se implementa la clonación.
* La separación entre **instancia original** y **clon creado** permite configurar prototipos previamente y generar copias rápidas y seguras desde ellos.
* El patrón evita duplicar lógica compleja de inicialización y permite extender el sistema añadiendo nuevos prototipos sin modificar el código existente.

