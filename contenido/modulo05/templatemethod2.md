# Ejemplo: Proceso de documentos

## Introducción

Para ilustrar la idea del **Template Method** desde una perspectiva moderna en C++, construiremos un pequeño sistema de **procesamiento de documentos** basado en un *flujo de ejecución fijo* combinado con **pasos personalizados inyectados como funciones**.

El objetivo es que el código cliente pueda ejecutar un proceso estandarizado de:

1. **abrir** el documento,
2. **leer** el contenido,
3. **procesar** la información,
4. **cerrar** el documento,

sin utilizar clases base, herencia ni métodos virtuales.
Las variaciones de lectura y procesamiento se inyectan como funciones invocables, permitiendo una composición flexible y sin jerarquías.

El ejemplo se organiza en:

* **ProcesoDocumento.hpp / ProcesoDocumento.cpp** – implementación del algoritmo fijo
* **ProcesosConcretos.hpp / ProcesosConcretos.cpp** – configuraciones concretas del proceso
* **main.cpp** – código cliente

## ProcesoDocumento.hpp

```cpp
#pragma once
#include <functional>

class ProcesoDocumento {
private:
    std::function<void()> leer_;
    std::function<void()> procesar_;

public:
    ProcesoDocumento(std::function<void()> leer,
                     std::function<void()> procesar);

    void ejecutar() const;

private:
    void abrir() const;
    void cerrar() const;
};
```

## ProcesoDocumento.cpp

```cpp
#include "ProcesoDocumento.hpp"
#include <iostream>

ProcesoDocumento::ProcesoDocumento(std::function<void()> leer,
                                   std::function<void()> procesar)
    : leer_(std::move(leer)),
      procesar_(std::move(procesar)) {}

void ProcesoDocumento::ejecutar() const {
    abrir();
    leer_();
    procesar_();
    cerrar();
}

void ProcesoDocumento::abrir() const {
    std::cout << "[ProcesoDocumento] Abriendo documento...\n";
}

void ProcesoDocumento::cerrar() const {
    std::cout << "[ProcesoDocumento] Cerrando documento.\n";
}
```

## ProcesosConcretos.hpp

```cpp
#pragma once
#include "ProcesoDocumento.hpp"

// Funciones factoría que configuran distintos procesos
ProcesoDocumento crear_proceso_texto();
ProcesoDocumento crear_proceso_csv();
ProcesoDocumento crear_proceso_json();
```

## ProcesosConcretos.cpp

```cpp
#include "ProcesosConcretos.hpp"
#include <iostream>
#include <sstream>

ProcesoDocumento crear_proceso_texto() {
    std::string contenido = "Ejemplo de texto plano.";

    return ProcesoDocumento(
        [contenido]() {
            std::cout << "[Texto] Leyendo texto...\n";
        },
        [contenido]() {
            std::cout << "[Texto] Procesando contenido: "
                      << contenido << "\n";
        }
    );
}

ProcesoDocumento crear_proceso_csv() {
    std::string linea = "10,20,30";

    return ProcesoDocumento(
        [linea]() {
            std::cout << "[CSV] Leyendo línea CSV...\n";
        },
        [linea]() {
            std::cout << "[CSV] Procesando valores: ";
            std::stringstream ss(linea);
            std::string valor;
            while (std::getline(ss, valor, ',')) {
                std::cout << valor << " ";
            }
            std::cout << "\n";
        }
    );
}

ProcesoDocumento crear_proceso_json() {
    std::string contenido = "{\"clave\":\"valor\"}";

    return ProcesoDocumento(
        [contenido]() {
            std::cout << "[JSON] Simulando lectura...\n";
        },
        [contenido]() {
            std::cout << "[JSON] Procesando JSON: "
                      << contenido << "\n";
        }
    );
}
```

## main.cpp

```cpp
#include <iostream>
#include "ProcesosConcretos.hpp"

int main() {
    auto procTexto = crear_proceso_texto();
    auto procCSV   = crear_proceso_csv();
    auto procJSON  = crear_proceso_json();

    std::cout << "=== Proceso Texto ===\n";
    procTexto.ejecutar();

    std::cout << "\n=== Proceso CSV ===\n";
    procCSV.ejecutar();

    std::cout << "\n=== Proceso JSON ===\n";
    procJSON.ejecutar();

    return 0;
}
```

Recuerda que debemos realizar la compilación de la siguiente manera:

```bash
g++ main.cpp ProcesoDocumento.cpp ProcesosConcretos.cpp -o proceso_documentos
```

## Añadir un nuevo tipo de documento

Para añadir un nuevo tipo de documento no es necesario modificar ninguna clase existente.
Basta con definir una nueva función factoría que configure el proceso con los pasos adecuados.

### Ejemplo: documento XML (`ProcesosConcretos.cpp`)

```cpp
ProcesoDocumento crear_proceso_xml() {
    std::string contenido = "<root><nodo>valor</nodo></root>";

    return ProcesoDocumento(
        [contenido]() {
            std::cout << "[XML] Leyendo XML...\n";
        },
        [contenido]() {
            std::cout << "[XML] Procesando: " << contenido << "\n";
        }
    );
}
```

Y declararla en `ProcesosConcretos.hpp`:

```cpp
ProcesoDocumento crear_proceso_xml();
```

## Qué no hemos modificado

* No hemos cambiado la clase `ProcesoDocumento`.
* No hemos tocado el algoritmo fijo de ejecución.
* No hemos creado clases derivadas.
* No hemos escrito métodos virtuales.

Solo hemos:

1. añadido una **nueva función factoría** que configura un proceso concreto,
2. inyectado el comportamiento variable mediante funciones,
3. utilizado el nuevo proceso desde el código cliente.

