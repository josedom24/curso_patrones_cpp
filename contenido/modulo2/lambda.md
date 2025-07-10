




Aquí tienes el material didáctico sobre el tema:

---

# 📘 Funciones Avanzadas y Abstracción de Comportamiento

### 🧩 Uso de Lambdas para Comportamiento Flexible en C++ Moderno

---

## 1. Introducción y propósito

En C++ moderno, las **expresiones lambda** permiten definir funciones **de forma concisa**, **en línea** y **flexible**. Este mecanismo forma parte de un conjunto de herramientas que permiten **abstraer comportamiento**, es decir, **parametrizar el *qué hacer*** sin necesidad de crear nuevas clases o funciones independientes.

### ¿Qué problema resuelve?

* Reduce el número de funciones auxiliares “boilerplate”.
* Permite **pasar comportamiento como parámetro**, al estilo funcional.
* Facilita la **configuración dinámica** de algoritmos y estructuras.

### Analogía

Una lambda es como **una receta de cocina escrita al momento**: no necesitas un libro (función global), sino que escribes ahí mismo lo que se necesita hacer, solo para esa ocasión.

---

## 2. Motivación y casos de uso

### Casos comunes donde lambdas aportan valor:

* Ordenación personalizada con `std::sort`.
* Filtrado de datos con `std::find_if`, `std::remove_if`, etc.
* Callbacks y respuestas a eventos (por ejemplo, en GUIs).
* Estrategias o personalización de algoritmos (como en un `Logger`, un `Visitor`, etc.).
* Configuración de comportamiento en objetos reutilizables.

### ¿Qué mejora?

* Evita la creación de clases auxiliares innecesarias.
* Promueve código más expresivo y localizado.
* Permite mayor reutilización de estructuras con comportamiento flexible.

---

## 3. Relación con principios SOLID y buenas prácticas

| Principio                           | Relación con lambdas                                                         |
| ----------------------------------- | ---------------------------------------------------------------------------- |
| **SRP** (Responsabilidad Única)     | La lógica de comportamiento puede aislarse del objeto que lo usa.            |
| **OCP** (Abierto/Cerrado)           | Puedes extender el comportamiento sin modificar estructuras.                 |
| **DIP** (Inversión de dependencias) | El algoritmo depende de funciones proporcionadas externamente (abstracción). |

También se relaciona con:

* **RAII**, al integrarse con smart pointers para comportamiento personalizado al liberar recursos.
* **`std::function`**, que almacena lambdas de forma polimórfica.

---

## 4. Sintaxis y estructura de lambdas

```cpp
[captura](parámetros) -> tipo_retorno {
    cuerpo;
}
```

### Ejemplo básico:

```cpp
auto sumar = [](int a, int b) {
    return a + b;
};

std::cout << sumar(3, 4); // 7
```

### Capturas:

```cpp
int x = 10;
auto imprimir = [x]() { std::cout << "Valor: " << x << '\n'; };
imprimir(); // Valor: 10
```

---

## 5. Ejemplos prácticos y aplicados

### 🔹 Uso con algoritmos estándar

```cpp
#include <algorithm>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> datos = {1, 2, 3, 4, 5, 6};

    // Filtrar números pares
    auto es_par = [](int x) { return x % 2 == 0; };
    auto it = std::find_if(datos.begin(), datos.end(), es_par);

    if (it != datos.end()) {
        std::cout << "Primer par: " << *it << '\n';
    }
}
```

### 🔹 Pasar lambdas como comportamiento a una función

```cpp
void aplicar(std::function<void(int)> f, const std::vector<int>& datos) {
    for (int valor : datos)
        f(valor);
}

int main() {
    std::vector<int> datos = {1, 2, 3};

    aplicar([](int x) { std::cout << "Doble: " << x * 2 << '\n'; }, datos);
}
```

---

## 6. Ventajas, desventajas y consideraciones

### ✅ Ventajas

* **Código más expresivo** y conciso.
* Mayor **reutilización de estructuras**.
* Permite **abstracción sin herencia**.
* Se integran bien con `std::function`, `std::thread`, `std::async`, etc.

### ❌ Desventajas

* **Capturas incorrectas** pueden llevar a errores sutiles.
* Puede dificultar la legibilidad si se abusa de lambdas complejas.
* No todas las lambdas se pueden convertir automáticamente en `std::function`.

### Consejos prácticos

* Úsalas para definir **acciones puntuales** o personalización local.
* Si se repiten, considera convertirlas en funciones normales.
* Usa `auto` siempre que sea posible para facilitar inferencia de tipos.

---

## 7. Mini-proyecto de práctica

### 💡 Proyecto: Filtro configurable de mensajes

Implementa una clase `FiltroMensajes` que recibe un vector de strings y una función lambda que decide si un mensaje debe mostrarse. El método `mostrarFiltrados` imprime solo los mensajes que pasan el filtro.

```cpp
class FiltroMensajes {
public:
    void mostrarFiltrados(
        const std::vector<std::string>& mensajes,
        std::function<bool(const std::string&)> filtro) const
    {
        for (const auto& msg : mensajes) {
            if (filtro(msg))
                std::cout << msg << '\n';
        }
    }
};
```

---

## 8. Resumen y puntos clave

* Las **lambdas permiten abstraer comportamiento de forma local y flexible**.
* Son útiles para parametrizar algoritmos, responder a eventos, configurar acciones.
* Se relacionan con la inversión de dependencias y el principio abierto/cerrado.
* Bien usadas, mejoran la expresividad y reducen acoplamiento.

