# Ejemplo: Sistema de control remoto

## Introducción

Para ilustrar el patrón **Command** desde una perspectiva moderna en C++, construiremos un pequeño **sistema de control remoto programable**.
El objetivo es permitir que el código cliente asigne acciones a los botones del control remoto **inyectando directamente el comportamiento**, sin necesidad de clases de comando ni jerarquías complejas.

Cada botón del control remoto recibirá una **función invocable** —por ejemplo, una *lambda*— que encapsula:

1. la operación a realizar,
2. el dispositivo sobre el que actúa,
3. y los parámetros necesarios.

El control remoto simplemente almacena y ejecuta estas funciones.
Los dispositivos (luz, persiana, ventilador, etc.) proporcionan los métodos reales que operan sobre el hardware simulado.

La técnica de inyección de comportamiento utilizada será: Inyección directa mediante funciones invocables (`std::function<void()>`) y lambdas con captura.

A continuación se muestra el código completo dividido en:

* **Receptor.hpp** – dispositivos que realizan las acciones reales
* **ControlRemoto.hpp** – invocador que almacena funciones
* **main.cpp** – código cliente que inyecta el comportamiento

## Receptor.hpp

```cpp
#pragma once
#include <iostream>

// ----------------------------------------
// Receptor: dispositivos reales
// ----------------------------------------

class Luz {
public:
    void encender() const {
        std::cout << "Luz: encendida\n";
    }
    void apagar() const {
        std::cout << "Luz: apagada\n";
    }
};

class Persiana {
public:
    void subir() const {
        std::cout << "Persiana: subida\n";
    }
    void bajar() const {
        std::cout << "Persiana: bajada\n";
    }
};
```

## ControlRemoto.hpp

```cpp
#pragma once
#include <functional>
#include <iostream>

// ----------------------------------------
// Invocador moderno: almacena comportamientos
// ----------------------------------------

class ControlRemoto {
private:
    std::function<void()> accion_;

public:
    void asignar_accion(std::function<void()> f) {
        accion_ = std::move(f);
    }

    void pulsar_boton() const {
        if (accion_) {
            accion_();
        } else {
            std::cout << "ControlRemoto: no hay acción asignada.\n";
        }
    }
};
```

## main.cpp

```cpp
#include "ControlRemoto.hpp"
#include "Receptor.hpp"

int main() {
    Luz luz;
    Persiana persiana;

    ControlRemoto control;

    // Encender luz
    control.asignar_accion([&]() { luz.encender(); });
    control.pulsar_boton();

    // Apagar luz
    control.asignar_accion([&]() { luz.apagar(); });
    control.pulsar_boton();

    // Subir persiana
    control.asignar_accion([&]() { persiana.subir(); });
    control.pulsar_boton();

    // Bajar persiana
    control.asignar_accion([&]() { persiana.bajar(); });
    control.pulsar_boton();

    return 0;
}
```

## Añadir un nuevo "comando"

Supongamos que queremos añadir un nuevo dispositivo: **Ventilador**.

### Añadir el receptor en `Receptor.hpp`

```cpp
class Ventilador {
public:
    void activar() const {
        std::cout << "Ventilador: activado\n";
    }
    void desactivar() const {
        std::cout << "Ventilador: desactivado\n";
    }
};
```

### Usarlo en `main.cpp`

```cpp
Ventilador ventilador;

control.asignar_accion([&]() { ventilador.activar(); });
control.pulsar_boton();

control.asignar_accion([&]() { ventilador.desactivar(); });
control.pulsar_boton();
```

### Qué no hemos modificado

* No hemos cambiado **ControlRemoto.hpp**.
* No hemos añadido **nuevas clases de comando**.
* No hemos definido **interfaces** ni **herencias**.

Solo hemos creado un nuevo receptor y lo hemos combinado con una lambda.
