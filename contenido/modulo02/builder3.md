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
//             Producto: SolicitudHTTP (INMUTABLE)
// ======================================================

class SolicitudHTTP {
public:
    using Cabeceras = std::map<std::string, std::string>;

    // --- Métodos de acceso ---
    const std::string& metodo()    const noexcept { return metodo_; }
    const std::string& url()       const noexcept { return url_; }
    const Cabeceras&   cabeceras() const noexcept { return cabeceras_; }
    const std::string& cuerpo()    const noexcept { return cuerpo_; }

    void mostrar() const {
        std::cout << "SolicitudHTTP {\n"
                  << "  Método: " << metodo_ << "\n"
                  << "  URL:    " << url_ << "\n"
                  << "  Cabeceras:\n";
        for (const auto& par : cabeceras_) {
            std::cout << "    - " << par.first << ": " << par.second << "\n";
        }
        std::cout << "  Cuerpo: " << cuerpo_ << "\n}\n";
    }

    // ======================================================
    //     Fábrica estática moderna (sin make_unique posible)
    // ======================================================
    static std::unique_ptr<SolicitudHTTP> crear(
        const std::string& metodo,
        const std::string& url,
        const Cabeceras& cab,
        const std::string& cuerpo)
    {
        /*
         * Por qué usamos `new` aquí:
         * -----------------------------------------
         * El constructor de SolicitudHTTP es privado
         * porque el patrón Builder exige que solo los
         * builders autorizados puedan crear instancias.
         *
         * std::make_unique NO puede usarse porque intenta
         * construir el objeto dentro de <memory>, que NO es
         * amigo de la clase; por tanto, no puede llamar al
         * constructor privado.
         *
         * En cambio, este método estático SÍ forma parte de
         * la propia clase, por lo que puede usar `new` para
         * invocar al constructor privado.
         *
         * El usuario final nunca usa `new` ni gestiona memoria:
         * la instancia se devuelve siempre envuelta en
         * std::unique_ptr, respetando RAII y C++ moderno.
         */
        return std::unique_ptr<SolicitudHTTP>(
            new SolicitudHTTP(metodo, url, cab, cuerpo)
        );
    }

private:
    // --- Atributos inmutables ---
    const std::string metodo_;
    const std::string url_;
    const Cabeceras   cabeceras_;
    const std::string cuerpo_;

    // Constructor privado: solo accesible desde la fábrica y friends
    SolicitudHTTP(const std::string& metodo,
                  const std::string& url,
                  const Cabeceras& cab,
                  const std::string& cuerpo)
        : metodo_(metodo),
          url_(url),
          cabeceras_(cab),
          cuerpo_(cuerpo)
    {}

    friend class ConstructorSolicitud;
    friend class ConstructorSolicitudConcreto;
    friend class ConstructorSolicitudFluido;
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
        metodo_ = "GET";
        url_.clear();
        cabeceras_.clear();
        cuerpo_.clear();
    }

    void establecer_metodo(const std::string& m) override { metodo_ = m; }
    void establecer_url(const std::string& u) override { url_ = u; }

    void agregar_cabecera(const std::string& clave,
                          const std::string& valor) override {
        cabeceras_[clave] = valor;
    }

    void establecer_cuerpo(const std::string& c) override { cuerpo_ = c; }

    std::unique_ptr<SolicitudHTTP> obtener_solicitud() override {
        // La construcción se delega a la fábrica estática
        return SolicitudHTTP::crear(metodo_, url_, cabeceras_, cuerpo_);
    }

private:
    std::string metodo_;
    std::string url_;
    SolicitudHTTP::Cabeceras cabeceras_;
    std::string cuerpo_;
};


// ======================================================
//   Builder fluido (sin Director, típico en C++ moderno)
// ======================================================

class ConstructorSolicitudFluido {
public:
    ConstructorSolicitudFluido& metodo(const std::string& m) {
        metodo_ = m;
        return *this;
    }

    ConstructorSolicitudFluido& url(const std::string& u) {
        url_ = u;
        return *this;
    }

    ConstructorSolicitudFluido& cabecera(const std::string& clave,
                                         const std::string& valor) {
        cabeceras_[clave] = valor;
        return *this;
    }

    ConstructorSolicitudFluido& cuerpo(const std::string& c) {
        cuerpo_ = c;
        return *this;
    }

    // Crea el objeto inmutable desde el builder fluido
    std::unique_ptr<SolicitudHTTP> construir() const {
        return SolicitudHTTP::crear(metodo_, url_, cabeceras_, cuerpo_);
    }

private:
    std::string metodo_ = "GET";
    std::string url_;
    SolicitudHTTP::Cabeceras cabeceras_;
    std::string cuerpo_;
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
    std::unique_ptr<SolicitudHTTP> construir_get_simple(const std::string& url) {
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
        R"({"usuario": "admin", "clave": "1234"})"
    );
    sol2->mostrar();


