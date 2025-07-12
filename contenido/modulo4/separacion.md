
# Separación entre interfaz y detalle de implementación

Uno de los principios fundamentales del diseño de software bien estructurado es la **separación entre interfaz y detalle de implementación**. Esta práctica permite desarrollar sistemas modulares, mantenibles y fáciles de extender. En C++, este principio se aplica tanto en el diseño de clases como en la organización del código fuente (archivos `.h` y `.cpp`), y se ve reforzado mediante el uso de **interfaces puras** y **encapsulamiento**.

## ¿Qué significa este principio?

Separar la **interfaz** de la **implementación** implica:

* **Interfaz**: es la definición pública de cómo se puede interactuar con un componente (por ejemplo, los métodos públicos de una clase).
* **Implementación**: es el código interno que realiza las tareas necesarias para cumplir lo que promete la interfaz.

## Beneficios de esta separación

* **Encapsulamiento**: oculta los detalles internos al usuario del componente.
* **Modularidad**: facilita el desarrollo y prueba independiente de las partes del sistema.
* **Reutilización**: promueve el uso de interfaces comunes en distintos contextos.
* **Mantenimiento**: permite cambiar la implementación sin afectar al código que depende de la interfaz.
* **Polimorfismo**: permite trabajar con distintos tipos que implementan la misma interfaz.



## Separación en la práctica: Archivos `.h` y `.cpp`

En C++, la convención general es declarar la interfaz en un archivo `.h` (cabecera) y definir la implementación en un archivo `.cpp`.

**Archivo `Operacion.h`**

```cpp
#pragma once

class Operacion {
public:
    virtual int aplicar(int a, int b) const = 0;
    virtual ~Operacion() = default;
};
```

**Archivo `Suma.cpp`**

```cpp
#include "Operacion.h"

class Suma : public Operacion {
public:
    int aplicar(int a, int b) const override {
        return a + b;
    }
};
```


## Separación mediante clases abstractas (interfaces puras)

En proyectos más complejos, es común definir una **interfaz pura** que establece el contrato, y luego ofrecer una o varias clases concretas que implementan dicha interfaz:

```cpp
// Interfaz pura
class Dibujable {
public:
    virtual void dibujar() const = 0;
    virtual ~Dibujable() = default;
};

// Implementación concreta
class Circulo : public Dibujable {
public:
    void dibujar() const override {
        std::cout << "Dibujando un círculo\n";
    }
};
```

Este enfoque permite que otras partes del programa trabajen únicamente con `Dibujable`, sin necesidad de conocer cómo se dibuja un `Circulo` o un `Rectangulo`.


## Ejemplo completo con separación

```cpp
// Archivo: Procesador.h
#pragma once
#include <string>

class Procesador {
public:
    virtual void procesar(const std::string& dato) = 0;
    virtual ~Procesador() = default;
};
```

```cpp
// Archivo: ProcesadorConsola.cpp
#include "Procesador.h"
#include <iostream>

class ProcesadorConsola : public Procesador {
public:
    void procesar(const std::string& dato) override {
        std::cout << "Procesando en consola: " << dato << '\n';
    }
};
```

```cpp
// Archivo: main.cpp
#include "Procesador.h"
#include <memory>

// Supongamos que se incluye ProcesadorConsola aquí o en otro archivo

int main() {
    std::unique_ptr<Procesador> proc = std::make_unique<ProcesadorConsola>();
    proc->procesar("mensaje");
}
```

