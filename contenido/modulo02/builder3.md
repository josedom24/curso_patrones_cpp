# Ejemplo: Construcción de solicitudes HTTP

## Introducción

Para ilustrar el patrón **Builder** en un escenario realista, construiremos un sistema para crear **solicitudes HTTP** de forma flexible, clara y segura.

Una solicitud HTTP puede contener múltiples valores opcionales:

* método (`GET`, `POST`, `PUT`, ...)
* URL
* cabeceras
* cuerpo del mensaje
* parámetros adicionales

Crear este tipo de objetos mediante constructores tradicionales puede conducir a **constructores largos y difíciles de mantener**, o a objetos mal formados.

Por ello emplearemos el patrón **Builder**, separando la **construcción paso a paso** de la **representación final**.

En este ejemplo además, el objeto `SolicitudHTTP` será **inmutable**, con atributos `const`

* Todos sus campos internos serán constantes.
* Su constructor será **privado**.
* Solo el builder podrá crear instancias válidas.

Mostraremos dos variantes:

1. **Builder con Director** (versión clásica del patrón)
2. **Builder sin Director** (builder fluido moderno)

El código se divide en:

* **Solicitud.hpp**: definición del producto inmutable
* **Builder.hpp**: builder abstracto y builder concreto
* **Director.hpp**: clase director que define secuencias de construcción
* **main.cpp**: código cliente

## Solicitud.hpp

```cpp
#pragma once
#include <string>
#include <map>
#include <iostream>

// ======================================================
//          Producto: SolicitudHTTP (MUTABLE)
// ======================================================

class SolicitudHTTP {
public:
    using Cabeceras = std::map<std::string, std::string>;

    // --- Setters ---
    void establecer_metodo(const std::string& m) { metodo_ = m; }
    void establecer_url(const std::string& u) { url_ = u; }
    void agregar_cabecera(const std::string& k, const std::string& v) {
        cabeceras_[k] = v;
    }
    void establecer_cuerpo(const std::string& c) { cuerpo_ = c; }

    // --- Getters ---
    const std::string& metodo()  { return metodo_; }
    const std::string& url()  { return url_; }
    const Cabeceras& cabeceras()  { return cabeceras_; }
    const std::string& cuerpo()  { return cuerpo_; }

    void mostrar() {
        std::cout << "SolicitudHTTP {\n"
                  << "  Método: " << metodo_ << "\n"
                  << "  URL:    " << url_ << "\n"
                  << "  Cabeceras:\n";
        for (const auto& [k, v] : cabeceras_) {
            std::cout << "    - " << k << ": " << v << "\n";
        }
        std::cout << "  Cuerpo: " << cuerpo_ << "\n}\n";
    }

private:
    std::string metodo_ = "GET";
    std::string url_;
    Cabeceras cabeceras_;
    std::string cuerpo_;
};

```

## Builder.hpp

