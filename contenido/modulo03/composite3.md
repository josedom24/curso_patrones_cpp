# Ejemplo: Sistema de archivos

## Introducción

Para ilustrar el patrón **Composite** en un escenario realista, construiremos un pequeño modelo de un **sistema de archivos**.

El objetivo es permitir que el código cliente trabaje con:

* **Archivos** (elementos indivisibles)
* **Directorios** (contenedores de archivos y otros directorios)

Cada elemento del sistema implementa la interfaz común `Elemento`, que define la operación `mostrar()`.

Los **Directorios** son componentes compuestos que almacenan una colección de `std::unique_ptr<Elemento>`.
Los **Archivos** son componentes hoja.

Dividiremos el código en dos partes:

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

void cliente(const Elemento& elemento) {
    elemento.mostrar();
}

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
    cliente(*raiz);

    return 0;
}
```

## Añadir un nuevo tipo de elemento

El patrón **Composite** permite ampliar la jerarquía de componentes incorporando nuevos tipos de elementos sin modificar las clases existentes ni el código cliente.

En este caso añadimos un nuevo tipo de elemento al sistema de archivos: un **enlace simbólico**, que representa una referencia a otra ubicación del sistema.

### Nuevo producto Enlace simbólico

Añade la siguiente clase al final de `Elementos.hpp`:

```cpp
// ----------------------------------------
// Nuevo tipo de hoja: Enlace simbólico
// ----------------------------------------
class Enlace : public Elemento {
private:
    std::string nombre_;
    std::string destino_;

public:
    Enlace(std::string nombre, std::string destino)
        : nombre_(std::move(nombre)), destino_(std::move(destino)) {}

    void mostrar(int indentacion = 0) const override {
        std::cout << std::string(indentacion, ' ')
                  << "- " << nombre_
                  << " -> " << destino_
                  << "\n";
    }
};
```

Este nuevo componente implementa la interfaz `Elemento` y se comporta como una **hoja**, ya que no contiene otros elementos.


### Uso desde `main.cpp`

El nuevo tipo de elemento puede utilizarse directamente desde el código cliente:

```cpp
raiz->agregar(std::make_unique<Enlace>("link_importante", "/home/documentos/cv.pdf"));
```

El cliente continúa trabajando con la abstracción común `Elemento`.


### Qué no hemos modificado

Al añadir este nuevo tipo de elemento:

* No se ha modificado la interfaz `Elemento`.
* No se ha modificado la clase `Directorio`.
* No se ha modificado la clase `Archivo`.
* No se ha modificado el comportamiento de `mostrar()` en los componentes existentes.

Solo hemos añadido:

* Un nuevo tipo de hoja (`Enlace`).
* Código de uso en `main.cpp`.


