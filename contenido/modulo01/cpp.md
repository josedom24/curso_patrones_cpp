# Patrones de diseño con C++ moderno

Los patrones de diseño fueron formulados originalmente en el contexto de lenguajes orientados a objetos clásicos como C++98 o Java. Sin embargo, la evolución de C++ en sus versiones modernas ha transformado profundamente la forma en que se diseñan e implementan dichos patrones.

Este curso adopta una perspectiva **moderna y idiomática** de los patrones de diseño, empleando las herramientas y convenciones del C++ contemporáneo para lograr implementaciones más claras, seguras, reutilizables y eficientes.

## ¿Qué aporta C++ moderno al diseño de patrones?

El lenguaje moderno proporciona nuevas construcciones que permiten replantear muchos patrones clásicos con menor complejidad y mayor expresividad. Algunas de estas herramientas clave incluyen:

| Característica                                                   | Aplicación en patrones                                                          |
| ---------------------------------------------------------------- | ------------------------------------------------------------------------------- |
| **RAII (Resource Acquisition Is Initialization)**                | Gestión automática de recursos en patrones que implican creación y destrucción. |
| **Punteros inteligentes (`std::unique_ptr`, `std::shared_ptr`)** | Encapsulan la propiedad y el ciclo de vida de objetos.                          |
| **Expresiones lambda**                                           | Representan comportamiento en tiempo de ejecución (e.g. Strategy).              |
| **`std::function`**                                              | Paso de comportamiento como parámetro o inyección de dependencias.              |
| **Plantillas y metaprogramación**                                | Permiten definir estructuras reutilizables sin sacrificar rendimiento.          |
| **`constexpr` y `inline`**                                       | Optimización y evaluación en tiempo de compilación.                             |
| **Inicialización uniforme y `auto`**                             | Reducción de errores y simplificación de sintaxis.                              |

## Enfoque didáctico del curso

En lugar de limitarse a transcribir patrones clásicos, este curso busca:

* **Aplicar principios SOLID** al implementar cada patrón.
* **Reformular patrones clásicos** para adaptarlos a las prácticas de C++ moderno.
* **Fomentar el diseño modular y flexible**, evitando herencias innecesarias.
* **Usar composición, lambdas y funciones**, como alternativa a jerarquías rígidas.
* **Comparar soluciones tradicionales y modernas**, analizando ventajas y desventajas.

## ¿Cómo se implementarán los patrones?

Cada patrón de diseño será presentado siguiendo una estructura clara y constante, que facilitará su comprensión y comparación. En una primera clase se hará una presentación general del patrón siguiendo esta estructura:

1. **Introducción y propósito del patrón**
2. **Problema que resuelve**
3. **Solución que propone**
4. **Diagrama y estructura conceptual** 
5. **Relación con los principios SOLID**
6. **Ventajas y desventajas**
7. **Aplicaciones reales o mini-proyectos**
 
En una segunda clase se verá como implementar el patrón en C** moderno, siguiendo el siguiente esquema:

1. **Cómo implementar el patrón** 
2. **Implementación en C++ moderno**
3. **Código de ejemplo**

