# Ejemplo: Editor de texto con historial (undo)

## Introducción

Para ilustrar el patrón **Memento** en un contexto realista, construiremos un pequeño **editor de texto** que permite guardar y restaurar versiones anteriores del contenido.

El objetivo del sistema es permitir que el editor pueda:

* **guardar** su estado actual (el texto completo),
* **restaurar** un estado anterior cuando el usuario solicita un **"Undo"**,
* sin exponer los detalles internos de cómo el editor almacena su estado.

Cada estado guardado será un **memento**, que mantiene encapsulado el contenido del texto.
El código cliente trabajará exclusivamente con:

* la clase `Editor` (Originador),
* la clase `Historial` (Cuidador), encargada de almacenar los mementos,
* y la clase `Memento`, que captura el estado del editor sin exponerlo.

A continuación se muestra el código completo dividido en:

* **Memento.hpp** – clase que encapsula el estado
* **Editor.hpp** – originador
* **Historial.hpp** – cuidador que gestiona el historial
* **main.cpp** – código cliente


## Memento.hpp

```cpp
#pragma once
#include <string>

// ------------------------------------------------------------
// Clase Memento (estado encapsulado)
// ------------------------------------------------------------
class Memento {
private:
    std::string estado_;

    // Solo el Editor puede acceder al contenido del memento
    friend class Editor;

    explicit Memento(std::string estado)
        : estado_(std::move(estado)) {}

public:
    // No se expone nada públicamente
};
```


## Editor.hpp

```cpp
#pragma once
#include <string>
#include <memory>
#include "Memento.hpp"

// ------------------------------------------------------------
// Clase Originador: Editor
// ------------------------------------------------------------
class Editor {
private:
    std::string texto_;

public:
    explicit Editor(std::string inicial = "")
        : texto_(std::move(inicial)) {}

    void escribir(const std::string& nuevo) {
        texto_ += nuevo;
    }

    void mostrar() const {
        std::cout << "Contenido actual: \"" << texto_ << "\"\n";
    }

    // Crear memento
    std::unique_ptr<Memento> crear_memento() const {
        return std::unique_ptr<Memento>(new Memento(texto_));
    }

    // Restaurar desde un memento
    void restaurar(const Memento& m) {
        texto_ = m.estado_;
    }
};
```

## Historial.hpp

```cpp
#pragma once
#include <vector>
#include <memory>
#include "Memento.hpp"

// ------------------------------------------------------------
// Clase Cuidador: Historial de estados
// ------------------------------------------------------------
class Historial {
private:
    std::vector<std::unique_ptr<Memento>> historial_;

public:
    void guardar(std::unique_ptr<Memento> m) {
        historial_.push_back(std::move(m));
    }

    const Memento* ultimo() const {
        if (historial_.empty()) return nullptr;
        return historial_.back().get();
    }

    void deshacer_ultimo() {
        if (!historial_.empty())
            historial_.pop_back();
    }
};
```

## main.cpp

```cpp
#include <iostream>
#include "Editor.hpp"
#include "Historial.hpp"

int main() {
    Editor editor("Hola");
    Historial historial;

    editor.mostrar();
    historial.guardar(editor.crear_memento());

    editor.escribir(", mundo");
    editor.mostrar();
    historial.guardar(editor.crear_memento());

    editor.escribir("!!!");
    editor.mostrar();

    // --- Undo ---
    std::cout << "\nDeshaciendo...\n";
    if (const Memento* m = historial.ultimo()) {
        editor.restaurar(*m);
        historial.deshacer_ultimo();
    }
    editor.mostrar();

    std::cout << "\nDeshaciendo...\n";
    if (const Memento* m = historial.ultimo()) {
        editor.restaurar(*m);
        historial.deshacer_ultimo();
    }
    editor.mostrar();

    return 0;
}
```


## Añadir un nuevo tipo de estado guardado

Supongamos que queremos guardar **también el estilo del texto**, no solo el contenido.
Por ejemplo, fuente, tamaño o color.

### Qué debemos añadir

1. **Un nuevo tipo de memento**, por ejemplo `MementoFormato`, con más información.
2. **Un nuevo método en `Editor` para crear ese memento avanzado**.
3. **Cambios mínimos en el cliente si quiere usarlo**.

### Qué no modificamos

* No modificamos el `Memento` original.
* No modificamos el historial básico.
* No modificamos el concepto general de *guardar/restaurar estado*.

Solo añadimos:

1. Un **nuevo memento concreto** si se desea guardar más información.
2. Métodos opcionales en el editor para trabajar con ese nuevo estado.
3. Opcionalmente, un nuevo historial especializado.

