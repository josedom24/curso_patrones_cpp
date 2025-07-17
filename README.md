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


3. Profundización en POO y diseño de interfaces

    * [Ampliación de constructores: control de creación y copia de objetos](contenido/modulo3/constructor.md)
    * [Clases abstractas y métodos virtuales](contenido/modulo3/constructor.md)
    * [Interfaces puras y uso correcto de `override`](contenido/modulo3/abstracta.md)
    * [Uso de `override` y `final`](contenido/modulo3/override.md)
    * [Devolución de interfaces mediante punteros inteligentes](contenido/modulo3/devolucion.md)
    * [Separación entre interfaz y detalle de implementación](contenido/modulo3/separacion.md)
    * [Fluidez de métodos](contenido/modulo3/fluidez.md)
    * [Ejercicios sobre profundización de POO](contenido/modulo3/ejercicios.md)

4. Gestión avanzado de recursos 

    * [Semántica de copia y movimiento](contenido/modulo4/move.md)
    * [Uso práctico de `std::unique_ptr` y `std::shared_ptr` en clases](contenido/modulo4/small_pointer.md)
    * [Clonación de objetos: copias superficiales y profundas](contenido/modulo4/clonacion.md)
    * [Composición de objetos con punteros inteligentes](contenido/modulo4/composicion.md)


5. Patrones Creacionales

    * [Singleton](contenido/modulo5/singleton.md)
    * [Factory Method](contenido/modulo5/factory_method.md)
    * [Abstract Factory](contenido/modulo5/abstract_factory.md)
    * [Builder](contenido/modulo5/builder.md)
    * Prototype

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