```cpp
#pragma once
#include <memory>
#include "Solicitud.hpp"

// ======================================================
//          Builder abstracto para SolicitudHTTP
// ======================================================

class ConstructorSolicitud {
public:
    virtual ~ConstructorSolicitud() = default;

    virtual void reiniciar() = 0;
    virtual void establecer_metodo(const std::string&) = 0;
    virtual void establecer_url(const std::string&) = 0;
    virtual void agregar_cabecera(const std::string&, const std::string&) = 0;
    virtual void establecer_cuerpo(const std::string&) = 0;

    virtual std::unique_ptr<SolicitudHTTP> obtener_solicitud() = 0;
};

// ======================================================
//        Builder concreto (versión clásica con Director)
// ======================================================

class ConstructorSolicitudConcreto : public ConstructorSolicitud {
public:
    ConstructorSolicitudConcreto() { reiniciar(); }

    void reiniciar() override {
        solicitud_ = std::make_unique<SolicitudHTTP>();
    }

    void establecer_metodo(const std::string& m) override {
        solicitud_->establecer_metodo(m);
    }

    void establecer_url(const std::string& u) override {
        solicitud_->establecer_url(u);
    }

    void agregar_cabecera(const std::string& k,
                          const std::string& v) override {
        solicitud_->agregar_cabecera(k, v);
    }

    void establecer_cuerpo(const std::string& c) override {
        solicitud_->establecer_cuerpo(c);
    }

    std::unique_ptr<SolicitudHTTP> obtener_solicitud() override {
        return std::move(solicitud_);
    }

private:
    std::unique_ptr<SolicitudHTTP> solicitud_;
};

// ======================================================
//   Builder fluido (sin Director, típico en C++ moderno)
// ======================================================

class ConstructorSolicitudFluido {
public:
    ConstructorSolicitudFluido& metodo(const std::string& m) {
        solicitud_.establecer_metodo(m);
        return *this;
    }

    ConstructorSolicitudFluido& url(const std::string& u) {
        solicitud_.establecer_url(u);
        return *this;
    }

    ConstructorSolicitudFluido& cabecera(const std::string& k,
                                         const std::string& v) {
        solicitud_.agregar_cabecera(k, v);
        return *this;
    }

    ConstructorSolicitudFluido& cuerpo(const std::string& c) {
        solicitud_.establecer_cuerpo(c);
        return *this;
    }

    std::unique_ptr<SolicitudHTTP> construir() {
        return std::make_unique<SolicitudHTTP>(solicitud_);
    }

private:
    SolicitudHTTP solicitud_;
};
``` 

## Director.hpp

```cpp
#pragma once
#include <memory>
#include "Builder.hpp"

// ======================================================
//                   Director
// ======================================================

class DirectorSolicitud {
public:
    explicit DirectorSolicitud(ConstructorSolicitud& builder)
        : builder_(builder) {}

    // Construcción mínima: GET sin cuerpo
    std::unique_ptr<SolicitudHTTP>
    construir_get_simple(const std::string& url) {
        builder_.reiniciar();
        builder_.establecer_metodo("GET");
        builder_.establecer_url(url);
        return builder_.obtener_solicitud();
    }

    // Construcción completa: POST con JSON
    std::unique_ptr<SolicitudHTTP>
    construir_post_json(const std::string& url,
                        const std::string& cuerpo_json) {
        builder_.reiniciar();
        builder_.establecer_metodo("POST");
        builder_.establecer_url(url);
        builder_.agregar_cabecera("Content-Type", "application/json");
        builder_.establecer_cuerpo(cuerpo_json);
        return builder_.obtener_solicitud();
    }

private:
    ConstructorSolicitud& builder_;
};
```

## main.cpp

```cpp
#include "Director.hpp"
#include <iostream>

int main() {
    std::cout << "=== Builder CON Director ===\n";

    ConstructorSolicitudConcreto ctor;
    DirectorSolicitud director(ctor);

    auto sol1 = director.construir_get_simple("https://ejemplo.com");
    sol1->mostrar();

    auto sol2 = director.construir_post_json(
        "https://api.ejemplo.com/login",
        "{\"usuario\": \"admin\", \"clave\": \"1234\"}"
    );
    sol2->mostrar();

    std::cout << "\n=== Builder SIN Director (fluido) ===\n";

    auto sol3 =
        ConstructorSolicitudFluido{}
            .metodo("PUT")
            .url("https://api.ejemplo.com/usuario/42")
            .cabecera("Authorization", "Bearer token123")
            .cuerpo(R"({"nombre": "Juan"})")
            .construir();

    sol3->mostrar();

    return 0;
}
```

## Añadir una nueva configuración

Supongamos que queremos añadir a la solicitud HTTP un nuevo parámetro opcional: **`timeout_ms`** (tiempo máximo de espera en milisegundos).

### Cambios en `Solicitud.hpp`

Añadimos el nuevo atributo **mutable**, su setter y su getter.

```cpp
private:
    int timeout_ms_ = 0;   // NUEVO
```