---

¿Quieres que integre este tema dentro de un módulo más amplio de “Programación funcional en C++ moderno”? También puedo enlazarlo con `std::function`, `std::bind`, o `std::ranges` si lo deseas.




















Perfecto. Vamos a **ampliar el material anterior** para mostrar cómo las **lambdas** se enlazan con otras herramientas clave del C++ moderno que permiten mayor expresividad y abstracción de comportamiento: `std::function`, `std::bind` y `std::ranges`.

---

# 📘 Funciones Avanzadas y Abstracción de Comportamiento (Ampliado)

## 🔗 Conexiones con `std::function`, `std::bind` y `std::ranges`

---

## 1. `std::function`: Almacenamiento y paso de comportamiento genérico

### 🧠 ¿Qué es?

`std::function` es un **objeto de función polimórfico**: puede contener *cualquier* función, lambda o functor compatible con su firma.

### 🔧 Sintaxis:

```cpp
std::function<tipo_retorno(parámetros)> f;
```

### 💡 Ejemplo:

```cpp
#include <functional>
#include <iostream>

void ejecutar(std::function<void()> f) {
    f();
}

int main() {
    int x = 42;
    ejecutar([x]() { std::cout << "Valor: " << x << '\n'; });
}
```

### 🔄 Relación con lambdas

Las lambdas **se pueden almacenar en `std::function`** siempre que su tipo sea compatible. Esto permite:

* Guardar estrategias o acciones personalizadas.
* Pasar funciones entre objetos.
* Implementar inyección de comportamiento (estrategia, callback, etc.).

---

## 2. `std::bind`: Parcialización de funciones

### 🧠 ¿Qué es?

`std::bind` permite **crear nuevas funciones** a partir de otras, fijando algunos argumentos (parcial aplicación).

### 🔧 Sintaxis:

```cpp
auto nueva_funcion = std::bind(función_original, arg1, std::placeholders::_1);
```

### 💡 Ejemplo:

```cpp
#include <functional>
#include <iostream>

void saludar(const std::string& nombre, const std::string& saludo) {
    std::cout << saludo << ", " << nombre << '\n';
}

int main() {
    auto saludarHola = std::bind(saludar, std::placeholders::_1, "Hola");
    saludarHola("Lucía"); // Hola, Lucía
}
```

### 🔄 Relación con lambdas

Aunque `std::bind` puede ser sustituido por lambdas, sigue siendo útil cuando se necesita:

* Parcializar funciones existentes.
* Pasar métodos con argumentos ya fijados.

✅ Consejo: Hoy en día se prefiere usar lambdas en la mayoría de los casos por legibilidad y claridad.

---

## 3. `std::ranges`: Funcionalidad moderna para algoritmos y vistas

### 🧠 ¿Qué es?

`std::ranges` (C++20) extiende la STL para permitir **composición funcional** sobre colecciones. Se basa en conceptos como:

* **Vistas**: colecciones “ligeras” sin copia.
* **Pipelines**: composición de transformaciones con `|`.
* **Lambdas**: para filtrar, transformar, agrupar, etc.

### 🔧 Sintaxis básica:

```cpp
#include <ranges>

auto vista = datos | std::views::filter(condición) | std::views::transform(acción);
```

### 💡 Ejemplo:

```cpp
#include <iostream>
#include <ranges>
#include <vector>

int main() {
    std::vector<int> datos = {1, 2, 3, 4, 5, 6};

    auto resultado = datos 
        | std::views::filter([](int x) { return x % 2 == 0; })
        | std::views::transform([](int x) { return x * 10; });

    for (int x : resultado)
        std::cout << x << " "; // 20 40 60
}
```

### 🔄 Relación con lambdas

* Las **transformaciones y filtros** se definen como lambdas.
* Permiten **expresar comportamiento local** directamente sobre colecciones.
* Combinan muy bien con `std::function` para hacer transformaciones dinámicas.

---

## 🧵 Integración de todo: Proyecto pequeño

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <ranges>

class Procesador {
public:
    void aplicar(std::function<bool(const std::string&)> filtro,
                 std::function<void(const std::string&)> accion,
                 const std::vector<std::string>& datos) const
    {
        for (const auto& x : datos | std::views::filter(filtro))
            accion(x);
    }
};

int main() {
    std::vector<std::string> nombres = {"Ana", "Álvaro", "Bea", "Bernardo", "Carlos"};

    Procesador p;

    p.aplicar(
        [](const std::string& nombre) {
            return nombre[0] == 'B';
        },
        [](const std::string& nombre) {
            std::cout << "Hola, " << nombre << '\n';
        },
        nombres
    );
}
```

---

## 📌 Conclusión: Cómo se conectan

| Herramienta         | Rol en la abstracción de comportamiento                   |
| ------------------- | --------------------------------------------------------- |
| **Lambda**          | Define funciones en línea, comportamiento local           |
| **`std::function`** | Almacena funciones o lambdas de forma polimórfica         |
| **`std::bind`**     | Permite crear funciones parciales o configurar parámetros |
| **`std::ranges`**   | Composición funcional sobre datos, usando lambdas         |

Todas estas herramientas permiten trabajar en C++ moderno con un estilo **más declarativo, flexible y reutilizable**, acercando el lenguaje al paradigma funcional **sin perder rendimiento ni control**.

---

¿Te gustaría que convirtamos esto en una unidad completa de tu curso, con ejercicios progresivos y autoevaluaciones?


