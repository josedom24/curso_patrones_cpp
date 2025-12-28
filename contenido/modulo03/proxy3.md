# Ejemplo: Acceso controlado a un servicio de datos

## Introducción

Para ilustrar el patrón **Proxy** en un contexto realista, construiremos un pequeño servicio de acceso a datos.
El objetivo del sistema es permitir que el código cliente solicite datos mediante una interfaz común (`ServicioDatos`), **sin conocer si está hablando con el objeto real o con un proxy** que controle el acceso.

El proxy añade tres responsabilidades adicionales:

* **Control de permisos** según el usuario.
* **Inicialización diferida** del servicio real, que es costoso.
* **Caché interna** para devolver resultados inmediatamente si ya fueron consultados antes.

Cada operación se hace a través de la interfaz `ServicioDatos`. El cliente nunca interactúa directamente con el servicio real (`ServicioDatosReal`).
Todo el control extra sucede dentro del `ProxyServicioDatos`, sin que el cliente lo note.

A continuación se muestra el código completo dividido en:

* **Servicio.hpp** – interfaz del servicio y objeto real
* **Proxy.hpp** – implementación del proxy
* **main.cpp** – código cliente

## Servicio.hpp

```cpp
#pragma once
#include <iostream>
#include <string>

// ----------------------------------------
// Interfaz base del servicio
// ----------------------------------------
class ServicioDatos {
public:
    virtual ~ServicioDatos() = default;
    virtual std::string obtener_datos(const std::string& clave) = 0;
};

// ----------------------------------------
// Servicio real, costoso o protegido
// ----------------------------------------
class ServicioDatosReal : public ServicioDatos {
public:
    ServicioDatosReal() {
        std::cout << "[ServicioDatosReal] Inicializando recursos pesados...\n";
    }

    std::string obtener_datos(const std::string& clave) override {
        return "Datos reales para '" + clave + "'";
    }
};
```

## Proxy.hpp

```cpp
#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include "Servicio.hpp"

// ----------------------------------------
// Proxy que controla acceso, inicializa el servicio
// bajo demanda y mantiene una pequeña caché
// ----------------------------------------
class ProxyServicioDatos : public ServicioDatos {
private:
    std::unique_ptr<ServicioDatosReal> servicio_real_;
    std::unordered_map<std::string, std::string> cache_;
    std::string usuario_;

    bool comprobar_acceso() const {
        return usuario_ == "admin";
    }

public:
    explicit ProxyServicioDatos(std::string usuario)
        : usuario_(std::move(usuario)) {}

    std::string obtener_datos(const std::string& clave) override {
        std::cout << "[Proxy] Solicitud para '" << clave << "'.\n";

        if (!comprobar_acceso()) {
            return "[Proxy] Acceso denegado para el usuario '" + usuario_ + "'";
        }

        if (cache_.find(clave) != cache_.end()) {
            return "[Proxy] (Caché) " + cache_[clave];
        }

        if (!servicio_real_) {
            std::cout << "[Proxy] Creando ServicioDatosReal bajo demanda...\n";
            servicio_real_ = std::make_unique<ServicioDatosReal>();
        }

        auto resultado = servicio_real_->obtener_datos(clave);

        cache_[clave] = resultado;

        return resultado;
    }
};
```

## main.cpp

```cpp
#include <iostream>
#include "Proxy.hpp"

void cliente(ServicioDatos& servicio) {
    std::cout << servicio.obtener_datos("perfil") << "\n";
    std::cout << servicio.obtener_datos("estadisticas") << "\n";

    // Segunda llamada repetida: vendrá de la caché
    std::cout << servicio.obtener_datos("perfil") << "\n";
}

int main() {
    ProxyServicioDatos proxyAdmin("admin");
    ProxyServicioDatos proxyInvitado("invitado");

    std::cout << "--- Acceso como 'admin' ---\n";
    cliente(proxyAdmin);

    std::cout << "\n--- Acceso como 'invitado' ---\n";
    cliente(proxyInvitado);

    return 0;
}
```
## Añadir un nuevo proxy especializado

Una de las mayores ventajas del patrón **Proxy** es que permite añadir nuevas capas de control **sin modificar el servicio real ni la interfaz común**.
Solo añadimos un nuevo tipo de proxy que implemente la misma interfaz.

Supongamos que queremos añadir un nuevo proxy:
**Proxy de registro** (un proxy que añade *logging detallado* de todas las solicitudes realizadas).

### Añadir el nuevo proxy en `Proxy.hpp`

Debajo de `ProxyServicioDatos`, añadimos un nuevo proxy que también implementa `ServicioDatos`:

```cpp
// ----------------------------------------
// Nuevo Proxy: añade registro detallado de solicitudes
// ----------------------------------------
class ProxyServicioDatosLogger : public ServicioDatos {
private:
    std::unique_ptr<ServicioDatosReal> servicio_real_;

public:
    std::string obtener_datos(const std::string& clave) override {
        std::cout << "[Logger] Solicitud para '" << clave << "'\n";

        if (!servicio_real_) {
            std::cout << "[Logger] Creando ServicioDatosReal bajo demanda...\n";
            servicio_real_ = std::make_unique<ServicioDatosReal>();
        }

        auto resultado = servicio_real_->obtener_datos(clave);

        std::cout << "[Logger] Resultado entregado: '" 
                  << resultado << "'\n";

        return resultado;
    }
};
```

Este nuevo proxy:

* No controla permisos
* No usa caché
* No modifica el servicio real
* Solo añade **registro detallado**
* Conserva la misma interfaz `ServicioDatos`

Así, el cliente puede sustituir cualquier proxy por este nuevo sin cambiar nada.

### Usarlo en `main.cpp`

Añadimos simplemente una línea:

```cpp
...

int main() {
    ProxyServicioDatosLogger proxyLogger;
    ProxyServicioDatos proxyAdmin("admin");

    std::cout << "--- Usando Proxy Logger ---\n";
    cliente(proxyLogger);

    std::cout << "\n--- Usando Proxy con control de acceso ---\n";
    cliente(proxyAdmin);

    return 0;
}
```

### Qué no hemos modificado

* No hemos cambiado la interfaz `ServicioDatos`.
* No hemos modificado `ServicioDatosReal`.
* No hemos tocado `ProxyServicioDatos`.
* El **cliente** sigue usando siempre `ServicioDatos&`, sin saber qué proxy está detrás.
* No se ha modificado el funcionamiento del servicio real.

Lo único necesario ha sido:

1. Crear un **nuevo proxy** que implemente la interfaz.
2. Usarlo en `main.cpp` si se desea.