```cpp
public:
    void establecer_timeout(int ms) { timeout_ms_ = ms; }   // NUEVO
    int timeout_ms() { return timeout_ms_; } // NUEVO
```

Además tenemos que cambiar el método `mostrar()`:

```cpp
void mostrar() {
    std::cout << "SolicitudHTTP {\n"
              << "  Método:  " << metodo_ << "\n"
              << "  URL:     " << url_ << "\n"
              << "  Timeout: " << timeout_ms_ << " ms\n"  //<-NUEVO
              << "  Cabeceras:\n";

    for (const auto& [k, v] : cabeceras_) {
        std::cout << "    - " << k << ": " << v << "\n";
    }

    std::cout << "  Cuerpo:  " << cuerpo_ << "\n"
              << "}\n";
}
```

No es necesario modificar constructores ni restringir el acceso: el producto sigue siendo completamente configurable mediante su interfaz pública.

### Cambios en `Builder.hpp`

### En la interfaz del builder abstracto

Añadimos un nuevo paso de construcción:

```cpp
virtual void establecer_timeout(int) = 0;   // NUEVO
```

#### En el builder clásico (`ConstructorSolicitudConcreto`)

No necesitamos nuevos campos internos: el builder trabaja directamente sobre el producto.

Añadimos la implementación del nuevo paso:

```cpp
void establecer_timeout(int ms) override {
    solicitud_->establecer_timeout(ms);
}
```

No hay cambios en `obtener_solicitud()`.

#### En el builder fluido (`ConstructorSolicitudFluido`)

Añadimos el método fluido correspondiente:

```cpp
ConstructorSolicitudFluido& timeout(int ms) {
    solicitud_.establecer_timeout(ms);
    return *this;
}
```

No hay cambios en `construir()`.

### Cambios en `Director.hpp`

Solo es necesario modificar el Director **si queremos que alguna construcción predefinida** incluya el nuevo parámetro.

Por ejemplo:

```cpp
builder_.establecer_timeout(5000);   // NUEVO
```

Si el Director no necesita configurar el timeout, **no se modifica**.

### Cambios en `main.cpp` para probar la nueva configuración

```cpp
#include "Director.hpp"
#include <iostream>

int main() {
    std::cout << "=== Builder CON Director ===\n";

    ConstructorSolicitudConcreto ctor;
    DirectorSolicitud director(ctor);

    // Solicitud GET simple (sin timeout)
    auto sol1 = director.construir_get_simple("https://ejemplo.com");
    sol1->mostrar();

    // Solicitud POST con JSON y timeout (NUEVO)
    ctor.reiniciar();
    ctor.establecer_metodo("POST");
    ctor.establecer_url("https://api.ejemplo.com/datos");
    ctor.agregar_cabecera("Content-Type", "application/json");
    ctor.establecer_cuerpo("{\"dato\": 123}");
    ctor.establecer_timeout(5000);               // ← NUEVO
    auto sol_timeout = ctor.obtener_solicitud();
    sol_timeout->mostrar();

    std::cout << "\n=== Builder SIN Director (fluido) ===\n";

    // Solicitud PUT con timeout (NUEVO)
    auto sol2 =
        ConstructorSolicitudFluido{}
            .metodo("PUT")
            .url("https://api.ejemplo.com/usuario/42")
            .cabecera("Authorization", "Bearer token123")
            .cuerpo("{\"nombre\": \"Juan\"}")
            .timeout(3000)                       // ← NUEVO
            .construir();

    sol2->mostrar();

    return 0;
}
```

### Qué no hemos modificado

* La estructura del patrón Builder.
* La separación producto / builder / director.
* El flujo de construcción existente.
* El código cliente previo (salvo para probar el nuevo parámetro).

Solo hemos añadido:

* Un **nuevo atributo mutable** en el producto.
* Un **nuevo setter y getter** públicos.
* Un **nuevo paso de construcción** en los builders.
* Opcionalmente, su uso desde el Director o el cliente.

