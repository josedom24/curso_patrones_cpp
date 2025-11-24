# Ejemplo: Sistema de notificaciones

# Introducción

Para ilustrar el patrón **Decorator** en un contexto realista, construiremos un pequeño **sistema de notificaciones**.

El objetivo es permitir que un mensaje básico pueda ser enviado a través de diferentes canales **sin modificar la clase original**, y además que un mismo mensaje pueda pasar por **varias capas adicionales** de comportamiento, como:

* enviar la notificación por **email**,
* enviar un **SMS**,
* registrar la acción en un **log**,
* enviar una notificación **push**,
* o cualquier otra extensión futura.

Cada decorador representa una responsabilidad adicional y **extiende** el comportamiento de la notificación base.
El código cliente solo interactúa con la interfaz común `Notificador`, sin preocuparse de cómo está construido el “pipeline” de decoradores.

A continuación se muestra el código completo dividido en:

* **Notificaciones.hpp** – interfaz base, componente concreto y decoradores
* **main.cpp** – código cliente y construcción dinámica de decoradores

## Notificaciones.hpp

```cpp
#pragma once
#include <iostream>
#include <memory>
#include <string>

// ----------------------------------------
// Interfaz base del componente
// ----------------------------------------
class Notificador {
public:
    virtual ~Notificador() = default;
    virtual void enviar(const std::string& mensaje) const = 0;
};

// ----------------------------------------
// Componente concreto: Notificación básica
// ----------------------------------------
class NotificadorBase : public Notificador {
public:
    void enviar(const std::string& mensaje) const override {
        std::cout << "[Base] Enviando mensaje: " << mensaje << "\n";
    }
};

// ----------------------------------------
// Clase base del decorador
// ----------------------------------------
class DecoradorNotificador : public Notificador {
protected:
    std::unique_ptr<Notificador> componente_;

public:
    explicit DecoradorNotificador(std::unique_ptr<Notificador> componente)
        : componente_(std::move(componente)) {}

    void enviar(const std::string& mensaje) const override {
        componente_->enviar(mensaje);
    }
};

// ----------------------------------------
// Decorador concreto: Notificación por Email
// ----------------------------------------
class NotificadorEmail : public DecoradorNotificador {
public:
    explicit NotificadorEmail(std::unique_ptr<Notificador> componente)
        : DecoradorNotificador(std::move(componente)) {}

    void enviar(const std::string& mensaje) const override {
        std::cout << "[Email] Enviando email con mensaje: " 
                  << mensaje << "\n";
        DecoradorNotificador::enviar(mensaje);
    }
};

// ----------------------------------------
// Decorador concreto: Notificación por SMS
// ----------------------------------------
class NotificadorSMS : public DecoradorNotificador {
public:
    explicit NotificadorSMS(std::unique_ptr<Notificador> componente)
        : DecoradorNotificador(std::move(componente)) {}

    void enviar(const std::string& mensaje) const override {
        std::cout << "[SMS] Enviando SMS: " << mensaje << "\n";
        DecoradorNotificador::enviar(mensaje);
    }
};

// ----------------------------------------
// Decorador concreto: Registro en Log
// ----------------------------------------
class NotificadorLog : public DecoradorNotificador {
public:
    explicit NotificadorLog(std::unique_ptr<Notificador> componente)
        : DecoradorNotificador(std::move(componente)) {}

    void enviar(const std::string& mensaje) const override {
        std::cout << "[Log] Registrando evento: " << mensaje << "\n";
        DecoradorNotificador::enviar(mensaje);
    }
};
```

## main.cpp

```cpp
#include "Notificaciones.hpp"

int main() {
    // Notificación básica
    std::unique_ptr<Notificador> notificador =
        std::make_unique<NotificadorBase>();

    // Añadimos decoradores dinámicamente
    notificador = std::make_unique<NotificadorEmail>(std::move(notificador));
    notificador = std::make_unique<NotificadorSMS>(std::move(notificador));
    notificador = std::make_unique<NotificadorLog>(std::move(notificador));

    // Envío final: pasa por todas las capas
    notificador->enviar("Bienvenido al sistema Decorator");

    return 0;
}
```

# Añadir un nuevo decorador

Una de las mayores ventajas del patrón **Decorator** es que permite añadir nueva funcionalidad **sin modificar ninguna clase existente**.

Supongamos que queremos añadir un nuevo decorador: **notificación Push**.

## Añadir el nuevo decorador en `Notificaciones.hpp`

```cpp
// Decorador concreto: Notificación Push
class NotificadorPush : public DecoradorNotificador {
public:
    explicit NotificadorPush(std::unique_ptr<Notificador> componente)
        : DecoradorNotificador(std::move(componente)) {}

    void enviar(const std::string& mensaje) const override {
        std::cout << "[Push] Enviando notificación push: "
                  << mensaje << "\n";
        DecoradorNotificador::enviar(mensaje);
    }
};
```

## Usarlo en `main.cpp`

```cpp
notificador = std::make_unique<NotificadorPush>(std::move(notificador));
```

## Qué no hemos modificado

* La interfaz `Notificador`.
* La clase base decoradora `DecoradorNotificador`.
* El componente concreto `NotificadorBase`.
* El cliente no necesita cambiar su forma de trabajar.
