# Implementación de Observer con C++

## Estructura y elementos modernos utilizados

La implementación del **Observer** en C++ moderno se organiza en torno a dos tipos principales de roles: el **sujeto** (quien genera los cambios) y los **observadores** (quienes reaccionan a esos cambios). A continuación se describen estas clases y, para cada una, los mecanismos de C++ moderno que resultan relevantes.

### 1. Interfaz base del **Observador**

Define la operación que el sujeto utilizará para notificar cambios. El código del sujeto solo conoce esta interfaz, no las clases concretas que la implementan.

**Elementos de C++ moderno utilizados:**

* **Destructores virtuales** para permitir una gestión segura de objetos polimórficos mediante punteros inteligentes.
* **Métodos virtuales puros** para definir el contrato `actualizar(...)`.
* Posible uso de **tipos fuertemente tipados** (por ejemplo, `int` o estructuras específicas) como información de actualización.

### 2. Interfaz base del **Sujeto (observable)**

Declara las operaciones para gestionar la lista de observadores (suscripción / desuscripción) y la operación de notificación.

**Elementos de C++ moderno utilizados:**

* Métodos que aceptan **`std::shared_ptr<Observador>`** para registrar y eliminar observadores.
* Almacenamiento interno mediante **`std::weak_ptr<Observador>`** para evitar ciclos de referencia entre sujeto y observadores.
* Separación clara entre **gestión de suscripciones** y **notificación de cambios**.

### 3. **Sujetos concretos**

Implementan la lógica específica del dominio y mantienen el estado que será observado. Cada vez que este estado cambia, el sujeto notifica a todos los observadores.

**Elementos de C++ moderno utilizados:**

* **`std::vector<std::weak_ptr<Observador>>`** para mantener una lista dinámica de observadores.
* Uso de **`std::remove_if`** y bucles `for` basados en rango para limpiar observadores caducados y recorrer la lista.
* Encapsulación y RAII: el sujeto se encarga de su propio estado y de la lista de observadores, sin fugas de memoria.

### 4. **Observadores concretos**

Implementan la reacción ante los cambios notificados por el sujeto. Cada observador puede interpretar la notificación de forma diferente.

**Elementos de C++ moderno utilizados:**

* Implementaciones concretas de `actualizar(...)` que pueden usar **`std::string`**, flujos de salida (`std::cout`) u otros recursos.
* Uso de **constructores seguros** y miembros privados para mantener el estado interno del observador (por ejemplo, un nombre descriptivo).

### 5. **Código cliente**

Es el encargado de crear el sujeto, instanciar los observadores y registrar/desregistrar estos últimos. No necesita conocer cómo el sujeto almacena ni notifica a sus observadores.

**Elementos de C++ moderno utilizados:**

* **`std::make_shared<T>()`** para crear instancias gestionadas automáticamente.
* Programación a interfaces: el cliente trabaja con `std::shared_ptr<Sujeto>` y `std::shared_ptr<Observador>` sin acoplarse a las clases concretas.
* Uso natural de RAII: la destrucción de `std::shared_ptr` elimina automáticamente observadores que ya no se usan.

## Diagrama UML

![uml](uml/observer.png)

## Ejemplo genérico

