# Patrones de diseño

Los **patrones de diseño** son soluciones generales, probadas y reutilizables para problemas recurrentes que aparecen durante el diseño de software orientado a objetos. No son fragmentos de código concretos, sino **estructuras conceptuales** que indican cómo organizar clases, objetos y responsabilidades para resolver eficazmente un determinado tipo de problema.

Los patrones proporcionan un **lenguaje común**, una colección de **buenas prácticas** y una forma sistemática de aplicar los principios vistos anteriormente: encapsular lo que varía, programar a interfaces, favorecer la composición y reducir el acoplamiento.


## ¿Por qué usar patrones de diseño?

El uso de patrones aporta múltiples ventajas:

* **Reutilización del conocimiento:** aprovechan soluciones ampliamente contrastadas.
* **Mejor comunicación:** permiten describir arquitecturas complejas mediante un vocabulario compartido (“esto es un *Factory Method*”, “esto funciona igual que *Observer*”, etc.).
* **Diseño más flexible:** fomentan la separación de responsabilidades y las abstracciones.
* **Evolución más sencilla:** se alinean con principios como SOLID, facilitando cambios futuros.
* **Contexto histórico y conceptual:** ayudan a entender cómo evolucionó el diseño orientado a objetos y por qué ciertas técnicas se consideran buenas prácticas.


## Patrones de diseño vs. algoritmos

Un **algoritmo** resuelve un problema computacional concreto describiendo paso a paso cómo obtener un resultado.

Un **patrón de diseño**, en cambio, resuelve un **problema de diseño**: indica cómo estructurar la colaboración entre clases y objetos. No describe cálculos, sino **relaciones**.

Ejemplo: un patrón no te dice cómo ordenar una lista, pero sí cómo permitir que una familia de algoritmos de ordenación sea intercambiable (*Strategy*).


## Clasificación clásica de los patrones

El catálogo clásico del “Gang of Four” distingue tres grandes familias de patrones:

1. **Patrones creacionales**
   Se ocupan de la creación de objetos, encapsulando la lógica de construcción y el ciclo de vida.
   Ejemplos típicos: *Singleton*, *Factory Method*, *Abstract Factory*, *Builder*, *Prototype*.

2. **Patrones estructurales**
   Describen formas de **componer** clases y objetos para formar estructuras más complejas, sin aumentar el acoplamiento.
   Ejemplos típicos: *Adapter*, *Composite*, *Decorator*, *Bridge*, *Facade*, *Proxy*.

3. **Patrones de comportamiento**
   Se centran en la **interacción**, la comunicación y la asignación de responsabilidades entre objetos.
   Ejemplos típicos: *Strategy*, *Observer*, *State*, *Mediator*, *Command*, *Visitor*, *Iterator*.

Esta clasificación ayuda a orientar el estudio, indicando **qué tipo de problema** aborda cada familia de patrones.


## ¿Cuándo usar un patrón?

Conviene considerar un patrón cuando:

* El problema aparece de forma recurrente en otros sistemas.
* Se requiere una solución flexible, extensible y mantenible.
* Es útil emplear un vocabulario común de diseño para comunicar ideas.
* Se quiere aplicar principios como OCP y DIP de manera sistemática.
* Existe una solución compleja que ya ha sido estudiada y formalizada.

En cambio, **no** se debe aplicar un patrón cuando:

* La solución directa y simple es suficiente.
* La complejidad introducida no aporta beneficios reales.
* El patrón solo existe por limitaciones históricas de lenguajes antiguos.

## Conexión con los principios anteriores

Los patrones de diseño ponen en práctica los principios básicos y SOLID:

* Encapsulan lo que varía (*Strategy*, *State*, *Command*).
* Promueven programar a interfaces (*Abstract Factory*, *Observer*, *Mediator*).
* Favorecen la composición (*Decorator*, *Composite*, *Bridge*).
* Reducen el acoplamiento (*Observer*, *Mediator*, *Facade*).
* Aplican OCP y DIP de forma explícita (*Factory Method*, *Template Method*, *Decorator*).
