# Curso de patrones de diseño con C++

1. Principios SOLID y patrones de diseño
    * SOLID: Principios de diseño orientado a objetos
    * ¿Qué son los patrones de diseño
    * Patrones de diseño con C++ moderno

2. Funciones avanzadas y abstracción de comportamiento

    * [Uso de lambdas para comportamiento flexible](contenido/modulo2/lambda.md)
    * [`std::function` para callbacks o comportamientos configurables](contenido/modulo2/function.md)
    * [Clases functoras y lambdas como objetos de primera clase](contenido/modulo2/functor.md)
    * [Ejercicios sobre abstracción de comportamiento](contenido/modulo2/ejercicios.md)

3. Gestión de Recursos en Programas Complejos

    * [Semántica de copia y movimiento](contenido/modulo3/move.md)
    * [Uso práctico de `std::unique_ptr` y `std::shared_ptr` en clases](contenido/modulo3/small_pointer.md)
    * Clonación de objetos (copias profundas y superficiales)
    * Ejemplos de composición de objetos con punteros inteligentes


4. Profundización en POO y Diseño de Interfaces

    * [Ampliación de constructores: control de creación y copia de objetos](contenido/modulo4/constructor.md)
    * [Clases abstractas y métodos virtuales](contenido/modulo4/constructor.md)
    * [Interfaces puras y uso correcto de `override`](contenido/modulo4/abstracta.md)
    * [Separación entre interfaz y detalle de implementación](contenido/modulo4/separacion.md)
    * Ejercicios sobre profundización de POO
     

5. Técnicas de Diseño de Interfaces y Fluidez

    * Encadenamiento de métodos (`return *this`)
    * Inicialización flexible de objetos (builder básico)
    * Ocultación de detalles internos (PImpl idiom si quieres ir más lejos)
    * Ejercicios de creación controlada de objetos

6. Patrones Creacionales

    * [Singleton](contenido/modulo6/singleton.md)
    * Factory Method
    * Abstract Factory
    * Builder
    * Prototype (incluyendo uso seguro de copias y clonación)

7. Patrones Estructurales

    * Adapter
    * Decorator (composición moderna con punteros inteligentes)
    * Composite
    * Facade
    * Bridge
    * Proxy

8. Patrones de Comportamiento

    * Strategy (usando plantillas y polimorfismo moderno)
    * Observer (con `std::function` y lambdas como callbacks)
    * Command
    * Template Method (esqueleto de un algoritmo dejando pasos a subclases)
    * Iterator (introduciendo ranges de C++20 si se desea)
    * Visitor
    * State
    
    