```cpp
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <algorithm>

// ----------------------------------------
// Interfaz base del observador
// ----------------------------------------
class Observador {
public:
    virtual ~Observador() = default;
    virtual void actualizar(int nuevo_valor) = 0;
};

// ----------------------------------------
// Interfaz base del sujeto (observable)
// ----------------------------------------
class Sujeto {
public:
    virtual ~Sujeto() = default;

    virtual void adjuntar(const std::shared_ptr<Observador>& observador) = 0;
    virtual void desadjuntar(const std::shared_ptr<Observador>& observador) = 0;

protected:
    virtual void notificar(int nuevo_valor) = 0;
};

// ----------------------------------------
// Sujeto concreto
// ----------------------------------------
class SujetoConcreto : public Sujeto {
public:
    void establecer_valor(int valor) {
        if (valor_ != valor) {
            valor_ = valor;
            notificar(valor_);
        }
    }

    int obtener_valor() const {
        return valor_;
    }

    void adjuntar(const std::shared_ptr<Observador>& observador) override {
        observadores_.push_back(observador);
    }

    void desadjuntar(const std::shared_ptr<Observador>& observador) override {
        // Eliminamos el observador indicado y limpiamos los expirados
        observadores_.erase(
            std::remove_if(
                observadores_.begin(),
                observadores_.end(),
                [&observador](const std::weak_ptr<Observador>& debil) {
                    auto fuerte = debil.lock();
                    return !fuerte || fuerte == observador;
                }),
            observadores_.end()
        );
    }

protected:
    void notificar(int nuevo_valor) override {
        // Recorremos los observadores; si alguno ha expirado, lo limpiamos más tarde
        observadores_.erase(
            std::remove_if(
                observadores_.begin(),
                observadores_.end(),
                [nuevo_valor](std::weak_ptr<Observador>& debil) {
                    auto fuerte = debil.lock();
                    if (!fuerte) {
                        // Observador ya no existe: se elimina
                        return true;
                    }
                    fuerte->actualizar(nuevo_valor);
                    return false;
                }),
            observadores_.end()
        );
    }

private:
    int valor_{0};
    std::vector<std::weak_ptr<Observador>> observadores_;
};

// ----------------------------------------
// Observadores concretos
// ----------------------------------------
class ObservadorConcretoA : public Observador {
public:
    explicit ObservadorConcretoA(std::string nombre)
        : nombre_{std::move(nombre)} {}

    void actualizar(int nuevo_valor) override {
        std::cout << "[ObservadorConcretoA - " << nombre_
                  << "] Nuevo valor recibido: " << nuevo_valor << '\n';
    }

private:
    std::string nombre_;
};

class ObservadorConcretoB : public Observador {
public:
    explicit ObservadorConcretoB(std::string nombre)
        : nombre_{std::move(nombre)} {}

    void actualizar(int nuevo_valor) override {
        std::cout << "[ObservadorConcretoB - " << nombre_
                  << "] Procesando cambio de valor: " << nuevo_valor << '\n';
    }

private:
    std::string nombre_;
};

// ----------------------------------------
// Función cliente
// ----------------------------------------
void ejemplo_cliente() {
    auto sujeto = std::make_shared<SujetoConcreto>();

    auto observador1 = std::make_shared<ObservadorConcretoA>("A1");
    auto observador2 = std::make_shared<ObservadorConcretoB>("B1");

    sujeto->adjuntar(observador1);
    sujeto->adjuntar(observador2);

    std::cout << "Estableciendo valor = 10\n";
    sujeto->establecer_valor(10);

    std::cout << "Desadjuntando observador A1\n";
    sujeto->desadjuntar(observador1);

    std::cout << "Estableciendo valor = 20\n";
    sujeto->establecer_valor(20);
}

int main() {
    ejemplo_cliente();
    return 0;
}
```

## Puntos clave del ejemplo

* El **sujeto** (`SujetoConcreto`) mantiene una lista de observadores usando `std::weak_ptr`, evitando ciclos de referencia con los `std::shared_ptr` que se usan en el código cliente.
* La interfaz `Observador` define un método `actualizar(int nuevo_valor)` que representa la notificación de cambio; cada observador concreto decide cómo reaccionar.
* La interfaz `Sujeto` separa claramente la **gestión de suscriptores** (`adjuntar`, `desadjuntar`) de la **notificación** (`notificar`), reforzando el principio de responsabilidad única.
* El código cliente programa contra **interfaces** y usa `std::make_shared` para crear instancias, aprovechando RAII y evitando la gestión manual de memoria.
* Añadir un nuevo tipo de observador (por ejemplo, `ObservadorConcretoC`) solo requiere implementar la interfaz `Observador` y registrar instancias en el sujeto, sin modificar el código del sujeto ni del resto de observadores.
