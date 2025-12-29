# Ejemplo: Estados de un reproductor multimedia

## Introducción

Para ilustrar el patrón **State** en un contexto realista, se construye un pequeño sistema que modela el **comportamiento de un reproductor multimedia**.
Un reproductor puede encontrarse en distintos estados y **cada estado determina cómo responde a las acciones del usuario**:

* **Detenido**: el reproductor no está reproduciendo contenido.
* **Reproduciendo**: el contenido se está reproduciendo.
* **Pausado**: la reproducción está temporalmente detenida.

El objeto `Reproductor` actúa como **Contexto** y delega su comportamiento en objetos que representan cada estado concreto.
El código cliente interactúa únicamente con `Reproductor`; el cambio de comportamiento se produce automáticamente al cambiar el estado interno.

El ejemplo se organiza en:

* **EstadoReproductor.hpp** – interfaz común del estado
* **Reproductor.hpp / Reproductor.cpp** – contexto
* **Estados.cpp** – implementación de los estados concretos
* **main.cpp** – código cliente


## EstadoReproductor.hpp

```cpp
#pragma once

// Declaración anticipada
class Reproductor;

// ----------------------------------------
// Interfaz base del estado
// ----------------------------------------
class EstadoReproductor {
public:
    virtual ~EstadoReproductor() = default;

    virtual void play(Reproductor&) = 0;
    virtual void pause(Reproductor&) = 0;
    virtual void stop(Reproductor&) = 0;
};
```


## Reproductor.hpp

```cpp
#pragma once
#include <memory>
#include "EstadoReproductor.hpp"

// ----------------------------------------
// Contexto
// ----------------------------------------
class Reproductor {
public:
    Reproductor();

    void cambiar_estado(std::unique_ptr<EstadoReproductor> nuevoEstado);

    void play();
    void pause();
    void stop();

private:
    std::unique_ptr<EstadoReproductor> estado_;
};
```


## Reproductor.cpp

```cpp
#include "Reproductor.hpp"
#include "Estados.hpp"

Reproductor::Reproductor()
    : estado_(std::make_unique<EstadoDetenido>()) {}

void Reproductor::cambiar_estado(std::unique_ptr<EstadoReproductor> nuevoEstado) {
    estado_ = std::move(nuevoEstado);
}

void Reproductor::play() {
    estado_->play(*this);
}

void Reproductor::pause() {
    estado_->pause(*this);
}

void Reproductor::stop() {
    estado_->stop(*this);
}
```


## Estados.hpp

```cpp
#pragma once
#include "EstadoReproductor.hpp"

// Declaraciones anticipadas
class EstadoDetenido;
class EstadoReproduciendo;
class EstadoPausado;

// ----------------------------------------
// Estados concretos
// ----------------------------------------
class EstadoDetenido : public EstadoReproductor {
public:
    void play(Reproductor&) override;
    void pause(Reproductor&) override;
    void stop(Reproductor&) override;
};

class EstadoReproduciendo : public EstadoReproductor {
public:
    void play(Reproductor&) override;
    void pause(Reproductor&) override;
    void stop(Reproductor&) override;
};

class EstadoPausado : public EstadoReproductor {
public:
    void play(Reproductor&) override;
    void pause(Reproductor&) override;
    void stop(Reproductor&) override;
};
```


## Estados.cpp

```cpp
#include <iostream>
#include <memory>
#include "Estados.hpp"
#include "Reproductor.hpp"

// ----------------------------------------
// EstadoDetenido
// ----------------------------------------
void EstadoDetenido::play(Reproductor& r) {
    std::cout << "[Detenido] Iniciando reproducción.\n";
    r.cambiar_estado(std::make_unique<EstadoReproduciendo>());
}

void EstadoDetenido::pause(Reproductor&) {
    std::cout << "[Detenido] No se puede pausar.\n";
}

void EstadoDetenido::stop(Reproductor&) {
    std::cout << "[Detenido] Ya está detenido.\n";
}

// ----------------------------------------
// EstadoReproduciendo
// ----------------------------------------
void EstadoReproduciendo::play(Reproductor&) {
    std::cout << "[Reproduciendo] Ya se está reproduciendo.\n";
}

void EstadoReproduciendo::pause(Reproductor& r) {
    std::cout << "[Reproduciendo] Pausando reproducción.\n";
    r.cambiar_estado(std::make_unique<EstadoPausado>());
}

void EstadoReproduciendo::stop(Reproductor& r) {
    std::cout << "[Reproduciendo] Deteniendo reproducción.\n";
    r.cambiar_estado(std::make_unique<EstadoDetenido>());
}

// ----------------------------------------
// EstadoPausado
// ----------------------------------------
void EstadoPausado::play(Reproductor& r) {
    std::cout << "[Pausado] Reanudando reproducción.\n";
    r.cambiar_estado(std::make_unique<EstadoReproduciendo>());
}

void EstadoPausado::pause(Reproductor&) {
    std::cout << "[Pausado] Ya está en pausa.\n";
}

void EstadoPausado::stop(Reproductor& r) {
    std::cout << "[Pausado] Deteniendo reproducción.\n";
    r.cambiar_estado(std::make_unique<EstadoDetenido>());
}
```


## main.cpp

```cpp
#include "Reproductor.hpp"

int main() {
    Reproductor r;

    r.play();   // Detenido → Reproduciendo
    r.pause(); // Reproduciendo → Pausado
    r.play();  // Pausado → Reproduciendo
    r.stop();  // Reproduciendo → Detenido

    return 0;
}
```

Recuerda que debemos realizar la compilación de la siguiente manera:

```bash
g++ main.cpp Reproductor.cpp Estados.cpp -o reproductor
```

## Añadir un nuevo estado

Como en la versión actual **los estados se definen con sus métodos dentro de la clase**, basta con añadir una nueva clase que implemente la interfaz `EstadoReproductor`.

### Nuevo estado: `EstadoSinContenido`

```cpp
class EstadoSinContenido : public EstadoReproductor {
public:
    void play(Reproductor&) override {
        std::cout << "[Sin contenido] No hay contenido para reproducir.\n";
    }

    void pause(Reproductor&) override {
        std::cout << "[Sin contenido] No se puede pausar.\n";
    }

    void stop(Reproductor&) override {
        std::cout << "[Sin contenido] El reproductor está inactivo.\n";
    }
};
```

No es necesario modificar la interfaz `EstadoReproductor`, ya que el nuevo estado **se adapta a las operaciones ya definidas**.

### Activar el nuevo estado desde otro estado

Por ejemplo, desde `EstadoDetenido`:

```cpp
class EstadoDetenido : public EstadoReproductor {
public:
    void play(Reproductor& r) override {
        std::cout << "[Detenido] No hay contenido cargado.\n";
        r.cambiar_estado(std::make_unique<EstadoSinContenido>());
    }

    void pause(Reproductor&) override {
        std::cout << "[Detenido] No se puede pausar.\n";
    }

    void stop(Reproductor&) override {
        std::cout << "[Detenido] Ya está detenido.\n";
    }
};
```

La transición queda encapsulada en el propio estado, sin condicionales externos ni lógica adicional en el contexto.

### Qué no hemos modificado

Es importante destacar que **la incorporación del nuevo estado no ha requerido cambios en**:

* la interfaz `EstadoReproductor`,
* la clase `Reproductor`,
* el código cliente (`main.cpp`).

Solo hemos:

1. añadido un **nuevo estado concreto**,
2. definido su comportamiento específico,
3. incorporado una **nueva transición** desde un estado existente.

