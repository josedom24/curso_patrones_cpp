# Decorator

## Introducción y propósito

El patrón **Decorator** permite **añadir funcionalidades a un objeto de manera dinámica** sin modificar su clase original ni usar herencia múltiple. Su objetivo es **extender el comportamiento** de los objetos de forma flexible y modular, encapsulando la lógica adicional en objetos *decoradores*.

## Problemas que resuelve

Este patrón resulta útil cuando:

* Necesitamos **extender el comportamiento de objetos individuales** sin afectar al resto de la jerarquía de clases.
* Queremos evitar una **explosión de subclases** al combinar múltiples variantes de comportamiento.
* Deseamos aplicar **responsabilidades de forma acumulativa o modular**, manteniendo el principio de *responsabilidad única*.

Ejemplos de uso:

* Interfaces gráficas donde se añaden bordes, scroll o sombreado a componentes visuales.
* Capas de seguridad o compresión en flujos de datos (`std::iostream`).
* Funcionalidades extendidas sobre servicios (caching, logging, métricas).

## **Diagrama UML y estructura**

```plaintext
         +--------------------+
         |     Component      |<-------------------+
         | (interfaz común)   |                    |
         +--------------------+                    |
                   ^                               |
                   |                               |
        +----------+----------+        +-----------+-------------+
        |   ConcreteComponent |        |       Decorator         |
        | (implementación base)|       | (implementa Component y |
        +----------------------+       |  contiene un Component) |
                                       +-----------+-------------+
                                                   |
                                       +-----------+-------------+
                                       |   ConcreteDecoratorX     |
                                       +--------------------------+
```

* **Component**: interfaz común para todos los objetos (base y decoradores).
* **ConcreteComponent**: objeto base que se desea decorar.
* **Decorator**: clase abstracta que implementa la interfaz y contiene un puntero al componente decorado.
* **ConcreteDecorator**: clase que añade funcionalidad antes o después de delegar en el componente.

## Implementación en C++ moderno

Creamos un sistema de notificaciones que permite enviar mensajes por distintos canales, y se desea agregar comportamiento adicional como log o cifrado sin modificar el componente base.

```cpp
#include <iostream>
#include <memory>
#include <string>

// Interfaz común
class Notifier {
public:
    virtual void send(const std::string& message) const = 0;
    virtual ~Notifier() = default;
};

// Implementación base
class EmailNotifier : public Notifier {
public:
    void send(const std::string& message) const override {
        std::cout << "Enviando correo: " << message << '\n';
    }
};

// Clase Decorador base
class NotifierDecorator : public Notifier {
public:
    explicit NotifierDecorator(std::shared_ptr<Notifier> wrappee)
        : wrappee_(std::move(wrappee)) {}

protected:
    std::shared_ptr<Notifier> wrappee_;
};

// Decorador concreto: añade logging
class LoggerNotifier : public NotifierDecorator {
public:
    using NotifierDecorator::NotifierDecorator;

    void send(const std::string& message) const override {
        std::cout << "[Log] Mensaje: " << message << '\n';
        wrappee_->send(message);
    }
};

// Decorador concreto: añade cifrado simulado
class EncryptedNotifier : public NotifierDecorator {
public:
    using NotifierDecorator::NotifierDecorator;

    void send(const std::string& message) const override {
        std::string encrypted = "[ENCRYPTED] " + message;
        wrappee_->send(encrypted);
    }
};

int main() {
    auto email = std::make_shared<EmailNotifier>();
    auto logged = std::make_shared<LoggerNotifier>(email);
    auto secured = std::make_shared<EncryptedNotifier>(logged);

    secured->send("Reunión a las 10 AM.");
}
```

* `Notifier` define la interfaz estándar.
* `EmailNotifier` es la clase base que envía el mensaje.
* `NotifierDecorator` mantiene una referencia al componente decorado (`wrappee_`) y delega.
* `LoggerNotifier` y `EncryptedNotifier` extienden el comportamiento sin modificar el objeto original.
* Los decoradores pueden **encadenarse** dinámicamente.
* `using` se puede usar para distintas funciones en C++ en este caso nos permite heredar todos los constructores de la clase base `NotifierDecorator` en las clases derivadas. 

## Ventajas

* Extiende funcionalidades de forma **modular y reutilizable**.
* Evita la necesidad de crear múltiples subclases para cada combinación posible.
* Aplica el principio de **abierto/cerrado**: clases cerradas a modificación pero abiertas a extensión.
* Composición en tiempo de ejecución: **mayor flexibilidad** que la herencia.

## Desventajas

* Introduce **muchas clases pequeñas** que pueden aumentar la complejidad del diseño.
* El encadenamiento de decoradores puede **dificultar el seguimiento del flujo de ejecución**.
* El rendimiento puede verse afectado si se añaden muchos niveles de decoración innecesaria.

Cuándo no usarlo:

* Cuando el número de decoradores es fijo y conocido de antemano (una jerarquía tradicional puede ser más simple).
* Si la decoración no aporta comportamiento real sino solo estructura redundante.

## Buenas prácticas

* Combine decoradores con **punteros inteligentes** (`std::shared_ptr` o `std::unique_ptr`) para facilitar la gestión de recursos.
* Mantenga los decoradores lo más **cohesionados y atómicos** posible.
* Nombre explícitamente las clases decoradoras para expresar claramente qué comportamiento añaden.

