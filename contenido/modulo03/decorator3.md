# Ejemplo: Generador de Markdown

## Introducción

En este ejemplo construimos un **generador de Markdown** que permite partir de un contenido base y **añadir dinámicamente capas de formato**, como:

* títulos
* texto en negrita
* cursiva
* bloques de código

Cada formato se implementa como un **decorador independiente**, que envuelve al componente anterior y añade su responsabilidad sin modificar ninguna clase existente.

El cliente trabaja únicamente con la interfaz común `Markdown`, sin conocer cuántos decoradores hay ni en qué orden se aplican.

El código se divide en:

* `Markdown.hpp` – interfaz base, componente concreto y decoradores
* `main.cpp` – código cliente y composición dinámica

## Markdown.hpp

````cpp
#pragma once
#include <memory>
#include <string>

// ----------------------------------------
// Interfaz base del componente
// ----------------------------------------
class Markdown {
public:
    virtual ~Markdown() = default;
    virtual std::string render() const = 0;
};

// ----------------------------------------
// Componente concreto: texto base
// ----------------------------------------
class TextoMarkdown : public Markdown {
    std::string texto_;

public:
    explicit TextoMarkdown(std::string texto)
        : texto_(std::move(texto)) {}

    std::string render() const override {
        return texto_;
    }
};

// ----------------------------------------
// Clase base del decorador
// ----------------------------------------
class DecoradorMarkdown : public Markdown {
protected:
    std::unique_ptr<Markdown> componente_;

public:
    explicit DecoradorMarkdown(std::unique_ptr<Markdown> componente)
        : componente_(std::move(componente)) {}

    std::string render() const override {
        return componente_->render();
    }
};

// ----------------------------------------
// Decorador concreto: título
// ----------------------------------------
class TituloMarkdown : public DecoradorMarkdown {
    int nivel_;

public:
    TituloMarkdown(std::unique_ptr<Markdown> componente, int nivel)
        : DecoradorMarkdown(std::move(componente)),
          nivel_(nivel) {}

    std::string render() const override {
        return std::string(nivel_, '#') + " " +
               DecoradorMarkdown::render();
    }
};

// ----------------------------------------
// Decorador concreto: negrita
// ----------------------------------------
class NegritaMarkdown : public DecoradorMarkdown {
public:
    using DecoradorMarkdown::DecoradorMarkdown;

    std::string render() const override {
        return "**" + DecoradorMarkdown::render() + "**";
    }
};

// ----------------------------------------
// Decorador concreto: cursiva
// ----------------------------------------
class CursivaMarkdown : public DecoradorMarkdown {
public:
    using DecoradorMarkdown::DecoradorMarkdown;

    std::string render() const override {
        return "*" + DecoradorMarkdown::render() + "*";
    }
};

// ----------------------------------------
// Decorador concreto: bloque de código
// ----------------------------------------
class CodigoMarkdown : public DecoradorMarkdown {
public:
    using DecoradorMarkdown::DecoradorMarkdown;

    std::string render() const override {
        return "```cpp\n" +
               DecoradorMarkdown::render() +
               "\n```";
    }
};
````

## main.cpp

```cpp
#include "Markdown.hpp"
#include <iostream>

int main() {
    std::unique_ptr<Markdown> md =
        std::make_unique<TextoMarkdown>(
            "Ejemplo de Decorator en C++ moderno"
        );

    md = std::make_unique<NegritaMarkdown>(std::move(md));
    md = std::make_unique<CursivaMarkdown>(std::move(md));
    md = std::make_unique<TituloMarkdown>(std::move(md), 2);

    std::cout << md->render() << "\n";
}
```

Salida aproximada:

```markdown
## ***Ejemplo de Decorator en C++ moderno***
```

## Añadir un nuevo decorador

Supongamos que queremos añadir un decorador para **listas Markdown**.

### Nuevo decorador

```cpp
class ListaMarkdown : public DecoradorMarkdown {
public:
    using DecoradorMarkdown::DecoradorMarkdown;

    std::string render() const override {
        return "- " + DecoradorMarkdown::render();
    }
};
```

### Uso en el cliente

```cpp
md = std::make_unique<ListaMarkdown>(std::move(md));
```

## Qué no hemos modificado

* La interfaz `Markdown`
* El componente concreto `TextoMarkdown`
* La clase base `DecoradorMarkdown`
* El código cliente

