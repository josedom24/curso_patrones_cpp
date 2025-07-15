# Plantilla de clase: `std::optional`

Una **plantilla de clase** (en inglés *class template*) es un **mecanismo del lenguaje C++** que permite **definir clases genéricas**, es decir, clases que funcionan con uno o más **tipos de datos que se especifican al usarlas**.

Permiten **escribir código reutilizable y flexible**, sin duplicar implementaciones para cada tipo de dato.
Con ellas, una única definición de clase puede adaptarse a múltiples tipos.

En la STL tenemos varias plantillas de clases definidas:

## Plantilla `std::optional`

`std::optional` es una **plantilla de clase** introducida en C++17, definida en el encabezado `<optional>`, que representa **un objeto que puede contener un valor de tipo `T` o no contener ningún valor**.

`std::optional<T>` es un **wrapper de valor** que permite modelar la presencia o ausencia de un valor de tipo `T`, de forma segura y expresiva, sin necesidad de usar punteros o valores centinela.

Es una clase plantilla que:

* Puede estar en **estado vacío** (no contiene valor).
* Puede estar en **estado ocupado** (contiene un valor de tipo `T`).
* Proporciona operadores y funciones miembro para:
    * Consultar si hay valor (`has_value()`, `operator bool` (se puede usar como una expresión lógica por ejemplo en un `if`)).
    * Acceder al valor (`*`, `value()`).
    * Obtener un valor por defecto (`value_or()`).
    * Construir y destruir el valor de forma controlada.

Veamos un ejemplo:

```cpp
#include <optional>
#include <string>
#include <iostream>

std::optional<std::string> obtenerNombreUsuario(int id) {
    if (id == 0) return std::nullopt; // sin valor
    return "Juan Pérez";
}

int main() {
    std::optional<std::string> nombre = obtenerNombreUsuario(0);

    if (nombre.has_value()) {   //Se puede pponer también como if (nombre)
        std::cout << "Usuario: " << *nombre << "\n";
    } else {
        std::cout << "Usuario no encontrado.\n";
    }
}
```
