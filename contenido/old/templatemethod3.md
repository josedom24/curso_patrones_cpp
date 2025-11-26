# Ejemplo: Proceso de documentos

## Introducción

Para ilustrar el patrón **Template Method** en un contexto realista, construiremos un pequeño sistema de **procesamiento de documentos**.
El objetivo del sistema es permitir que el código cliente ejecute un flujo estandarizado de procesamiento sin conocer los detalles concretos de cada tipo de documento.

El flujo completo del proceso está **fijado por la clase base**, e incluye:

1. **abrir** el documento,
2. **leer** su contenido,
3. **procesar** la información,
4. ejecutar un **hook opcional**,
5. **cerrar** el documento.

Las variaciones aparecen en los pasos especializados, como la forma de leer y procesar cada tipo de documento.

Implementaremos tres tipos concretos de procesos:

* **Documento de texto** (lee texto plano),
* **Documento CSV** (parsea valores separados por comas),
* **Documento JSON** (simulación de lectura JSON).

Cada uno implementa los pasos personalizados, pero todos utilizan el flujo estructurado definido por la clase abstracta `ProcesoDocumento`.

A continuación se muestra el código completo dividido en:

* **ProcesoDocumento.hpp** – clase base y su algoritmo plantilla
* **ProcesosConcretos.hpp** – implementaciones concretas
* **main.cpp** – código cliente

## ProcesoDocumento.hpp

```cpp
#pragma once
#include <iostream>
#include <string>

// --------------------------------------------------------------
// Clase base: define el algoritmo plantilla
// --------------------------------------------------------------
class ProcesoDocumento {
public:
    virtual ~ProcesoDocumento() = default;

    // Método plantilla (no puede ser sobrescrito)
    void ejecutar() final {
        abrir();
        leer();
        procesar();
        hook_post_procesado();   // Punto de extensión opcional
        cerrar();
    }

protected:
    // Pasos obligatorios a implementar por las subclases
    virtual void leer() = 0;
    virtual void procesar() = 0;

    // Pasos con implementación fija
    void abrir() {
        std::cout << "[ProcesoDocumento] Abriendo documento...\n";
    }

    void cerrar() {
        std::cout << "[ProcesoDocumento] Cerrando documento.\n";
    }

    // Hook opcional (vacío por defecto)
    virtual void hook_post_procesado() {}
};
```

## ProcesosConcretos.hpp

```cpp
#pragma once
#include "ProcesoDocumento.hpp"
#include <iostream>
#include <sstream>

// --------------------------------------------------------------
// Documento de texto
// --------------------------------------------------------------
class ProcesoTexto : public ProcesoDocumento {
private:
    std::string contenido_ = "Ejemplo de texto plano.";

protected:
    void leer() override {
        std::cout << "[Texto] Leyendo texto...\n";
    }

    void procesar() override {
        std::cout << "[Texto] Procesando contenido: " << contenido_ << "\n";
    }

    void hook_post_procesado() override {
        std::cout << "[Texto] Hook: Conteo de caracteres = "
                  << contenido_.size() << "\n";
    }
};

// --------------------------------------------------------------
// Documento CSV
// --------------------------------------------------------------
class ProcesoCSV : public ProcesoDocumento {
private:
    std::string linea_ = "10,20,30";

protected:
    void leer() override {
        std::cout << "[CSV] Leyendo línea CSV...\n";
    }

    void procesar() override {
        std::cout << "[CSV] Procesando valores: ";
        std::stringstream ss(linea_);
        std::string valor;
        while (std::getline(ss, valor, ',')) {
            std::cout << valor << " ";
        }
        std::cout << "\n";
    }
};

// --------------------------------------------------------------
// Documento JSON (simulado)
// --------------------------------------------------------------
class ProcesoJSON : public ProcesoDocumento {
private:
    std::string contenido_ = R"({"clave":"valor"})";

protected:
    void leer() override {
        std::cout << "[JSON] Simulando lectura de JSON...\n";
    }

    void procesar() override {
        std::cout << "[JSON] Procesando contenido JSON: " << contenido_ << "\n";
    }
};
```

## main.cpp

```cpp
#include "ProcesosConcretos.hpp"

void cliente(ProcesoDocumento& proceso) {
    proceso.ejecutar();
}

int main() {
    ProcesoTexto procTexto;
    ProcesoCSV procCSV;
    ProcesoJSON procJSON;

    std::cout << "=== Proceso Texto ===\n";
    cliente(procTexto);

    std::cout << "\n=== Proceso CSV ===\n";
    cliente(procCSV);

    std::cout << "\n=== Proceso JSON ===\n";
    cliente(procJSON);

    return 0;
}
```

## Añadir un nuevo tipo de documento

**Para añadir un nuevo proceso no modificamos la clase base `ProcesoDocumento`, solo añadimos nuevas clases.**

Supongamos que queremos añadir un nuevo proceso: **documento XML**.

### Añadir el nuevo proceso concreto en `ProcesosConcretos.hpp`

```cpp
class ProcesoXML : public ProcesoDocumento {
private:
    std::string contenido_ = "<root><nodo>valor</nodo></root>";

protected:
    void leer() override {
        std::cout << "[XML] Leyendo XML...\n";
    }

    void procesar() override {
        std::cout << "[XML] Procesando XML: " << contenido_ << "\n";
    }
};
```

### Usar el nuevo proceso en `main.cpp`

```cpp
ProcesoXML procXML;
cliente(procXML);
```

### Qué no hemos modificado

* No hemos modificado la interfaz `ProcesoDocumento`.
* No hemos modificado el método plantilla `ejecutar()`.
* No hemos modificado el código de `cliente`.

Solo hemos:

1. añadido un **nuevo proceso concreto** (`ProcesoXML`),
2. y opcionalmente una línea en `main.cpp` para utilizarlo.

