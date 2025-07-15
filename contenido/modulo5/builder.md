# Builder

## Introducción y propósito

El patrón **Builder** es un patrón de creación que permite construir objetos complejos paso a paso, separando la construcción de la representación final. Es especialmente útil cuando un objeto requiere una configuración flexible o múltiples pasos de inicialización.

## Problemas que resuelve

Cuando la creación de un objeto implica múltiples parámetros opcionales o configuraciones complejas, utilizar constructores tradicionales puede resultar en firmas difíciles de leer, propensas a errores y poco mantenibles.

El patrón Builder resuelve varias dificultades comunes al construir objetos:

* **Constructores con demasiados parámetros**: especialmente cuando muchos de ellos son opcionales.
* **Inflexibilidad en la creación**: los constructores tradicionales requieren todos los argumentos en un orden fijo.
* **Duplicación de lógica de inicialización**: cuando hay múltiples formas de construir un objeto.
* **Acoplamiento entre la creación y el uso**: el patrón permite encapsular la lógica de construcción en una entidad separada.

**Aplicaciones típicas**:

* Configuración de conexiones (base de datos, red, etc.).
* Construcción de interfaces gráficas con múltiples elementos opcionales.
* Generación de documentos o reportes personalizados.
* Creación de objetos con estructuras jerárquicas.


## Diagrama UML y estructura


```plaintext
      +----------------+             +----------------------------+
      |    Director    |             |     ConnectionBuilder      |
      +----------------+             +----------------------------+
            |                                /\
            | uses                          /  \
            v                           <<interface>>
+----------------------------+     +----------------------------+
| TCPConnectionBuilder       |<----| AbstractConnectionBuilder |
+----------------------------+     +----------------------------+
| - host: string             |       
| - port: int                |
| - timeout: int             |       
| + setHost(...)             |
| + setPort(...)             |
| + setTimeout(...)          |
| + build() -> TCPConnection |
+----------------------------+
            |
            v
     +----------------------+
     |    TCPConnection     |
     +----------------------+
```

* **`AbstractConnectionBuilder`** (*Builder*): Define una **interfaz abstracta** con los métodos necesarios para configurar y construir el objeto (`setHost`, `setPort`, `setTimeout`, `build`). Este nivel de abstracción es útil si se van a definir múltiples tipos de conexiones (TCP, UDP, etc.).

* **`TCPConnectionBuilder`** (*ConcreteBuilder*): Implementa la interfaz `AbstractConnectionBuilder` y mantiene el estado intermedio necesario para construir una instancia de `TCPConnection`.

* **`TCPConnection`** (*Product*): Es el objeto complejo que se desea construir. Se crea a partir de la configuración mantenida por el *builder*.

* **`Director`** (opcional): Es una clase que puede encapsular una **secuencia predefinida de pasos** para construir configuraciones comunes, como una "conexión segura por defecto". Si se desea, puede añadirse fácilmente.


## Implementación en C++ moderno

A continuación, se presenta una implementación didáctica utilizando características modernas de C++:

Perfecto. A continuación te presento el **material extendido**, incluyendo ahora:

* Una **interfaz abstracta** `AbstractConnectionBuilder`.
* Una clase concreta `TCPConnectionBuilder` que la implementa.
* Una clase `Director` que encapsula construcciones predefinidas (por ejemplo, una “conexión segura por defecto”).

---

## 🔧 **Implementación completa en C++ moderno con `Director` y `AbstractConnectionBuilder`**

### Interfaz del Builder