    std::cout << "\n=== Builder SIN Director (fluido) ===\n";

    SolicitudHTTP sol3 =
        ConstructorSolicitudFluido{}
            .metodo("PUT")
            .url("https://api.ejemplo.com/usuario/42")
            .cabecera("Authorization", "Bearer token123")
            .cuerpo(R"({"nombre": "Juan"})")
            .construir();

    sol3.mostrar();

    return 0;
}
```
* `R"(...)"` permite escribir un **string literal sin procesar** (raw string literal), que nos permite escribir cadenas exactamente tal como aparecen, sin necesidad de escapar comillas, barras o caracteres especiales.

## Añadir una nueva configuración

Supongamos que queremos añadir a la solicitud HTTP un nuevo parámetro opcional: **`timeout_ms`** (tiempo máximo de espera en milisegundos).

A continuación se muestran únicamente los cambios requeridos en cada fichero, siguiendo la arquitectura moderna del patrón Builder.

### Cambios en `Solicitud.hpp`

Añadimos el nuevo atributo **const**, el getter y la actualización del constructor privado:

```cpp
private:
    const int timeout_ms_ = 0;   // NUEVO

    SolicitudHTTP(const std::string& metodo,
                  const std::string& url,
                  const Cabeceras& cab,
                  const std::string& cuerpo,
                  int timeout_ms)               // NUEVO
        : metodo_(metodo),
          url_(url),
          cabeceras_(cab),
          cuerpo_(cuerpo),
          timeout_ms_(timeout_ms)              // NUEVO
    {}

public:
    int timeout_ms() const noexcept { return timeout_ms_; }  // NUEVO
```

También debemos actualizar la **fábrica estática**, que ahora debe recibir el nuevo parámetro:

```cpp
static std::unique_ptr<SolicitudHTTP> crear(
    const std::string& metodo,
    const std::string& url,
    const Cabeceras& cab,
    const std::string& cuerpo,
    int timeout_ms = 0                // NUEVO
)
{
    return std::unique_ptr<SolicitudHTTP>(
        new SolicitudHTTP(metodo, url, cab, cuerpo, timeout_ms)
    );
}
```

### Cambios en `Builder.hpp`

Debemos añadir una nuevo método virtual:

```cpp
virtual void establecer_timeout(int) = 0;   // NUEVO
```



#### En el builder clásico (`ConstructorSolicitudConcreto`)

Añadimos el campo interno y el setter:

```cpp
private:
    int timeout_ms_ = 0;   // NUEVO

public:
    void establecer_timeout(int ms) override { timeout_ms_ = ms; }   // NUEVO
```

Propagamos el nuevo parámetro al crear la solicitud:

```cpp
return SolicitudHTTP::crear(
    metodo_,
    url_,
    cabeceras_,
    cuerpo_,
    timeout_ms_      // NUEVO
);
```

#### En el builder fluido (`ConstructorSolicitudFluido`)

Añadimos el nuevo atributo y el método fluido:

```cpp
private:
    int timeout_ms_ = 0;  // NUEVO

public:
    ConstructorSolicitudFluido& timeout(int ms) {
        timeout_ms_ = ms;
        return *this;
    }
```

Propagación en `construir()`:

```cpp
return SolicitudHTTP::crear(metodo_, url_, cabeceras_, cuerpo_, timeout_ms_);
```

### Cambios en `Director.hpp` 

Si queremos que el Director configure un timeout:

```cpp
builder_.establecer_timeout(5000);   // NUEVO
```

Solo es necesario si el Director debe usar esta nueva opción.

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
    ctor.establecer_cuerpo(R"({"dato": 123})");
    ctor.establecer_timeout(5000);                 // ← NUEVO
    auto sol_timeout = ctor.obtener_solicitud();
    sol_timeout->mostrar();


    std::cout << "\n=== Builder SIN Director (fluido) ===\n";

    // Solicitud PUT con timeout (NUEVO)
    auto sol2 =
        ConstructorSolicitudFluido{}
            .metodo("PUT")
            .url("https://api.ejemplo.com/usuario/42")
            .cabecera("Authorization", "Bearer token123")
            .cuerpo(R"({"nombre": "Juan"})")
            .timeout(3000)                         // ← NUEVO
            .construir();

    sol2->mostrar();

    return 0;
}
```

### Qué no hemos modificado

* La interfaz del producto (`SolicitudHTTP`).
* La arquitectura general del patrón Builder.
* El comportamiento de los builders ya existentes.
* El flujo del Director.
* El resto del código cliente.

Solo se añadieron:

1. un **nuevo atributo inmutable**,
2. un **nuevo parámetro en el constructor privado y la fábrica**,
3. los nuevos métodos correspondientes en los builders,
4. la propagación del parámetro en la construcción del producto.

