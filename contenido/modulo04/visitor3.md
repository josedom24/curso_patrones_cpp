# Ejemplo: Sistema de procesamiento de documentos

## Introducción

Para ilustrar el patrón **Visitor**, construiremos un sistema formado por distintos tipos de **documentos** dentro de una aplicación empresarial.

Por ejemplo:

* `Factura`
* `Informe`

En este tipo de sistemas es habitual necesitar múltiples operaciones sobre los documentos:

* Mostrar información
* Validar contenido
* Exportar a distintos formatos (JSON, XML, etc.)

El objetivo es permitir añadir **nuevas operaciones** **sin modificar las clases de los documentos**, delegando dichas operaciones en objetos visitante.

El ejemplo se organiza en:

* **Documentos.hpp / Documentos.cpp**: jerarquía de documentos visitables.
* **Visitantes.hpp / Visitantes.cpp**: interfaz visitante y visitantes concretos.
* **main.cpp**: código cliente.

## Documentos.hpp

```cpp
#pragma once
#include <string>

// Declaración anticipada
class Visitante;

// ----------------------------------------
// Interfaz base del documento
// ----------------------------------------
class Documento {
public:
    virtual ~Documento() = default;
    virtual void accept(Visitante& v) = 0;
};

// ----------------------------------------
// Documento concreto: Factura
// ----------------------------------------
class Factura : public Documento {
private:
    std::string cliente;
    double importe;

public:
    Factura(std::string cliente, double importe);

    void accept(Visitante& v) override;

    // Métodos específicos
    const std::string& getCliente() const;
    double getImporte() const;
};

// ----------------------------------------
// Documento concreto: Informe
// ----------------------------------------
class Informe : public Documento {
private:
    std::string titulo;
    int paginas;

public:
    Informe(std::string titulo, int paginas);

    void accept(Visitante& v) override;

    // Métodos específicos
    const std::string& getTitulo() const;
    int getPaginas() const;
};
```

## Documentos.cpp

```cpp
#include "Documentos.hpp"
#include "Visitantes.hpp"

// ----------------------------------------
// Constructores
// ----------------------------------------
Factura::Factura(std::string cliente, double importe)
    : cliente(std::move(cliente)), importe(importe) {}

Informe::Informe(std::string titulo, int paginas)
    : titulo(std::move(titulo)), paginas(paginas) {}

// ----------------------------------------
// Double dispatch
// ----------------------------------------
void Factura::accept(Visitante& v) {
    v.visitar(*this);
}

void Informe::accept(Visitante& v) {
    v.visitar(*this);
}

// ----------------------------------------
// Getters
// ----------------------------------------
const std::string& Factura::getCliente() const {
    return cliente;
}

double Factura::getImporte() const {
    return importe;
}

const std::string& Informe::getTitulo() const {
    return titulo;
}

int Informe::getPaginas() const {
    return paginas;
}
```

## Visitantes.hpp

```cpp
#pragma once
#include "Documentos.hpp"

// ----------------------------------------
// Interfaz Visitante
// ----------------------------------------
class Visitante {
public:
    virtual ~Visitante() = default;

    virtual void visitar(Factura&) = 0;
    virtual void visitar(Informe&) = 0;
};

// ----------------------------------------
// Visitante concreto: Mostrar información
// ----------------------------------------
class VisitanteMostrar : public Visitante {
public:
    void visitar(Factura&) override;
    void visitar(Informe&) override;
};

// ----------------------------------------
// Visitante concreto: Validar
// ----------------------------------------
class VisitanteValidar : public Visitante {
public:
    void visitar(Factura&) override;
    void visitar(Informe&) override;
};
```

## Visitantes.cpp

```cpp
#include <iostream>
#include "Visitantes.hpp"

// ----------------------------------------
// VisitanteMostrar
// ----------------------------------------
void VisitanteMostrar::visitar(Factura& f) {
    std::cout << "[Mostrar] Factura\n";
    std::cout << "Cliente: " << f.getCliente() << "\n";
    std::cout << "Importe: " << f.getImporte() << "\n";
}

void VisitanteMostrar::visitar(Informe& i) {
    std::cout << "[Mostrar] Informe\n";
    std::cout << "Título: " << i.getTitulo() << "\n";
    std::cout << "Páginas: " << i.getPaginas() << "\n";
}

// ----------------------------------------
// VisitanteValidar
// ----------------------------------------
void VisitanteValidar::visitar(Factura& f) {
    std::cout << "[Validar] Factura...\n";

    if (f.getImporte() <= 0) {
        std::cout << "Error: importe inválido\n";
    }
}

void VisitanteValidar::visitar(Informe& i) {
    std::cout << "[Validar] Informe...\n";

    if (i.getPaginas() <= 0) {
        std::cout << "Error: número de páginas inválido\n";
    }
}
```

## main.cpp

```cpp
#include <iostream>
#include <vector>
#include <memory>
#include "Visitantes.hpp"

// El cliente opera solo con Documento y Visitante
void cliente(Documento& doc, Visitante& visitante) {
    doc.accept(visitante);
}

int main() {
    std::vector<std::unique_ptr<Documento>> documentos;

    documentos.push_back(std::make_unique<Factura>("Cliente A", 1200.50));
    documentos.push_back(std::make_unique<Informe>("Informe anual", 35));

    VisitanteMostrar mostrar;
    VisitanteValidar validar;

    for (auto& d : documentos) {
        cliente(*d, mostrar);
    }

    std::cout << "\n--- Validando ---\n";

    for (auto& d : documentos) {
        cliente(*d, validar);
    }

    return 0;
}
```

## Compilación

```bash
g++ main.cpp Documentos.cpp Visitantes.cpp -o visitor
```

## Añadir un nuevo visitante

Para añadir una **nueva operación**, **no se modifican los documentos**.

### Nuevo visitante: `VisitanteExportar`

#### Declaración (`Visitantes.hpp`)

```cpp
class VisitanteExportar : public Visitante {
public:
    void visitar(Factura&) override;
    void visitar(Informe&) override;
};
```

#### Implementación (`Visitantes.cpp`)

```cpp
#include <iostream>

// ----------------------------------------
// VisitanteExportar
// ----------------------------------------
void VisitanteExportar::visitar(Factura& f) {
    std::cout << "{ \"tipo\": \"factura\", \"cliente\": \""
              << f.getCliente()
              << "\", \"importe\": "
              << f.getImporte()
              << " }\n";
}

void VisitanteExportar::visitar(Informe& i) {
    std::cout << "{ \"tipo\": \"informe\", \"titulo\": \""
              << i.getTitulo()
              << "\", \"paginas\": "
              << i.getPaginas()
              << " }\n";
}
```

#### Uso desde `main.cpp`

```cpp
VisitanteExportar exportar;

std::cout << "\n--- Exportando ---\n";
for (auto& d : documentos) {
    cliente(*d, exportar);
}
```

## Qué no hemos modificado

* No se ha modificado la interfaz `Documento`.
* No se ha modificado la interfaz `Visitante`.
* No se ha modificado la lógica interna de `Factura` ni `Informe`.
* No se ha modificado la función `cliente`.

Solo hemos añadido:

* Un **nuevo visitante concreto** (`VisitanteExportar`)
* Nuevas operaciones sobre documentos ya existentes
* Uso desde el cliente