```cpp
#include <memory>
#include <string>
#include <optional>

// Producto final
class TCPConnection {
    std::string host_;
    int port_;
    std::optional<int> timeout_;

public:
    TCPConnection(std::string host, int port, std::optional<int> timeout)
        : host_(std::move(host)), port_(port), timeout_(timeout) {}

    void connect() const {
        std::cout << "Conectando a " << host_ << ":" << port_;
        if (timeout_) {
            std::cout << " con timeout de " << *timeout_ << " ms.\n";
        } else {
            std::cout << " sin timeout configurado.\n";
        }
    }
};

// Interfaz abstracta del builder
class AbstractConnectionBuilder {
public:
    virtual ~AbstractConnectionBuilder() = default;

    virtual AbstractConnectionBuilder& setHost(std::string host) = 0;
    virtual AbstractConnectionBuilder& setPort(int port) = 0;
    virtual AbstractConnectionBuilder& setTimeout(int timeout) = 0;

    virtual std::unique_ptr<TCPConnection> build() const = 0;
};
```

### Builder concreto

```cpp
class TCPConnectionBuilder : public AbstractConnectionBuilder {
    std::string host_ = "127.0.0.1";
    int port_ = 80;
    std::optional<int> timeout_;

public:
    AbstractConnectionBuilder& setHost(std::string host) override {
        host_ = std::move(host);
        return *this;
    }

    AbstractConnectionBuilder& setPort(int port) override {
        port_ = port;
        return *this;
    }

    AbstractConnectionBuilder& setTimeout(int timeout) override {
        timeout_ = timeout;
        return *this;
    }

    std::unique_ptr<TCPConnection> build() const override {
        return std::make_unique<TCPConnection>(host_, port_, timeout_);
    }
};
```

### Clase Director

```cpp
class ConnectionDirector {
    AbstractConnectionBuilder& builder_;

public:
    ConnectionDirector(AbstractConnectionBuilder& builder)
        : builder_(builder) {}

    std::unique_ptr<TCPConnection> createSecureConnection() {
        return builder_
            .setHost("secure.example.com")
            .setPort(443)
            .setTimeout(10000)
            .build();
    }

    std::unique_ptr<TCPConnection> createFastLocalConnection() {
        return builder_
            .setHost("192.168.0.1")
            .setPort(8080)
            .build();
    }
};
```

### Ejemplo de uso

```cpp
int main() {
    TCPConnectionBuilder builder;

    ConnectionDirector director(builder);

    auto secureConn = director.createSecureConnection();
    secureConn->connect();

    auto localConn = director.createFastLocalConnection();
    localConn->connect();

    // También se puede usar directamente sin el director
    auto customConn = builder
        .setHost("custom.server.net")
        .setPort(3000)
        .setTimeout(5000)
        .build();

    customConn->connect();
}
```

* El objeto `TCPConnectionBuilder` permite establecer propiedades de la conexión paso a paso.
* El método `build()` construye finalmente el objeto `TCPConnection`.
* El uso de `std::optional` refleja claramente los parámetros opcionales.
* Se emplea `std::unique_ptr` para gestionar automáticamente la memoria del objeto construido.

Al introducir la clase `Director`, que es opcional, conseguimos:

* **Extensibilidad**: se pueden implementar otros builders (e.g., `UDPConnectionBuilder`) sin modificar el código del `Director`.
* **Reutilización**: el `Director` permite encapsular configuraciones estándar reutilizables.
* **Abstracción**: se puede programar contra la interfaz `AbstractConnectionBuilder` sin conocer la implementación concreta.

## Ventajas

* **Claridad y legibilidad**: la fluidez de métodos hace que la construcción sea autoexplicativa.
* **Flexibilidad**: permite múltiples combinaciones de configuración sin necesidad de múltiples constructores.
* **Encapsulación**: separa la lógica de construcción de la lógica del objeto.
* **Escalabilidad**: se adapta fácilmente a objetos con muchos parámetros opcionales.

## Desventajas

* **Sobrecoste estructural**: requiere clases adicionales (el *builder*).
* **Posible sobreingeniería**: en objetos simples puede ser innecesario.
* **No evita por sí solo errores de configuración**: es útil acompañarlo de validaciones.

## Buenas prácticas

* Acompañar el builder de validaciones internas antes de construir (`build()`).
* Usar `std::optional` o valores por defecto para gestionar configuración opcional.

