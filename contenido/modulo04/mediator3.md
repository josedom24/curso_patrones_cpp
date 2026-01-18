# Ejemplo: Sistema de chat entre usuarios

## Introducción

Para ilustrar el patrón **Mediator** en un contexto realista, construiremos un pequeño sistema de comunicación tipo *chat* entre varios usuarios.
El objetivo es permitir que los usuarios puedan enviarse mensajes **sin conocerse directamente entre sí**, delegando toda la coordinación de la comunicación en un **mediador central**.

El mediador se encarga de:

* registrar a los usuarios participantes,
* recibir los mensajes enviados por un usuario,
* reenviarlos a los destinatarios adecuados,
* aplicar las reglas de comunicación.

En este ejemplo, el mediador implementa un modelo de **difusión (*broadcast*)**, reenviando cada mensaje a todos los usuarios registrados excepto al emisor. Este comportamiento es una decisión de diseño concreta del ejemplo; el patrón *Mediator* permite aplicar reglas de enrutamiento más complejas si fuera necesario.

Cada usuario es un **colega** del mediador: conoce al mediador, pero **no conoce a los demás usuarios**.
El código cliente configura el mediador, crea los usuarios y ejecuta la interacción.

Como contrapartida, este patrón puede llevar a que el mediador concentre demasiada lógica y **crezca en complejidad** si no se diseña con cuidado, convirtiéndose en un punto difícil de mantener.

El ejemplo se divide en:

* **Mediador.hpp** – interfaz del mediador y mediador concreto
* **Colegas.hpp** – interfaz del usuario, clase base y usuarios concretos
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
// Interfaz mínima del Colega
// ----------------------------------------
class InterfazUsuario {
public:
    virtual ~InterfazUsuario() = default;

    virtual std::string nombre() const = 0;
    virtual void recibir(const std::string& emisor,
                         const std::string& mensaje) = 0;
};

// ----------------------------------------
// Mediador Concreto
// ----------------------------------------
class MediadorConcreto : public InterfazMediador {
public:
    void registrar_usuario(const std::shared_ptr<InterfazUsuario>& usuario) {
        usuarios_.push_back(usuario);
    }

    void notificar(const std::string& emisor,
                   const std::string& mensaje) override
    {
        std::cout << "[Mediador] " << emisor
                  << " envía mensaje: " << mensaje << "\n";

        for (auto& u : usuarios_) {
            if (u && u->nombre() != emisor) {
                u->recibir(emisor, mensaje);
            }
        }
    }

private:
    std::vector<std::shared_ptr<InterfazUsuario>> usuarios_;
};
```


## Colegas.hpp

```cpp
#pragma once
#include "Mediador.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <utility>

// ----------------------------------------
// Clase base: Usuario (Colega)
// ----------------------------------------
class Usuario : public InterfazUsuario {
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

private:
    std::weak_ptr<InterfazMediador> mediador_;
};

// ----------------------------------------
// Usuario Regular
// ----------------------------------------
class UsuarioRegular : public Usuario {
public:
    explicit UsuarioRegular(std::string id)
        : id_(std::move(id)) {}

    std::string nombre() const override {
        return id_;
    }

    void recibir(const std::string& emisor,
                 const std::string& mensaje) override
    {
        std::cout << "[" << id_ << "] recibe: "
                  << mensaje << " (de " << emisor << ")\n";
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

    std::string nombre() const override {
        return id_;
    }

    void recibir(const std::string& emisor,
                 const std::string& mensaje) override
    {
        std::cout << "[ADMIN " << id_ << "] recibe: "
                  << mensaje << " (de " << emisor << ")\n";
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

Para añadir un nuevo tipo de usuario **no es necesario modificar la interfaz del mediador**, ni los usuarios existentes.
La interfaz `InterfazMediador` **permanece estable**, y la extensión se realiza únicamente añadiendo un nuevo colega concreto.

### En `Colegas.hpp`

```cpp
// ----------------------------------------
// Usuario Premium
// ----------------------------------------
class UsuarioPremium : public Usuario {
public:
    explicit UsuarioPremium(std::string id)
        : id_(std::move(id)) {}

    std::string nombre() const override {
        return id_;
    }

    void recibir(const std::string& emisor,
                 const std::string& mensaje) override
    {
        std::cout << "[Premium " << id_
                  << "] recibe mensaje PRIORITARIO: "
                  << mensaje << " (de " << emisor << ")\n";
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

* La **interfaz `InterfazMediador` permanece estable**
* No se ha modificado la clase base `Usuario`
* No se han modificado los usuarios existentes

Solo se ha:

1. añadido un **nuevo colega concreto** (`UsuarioPremium`)
2. mantenido la coordinación completamente centralizada en el mediador
3. conservado el ejemplo **simple, extensible y autocontenido**

