# Ejemplo: Sistema de control remoto

## Introducción

Para ilustrar el patrón **Command** desde una perspectiva moderna en C++, construiremos un pequeño **sistema de control remoto programable**.
El objetivo es permitir que el código cliente asigne acciones a los botones del control remoto **inyectando directamente el comportamiento**, sin necesidad de clases de comando ni jerarquías complejas.

Cada botón del control remoto recibirá una **función invocable**, por ejemplo, una *lambda*, que encapsula:

* La operación a realizar.
* El dispositivo sobre el que actúa.
* Los parámetros necesarios.

El control remoto simplemente almacena y ejecuta estas funciones.
Los dispositivos (luz, persiana, ventilador, etc.) proporcionan los métodos reales que operan sobre el hardware simulado.

La técnica de inyección de comportamiento utilizada será: **inyección directa mediante funciones invocables (`std::function<void()>`) y lambdas con captura**.

A continuación se muestra el código completo dividido en:

* **Receptor.hpp**: dispositivos que realizan las acciones reales.
* **ControlRemoto.hpp**: invocador que almacena funciones.
* **main.cpp**: código cliente que inyecta el comportamiento.


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
#include <utility>

// ----------------------------------------
// Invocador moderno: almacena comportamientos
// ----------------------------------------

class ControlRemoto {
private:
    std::function<void()> boton1_;
    std::function<void()> boton2_;

public:
    void asignar_boton1(std::function<void()> f) {
        boton1_ = std::move(f);
    }

    void asignar_boton2(std::function<void()> f) {
        boton2_ = std::move(f);
    }

    void pulsar_boton1() const {
        if (boton1_) {
            boton1_();
        } else {
            std::cout << "Botón 1: sin acción asignada.\n";
        }
    }

    void pulsar_boton2() const {
        if (boton2_) {
            boton2_();
        } else {
            std::cout << "Botón 2: sin acción asignada.\n";
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

    // ----------------------------
    // Configuración inicial
    // ----------------------------

    control.asignar_boton1([&]() { luz.encender(); });
    control.asignar_boton2([&]() { persiana.subir(); });

    control.pulsar_boton1(); // Luz encendida
    control.pulsar_boton2(); // Persiana subida

    // ----------------------------
    // Reconfiguración dinámica
    // ----------------------------

    control.asignar_boton1([&]() { luz.apagar(); });
    control.asignar_boton2([&]() { persiana.bajar(); });

    control.pulsar_boton1(); // Luz apagada
    control.pulsar_boton2(); // Persiana bajada

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

control.asignar_boton1([&]() { ventilador.activar(); });
control.asignar_boton2([&]() { ventilador.desactivar(); });

control.pulsar_boton1();
control.pulsar_boton2();
```


## Qué no hemos modificado

* No hemos cambiado **ControlRemoto.hpp**.
* No hemos añadido **nuevas clases de comando**.
* No hemos definido **interfaces** ni **herencias**.

Solo hemos creado un nuevo receptor y lo hemos combinado con una lambda.
