# Fluidez de métodos

La fluidez de métodos es una técnica de diseño que permite encadenar múltiples llamadas a métodos sobre un mismo objeto de manera legible y expresiva. En C++, esta técnica se implementa generalmente mediante el retorno de una referencia al objeto actual desde los métodos modificadores, utilizando la expresión `return *this`.

Veamos un ejemplo donde tenemos la necesidad de realizar múltiples modificaciones sobre un objeto. En lugar de efectuar llamadas separadas:

```cpp
obj.setNombre("Alice");
obj.setEdad(30);
obj.setActivo(true);
```

la fluidez permite:

```cpp
obj.setNombre("Alice").setEdad(30).setActivo(true);
```

Este enfoque no solo mejora la legibilidad, sino que también facilita la escritura de código más compacto, con menor riesgo de errores por omisión o repetición.

## Implementación técnica

Para permitir la fluidez, los métodos deben retornar una referencia al objeto que los contiene. En el cuerpo del método, esto se logra mediante `return *this;`. A continuación, se muestra un ejemplo básico:

```cpp
class Persona {
private:
    std::string nombre_;
    int edad_ = 0;
    bool activo_ = false;

public:
    Persona& setNombre(const std::string& nombre) {
        nombre_ = nombre;
        return *this;
    }

    Persona& setEdad(int edad) {
        edad_ = edad;
        return *this;
    }

    Persona& setActivo(bool activo) {
        activo_ = activo;
        return *this;
    }

    void imprimir() const {
        std::cout << "Nombre: " << nombre_ << ", Edad: " << edad_
                  << ", Activo: " << std::boolalpha << activo_ << '\n';
    }
};


int main() {
    Persona p;
    p.setNombre("Carlos").setEdad(45).setActivo(true).imprimir();
}
```
* **Tipo de retorno**: El tipo de retorno debe ser una **referencia no constante al objeto actual** (`T&`). Esto permite continuar modificando el objeto. Si se desea usar fluidez en objetos constantes, se puede sobrecargar el método con una versión `const` que retorne `const T&`. Ejemplo:

```cpp
class Ejemplo {
public:
    Ejemplo& metodoNoConst() {
        // modificación
        return *this;
    }

    const Ejemplo& metodoConst() const {
        // sin modificación
        return *this;
    }
};
```
## Ventajas

* **Código más legible y expresivo**.
* **Reducción de errores** al evitar múltiples referencias repetidas al objeto.
* **Mejor experiencia de uso para el cliente de la clase**, especialmente en APIs públicas.

## Desventajas

* Puede **ocultar errores de estado mutable** si se abusa de la modificación encadenada sin control.
* Dificulta la depuración línea a línea, ya que varias operaciones pueden estar condensadas en una única línea.
* El uso excesivo puede **romper la separación de responsabilidades** si la fluidez invade la lógica de negocio.

