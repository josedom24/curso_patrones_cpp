# Patrones de diseño

Los **patrones de diseño** son soluciones generales y reutilizables a problemas comunes que aparecen una y otra vez durante el desarrollo de software orientado a objetos. No son fragmentos de código listos para usar, sino descripciones o esquemas que indican cómo estructurar relaciones entre clases y objetos para resolver ciertos problemas de diseño.

Un **patrón de diseño** es una solución probada, estructurada y reutilizable para un problema recurrente en un contexto determinado dentro del diseño de software.

Los patrones ayudan a formalizar el conocimiento experto acumulado a lo largo del tiempo por la comunidad de desarrolladores, y proporcionan un lenguaje común para comunicar ideas de diseño.

## ¿Por qué usar patrones de diseño?

El uso de patrones de diseño aporta numerosos beneficios:

* **Reutilización del conocimiento:** Aprovechan soluciones ya probadas por otros desarrolladores.
* **Mejora de la comunicación:** Permiten describir arquitecturas complejas usando un lenguaje compartido (por ejemplo, “esto sigue el patrón *Factory Method*”).
* **Diseño flexible y mantenible:** Fomentan el uso de buenas prácticas como la composición, el uso de interfaces y la separación de responsabilidades.
* **Facilitan la evolución del software:** Al estar basados en principios como SOLID, permiten que el sistema sea más adaptable a cambios futuros.

## Clasificación clásica de los patrones

Según el catálogo clásico de *Design Patterns* de Gamma, Helm, Johnson y Vlissides (los “Gang of Four”), los patrones se clasifican en tres grandes categorías:

| Categoría          | Propósito general                                        | Ejemplos comunes                   |
| ------------------ | -------------------------------------------------------- | ---------------------------------- |
| **Creacionales**   | Encapsulan el proceso de creación de objetos             | Singleton, Factory Method, Builder |
| **Estructurales**  | Describen formas de componer objetos y clases            | Adapter, Composite, Decorator      |
| **Comportamiento** | Gestionan la interacción y responsabilidad entre objetos | Strategy, Observer, State          |

Esta clasificación ayuda a entender cuándo y por qué utilizar cada tipo de patrón.

## Patrones de diseño vs. algoritmos

Es importante diferenciar los patrones de diseño de los algoritmos:

* **Algoritmo:** Describe un proceso paso a paso para resolver una tarea específica.
* **Patrón de diseño:** Describe una estructura general para organizar código y objetos con el fin de resolver problemas de diseño, no problemas computacionales concretos.

Por ejemplo, un patrón no dirá cómo ordenar una lista, sino cómo permitir que diferentes algoritmos de ordenamiento puedan usarse intercambiablemente (*Strategy*).

## ¿Cuándo usar un patrón?

No todos los problemas requieren un patrón, y no todos los patrones son apropiados para todos los contextos. Es recomendable considerar un patrón cuando:

* El problema es recurrente y ha aparecido en otros sistemas similares.
* Se busca una solución flexible y extensible que cumpla principios de buen diseño.
* Es útil adoptar una solución reconocida que mejore la comunicación y mantenimiento del código.

