# Implementación de Observer con C++

## Estructura general

La implementación del **Observer** en C++ moderno permite **definir una dependencia uno-a-muchos** entre objetos, de modo que cuando el estado de un sujeto cambia, todos sus observadores son notificados automáticamente. El sujeto no conoce los detalles concretos de los observadores, solo que cumplen una interfaz común.

Este enfoque desacopla la fuente de los cambios de las reacciones a dichos cambios y facilita añadir o eliminar observadores sin modificar el sujeto.

## Elementos de C++ moderno utilizados

* **Clases abstractas e interfaces puras** para definir los contratos de sujeto y observador.
* **Métodos virtuales y virtuales puros** para permitir notificación polimórfica.
* **Polimorfismo dinámico** para tratar observadores de forma uniforme.
* **Destructores virtuales** para destrucción segura mediante punteros a la interfaz.
* **`std::shared_ptr`** para gestionar la propiedad compartida de los observadores.
* **`std::weak_ptr`** para evitar ciclos de referencia entre sujeto y observadores.
* **RAII** para la gestión automática del ciclo de vida.
* **Contenedores de la STL** como `std::vector` para almacenar observadores.
* Algoritmos de la STL como **`std::remove_if`** para limpiar observadores caducados.

## Componentes del patrón y responsabilidades

### 1. Interfaz base del **Observador**

* Define la operación que el sujeto utilizará para notificar cambios.
* Establece un contrato común para todos los observadores.
* Permite implementar reacciones heterogéneas ante un mismo evento.
* Se utiliza de forma polimórfica mediante punteros inteligentes.

### 2. Interfaz base del **Sujeto (Observable)**

* Declara las operaciones de suscripción y desuscripción de observadores.
* Define el mecanismo de notificación de cambios.
* Mantiene una colección de observadores registrados.
* No conoce las implementaciones concretas de los observadores.

### 3. **Sujetos concretos**

* Implementan la lógica específica del dominio.
* Mantienen el estado que será observado.
* Notifican a los observadores cuando el estado cambia.
* Gestionan internamente la lista de observadores de forma segura.

### 4. **Observadores concretos**

* Implementan la reacción ante las notificaciones del sujeto.
* Interpretan los cambios según sus propias responsabilidades.
* Mantienen su propio estado interno de forma encapsulada.
* No modifican directamente el estado del sujeto.

### 5. **Código cliente**

* Crea el sujeto y los observadores concretos.
* Registra y desregistra observadores en el sujeto.
* No conoce los detalles internos de la notificación.
* Se beneficia de la gestión automática de recursos mediante RAII.

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
