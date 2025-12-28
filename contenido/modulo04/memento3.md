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

Supongamos que queremos guardar **también el estilo del texto**, además del contenido. Por ejemplo: **fuente**, **tamaño** y **color**.

### Creamos `MementoFormato.hpp`

Creamos un **nuevo memento concreto** `MementoFormato`, independiente del anterior.

```cpp
#pragma once
#include <string>

// ------------------------------------------------------------
// Memento avanzado: contenido + formato
// ------------------------------------------------------------
class MementoFormato {
private:
    std::string texto_;
    std::string fuente_;
    int tamaño_;
    std::string color_;

    // Solo el Editor puede crear y leer este memento
    friend class Editor;

    MementoFormato(std::string texto,
                   std::string fuente,
                   int tamaño,
                   std::string color)
        : texto_(std::move(texto))
        , fuente_(std::move(fuente))
        , tamaño_(tamaño)
        , color_(std::move(color)) {}

public:
    // Sin interfaz pública
};
```

### En `Editor.hpp`

Añadimos **estado de formato** y **métodos opcionales**. No tocamos el `Memento` original.

```cpp
#include "MementoFormato.hpp"

// ------------------------------------------------------------
// Editor (extensión opcional)
// ------------------------------------------------------------
class Editor {
private:
    std::string texto_;
    std::string fuente_ = "Arial";
    int tamaño_ = 12;
    std::string color_ = "Negro";

public:
    // Métodos existentes no cambian

    void cambiar_formato(std::string fuente, int tamaño, std::string color) {
        fuente_ = std::move(fuente);
        tamaño_ = tamaño;
        color_ = std::move(color);
    }

    void mostrar() const {
        std::cout << "Texto: \"" << texto_ << "\"\n"
                  << "Formato: " << fuente_
                  << ", " << tamaño_
                  << ", " << color_ << "\n";
    }

    // Crear memento avanzado
    std::unique_ptr<MementoFormato> crear_memento_formato() const {
        return std::unique_ptr<MementoFormato>(
            new MementoFormato(texto_, fuente_, tamaño_, color_));
    }

    // Restaurar desde memento avanzado
    void restaurar(const MementoFormato& m) {
        texto_  = m.texto_;
        fuente_ = m.fuente_;
        tamaño_ = m.tamaño_;
        color_  = m.color_;
    }
};
```

### En `main.cpp`

El cliente **elige conscientemente** usar el nuevo memento. El historial básico **no se toca**.

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
    editor.cambiar_formato("Courier", 14, "Azul");
    editor.mostrar();

    // Guardamos estado avanzado
    auto m_formato = editor.crear_memento_formato();

    // Cambiamos todo
    editor.escribir("!!!");
    editor.cambiar_formato("Times", 18, "Rojo");
    editor.mostrar();

    // Restauramos estado avanzado
    std::cout << "\nRestaurando estado con formato...\n";
    editor.restaurar(*m_formato);
    editor.mostrar();

    return 0;
}

```

## Qué no hemos modificado

* `Memento` original.
* `Historial` básico.
* Lógica general de undo.
* Interfaz pública del patrón.

Se ha creado:

1. Un **nuevo memento concreto**
2. Métodos opcionales en el `Editor`
3. Uso explícito desde el cliente

