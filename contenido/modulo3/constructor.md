# Ampliación de constructores: control de creación y copia de objetos en C++

En C++ moderno, los constructores no solo sirven para inicializar objetos, sino también para **controlar su creación y su comportamiento frente a la copia y asignación**. Esta capacidad resulta esencial al diseñar clases que deben cumplir **restricciones específicas de uso**, como evitar que se creen múltiples instancias, impedir la copia o controlar la construcción desde funciones determinadas.

Este material presenta dos técnicas fundamentales para lograrlo: los constructores privados y la eliminación de operaciones con `= delete`.

## Constructores privados

Un **constructor privado** es un constructor que **no puede ser invocado desde fuera de la clase**, lo que impide que los objetos se creen libremente desde el exterior. Esta técnica permite **restringir la creación de objetos** a métodos estáticos dentro de la propia clase.

Creando constructores privados conseguimos **controlar la creación de objetos** e **impedir la instanciación directa**.

Veamos un ejemplo: imaginemos una clase `Token` que representa un identificador secreto. No queremos que cualquier parte del código pueda crear instancias libremente. En su lugar, solo queremos permitir su creación **a través de una función controlada** (una "fábrica").


```cpp
#include <iostream>
#include <string>

class Token {
private:
    std::string valor;

    // Constructor privado: solo accesible por funciones amigas
    Token(const std::string& v) : valor(v) {}

public:
    void mostrar() const {
        std::cout << "Token: " << valor << '\n';
    }

    // Función amiga que puede construir objetos Token
    friend Token crearTokenSeguro();
};

// Función amiga que puede acceder al constructor privado
Token crearTokenSeguro() {
    // Aquí podríamos generar un valor aleatorio o aplicar validación
    return Token("ABC123");
}

int main() {
    // Token t("XYZ"); //  Error: constructor es privado
    Token t = crearTokenSeguro(); //  Creación controlada
    t.mostrar();
}
```

* Hemos **encapsulado la construcción** del objeto `Token`.
* Obligamos a que los objetos se creen **solo desde una función validada o controlada**.
* Facilitar que la creación del objeto incluya pasos como validación, logging, generación de valores únicos, etc.

##  Eliminar constructor de copia y operador de asignación con `= delete`


C++ permite **eliminar explícitamente** funciones, incluyendo constructores y operadores. Esto significa que el compilador **no generará** versiones por defecto y **prohibirá su uso**.

```cpp
class Conexion {
public:
    Conexion() = default;

    Conexion(const Conexion&) = delete;            // eliminar copia
    Conexion& operator=(const Conexion&) = delete; // eliminar asignación
};
```

Esta técnica sirve para:

* Impedir copias accidentales de objetos con recursos no compartibles (archivos, sockets, memoria exclusiva).
* Hacer explícito en el diseño que la clase **no debe ser copiada** ni asignada.
* Reforzar el principio de **única propiedad** o **movilidad exclusiva** de un recurso.

Veamos un ejemplo:

```cpp
class Archivo {
public:
    Archivo(const std::string& nombre) {
        std::cout << "Abriendo archivo: " << nombre << '\n';
    }

    Archivo(const Archivo&) = delete;            // prohibir copia
    Archivo& operator=(const Archivo&) = delete; // prohibir asignación
};

int main() {
    Archivo a("datos.txt");
    // Archivo b = a;          //  Error: copia eliminada
    // Archivo c;
    // c = a;                  //  Error: asignación eliminada
}
```

