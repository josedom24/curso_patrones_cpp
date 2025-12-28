# Patrón Visitor

## Definición

El **Visitor** es un patrón de diseño de comportamiento que permite **separar operaciones** de las estructuras de objetos sobre las que actúan. Su objetivo principal es permitir añadir nuevas operaciones sin modificar las clases de los objetos sobre los que operan, favoreciendo así la extensibilidad del sistema y cumpliendo el principio *Open/Closed*.

## Problemas que intenta solucionar

El patrón aborda principalmente estas situaciones:

* La jerarquía de clases contiene muchos tipos de objetos y se desean realizar **múltiples operaciones** sobre ellos.
* Añadir una nueva operación obligaría a **modificar todas las clases** de la jerarquía, violando *Open/Closed Principle*.
* El código de las operaciones está disperso dentro de las clases, mezclando **datos** y **comportamiento** que podría estar mejor separado.
* La lógica depende del **tipo concreto** del objeto, requiriendo estructuras con `if`/`switch` o *type-checking* explícito.
* Se necesita realizar operaciones complejas o acumulativas (como contadores, exportadores, optimizadores) que deben atravesar estructuras compuestas.

## Cómo lo soluciona

El Visitor aporta estas soluciones:

* Define una interfaz `Visitor` con un método de visita por cada tipo concreto de objeto al que se quiera aplicar operaciones.
* Cada clase de la jerarquía implementa un método `accept(Visitor&)`, que **delegará** en el visitante la operación específica, habilitando **double dispatch**.
* Permite añadir **nuevas operaciones** simplemente creando nuevos visitantes, sin modificar las clases existentes.
* Centraliza la lógica asociada a cada operación en un único objeto visitante, mejorando la **cohesión** del sistema.
* Evita el uso de comprobaciones de tipo: el propio mecanismo de doble despacho ya escoge la operación adecuada según el tipo concreto.

## Relación con los principios SOLID

* **Single Responsibility Principle (SRP)**: El patrón *Visitor* separa la responsabilidad de **almacenar la estructura de datos** de la responsabilidad de **implementar operaciones sobre dicha estructura**. Los elementos gestionan su estado, y los visitantes encapsulan la lógica de las operaciones.
* **Open/Closed Principle (OCP)**: Nuevas operaciones pueden añadirse creando nuevos visitantes sin modificar las clases de los elementos. El sistema se extiende funcionalmente sin alterar la estructura existente.
* **Liskov Substitution Principle (LSP)**: Cualquier visitante concreto puede sustituir a otro siempre que respete la interfaz del visitante. Los elementos pueden aceptar distintos visitantes sin cambiar su comportamiento estructural.
* **Interface Segregation Principle (ISP)**: La interfaz del visitante agrupa únicamente operaciones relacionadas con la visita de elementos concretos, evitando interfaces genéricas o sobrecargadas para los elementos participantes.
* **Dependency Inversion Principle (DIP)**: Los elementos dependen de la **abstracción del visitante**, no de implementaciones concretas. A su vez, los visitantes dependen de la abstracción de los elementos, reduciendo el acoplamiento entre ambas jerarquías.

## Ejemplos concretos

* **Árboles sintácticos en compiladores**: Recorrer nodos para análisis semántico, generación de código o optimizaciones sin modificar las clases de los nodos.
* **Estructuras de documentos (XML, JSON, HTML)**: Implementar validadores, exportadores, transformadores o medidores de tamaño a través de distintos visitantes.
* **Escenas gráficas (scene graphs)**: Aplicar operaciones de renderizado, conteo de elementos, cálculos geométricos u optimizaciones sin alterar los nodos.
* **Modelos geométricos**: Calcular área, perímetro o transformaciones en figuras usando distintos visitantes.
* **Sistemas de archivos virtuales**: Determinar tamaños totales, permisos, rutas, o generar listados aplicando diferentes visitantes a archivos y directorios.
* **Herramientas de análisis estático**: Añadir chequeos o reglas adicionales mediante nuevos visitantes que recorren la estructura del código.
* **Motores de juegos**: Implementar lógicas de colisión, física, IA o depuración sin modificar los objetos del mundo del juego.
* **Generadores de informes**: Producir estadísticas, resúmenes o exportaciones a distintos formatos sin cambiar la jerarquía de objetos.
* **Sistemas de facturación o contabilidad**: Calcular impuestos, generar facturas, aplicar descuentos u otras reglas mediante visitantes especializados.
* **Aplicaciones CAD**: Añadir nuevas herramientas de inspección, medición o simulación a estructuras de objetos complejas con solo crear nuevos visitantes.
