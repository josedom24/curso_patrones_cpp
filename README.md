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
    * [Plantilla de clase: `std::optional`](contenido/modulo2/plantilla.md)

3. Gestión de Recursos en Programas Complejos

    * [Semántica de copia y movimiento](contenido/modulo3/move.md)
    * [Uso práctico de `std::unique_ptr` y `std::shared_ptr` en clases](contenido/modulo3/small_pointer.md)
    * Clonación de objetos (copias profundas y superficiales)
    * Composición de objetos con punteros inteligentes

4. Profundización en POO y Diseño de Interfaces

    * [Ampliación de constructores: control de creación y copia de objetos](contenido/modulo4/constructor.md)
    * [Clases abstractas y métodos virtuales](contenido/modulo4/constructor.md)
    * [Interfaces puras y uso correcto de `override`](contenido/modulo4/abstracta.md)
    * [Uso de `override` y `final`](contenido/modulo4/override.md)
    * [Devolución de interfaces mediante punteros inteligentes](contenido/modulo4/devolucion.md)
    * [Separación entre interfaz y detalle de implementación](contenido/modulo4/separacion.md)
    * [Fluidez de métodos](contenido/modulo4/fluidez.md)
    * Inicialización flexible de objetos
    * [Ejercicios sobre profundización de POO](contenido/modulo4/ejercicios.md)
     
5. Patrones Creacionales

    * [Singleton](contenido/modulo5/singleton.md)
    * [Factory Method](contenido/modulo5/factory_method.md)
    * [Abstract Factory](contenido/modulo5/abstract_factory.md)
    * Builder
    * Prototype (incluyendo uso seguro de copias y clonación)

6. Patrones Estructurales

    * Adapter
    * Decorator (composición moderna con punteros inteligentes)
    * Composite
    * Facade
    * Bridge
    * Proxy

7. Patrones de Comportamiento

    * Strategy (usando plantillas y polimorfismo moderno)
    * Observer (con `std::function` y lambdas como callbacks)
    * Command
    * Template Method (esqueleto de un algoritmo dejando pasos a subclases)
    * Iterator (introduciendo ranges de C++20 si se desea)
    * Visitor
    * State
    
8. Proyecto final

