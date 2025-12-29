# Ejemplo: Sistema de validación de solicitudes

## Introducción

Para ilustrar el patrón **Chain of Responsibility** en un contexto práctico, construiremos un pequeño **sistema de validación**.
El objetivo es permitir que una solicitud pase por una cadena de validadores independientes, donde **cada uno puede aprobarla, rechazarla o delegarla al siguiente**.

La cadena de validación estará compuesta por:

* un validador de **autenticación**,
* un validador de **permisos**,
* un validador de **formato**,
* y cualquier otro que deseemos añadir en el futuro.

Cada validador es un manejador concreto que implementa la interfaz común `Manejador`.
El código cliente solo conoce el primer elemento de la cadena y le envía peticiones.
La solicitud pasará de un manejador a otro hasta que alguno la procese o la cadena se agote.

El código se presenta en tres partes:

* **Manejadores.hpp / Manejadores.cpp** – interfaz base y manejadores concretos
* **Cadena.hpp / Cadena.cpp** – lógica de construcción de la cadena
* **main.cpp** – código cliente

## Manejadores.hpp

```cpp
#pragma once
#include <memory>
#include <string>

// ----------------------------------------
// Interfaz base del manejador
// ----------------------------------------
class Manejador {
public:
    virtual ~Manejador() = default;

    void establecer_siguiente(std::unique_ptr<Manejador> siguiente);
    void manejar(const std::string& solicitud) const;

protected:
    virtual bool procesar(const std::string& solicitud) const = 0;

private:
    std::unique_ptr<Manejador> siguiente_;
};

// ----------------------------------------
// Manejadores concretos
// ----------------------------------------
class ValidadorAutenticacion : public Manejador {
protected:
    bool procesar(const std::string& solicitud) const override;
};

class ValidadorPermisos : public Manejador {
protected:
    bool procesar(const std::string& solicitud) const override;
};

class ValidadorFormato : public Manejador {
protected:
    bool procesar(const std::string& solicitud) const override;
};
```

## Manejadores.cpp

```cpp
#include <iostream>
#include "Manejadores.hpp"

// ----------------------------------------
// Implementación de Manejador
// ----------------------------------------
void Manejador::establecer_siguiente(std::unique_ptr<Manejador> siguiente) {
    siguiente_ = std::move(siguiente);
}

void Manejador::manejar(const std::string& solicitud) const {
    if (!procesar(solicitud) && siguiente_) {
        siguiente_->manejar(solicitud);
    }
}

// ----------------------------------------
// Manejadores concretos
// ----------------------------------------
bool ValidadorAutenticacion::procesar(const std::string& solicitud) const {
    if (solicitud == "token-invalido") {
        std::cout << "Autenticación fallida.\n";
        return true;
    }
    return false;
}

bool ValidadorPermisos::procesar(const std::string& solicitud) const {
    if (solicitud == "sin-permisos") {
        std::cout << "Permisos insuficientes.\n";
        return true;
    }
    return false;
}

bool ValidadorFormato::procesar(const std::string& solicitud) const {
    if (solicitud.empty()) {
        std::cout << "Formato inválido: solicitud vacía.\n";
        return true;
    }
    return false;
}
```

## Cadena.hpp

```cpp
#pragma once
#include <memory>
#include "Manejadores.hpp"

// Construye una cadena: Autenticación -> Permisos -> Formato
std::unique_ptr<Manejador> construir_cadena_basica();
```

## Cadena.cpp

```cpp
#include "Cadena.hpp"

// Autenticación -> Permisos -> Formato
std::unique_ptr<Manejador> construir_cadena_basica() {
    auto autenticacion = std::make_unique<ValidadorAutenticacion>();
    auto permisos      = std::make_unique<ValidadorPermisos>();
    auto formato       = std::make_unique<ValidadorFormato>();

    permisos->establecer_siguiente(std::move(formato));
    autenticacion->establecer_siguiente(std::move(permisos));

    return autenticacion;
}
```

## main.cpp

```cpp
#include "Cadena.hpp"

void cliente(const Manejador& manejador) {
    manejador.manejar("token-invalido");
    manejador.manejar("sin-permisos");
    manejador.manejar("");
    manejador.manejar("solicitud-correcta");
}

int main() {
    auto cadena = construir_cadena_basica();
    cliente(*cadena);
    return 0;
}
```

Recuerda que debemos realizar la compilación de la siguiente manera:

```bash
g++ main.cpp Manejadores.cpp Cadena.cpp -o manejador
```

## Añadir un nuevo manejador

Una de las grandes ventajas del patrón **Chain of Responsibility** es que permite añadir nuevas verificaciones sin modificar ninguna clase existente.

Añadamos un nuevo validador: **`ValidadorContenido`**, que rechaza solicitudes que contengan palabras prohibidas.

### Añadir el nuevo manejador en `Manejadores.hpp`

```cpp
// ----------------------------------------
// Nuevo manejador concreto
// Validador que comprueba contenido prohibido
// ----------------------------------------
class ValidadorContenido : public Manejador {
protected:
    bool procesar(const std::string& solicitud) const override;
};
```

### Implementación del nuevo manejador (`Manejadores.cpp`)

```cpp
bool ValidadorContenido::procesar(const std::string& solicitud) const {
    if (solicitud.find("prohibido") != std::string::npos) {
        std::cout << "Contenido prohibido detectado.\n";
        return true;
    }
    return false;
}
```

### Insertar el nuevo manejador en la cadena

#### En `Cadena.hpp`

```cpp
// Construye una cadena: Autenticación -> Permisos -> Contenido -> Formato
std::unique_ptr<Manejador> construir_cadena_con_contenido();
```

#### En `Cadena.cpp`

```cpp

//Autenticación -> Permisos -> Contenido -> Formato

std::unique_ptr<Manejador> construir_cadena_con_contenido() {
    auto autenticacion = std::make_unique<ValidadorAutenticacion>();
    auto permisos      = std::make_unique<ValidadorPermisos>();
    auto contenido     = std::make_unique<ValidadorContenido>();
    auto formato       = std::make_unique<ValidadorFormato>();

    contenido->establecer_siguiente(std::move(formato));
    permisos->establecer_siguiente(std::move(contenido));
    autenticacion->establecer_siguiente(std::move(permisos));

    return autenticacion;
}
```

### Usar la nueva cadena desde el cliente (`main.cpp`)

```cpp
#include "Cadena.hpp"

void cliente(const Manejador& manejador) {
    manejador.manejar("token-invalido");
    manejador.manejar("sin-permisos");
    manejador.manejar("texto con palabra prohibido dentro");
    manejador.manejar("");
    manejador.manejar("solicitud-correcta");
}

int main() {
    auto cadena = construir_cadena_con_contenido();
    cliente(*cadena);
    return 0;
}

```

### Qué no hemos modificado

* No hemos cambiado la interfaz `Manejador`.
* No hemos modificado ninguno de los manejadores existentes.
* No hemos cambiado la lógica del código cliente.

Solo hemos:

1. añadido un **nuevo manejador concreto** (`ValidadorContenido`),
2. modificado la función de construcción de la cadena para insertarlo,
3. y utilizado la nueva cadena desde `main.cpp`.

