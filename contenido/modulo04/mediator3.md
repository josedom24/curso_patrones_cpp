# Ejemplo: Sistema de chat entre usuarios

## Introducción

Para ilustrar el patrón **Mediator** en un contexto realista, construiremos un pequeño sistema de comunicación tipo “chat” entre varios usuarios.
El objetivo es permitir que los usuarios puedan enviarse mensajes **sin conocerse directamente entre sí**, delegando toda la coordinación en un **Mediador** central.

El Mediador se encargará de:

* registrar usuarios,
* recibir los mensajes enviados por un usuario,
* reenviarlos a los destinatarios adecuados,
* decidir reglas de comunicación (por ejemplo, que todos reciban el mensaje, o solo ciertos usuarios).

Cada usuario es un **colega** del mediador: conoce al mediador, pero **no conoce a los demás usuarios**.
El código cliente configura el mediador, crea los usuarios y ejecuta la interacción.

El ejemplo se divide en:

* **Mediador.hpp** – interfaz del mediador y mediador concreto
* **Colegas.hpp** – clase base Colega y sus implementaciones
* **main.cpp** – código cliente


## Mediador.hpp

```cpp
#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// ----------------------------------------
// Interfaz del Mediador
// ----------------------------------------
class InterfazMediador {
public:
    virtual ~InterfazMediador() = default;
    virtual void notificar(const std::string& emisor,
                           const std::string& mensaje) = 0;
};

// ----------------------------------------
// Mediador Concreto
// ----------------------------------------
class MediadorConcreto : public InterfazMediador {
public:
    void registrar_usuario(const std::shared_ptr<class Usuario>& usuario) {
        usuarios_.push_back(usuario);
    }

    void notificar(const std::string& emisor,
                   const std::string& mensaje) override
    {
        std::cout << "[Mediador] " << emisor << " envía mensaje: " << mensaje << "\n";

        for (auto& u : usuarios_) {
            u->recibir(emisor, mensaje);
        }
    }

private:
    std::vector<std::shared_ptr<class Usuario>> usuarios_;
};
```


## Colegas.hpp

```cpp
#pragma once
#include "Mediador.hpp"
#include <iostream>
#include <memory>
#include <string>

// ----------------------------------------
// Clase base: Colega (Usuario)
// ----------------------------------------
class Usuario {
public:
    virtual ~Usuario() = default;

    void establecer_mediador(std::weak_ptr<InterfazMediador> mediador) {
        mediador_ = mediador;
    }

    void enviar(const std::string& mensaje) {
        if (auto m = mediador_.lock()) {
            m->notificar(nombre(), mensaje);
        }
    }

    virtual void recibir(const std::string& emisor,
                         const std::string& mensaje) = 0;

protected:
    virtual std::string nombre() const = 0;

private:
    std::weak_ptr<InterfazMediador> mediador_;
};

// ----------------------------------------
// Usuario Concreto A
// ----------------------------------------
class UsuarioRegular : public Usuario {
public:
    explicit UsuarioRegular(std::string id)
        : id_(std::move(id)) {}

    void recibir(const std::string& emisor,
                 const std::string& mensaje) override
    {
        if (emisor != id_) {
            std::cout << "[" << id_ << "] recibe: " << mensaje
                      << " (de " << emisor << ")\n";
        }
    }

protected:
    std::string nombre() const override {
        return id_;
    }

private:
    std::string id_;
};

// ----------------------------------------
// Usuario Administrador
// ----------------------------------------
class UsuarioAdministrador : public Usuario {
public:
    explicit UsuarioAdministrador(std::string id)
        : id_(std::move(id)) {}

    void recibir(const std::string& emisor,
                 const std::string& mensaje) override
    {
        if (emisor != id_) {
            std::cout << "[ADMIN " << id_ << "] recibe: " << mensaje
                      << " (de " << emisor << ")\n";
        }
    }

protected:
    std::string nombre() const override {
        return id_;
    }

private:
    std::string id_;
};
```


## main.cpp

```cpp
#include "Mediador.hpp"
#include "Colegas.hpp"

int main() {
    auto mediador = std::make_shared<MediadorConcreto>();

    auto usuario1 = std::make_shared<UsuarioRegular>("Usuario1");
    auto usuario2 = std::make_shared<UsuarioRegular>("Usuario2");
    auto admin    = std::make_shared<UsuarioAdministrador>("Admin");

    usuario1->establecer_mediador(mediador);
    usuario2->establecer_mediador(mediador);
    admin->establecer_mediador(mediador);

    mediador->registrar_usuario(usuario1);
    mediador->registrar_usuario(usuario2);
    mediador->registrar_usuario(admin);

    usuario1->enviar("Hola a todos!");
    usuario2->enviar("Saludos!");
    admin->enviar("Recordad las normas.");

    return 0;
}
```


## Añadir un nuevo tipo de Usuario

**Para añadir un nuevo usuario no modificamos las clases base**, solo añadimos una nueva clase y, como mucho, una línea en `main.cpp`.

Por ejemplo: `UsuarioPremium`.

### En `Colegas.hpp`

```cpp
class UsuarioPremium : public Usuario {
public:
    explicit UsuarioPremium(std::string id)
        : id_(std::move(id)) {}

    void recibir(const std::string& emisor,
                 const std::string& mensaje) override
    {
        if (emisor != id_) {
            std::cout << "[Premium " << id_ << "] recibe mensaje PRIORITARIO: "
                      << mensaje << " (de " << emisor << ")\n";
        }
    }

protected:
    std::string nombre() const override {
        return id_;
    }

private:
    std::string id_;
};
```

### En `main.cpp`

```cpp
auto premium = std::make_shared<UsuarioPremium>("Premium1");
premium->establecer_mediador(mediador);
mediador->registrar_usuario(premium);

premium->enviar("Hola, soy usuario premium.");
```

## Qué no hemos modificado

* No hemos modificado la interfaz `InterfazMediador`.
* No hemos modificado la clase abstracta `Usuario`.
* No hemos modificado las clases `UsuarioRegular` ni `UsuarioAdministrador`.

Solo hemos:

1. añadido un **nuevo colega concreto** (`UsuarioPremium`),
2. registrado el nuevo colega en el mediador,
3. y opcionalmente una línea en `main.cpp` para usarlo.


