# Clases abstractas y métodos virtuales

Las clases abstractas y los métodos virtuales permiten definir **acciones comunes** que pueden realizar distintos tipos de objetos, aunque cada uno las implemente de forma distinta. Esto hace posible escribir código que trabaje con objetos diferentes de manera uniforme, y al mismo tiempo mantener la flexibilidad para cambiar o extender el comportamiento sin modificar el código original.

Las clases abstractas y los métodos virtuales permiten expresar relaciones de generalización entre tipos, facilitando la definición de comportamientos comunes mediante interfaces base y su implementación específica en clases derivadas. Son herramientas fundamentales para lograr el **polimorfismo en tiempo de ejecución** y diseñar sistemas extensibles y mantenibles.

---

## 🧠 Definición formal

### Clase abstracta

Una clase se considera **abstracta** si contiene al menos una función miembro declarada como `virtual` y con el sufijo `= 0`, conocida como **función virtual pura**. No se puede instanciar directamente una clase abstracta.

```cpp
class Forma {
public:
    virtual void dibujar() const = 0; // Método virtual puro
};
```

### Método virtual

Un **método virtual** es una función miembro que puede ser redefinida por clases derivadas y cuya invocación se resuelve en tiempo de ejecución mediante una tabla de funciones virtuales (*vtable*).

```cpp
class Animal {
public:
    virtual void hablar() const {
        std::cout << "Sonido genérico\n";
    }
};
```

---

## 🧱 Ejemplo: clase abstracta y derivación

```cpp
#include <iostream>
#include <memory>
#include <vector>

class Figura {
public:
    virtual void dibujar() const = 0; // Método virtual puro
    virtual ~Figura() = default;      // Destructor virtual
};

class Circulo : public Figura {
public:
    void dibujar() const override {
        std::cout << "Dibujando un círculo\n";
    }
};

class Rectangulo : public Figura {
public:
    void dibujar() const override {
        std::cout << "Dibujando un rectángulo\n";
    }
};
```

---

### 🧪 Uso polimórfico

```cpp
int main() {
    std::vector<std::unique_ptr<Figura>> figuras;

    figuras.push_back(std::make_unique<Circulo>());
    figuras.push_back(std::make_unique<Rectangulo>());

    for (const auto& figura : figuras)
        figura->dibujar();  // Llamada polimórfica
}
```

---

### ✅ Salida esperada

```
Dibujando un círculo
Dibujando un rectángulo
```

---

## 📌 Ventajas de usar clases abstractas

* Definen una **interfaz común** para un conjunto de clases relacionadas.
* Permiten implementar algoritmos genéricos que operan sobre punteros o referencias a la clase base.
* Favorecen el cumplimiento del **principio de sustitución de Liskov**.
* Facilitan el diseño orientado a interfaces, desacoplando el “qué hace” del “cómo lo hace”.

---

## ⚠️ Consideraciones importantes

* Si una clase tiene un método virtual puro, no puede instanciarse.
* Toda clase con métodos virtuales debe declarar un **destructor virtual**, especialmente si se va a heredar.
* Las llamadas virtuales solo funcionan a través de punteros o referencias a la clase base.

---

## 🧩 Conclusión

Las clases abstractas y los métodos virtuales son pilares fundamentales de la **programación orientada a objetos en C++**. Permiten expresar relaciones jerárquicas claras, diseñar componentes reutilizables y extender el comportamiento sin modificar el código existente. Su uso adecuado con punteros inteligentes y el principio RAII fortalece aún más la robustez del diseño.

---

¿Deseas que el siguiente material sea sobre “Interfaces puras (`virtual ... = 0`)”, con un enfoque en cómo separar la interfaz del detalle de implementación?
