Perfecto. Aquí tienes el contenido para la sección **“Principios básicos de diseño”**, con un lenguaje formal y didáctico, orientado a introducir la motivación y las buenas prácticas fundamentales antes de abordar SOLID y los patrones de diseño:

---

## Principios básicos de diseño

Los principios básicos de diseño orientado a objetos son guías conceptuales que permiten construir software más mantenible, flexible y reutilizable. Aunque son anteriores a la formalización de los principios SOLID, siguen siendo fundamentales para entender el valor de los patrones de diseño y su aplicación efectiva.

### 1. Encapsula lo que varía

**Motivación:**
El software cambia con el tiempo. Los requerimientos evolucionan, las tecnologías se actualizan, y los comportamientos deben adaptarse. Identificar y aislar las partes del sistema que están sujetas a cambio es esencial para evitar que los cambios afecten otras partes del código.

**Principio:**

> Identifica los aspectos de tu aplicación que varían y sepáralos del resto del código que permanece estable.

**Aplicación en C++ moderno:**

* Uso de funciones virtuales o lambdas para representar comportamiento variable.
* Uso de clases base abstractas para definir interfaces que ocultan detalles de implementación concretos.
* Separación de la lógica cambiante mediante punteros inteligentes (`std::unique_ptr`, `std::function`, etc.).

**Ejemplo simple:**

```cpp
class Strategy {
public:
    virtual void execute() const = 0;
    virtual ~Strategy() = default;
};

class ConcreteStrategyA : public Strategy {
public:
    void execute() const override {
        std::cout << "Estrategia A\n";
    }
};

class Context {
    std::unique_ptr<Strategy> strategy_;
public:
    Context(std::unique_ptr<Strategy> s) : strategy_(std::move(s)) {}
    void run() const { strategy_->execute(); }
};
```

Este enfoque permite cambiar el comportamiento sin modificar el contexto.

---

### 2. Programa a una interfaz, no a una implementación

**Motivación:**
Acoplar directamente a clases concretas dificulta el cambio y la reutilización. En cambio, programar contra interfaces permite cambiar las implementaciones sin afectar al código que las utiliza.

**Principio:**

> Define dependencias en términos de abstracciones, no de clases concretas.

**Aplicación en C++ moderno:**

* Uso de clases abstractas o plantillas que definen contratos sin fijar detalles.
* Uso de `std::function` para representar comportamientos genéricos.
* Inversión de dependencias: las clases dependen de interfaces o abstracciones, no de detalles concretos.

**Ejemplo:**

```cpp
void procesar(std::function<void()> tarea) {
    tarea(); // No importa qué haga, solo que puede ejecutarse
}
```

Este enfoque favorece la reutilización y el desacoplamiento.

---

### 3. Favorece la composición sobre la herencia

**Motivación:**
La herencia introduce una fuerte relación entre clases, donde los cambios en la superclase pueden tener efectos colaterales no deseados en las subclases. Además, la herencia tiende a generar jerarquías rígidas. En cambio, la composición permite construir comportamientos complejos combinando objetos más simples.

**Principio:**

> Construye sistemas a partir de objetos que cooperan entre sí, en lugar de depender de jerarquías rígidas.

**Aplicación en C++ moderno:**

* Composición mediante atributos y punteros inteligentes.
* Uso de políticas o estrategias inyectables para extender comportamiento dinámicamente.
* Separación clara de responsabilidades: clases pequeñas que hacen una sola cosa.

**Ejemplo:**

```cpp
class Motor {
public:
    void encender() const { std::cout << "Motor encendido\n"; }
};

class Vehiculo {
    Motor motor_;
public:
    void arrancar() { motor_.encender(); }
};
```

Aquí `Vehiculo` no hereda de `Motor`, sino que lo **compone**, lo cual favorece la reutilización y facilita el cambio.

---

### Resumen

Los tres principios básicos aquí expuestos proporcionan una base conceptual sólida para entender el diseño orientado a objetos más allá de la sintaxis. Son el primer paso hacia arquitecturas flexibles y mantenibles, y preparan el terreno para aplicar los principios **SOLID** y, en consecuencia, los **patrones de diseño**.

* **Encapsula lo que varía:** facilita el cambio sin romper lo estable.
* **Programa a una interfaz:** permite abstraer y desacoplar.
* **Favorece la composición:** promueve flexibilidad y reutilización.

---

¿Te gustaría que prepare también un resumen visual o diagrama de esta sección para usarlo como apoyo didáctico?
