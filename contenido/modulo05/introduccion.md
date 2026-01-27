# Por qué algunos patrones se simplifican en C++ moderno

Muchos patrones clásicos urgieron en un contexto de lenguajes con importantes limitaciones, como la ausencia de funciones anónimas o lambdas, un sistema de tipos genéricos poco expresivo, gestión manual de memoria sin RAII y escasas facilidades para la composición de comportamiento. En ese contexto, los patrones ofrecían soluciones estructurales a problemas recurrentes del diseño de software.

En C++ moderno (C++11 en adelante), muchas de estas limitaciones se han atenuado o eliminado gracias a nuevas características del lenguaje y de la biblioteca estándar. Como consecuencia, **algunos patrones no desaparecen, pero sí se expresan de forma más simple, idiomática o directa**, y en ciertos casos su implementación clásica resulta innecesaria para los escenarios más comunes.

Este apartado presenta algunos de estos patrones y explica por qué, en C++ moderno, existen alternativas que permiten expresar la misma intención de diseño con menos infraestructura y menor complejidad accidental, sin invalidar el valor conceptual del patrón.

## Patrones con alternativas modernas en C++

Los siguientes son patrones clásicos. Su **idea de diseño sigue siendo válida**, pero su implementación tradicional puede ser sustituida, en muchos casos, por mecanismos propios del lenguaje o de la biblioteca estándar.

### Singleton

El patrón **Singleton** es un patrón creacional cuyo objetivo es garantizar que exista una única instancia global de una clase y proporcionar un punto de acceso a ella. En C++ moderno, su uso está **fuertemente desaconsejado en la mayoría de contextos**, ya que introduce acoplamiento global, dificulta la prueba unitaria y viola el principio de inversión de dependencias.

Aunque el lenguaje ofrece implementaciones seguras y sencillas (como variables estáticas de función), hoy se prefieren alternativas como la **inyección explícita de dependencias**, que permiten controlar el ciclo de vida de los objetos sin introducir dependencias globales implícitas.

### Strategy

El patrón **Strategy** define una familia de algoritmos intercambiables y permite variar su comportamiento de forma dinámica mediante herencia y polimorfismo. En C++ moderno, esta idea puede expresarse de forma más directa mediante **inyección de comportamiento**, utilizando funciones lambda, punteros a función o `std::function`.

Estas técnicas permiten sustituir jerarquías de clases completas por objetos funcionales ligeros, manteniendo la flexibilidad del diseño. El patrón no desaparece, pero su **implementación clásica basada en herencia suele resultar innecesaria** en muchos casos.

### Command

El patrón **Command** encapsula una operación como un objeto, desacoplando el invocador de la acción que se ejecuta. En C++ moderno, muchas implementaciones sencillas de este patrón pueden expresarse directamente mediante **objetos invocables**, como `std::function<void()>` o lambdas que capturan estado.

No obstante, el patrón sigue siendo relevante en escenarios más complejos, como la implementación de **undo/redo**, colas de comandos, historiales o sistemas de registro, donde el comando mantiene identidad, estado y ciclo de vida propios.

### Template Method

El patrón **Template Method** define la estructura general de un algoritmo y delega ciertos pasos en métodos que pueden redefinirse en subclases. En C++ moderno, esta intención puede lograrse sin recurrir necesariamente a herencia virtual, mediante el uso de **plantillas**, composición de funciones o inyección explícita de comportamiento.

El patrón sigue siendo conceptualmente válido, pero en muchos casos su implementación puede evitar la herencia profunda y el polimorfismo dinámico, favoreciendo soluciones más estáticas y eficientes.

## Otros patrones de diseño

Los siguientes patrones no se estudian de forma completa en el curso, pero su comprensión resulta útil para situarlos dentro del panorama general del diseño orientado a objetos y del diseño moderno en C++.

### Flyweight

El patrón estructural **Flyweight** tiene como objetivo reducir el consumo de memoria compartiendo partes inmutables del estado entre múltiples objetos. Aunque surgió en contextos con recursos muy limitados, **sigue siendo relevante** en sistemas modernos, especialmente en áreas como gráficos, motores de juego, procesamiento de texto o gestión de grandes volúmenes de objetos conceptualmente similares.


### Iterator

El patrón de comportamiento **Iterator** define una forma de recorrer los elementos de una colección sin exponer su representación interna. En C++, este patrón está **plenamente integrado en la biblioteca estándar**, donde cada contenedor define su propio tipo de iterador y estos interactúan con un amplio conjunto de algoritmos genéricos.

Más que obsoleto, el patrón **ha sido absorbido por la STL** y constituye uno de los pilares del diseño genérico en C++ moderno, reforzado aún más con la introducción de *ranges*.

### Interpreter

El patrón **Interpreter** describe una forma de representar y evaluar gramáticas mediante una jerarquía de clases. Si bien la implementación clásica resulta poco práctica para muchos casos reales, **la idea subyacente sigue vigente**.

En C++ moderno, esta intención se expresa de forma más eficiente y clara mediante alternativas como `std::variant` junto con `std::visit`, árboles sintácticos personalizados o herramientas externas de análisis léxico y sintáctico, que ofrecen mayor flexibilidad y rendimiento.



