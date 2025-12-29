# Ejemplo: Flujo de estados de un documento

## Introducción

Para ilustrar el patrón **State** en un contexto realista, se construye un pequeño sistema que modela el **ciclo de vida de un documento**.
Un documento puede encontrarse en distintos estados, y **cada estado determina qué operaciones están permitidas**:

* **Borrador**: el documento puede editarse.
* **En revisión**: el documento ya no puede editarse.
* **Publicado**: el documento está finalizado y no admite cambios.

El objeto `Documento` actúa como **Contexto** y delega su comportamiento en objetos que representan cada estado concreto.
El código cliente interactúa únicamente con `Documento`; el cambio de comportamiento se produce automáticamente al cambiar el estado interno.

El ejemplo se organiza en:

* **EstadoDocumento.hpp** – interfaz común del estado
* **Documento.hpp** – contexto y estados concretos
* **main.cpp** – código cliente


## EstadoDocumento.hpp

```cpp
#pragma once
#include <string>

// Declaración anticipada
class Documento;

// ----------------------------------------
// Interfaz base del estado
// ----------------------------------------
class EstadoDocumento {
public:
    virtual ~EstadoDocumento() = default;

    virtual void editar(Documento&, const std::string&) = 0;
    virtual void enviar_revision(Documento&) = 0;
    virtual void publicar(Documento&) = 0;
};
```


## Documento.hpp

Este archivo contiene:

* la clase **Contexto** (`Documento`)
* **todas las clases de estado concretas**
* métodos definidos **dentro de las clases**

```cpp
#pragma once
#include <memory>
#include <string>
#include <iostream>
#include "EstadoDocumento.hpp"

// ----------------------------------------
// Contexto
// ----------------------------------------
class Documento {
private:
    std::unique_ptr<EstadoDocumento> estado_;
    std::string contenido_;

public:
    Documento()
        : estado_(std::make_unique<EstadoBorrador>()) {}

    void cambiar_estado(std::unique_ptr<EstadoDocumento> nuevoEstado) {
        estado_ = std::move(nuevoEstado);
    }

    void editar(const std::string& texto) {
        estado_->editar(*this, texto);
    }

    void enviar_revision() {
        estado_->enviar_revision(*this);
    }

    void publicar() {
        estado_->publicar(*this);
    }

    void set_contenido(const std::string& texto) {
        contenido_ = texto;
    }

    const std::string& contenido() const {
        return contenido_;
    }
};

// ----------------------------------------
// Estados concretos
// ----------------------------------------

class EstadoBorrador : public EstadoDocumento {
public:
    void editar(Documento& doc, const std::string& texto) override {
        doc.set_contenido(texto);
        std::cout << "[Borrador] Documento editado: "
                  << doc.contenido() << "\n";
    }

    void enviar_revision(Documento& doc) override {
        std::cout << "[Borrador] Enviando a revisión...\n";
        doc.cambiar_estado(std::make_unique<EstadoRevision>());
    }

    void publicar(Documento&) override {
        std::cout << "[Borrador] No puede publicarse directamente.\n";
    }
};

class EstadoRevision : public EstadoDocumento {
public:
    void editar(Documento&, const std::string&) override {
        std::cout << "[Revisión] No se puede editar. "
                     "Debe volver a borrador.\n";
    }

    void enviar_revision(Documento&) override {
        std::cout << "[Revisión] Ya está en revisión.\n";
    }

    void publicar(Documento& doc) override {
        std::cout << "[Revisión] Publicando documento...\n";
        doc.cambiar_estado(std::make_unique<EstadoPublicado>());
    }
};

class EstadoPublicado : public EstadoDocumento {
public:
    void editar(Documento&, const std::string&) override {
        std::cout << "[Publicado] No puede editarse "
                     "un documento publicado.\n";
    }

    void enviar_revision(Documento&) override {
        std::cout << "[Publicado] No puede volver a revisión.\n";
    }

    void publicar(Documento&) override {
        std::cout << "[Publicado] Ya está publicado.\n";
    }
};
```


## main.cpp

```cpp
#include "Documento.hpp"

int main() {
    Documento doc;

    doc.editar("Primer borrador del texto");
    doc.enviar_revision();
    doc.editar("Intento de editar en revisión");
    doc.publicar();
    doc.editar("Intento de editar publicado");

    return 0;
}
```





## Añadir el nuevo estado

Como en la versión actual **los estados se definen con sus métodos dentro de la clase**, basta con añadir una nueva clase que implemente la interfaz `EstadoDocumento`.

### Nuevo estado: `EstadoArchivado`

```cpp
class EstadoArchivado : public EstadoDocumento {
public:
    void editar(Documento&, const std::string&) override {
        std::cout << "[Archivado] Documento bloqueado. No se puede editar.\n";
    }

    void enviar_revision(Documento&) override {
        std::cout << "[Archivado] No puede enviarse a revisión.\n";
    }

    void publicar(Documento&) override {
        std::cout << "[Archivado] El documento ya está archivado.\n";
    }
};
```

No es necesario modificar la interfaz `EstadoDocumento`, ya que el nuevo estado **se adapta a las operaciones ya definidas**.


### Activar el nuevo estado desde otro estado

Para que el documento pueda pasar al estado **Archivado**, basta con añadir una transición desde uno de los estados existentes.
Por ejemplo, desde `EstadoPublicado`:

```cpp
class EstadoPublicado : public EstadoDocumento {
public:
    void editar(Documento&, const std::string&) override {
        std::cout << "[Publicado] No puede editarse un documento publicado.\n";
    }

    void enviar_revision(Documento&) override {
        std::cout << "[Publicado] No puede volver a revisión.\n";
    }

    void publicar(Documento& doc) override {
        std::cout << "[Publicado] Archivando documento...\n";
        doc.cambiar_estado(std::make_unique<EstadoArchivado>());
    }
};
```

La transición queda encapsulada en el propio estado, sin condicionales externos ni lógica adicional en el contexto.


### Qué no hemos modificado

Es importante destacar que **la incorporación del nuevo estado no ha requerido cambios en**:

* la interfaz `EstadoDocumento`,
* la clase `Documento`,
* el código cliente (`main.cpp`).

Solo hemos:

1. añadido un **nuevo estado concreto** (`EstadoArchivado`),
2. definido su comportamiento específico,
3. incorporado una **nueva transición** desde un estado existente.

