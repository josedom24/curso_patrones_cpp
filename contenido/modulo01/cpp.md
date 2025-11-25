# Patrones de diseño con C++ moderno

Los patrones de diseño fueron formulados originalmente en el contexto de lenguajes orientados a objetos clásicos como C++98 o Java. Sin embargo, la evolución de C++ en sus versiones modernas ha transformado profundamente la forma en que se diseñan e implementan dichos patrones.

Este curso adopta una perspectiva **moderna y idiomática** de los patrones de diseño, empleando las herramientas y convenciones del C++ contemporáneo para lograr implementaciones más claras, seguras, reutilizables y eficientes.

## ¿Qué aporta C++ moderno al diseño de patrones?

C++ moderno introduce herramientas que permiten implementar patrones de diseño de forma más **segura**, **expresiva** y **eficiente**. Entre ellas destacan:

1. **RAII (Resource Acquisition Is Initialization)**

   * Facilita la gestión automática de recursos.
   * Usado en patrones con creación/destrucción controlada de objetos (Factory Method, Abstract Factory, Builder, Prototype).

2. **Punteros inteligentes (`std::unique_ptr`, `std::shared_ptr`)**

   * Controlan propiedad y ciclo de vida.
   * Utilizados en Factory Method, Prototype (clonado seguro), Strategy y State (gestión dinámica de objetos-estrategia/estado).

3. **Expresiones lambda**

   * Permiten encapsular comportamiento en tiempo de ejecución.
   * Empleadas como alternativa ligera a Strategy, Command y Template Method.

4. **`std::function`**

   * Abstrae callbacks o comportamientos configurables.
   * Útil en Strategy, Mediator, Observer y en la inyección de dependencias en general.

5. **Inicialización uniforme (`{}`) y deducción de tipos con `auto`**

   * Simplifican instanciación y reducen errores en construcción de objetos.
   * Usadas en ejemplos de Builder, Factory, Observer y Memento.

6. **Move semantics y forwarding (`std::move`, `std::forward`)**

   * Mejoran rendimiento evitando copias innecesarias.
   * Aplicadas en patrones que crean y transmiten objetos pesados (Builder, Prototype, Factories).

7. **Enum classes, `std::optional`, `std::variant`**

   * Alternativas modernas para decisiones de diseño más seguras.
   * Empleados en State (enum class), en Factory y Builder (variant/optional para configuraciones).


## ¿Cómo se presentarán los patrones?

Cada patrón de diseño será presentado siguiendo una estructura clara y constante, que facilitará su comprensión y comparación. 

* **Introducción al patrón**: Donde se dará la definición, los problemas que intenta solucionar, cómo lo soluciona, y finalmente, ejemplos concretos de uso.
* **Implementación en C++ moderno**: Donde se explicará la estructura y elementos modernos utilizados, se mostrará un diagrama UML y se presentará un ejemplo genérico de utilización del patrón.
* **Ejemplo concreto**: Finalmente, se elegirá un ejemplo representativo y se implementará en C++ moderno, indicando alguna modificación adicional para que se termine de entender el patrón.


