# Implementación de Prototype en C++

## Estructura y elementos modernos utilizados

La implementación del **Prototype** en C++ moderno se basa en una jerarquía que define una interfaz de clonación y una serie de clases concretas responsables de producir copias superficiales o profundas según corresponda.

### 1. Interfaz o clase base del Prototipo

Define el contrato común que todos los objetos clonables deben proporcionar. La operación fundamental es el método `clone()`, que retorna una nueva instancia del mismo tipo dinámico.

**Elementos de C++ moderno utilizados:**

* **`std::unique_ptr`** como tipo de retorno para expresar propiedad exclusiva de la copia creada.
* **Destructores virtuales** para garantizar un borrado seguro a través de la interfaz polimórfica.
* **Polimorfismo dinámico** para permitir que el cliente clone objetos sin conocer su tipo concreto.
* **Distinción entre copia superficial y copia profunda** en el interior de cada implementación concreta.

### 2. Prototipos concretos

Representan las distintas variantes de objetos clonables dentro del sistema. Cada uno decide si su proceso de clonación requiere copia superficial o profunda, dependiendo de si gestiona recursos dinámicos o estructuras compuestas.

**Elementos de C++ moderno utilizados:**

* **Constructores de copia bien definidos** cuando la lógica de clonación requiere copiar recursos.
* **Implementación explícita del método `clone()`** devolviendo objetos construidos mediante `std::make_unique`.
* Uso natural de **RAII** para administrar memoria y otros recursos durante la clonación.

### 3. Código cliente

Solicita nuevas instancias clones de prototipos sin conocer su clase concreta, ni cómo se realiza la copia. El cliente trabaja exclusivamente con la interfaz del prototipo.

**Elementos de C++ moderno utilizados:**

* **Programación a interfaces**, sin dependencia directa de las clases concretas.
* **Ámbito y ciclo de vida claros** gracias a punteros inteligentes.
* **Simplicidad semántica**: crear un objeto a partir de otro ya configurado es tan sencillo como llamar a `clone()`.

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
        return std::make_unique<PrototipoConcretoA>(*this); // copia superficial
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

