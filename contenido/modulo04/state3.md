# Ejemplo: Flujo de estados de un documento

## Introducción

Para ilustrar el patrón **State** en un contexto realista, construiremos un pequeño sistema que modela el **ciclo de vida de un documento**.
Un documento puede encontrarse en distintos estados y cada estado determina qué operaciones están permitidas:

* **Borrador**: el documento puede seguir editándose.
* **En revisión**: el documento ya no se puede editar, pero puede aceptarse o devolverse a borrador.
* **Publicado**: el documento está finalizado y no permite cambios.

El objeto `Documento` es el *Contexto*, y delega su comportamiento en clases que representan cada estado (`EstadoBorrador`, `EstadoRevision`, `EstadoPublicado`).

Cada estado implementa la interfaz común `EstadoDocumento`, que define las operaciones disponibles.
El código cliente solo interactúa con `Documento`: el patrón garantiza que las acciones varían automáticamente según el estado interno del documento.

El ejercicio se organiza en:

* **EstadoDocumento.hpp** – interfaz del estado y estados concretos
* **Documento.hpp** – clase Contexto
* **main.cpp** – código cliente que interactúa con el sistema


## EstadoDocumento.hpp

```cpp
#pragma once
#include <iostream>
#include <memory>
#include <string>

// Declaración anticipada necesaria (Estado -> Documento)
class Documento;

// ----------------------------------------
// Interfaz base del estado
// ----------------------------------------
class EstadoDocumento {
public:
    virtual ~EstadoDocumento() = default;

    virtual void editar(Documento& doc, const std::string& nuevoTexto) = 0;
    virtual void enviar_revision(Documento& doc) = 0;
    virtual void publicar(Documento& doc) = 0;
};

// ----------------------------------------
// Estado concreto: Borrador
// ----------------------------------------
class EstadoBorrador : public EstadoDocumento {
public:
    void editar(Documento& doc, const std::string& nuevoTexto) override;
    void enviar_revision(Documento& doc) override;
    void publicar(Documento& doc) override;
};

// ----------------------------------------
// Estado concreto: En revisión
// ----------------------------------------
class EstadoRevision : public EstadoDocumento {
public:
    void editar(Documento&, const std::string&) override;
    void enviar_revision(Documento&) override;
    void publicar(Documento& doc) override;
};

// ----------------------------------------
// Estado concreto: Publicado
// ----------------------------------------
class EstadoPublicado : public EstadoDocumento {
public:
    void editar(Documento&, const std::string&) override;
    void enviar_revision(Documento&) override;
    void publicar(Documento&) override;
};
```


## Documento.hpp

```cpp
#pragma once
#include <memory>
#include <string>
#include "EstadoDocumento.hpp"

// ----------------------------------------
// Contexto
// ----------------------------------------
class Documento {
private:
    std::unique_ptr<EstadoDocumento> estado_;
    std::string contenido_;

public:
    Documento();

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
// Implementaciones de los estados
// ----------------------------------------

inline Documento::Documento()
    : estado_(std::make_unique<EstadoBorrador>())
{}

// Estado Borrador
inline void EstadoBorrador::editar(Documento& doc, const std::string& nuevoTexto) {
    doc.set_contenido(nuevoTexto);
    std::cout << "[Borrador] Documento editado: " << doc.contenido() << "\n";
}

inline void EstadoBorrador::enviar_revision(Documento& doc) {
    std::cout << "[Borrador] Enviando a revisión...\n";
    doc.cambiar_estado(std::make_unique<EstadoRevision>());
}

inline void EstadoBorrador::publicar(Documento&) {
    std::cout << "[Borrador] No puede publicarse directamente. Debe pasar por revisión.\n";
}

// Estado Revisión
inline void EstadoRevision::editar(Documento&, const std::string&) {
    std::cout << "[Revisión] No se puede editar. Debe volver a borrador.\n";
}

inline void EstadoRevision::enviar_revision(Documento&) {
    std::cout << "[Revisión] Ya está en revisión.\n";
}

inline void EstadoRevision::publicar(Documento& doc) {
    std::cout << "[Revisión] Publicando documento...\n";
    doc.cambiar_estado(std::make_unique<EstadoPublicado>());
}

// Estado Publicado
inline void EstadoPublicado::editar(Documento&, const std::string&) {
    std::cout << "[Publicado] No puede editarse un documento publicado.\n";
}

inline void EstadoPublicado::enviar_revision(Documento&) {
    std::cout << "[Publicado] No puede volver a revisión.\n";
}

inline void EstadoPublicado::publicar(Documento&) {
    std::cout << "[Publicado] Ya está publicado.\n";
}
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


# Añadir un nuevo estado

Supongamos que queremos añadir un estado **Archivado**, donde el documento ya no puede modificarse y queda bloqueado para operaciones futuras.

### Añadir nuevo estado en `EstadoDocumento.hpp`

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
        std::cout << "[Archivado] Ya no puede publicarse.\n";
    }
};
```

### Activar el nuevo estado desde otro estado

Por ejemplo, desde `EstadoPublicado`:

```cpp
inline void EstadoPublicado::publicar(Documento& doc) {
    std::cout << "[Publicado] Archivando documento...\n";
    doc.cambiar_estado(std::make_unique<EstadoArchivado>());
}
```

### Qué no hemos modificado

* La interfaz `EstadoDocumento`.
* La clase `Documento`.
* El código del cliente.

Solo hemos:

1. añadido un **nuevo estado concreto** (`EstadoArchivado`),
2. añadido una transición a ese estado en otro estado,
3. y opcionalmente una llamada en `main.cpp` para probarlo.


