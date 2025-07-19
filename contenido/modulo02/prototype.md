# Prototype

## Introducción y propósito

El patrón **Prototype** es un patrón creacional que permite **crear nuevos objetos a partir de una instancia existente (prototipo)**, en lugar de construirlos directamente con `new` o con constructores. Se basa en el concepto de **clonación**: se define una interfaz para clonar objetos, y cada clase concreta implementa su propio método de copia.

## Problemas que resuelve

El patrón Prototype resulta especialmente útil en los siguientes escenarios:

* Cuando **crear un objeto desde cero es costoso o complejo**, y es más eficiente clonar uno ya configurado.
* Cuando existen **muchas combinaciones de configuraciones** posibles para un objeto y no se quiere usar muchos constructores ni parámetros.
* Cuando el sistema necesita **crear objetos sin conocer su clase concreta**, pero sí puede acceder a un prototipo.
* Cuando se trabaja con **jerarquías de clases y se quiere clonar objetos polimórficamente**.

Con este patrón conseguimos:

* Reducción del **acoplamiento** al encapsular el proceso de creación.
* Mejora de la **flexibilidad** y extensibilidad del sistema.
* Evita el uso excesivo de constructores y lógica de inicialización repetida.

## Diagrama UML y estructura

```plaintext
         +-------------------+
         |   IPrototype      |  <<interface>>
         +-------------------+
         | + clone()         |
         +-------------------+
                  ^
                  |
      +---------------------+
      |  ConcretePrototype  |
      +---------------------+
      | - atributos         |
      | + clone() override  |
      +---------------------+

Prototipos se registran o usan directamente:
         
     +---------------------+
     |  Cliente/Factory    |
     +---------------------+
     | usa objetos clonados|
     +---------------------+
```

* **IPrototype**: interfaz base con el método `clone()`, generalmente `virtual`.
* **ConcretePrototype**: clase concreta que implementa la clonación (`clone()` devuelve una copia).
* **Cliente**: crea nuevos objetos usando el método `clone()` sobre prototipos conocidos.

---

## Implementación en C++ moderno

A continuación, se presenta una implementación sencilla del patrón Prototype con C++ moderno.

### Paso 1: Definir la interfaz base clonable

```cpp
#include <iostream>
#include <memory>
#include <unordered_map>
#include <string>

// Interfaz abstracta con clonación polimórfica
class IPrototype {
public:
    virtual std::unique_ptr<IPrototype> clone() const = 0;
    virtual void mostrar() const = 0;
    virtual ~IPrototype() = default;
};
```

### Paso 2: Clases concretas que implementan la clonación

```cpp
class ConfigTCP : public IPrototype {
    std::string host;
    int puerto;
public:
    ConfigTCP(std::string h, int p) : host(std::move(h)), puerto(p) {}

    std::unique_ptr<IPrototype> clone() const override {
        return std::make_unique<ConfigTCP>(*this);
    }

    void mostrar() const override {
        std::cout << "TCP -> Host: " << host << ", Puerto: " << puerto << "\n";
    }
};

class ConfigUDP : public IPrototype {
    std::string ip;
    int puerto;
public:
    ConfigUDP(std::string i, int p) : ip(std::move(i)), puerto(p) {}

    std::unique_ptr<IPrototype> clone() const override {
        return std::make_unique<ConfigUDP>(*this);
    }

    void mostrar() const override {
        std::cout << "UDP -> IP: " << ip << ", Puerto: " << puerto << "\n";
    }
};
```

### Paso 3: Registro y uso de prototipos

```cpp
class PrototipoFactory {
    std::unordered_map<std::string, std::unique_ptr<IPrototype>> prototipos;
public:
    void registrar(const std::string& nombre, std::unique_ptr<IPrototype> p) {
        prototipos[nombre] = std::move(p);
    }

    std::unique_ptr<IPrototype> crear(const std::string& nombre) const {
        return prototipos.at(nombre)->clone();
    }
};

int main() {
    PrototipoFactory fabrica;

    fabrica.registrar("tcp_local", std::make_unique<ConfigTCP>("127.0.0.1", 8080));
    fabrica.registrar("udp_remoto", std::make_unique<ConfigUDP>("192.168.1.10", 5000));

    auto copia1 = fabrica.crear("tcp_local");
    auto copia2 = fabrica.crear("udp_remoto");

    copia1->mostrar();
    copia2->mostrar();
}
```
## Ventajas

* **Flexibilidad**: se pueden crear objetos dinámicamente sin depender de sus clases concretas.
* **Reutilización**: evita duplicación de lógica de construcción.
* **Extensibilidad**: permite añadir nuevos prototipos sin modificar el cliente.
* **Eficiencia**: clonar puede ser más rápido que crear desde cero.

## Desventajas

* Cada clase debe implementar su propia lógica de copia (`clone()`), lo que puede ser repetitivo.
* Las copias profundas pueden ser complejas si el objeto contiene recursos no copiables.
* Puede ocultar dependencias si se abusa del patrón.

## Buenas prácticas

* Asegúrate de implementar correctamente la semántica de copia o movimiento.
* Usa `std::unique_ptr` para evitar fugas de memoria.
* Considera usar este patrón solo cuando se necesite clonación dinámica.
