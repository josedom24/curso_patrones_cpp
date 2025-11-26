# Ejemplo: Sistema de control remoto

## Introducción

Para ilustrar el patrón **Command** en un contexto realista, construiremos un pequeño **sistema de control remoto programable**.
El objetivo del sistema es permitir que el código cliente asigne acciones a botones del control remoto **sin conocer la lógica concreta que ejecuta cada acción**.

Dependiendo del comando que se asigne, el control remoto podrá:

* encender o apagar una **luz**,
* abrir o cerrar una **persiana**,
* activar o desactivar un **ventilador**,
* o realizar cualquier acción similar.

Cada comando es un objeto que encapsula:

1. la operación a realizar,
2. el receptor sobre el que actúa,
3. y los parámetros necesarios.

El código cliente solo trabaja con el invocador (`ControlRemoto`), que almacena comandos y ejecuta `ejecutar()`.
Los comandos concretos son los únicos que conocen los detalles del receptor.

A continuación se muestra el código completo dividido en:

* **Receptor.hpp** – dispositivos que realizan las acciones reales
* **Comandos.hpp** – comandos e interfaz
* **ControlRemoto.hpp** – invocador
* **main.cpp** – código cliente

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

## Comandos.hpp

```cpp
#pragma once
#include <memory>
#include "Receptor.hpp"

// ----------------------------------------
// Interfaz base del comando
// ----------------------------------------

class Comando {
public:
    virtual ~Comando() = default;
    virtual void ejecutar() const = 0;
};

// ----------------------------------------
// Comandos concretos para Luz
// ----------------------------------------

class ComandoEncenderLuz : public Comando {
private:
    Luz& luz_;

public:
    explicit ComandoEncenderLuz(Luz& luz) : luz_(luz) {}

    void ejecutar() const override {
        luz_.encender();
    }
};

class ComandoApagarLuz : public Comando {
private:
    Luz& luz_;

public:
    explicit ComandoApagarLuz(Luz& luz) : luz_(luz) {}

    void ejecutar() const override {
        luz_.apagar();
    }
};

// ----------------------------------------
// Comandos concretos para Persiana
// ----------------------------------------

class ComandoSubirPersiana : public Comando {
private:
    Persiana& persiana_;

public:
    explicit ComandoSubirPersiana(Persiana& p) : persiana_(p) {}

    void ejecutar() const override {
        persiana_.subir();
    }
};

class ComandoBajarPersiana : public Comando {
private:
    Persiana& persiana_;

public:
    explicit ComandoBajarPersiana(Persiana& p) : persiana_(p) {}

    void ejecutar() const override {
        persiana_.bajar();
    }
};
```

## ControlRemoto.hpp

```cpp
#pragma once
#include <memory>
#include <iostream>
#include "Comandos.hpp"

// ----------------------------------------
// Invocador: Control Remoto
// ----------------------------------------

class ControlRemoto {
private:
    std::unique_ptr<Comando> comando_;

public:
    void asignar_comando(std::unique_ptr<Comando> cmd) {
        comando_ = std::move(cmd);
    }

    void pulsar_boton() const {
        if (comando_) {
            comando_->ejecutar();
        } else {
            std::cout << "ControlRemoto: no hay comando asignado.\n";
        }
    }
};
```

## main.cpp

```cpp
#include "ControlRemoto.hpp"

int main() {
    Luz luz;
    Persiana persiana;

    ControlRemoto control;

    control.asignar_comando(std::make_unique<ComandoEncenderLuz>(luz));
    control.pulsar_boton();

    control.asignar_comando(std::make_unique<ComandoApagarLuz>(luz));
    control.pulsar_boton();

    control.asignar_comando(std::make_unique<ComandoSubirPersiana>(persiana));
    control.pulsar_boton();

    control.asignar_comando(std::make_unique<ComandoBajarPersiana>(persiana));
    control.pulsar_boton();

    return 0;
}
```

## Añadir un nuevo comando

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

### Añadir comandos concretos en `Comandos.hpp`

```cpp
class ComandoActivarVentilador : public Comando {
private:
    Ventilador& v_;

public:
    explicit ComandoActivarVentilador(Ventilador& v) : v_(v) {}

    void ejecutar() const override {
        v_.activar();
    }
};

class ComandoDesactivarVentilador : public Comando {
private:
    Ventilador& v_;

public:
    explicit ComandoDesactivarVentilador(Ventilador& v) : v_(v) {}

    void ejecutar() const override {
        v_.desactivar();
    }
};
```

### Usarlo en `main.cpp`

```cpp
Ventilador ventilador;

control.asignar_comando(std::make_unique<ComandoActivarVentilador>(ventilador));
control.pulsar_boton();

control.asignar_comando(std::make_unique<ComandoDesactivarVentilador>(ventilador));
control.pulsar_boton();
```

### Qué no hemos modificado

* No hemos cambiado `ControlRemoto.hpp`.
* No hemos cambiado `Comando`.
* No hemos cambiado ningún otro comando.

Solo añadimos nuevos comandos y los usamos.
