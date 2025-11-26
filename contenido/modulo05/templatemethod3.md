# Ejemplo: Proceso de documentos

## Introducción

Para ilustrar la idea del **Template Method** desde una perspectiva moderna en C++, construiremos un pequeño sistema de **procesamiento de documentos** basado en un *flujo de ejecución fijo* combinado con **pasos personalizados inyectados como funciones**.

El objetivo es que el código cliente pueda ejecutar un proceso estandarizado de:

1. **abrir** el documento,
2. **leer** el contenido,
3. **procesar** la información,
4. ejecutar un **hook opcional**,
5. **cerrar** el documento,

pero sin utilizar clases base, herencia ni métodos virtuales.
Las variaciones de lectura, procesamiento y el hook se inyectarán como funciones invocables, permitiendo una composición flexible y sin jerarquías.

A continuación se muestra el código completo dividido en:

* **ProcesoDocumento.hpp** – implementación del algoritmo fijo con funciones inyectadas
* **ProcesosConcretos.hpp** – configuraciones concretas del proceso
* **main.cpp** – código cliente

## ProcesoDocumento.hpp

```cpp
#pragma once
#include <functional>
#include <iostream>

class ProcesoDocumento {
private:
    std::function<void()> leer_;
    std::function<void()> procesar_;

public:
    ProcesoDocumento(std::function<void()> leer,
                     std::function<void()> procesar)
        : leer_(std::move(leer)),
          procesar_(std::move(procesar)) {}

    void ejecutar() const {
        abrir();
        leer_();
        procesar_();
        cerrar();
    }

private:
    void abrir() const {
        std::cout << "[ProcesoDocumento] Abriendo documento...\n";
    }

    void cerrar() const {
        std::cout << "[ProcesoDocumento] Cerrando documento.\n";
    }
};
```

## ProcesosConcretos.hpp

```cpp
#pragma once
#include "ProcesoDocumento.hpp"
#include <iostream>
#include <sstream>

inline ProcesoDocumento crear_proceso_texto() {
    std::string contenido = "Ejemplo de texto plano.";

    return ProcesoDocumento(
        // Captura por valor
        [contenido]() {
            std::cout << "[Texto] Leyendo texto...\n";
        },
        [contenido]() {
            std::cout << "[Texto] Procesando contenido: "
                      << contenido << "\n";
        }
    );
}

inline ProcesoDocumento crear_proceso_csv() {
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

inline ProcesoDocumento crear_proceso_json() {
    std::string contenido = R"({"clave":"valor"})";

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
* `inline`: se usa porque las funciones están definidas en un archivo de cabecera; así evitamos errores de multiple definition al incluirlas desde varios .cpp.

## main.cpp

```cpp
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

## Añadir un nuevo tipo de documento

Supongamos que queremos añadir **documento XML**.
No hay clases que heredar ni métodos virtuales que sobrescribir: basta con inyectar los pasos específicos como funciones.

### En `ProcesosConcretos.hpp`

```cpp
inline ProcesoDocumento crear_proceso_xml() {
    std::string contenido = "<root><nodo>valor</nodo></root>";

    return ProcesoDocumento(
        // leer
        [contenido]() {
            std::cout << "[XML] Leyendo XML...\n";
        },
        // procesar
        [contenido]() {
            std::cout << "[XML] Procesando: " << contenido << "\n";
        }
    );
}
```

### En `main.cpp`

```cpp
auto procXML = crear_proceso_xml();
procXML.ejecutar();
```
### Qué no hemos modificado

* No hemos cambiado `ProcesoDocumento`.
* No hemos tocado el algoritmo fijo.
* No hemos creado clases derivadas.
* No hemos escrito métodos virtuales.

Solo hemos:

1. añadido una nueva función que construye un proceso con sus pasos personalizados,
2. y una llamada en `main.cpp` para ejecutarlo.

