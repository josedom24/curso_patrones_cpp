# Composición de objetos con punteros inteligentes

En el diseño de clases complejas, la **composición** es una técnica fundamental que permite construir objetos a partir de otros objetos más simples, favoreciendo la modularidad y la reutilización de código. En C++ moderno, el uso de **punteros inteligentes** en relaciones de composición aporta control explícito sobre la gestión de recursos, mejora la seguridad de memoria y habilita patrones de propiedad más flexibles.

## Composición y agregación

Antes de entrar en los aspectos técnicos, es importante distinguir dos formas comunes de relación entre objetos:

* **Composición** (ownership fuerte): un objeto "contiene" a otro, es responsable de su creación y destrucción, y su ciclo de vida está vinculado. Se modela naturalmente con `std::unique_ptr`.

* **Agregación** (ownership débil o compartido): un objeto "utiliza" a otro, pero no es el único responsable de su existencia. Puede representarse con `std::shared_ptr` (para propiedad compartida) o `std::weak_ptr` (para evitar ciclos de referencia).

## Composición con `std::unique_ptr`

Cuando una clase es propietaria única de un subobjeto dinámico, se recomienda utilizar `std::unique_ptr`. Esta elección garantiza que el recurso será destruido automáticamente junto con el objeto contenedor, evitando fugas de memoria y reflejando adecuadamente la relación de propiedad. Ejemplo:

```cpp
#include <memory>
#include <string>

class Engine {
public:
    explicit Engine(std::string type) : type_(std::move(type)) {}
    void start() const { /* lógica de encendido */ }

private:
    std::string type_;
};

class Car {
public:
    Car(std::unique_ptr<Engine> engine) 
        : engine_(std::move(engine)) {}

    void start() {
        engine_->start();
    }

private:
    std::unique_ptr<Engine> engine_;
};

int main() {
    auto engine = std::make_unique<Engine>("V8");
    Car car(std::move(engine));
    car.start();
}
```

Aquí, `Car` es responsable de la vida útil de `Engine`. La relación es fuerte y exclusiva, lo que concuerda con el principio de composición.



## Composición compartida con `std::shared_ptr`

En algunos diseños, múltiples objetos pueden compartir la propiedad de un mismo componente. En estos casos, se utiliza `std::shared_ptr`, que lleva una cuenta de referencias y destruye el recurso cuando ya no hay más propietarios activos. Ejemplo:

```cpp
#include <memory>
#include <vector>

class Sensor {
public:
    void read() const { /* lectura de datos */ }
};

class MonitoringSystem {
public:
    void add_sensor(std::shared_ptr<Sensor> sensor) {
        sensors_.push_back(sensor);
    }

private:
    std::vector<std::shared_ptr<Sensor>> sensors_;
};

int main() {
    auto shared_sensor = std::make_shared<Sensor>();
    MonitoringSystem system1;
    MonitoringSystem system2;

    system1.add_sensor(shared_sensor);
    system2.add_sensor(shared_sensor);
}
```

Aquí, varios sistemas de monitoreo pueden compartir el mismo sensor sin duplicarlo. Esto es útil cuando los objetos son costosos de crear o deben mantenerse sincronizados entre múltiples entidades.

## Evitar ciclos de referencia

Cuando se utilizan `std::shared_ptr` en ambas direcciones de una relación (por ejemplo, en estructuras de árbol o grafos con enlaces padres-hijos), puede producirse una **fuga de memoria por ciclo de referencias**. Para evitar esto, se emplea `std::weak_ptr` en una de las direcciones. Ejemplo:

```cpp
#include <memory>
#include <vector>

class Node : public std::enable_shared_from_this<Node> {
public:
    void add_child(std::shared_ptr<Node> child) {
        children_.push_back(child);
        child->parent_ = shared_from_this();
    }

private:
    std::vector<std::shared_ptr<Node>> children_;
    std::weak_ptr<Node> parent_; // evita ciclo
};
```

## Recomendaciones prácticas

* Utilice `std::unique_ptr` cuando el objeto compuesto sea el único responsable del recurso.
* Use `std::make_unique<T>(...)` o `std::make_shared<T>(...)` para construir punteros inteligentes de forma segura y eficiente.
* Prefiera `std::shared_ptr` cuando haya múltiples propietarios legítimos del mismo recurso.
* Introduzca `std::weak_ptr` en estructuras cíclicas para evitar fugas.
* Encapsule punteros inteligentes como miembros privados y proporcione interfaces de acceso controladas.
* Evite exponer punteros crudos que puedan comprometer la seguridad de la propiedad.

--

## Ejemplo completo

Vamos a crea un sistema modular de audio.

```cpp
class Amplifier {
public:
    void set_volume(int level) { /* ... */ }
};

class AudioSystem {
public:
    explicit AudioSystem(std::unique_ptr<Amplifier> amp)
        : amplifier_(std::move(amp)) {}

    void configure() {
        amplifier_->set_volume(5);
    }

private:
    std::unique_ptr<Amplifier> amplifier_;
};

int main() {
    auto amp = std::make_unique<Amplifier>();
    AudioSystem system(std::move(amp));
    system.configure();
}
```

La relación aquí representa claramente una composición: el sistema de audio posee y configura su amplificador, y se encarga de su destrucción al terminar su ciclo de vida.

