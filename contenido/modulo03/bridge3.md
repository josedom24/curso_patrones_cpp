# Ejemplo: Sistema de notificaciones con múltiples canales

## Introducción

Para ilustrar el patrón **Bridge** en un escenario realista, construiremos un pequeño sistema de **notificaciones**.

El objetivo es permitir que el código cliente envíe notificaciones **sin depender del canal de envío**, y al mismo tiempo poder crear diferentes **tipos de notificación** (alerta, aviso, reporte, etc.) sin acoplarlos a un medio concreto.

En este ejemplo separamos:

* la **abstracción**: el tipo de notificación que quiere enviar el cliente
* la **implementación**: el canal concreto mediante el cual se envía el mensaje

Los canales disponibles serán:

* **Canal Email**
* **Canal SMS**

Mientras que los tipos de notificación serán:

* `NotificacionAlerta`
* `NotificacionRecordatorio`

Gracias al patrón Bridge podremos combinar libremente:

* `NotificacionAlerta` por **Email**
* `NotificacionAlerta` por **SMS**
* `NotificacionRecordatorio` por **Email**
* `NotificacionRecordatorio` por **SMS**

sin crear jerarquías rígidas del tipo `AlertaEmail`, `AlertaSMS`, `RecordatorioEmail`, etc.

A continuación se muestra el código completo dividido en:

* **Canales.hpp** – implementación (Implementor)
* **Notificaciones.hpp** – abstracción y extensiones (Abstraction)
* **main.cpp** – código cliente

## Canales.hpp

```cpp
#pragma once
#include <iostream>
#include <memory>
#include <string>

// ----------------------------------------
// Implementador: interfaz del canal
// ----------------------------------------

class CanalNotificacion {
public:
    virtual ~CanalNotificacion() = default;

    virtual void enviar(const std::string& mensaje) const = 0;
};


// ----------------------------------------
// Implementador concreto: EMAIL
// ----------------------------------------

class CanalEmail : public CanalNotificacion {
public:
    void enviar(const std::string& mensaje) const override {
        std::cout << "[EMAIL] Enviando mensaje: " << mensaje << "\n";
    }
};


// ----------------------------------------
// Implementador concreto: SMS
// ----------------------------------------

class CanalSMS : public CanalNotificacion {
public:
    void enviar(const std::string& mensaje) const override {
        std::cout << "[SMS] Enviando mensaje corto: " << mensaje << "\n";
    }
};
```

## Notificaciones.hpp

```cpp
#pragma once
#include <memory>
#include <string>
#include "Canales.hpp"

// ----------------------------------------
// Abstracción: Notificación
// ----------------------------------------

class Notificacion {
protected:
    std::unique_ptr<CanalNotificacion> canal_;  // El "bridge"

public:
    explicit Notificacion(std::unique_ptr<CanalNotificacion> canal)
        : canal_(std::move(canal)) {}

    virtual ~Notificacion() = default;

    // Permite cambiar el canal en tiempo de ejecución si es necesario
    void cambiar_canal(std::unique_ptr<CanalNotificacion> nuevo_canal) {
        canal_ = std::move(nuevo_canal);
    }

    // Método de alto nivel que delega en la implementación
    virtual void enviar(const std::string& texto) const = 0;
};


// ----------------------------------------
// Abstracción refinada: Alerta
// ----------------------------------------

class NotificacionAlerta : public Notificacion {
public:
    using Notificacion::Notificacion;

    void enviar(const std::string& texto) const override {
        std::string mensaje = "[ALERTA] " + texto;
        canal_->enviar(mensaje);
    }
};


// ----------------------------------------
// Abstracción refinada: Recordatorio
// ----------------------------------------

class NotificacionRecordatorio : public Notificacion {
public:
    using Notificacion::Notificacion;

    void enviar(const std::string& texto) const override {
        std::string mensaje = "[RECORDATORIO] " + texto;
        canal_->enviar(mensaje);
    }
};
```

## main.cpp

```cpp
#include "Notificaciones.hpp"

void cliente(Notificacion& notif) {
    notif.enviar("Revisar el sistema de seguridad.");
}

int main() {
    // Notificación de alerta por EMAIL
    NotificacionAlerta alerta{
        std::make_unique<CanalEmail>()
    };
    cliente(alerta);

    // Notificación de recordatorio por SMS
    NotificacionRecordatorio recordatorio{
        std::make_unique<CanalSMS>()
    };
    cliente(recordatorio);

    // Cambiar canal en tiempo de ejecución
    recordatorio.cambiar_canal(std::make_unique<CanalEmail>());
    recordatorio.enviar("Reunión mañana a las 10.");

    return 0;
}
```

## Añadir un nuevo canal de envío

**Para añadir un nuevo canal solo hay que crear un nuevo implementador concreto.
No se modifica ninguna abstracción existente.**

Supongamos que añadimos un canal de **notificaciones push**.

### En `Canales.hpp`:

```cpp
// ----------------------------------------
// Implementador concreto: PUSH
// ----------------------------------------

class CanalPush : public CanalNotificacion {
public:
    void enviar(const std::string& mensaje) const override {
        std::cout << "[PUSH] Notificación enviada: " << mensaje << "\n";
    }
};
```

### Usar el nuevo canal en `main.cpp`

```cpp
NotificacionAlerta alertaPush{
    std::make_unique<CanalPush>()
};
alertaPush.enviar("Servidor reiniciado.");
```

### Qué no hemos modificado

* La interfaz `CanalNotificacion`
* La clase `Notificacion`
* Las abstracciones refinadas existentes
* El cliente

Solo hemos añadido:

1. un **nuevo canal** (`CanalPush`)
2. y opcionalmente una línea en `main.cpp` para usarlo

