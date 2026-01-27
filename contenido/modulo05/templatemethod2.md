# Ejemplo: Proceso de documentos

## Introducción

Para ilustrar la idea del **Template Method** desde una perspectiva moderna en C++, construiremos un pequeño sistema de **procesamiento de documentos** basado en un *flujo de ejecución fijo* combinado con **pasos personalizados inyectados como funciones**.

El objetivo es que el código cliente pueda ejecutar un proceso estandarizado de:

1. **Abrir** el documento,
2. **Leer** el contenido,
3. **Procesar** la información,
4. **Cerrar** el documento,

sin utilizar clases base, herencia ni métodos virtuales.
Las variaciones de lectura y procesamiento se inyectan como funciones invocables, permitiendo una composición flexible y sin jerarquías.

El ejemplo se organiza en:

* **ProcesoDocumento.hpp / ProcesoDocumento.cpp**: implementación del algoritmo fijo.
* **ProcesosConcretos.hpp / ProcesosConcretos.cpp**: configuraciones concretas del proceso.
* **main.cpp**: código cliente.


## ProcesoDocumento.hpp

```cpp
#pragma once
#include <functional>
#include <string>

class ProcesoDocumento {
private:
    std::function<std::string()> leer_;
    std::function<void(const std::string&)> procesar_;

public:
    ProcesoDocumento(std::function<std::string()> leer,
                     std::function<void(const std::string&)> procesar);

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
#include <utility>

ProcesoDocumento::ProcesoDocumento(
    std::function<std::string()> leer,
    std::function<void(const std::string&)> procesar)
    : leer_(std::move(leer)),
      procesar_(std::move(procesar)) {}

void ProcesoDocumento::ejecutar() const {
    abrir();
    auto contenido = leer_();
    procesar_(contenido);
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
    return ProcesoDocumento(
        []() {
            std::cout << "[Texto] Leyendo texto...\n";
            return std::string("Ejemplo de texto plano.");
        },
        [](const std::string& contenido) {
            std::cout << "[Texto] Procesando contenido: "
                      << contenido << "\n";
        }
    );
}

ProcesoDocumento crear_proceso_csv() {
    return ProcesoDocumento(
        []() {
            std::cout << "[CSV] Leyendo línea CSV...\n";
            return std::string("10,20,30");
        },
        [](const std::string& linea) {
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
    return ProcesoDocumento(
        []() {
            std::cout << "[JSON] Simulando lectura...\n";
            return std::string("{\"clave\":\"valor\"}");
        },
        [](const std::string& contenido) {
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


## Compilación

```bash
g++ main.cpp ProcesoDocumento.cpp ProcesosConcretos.cpp -o proceso_documentos
```


## Añadir un nuevo tipo de documento

Para añadir un nuevo tipo de documento **no es necesario modificar la clase `ProcesoDocumento` ni el algoritmo fijo**.
Basta con definir una nueva función factoría que configure el proceso con los pasos adecuados.

### Ejemplo: documento XML (`ProcesosConcretos.cpp`)

```cpp
ProcesoDocumento crear_proceso_xml() {
    return ProcesoDocumento(
        []() {
            std::cout << "[XML] Leyendo XML...\n";
            return std::string("<root><nodo>valor</nodo></root>");
        },
        [](const std::string& contenido) {
            std::cout << "[XML] Procesando: "
                      << contenido << "\n";
        }
    );
}
```

Y declararla en `ProcesosConcretos.hpp`:

```cpp
ProcesoDocumento crear_proceso_xml();
```

Y finalmente modificamos el fichero `main.cpp`:

```cpp
#include <iostream>
#include "ProcesosConcretos.hpp"

int main() {
    auto procTexto = crear_proceso_texto();
    auto procCSV   = crear_proceso_csv();
    auto procJSON  = crear_proceso_json();
    auto procXML   = crear_proceso_xml(); // NUEVO

    std::cout << "=== Proceso Texto ===\n";
    procTexto.ejecutar();

    std::cout << "\n=== Proceso CSV ===\n";
    procCSV.ejecutar();

    std::cout << "\n=== Proceso JSON ===\n";
    procJSON.ejecutar();

    std::cout << "\n=== Proceso XML ===\n"; // NUEVO
    procXML.ejecutar();

    return 0;
}
```

## Qué no hemos modificado

* No hemos cambiado la clase `ProcesoDocumento`.
* No hemos tocado el **esqueleto del algoritmo**.
* No hemos creado clases derivadas.
* No hemos usado herencia ni métodos virtuales.

Solo hemos añadido:

* Una **nueva configuración del proceso**.
* La inyección de comportamiento variable mediante funciones.



