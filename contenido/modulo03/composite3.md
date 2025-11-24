# Ejemplo: Sistema de archivos

## Introducción

Para ilustrar el patrón **Composite** en un escenario realista, construiremos un pequeño modelo de un **sistema de archivos**.

El objetivo es permitir que el código cliente trabaje con:

* **Archivos** (elementos indivisibles)
* **Directorios** (contenedores de archivos y otros directorios)

Cada elemento del sistema implementa la interfaz común `Elemento`, que define la operación `mostrar()`.

Los **Directorios** son componentes compuestos que almacenan una colección de `std::unique_ptr<Elemento>`.
Los **Archivos** son componentes hoja.

Dividiremos el código en tres partes:

* **Elementos.hpp** – interfaz común y productos (hoja y compuesto)
* **main.cpp** – código cliente que usa la estructura

## Elementos.hpp

```cpp
#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// ----------------------------------------
// Interfaz base del componente
// ----------------------------------------
class Elemento {
public:
    virtual ~Elemento() = default;
    virtual void mostrar(int indentacion = 0) const = 0;
};

// ----------------------------------------
// Componente hoja: Archivo
// ----------------------------------------
class Archivo : public Elemento {
private:
    std::string nombre_;

public:
    explicit Archivo(std::string nombre)
        : nombre_(std::move(nombre)) {}

    void mostrar(int indentacion = 0) const override {
        std::cout << std::string(indentacion, ' ')
                  << "- " << nombre_ << "\n";
    }
};

// ----------------------------------------
// Componente compuesto: Directorio
// ----------------------------------------
class Directorio : public Elemento {
private:
    std::string nombre_;
    std::vector<std::unique_ptr<Elemento>> hijos_;

public:
    explicit Directorio(std::string nombre)
        : nombre_(std::move(nombre)) {}

    // Añadir un elemento hijo
    void agregar(std::unique_ptr<Elemento> elemento) {
        hijos_.push_back(std::move(elemento));
    }

    void mostrar(int indentacion = 0) const override {
        std::cout << std::string(indentacion, ' ')
                  << "+ " << nombre_ << "/\n";

        for (const auto& hijo : hijos_) {
            hijo->mostrar(indentacion + 2); // recursión
        }
    }
};
```

## main.cpp

```cpp
#include "Elementos.hpp"

int main() {
    // Crear directorio raíz
    auto raiz = std::make_unique<Directorio>("home");

    // Añadir archivos a la raíz
    raiz->agregar(std::make_unique<Archivo>("notas.txt"));
    raiz->agregar(std::make_unique<Archivo>("foto.png"));

    // Crear subdirectorio
    auto documentos = std::make_unique<Directorio>("documentos");
    documentos->agregar(std::make_unique<Archivo>("cv.pdf"));
    documentos->agregar(std::make_unique<Archivo>("proyecto.docx"));

    // Insertar subdirectorio en la raíz
    raiz->agregar(std::move(documentos));

    // Mostrar estructura completa
    raiz->mostrar();

    return 0;
}
```
## Añadir un nuevo tipo de elemento

El patrón Composite facilita añadir nuevos componentes sin modificar las clases existentes.
Por ejemplo, queremos añadir un **Enlace simbólico** (`Enlace`) que apunta a otro `Elemento`.

### Nuevo producto: Enlace (hoja especial)

Añádelo al final de `Elementos.hpp`:

```cpp
// ----------------------------------------
// Nuevo tipo de hoja: Enlace simbólico
// ----------------------------------------
class Enlace : public Elemento {
private:
    std::string nombre_;
    const Elemento* objetivo_;  // no posee, solo referencia

public:
    Enlace(std::string nombre, const Elemento* objetivo)
        : nombre_(std::move(nombre)), objetivo_(objetivo) {}

    void mostrar(int indentacion = 0) const override {
        std::cout << std::string(indentacion, ' ')
                  << "- " << nombre_
                  << " -> (enlace a otro elemento)\n";
    }
};
```

### Usarlo desde `main.cpp`

```cpp
auto archivoImportante = std::make_unique<Archivo>("importante.txt");
auto* ptrArchivoImportante = archivoImportante.get();

raiz->agregar(std::move(archivoImportante));

// Crear enlace simbólico al archivo anterior
raiz->agregar(std::make_unique<Enlace>("link_importante", ptrArchivoImportante));
```

### Qué no hemos modificado

* No se ha cambiado la interfaz `Elemento`
* No se ha cambiado `Directorio`
* No se ha cambiado `Archivo`
* No se ha modificado `mostrar()` en los componentes existentes

Solo hemos añadido:

1. Una nueva clase hoja (`Enlace`)
2. Una línea en el `main.cpp` si queremos usarla

