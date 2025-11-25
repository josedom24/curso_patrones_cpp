# Implementación de Facade con C++

## Estructura y elementos modernos utilizados

La implementación del **Facade** en C++ moderno se organiza alrededor de una clase fachada que ofrece métodos simples y de alto nivel, ocultando la interacción entre múltiples subsistemas. Cada subsistema mantiene su propia responsabilidad, pero el cliente solo interactúa con la fachada.

### 1. **Subsistemas internos**

Representan módulos o componentes que realizan tareas específicas. El cliente no debe conocerlos directamente.

**Elementos de C++ moderno utilizados:**

* Métodos `const` cuando corresponde, para expresar claridad semántica.
* Uso de inicialización moderna y clases con recursos manejados automáticamente (RAII).
* Separación clara de responsabilidades mediante clases ligeras y cohesivas.

### 2. **Clase Fachada**

Actúa como punto de entrada único. Coordina los subsistemas y expone métodos de alto nivel que combinan operaciones internas.

**Elementos de C++ moderno utilizados:**

* Composición de objetos (miembros privados que representan subsistemas).
* Métodos que encapsulan operaciones complejas mediante pasos simples.
* Inicialización directa de subsistemas mediante listas de inicializadores.
* Interfaz simplificada y estable que protege al cliente de cambios internos.

### 3. **Código cliente**

Usa únicamente la fachada. Obtiene los resultados sin comprender ni gestionar la lógica interna.

**Elementos de C++ moderno utilizados:**

* Dependencia reducida y uso intuitivo gracias a la encapsulación fuerte.
* Código más legible, directo y fácil de mantener.

## Diagrama UML

![uml](uml/facade.png)

## Ejemplo genérico

```cpp
#include <iostream>
#include <string>

// ----------------------------------------
// Subsistemas internos
// ----------------------------------------

class SubsistemaA {
public:
    void inicializar() const {
        std::cout << "[A] Inicializando recursos...\n";
    }
    void procesar() const {
        std::cout << "[A] Procesando datos.\n";
    }
};

class SubsistemaB {
public:
    void cargar_configuracion() const {
        std::cout << "[B] Cargando configuración.\n";
    }
    void validar() const {
        std::cout << "[B] Validando parámetros.\n";
    }
};

class SubsistemaC {
public:
    void ejecutar_tarea() const {
        std::cout << "[C] Ejecutando tarea principal.\n";
    }
    void limpiar() const {
        std::cout << "[C] Limpiando recursos.\n";
    }
};

// ----------------------------------------
// Clase Fachada
// ----------------------------------------

class FachadaSistema {
private:
    SubsistemaA a_;
    SubsistemaB b_;
    SubsistemaC c_;

public:
    FachadaSistema() = default;

    // Operación de alto nivel
    void operacion_principal() const {
        std::cout << "=== Iniciando operación principal ===\n";
        a_.inicializar();
        b_.cargar_configuracion();
        b_.validar();
        a_.procesar();
        c_.ejecutar_tarea();
        c_.limpiar();
        std::cout << "=== Operación completada ===\n";
    }

    // Otra operación simplificada
    void operacion_rapida() const {
        std::cout << "=== Operación rápida ===\n";
        a_.procesar();
        c_.ejecutar_tarea();
    }
};

// ----------------------------------------
// Código cliente
// ----------------------------------------

int main() {
    FachadaSistema sistema;

    sistema.operacion_principal();
    std::cout << "\n";
    sistema.operacion_rapida();

    return 0;
}
```

## Puntos clave del ejemplo

* La clase `FachadaSistema` encapsula completamente la interacción entre múltiples subsistemas (`SubsistemaA`, `SubsistemaB`, `SubsistemaC`).
* Los subsistemas **no exponen detalles innecesarios** al cliente: solo la fachada coordina su uso.
* La interfaz de la fachada ofrece métodos de **alto nivel**, fáciles de entender y usar.
* Si los subsistemas cambian internamente, el cliente no necesita ser modificado mientras la fachada mantenga su API.
* El patrón mejora la **modularidad**, disminuye el acoplamiento y aumenta la legibilidad de las operaciones complejas.
