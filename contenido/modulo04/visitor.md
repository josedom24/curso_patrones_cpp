# Patrón Visitor

## Definición

El **Visitor** es un patrón de diseño de comportamiento que permite **separar operaciones** de las estructuras de objetos sobre las que actúan. Su objetivo principal es permitir añadir nuevas operaciones sin modificar las clases de los objetos sobre los que operan, favoreciendo así la extensibilidad del sistema y cumpliendo el principio *Open/Closed*.

## Objetivos del patrón

* **Permitir añadir nuevas operaciones** sobre una jerarquía de objetos **sin modificar sus clases**, cumpliendo el principio *Open/Closed*.
* **Separar la lógica de las operaciones** de la estructura de los objetos que las soportan, mejorando la cohesión y la claridad del diseño.
* **Eliminar comprobaciones explícitas de tipo** (`if`/`switch`, `dynamic_cast`) mediante el uso de *double dispatch*, garantizando que la operación correcta se ejecute según el tipo concreto.
* **Facilitar la implementación de operaciones complejas o transversales** (recorridos, acumulaciones, exportaciones, análisis) que deben aplicarse de forma consistente sobre estructuras de objetos heterogéneas.

## Problemas que intenta solucionar

El patrón aborda principalmente estas situaciones:

* **Dificultad para añadir nuevas operaciones** sobre una jerarquía de objetos, ya que cada nueva funcionalidad obliga a modificar todas las clases existentes, violando el *Open/Closed Principle*.
* **Mezcla de responsabilidades** dentro de las clases de la jerarquía, donde la lógica de múltiples operaciones se dispersa junto con los datos, reduciendo cohesión y dificultando el mantenimiento.
* **Dependencia del tipo concreto de los objetos** para ejecutar operaciones específicas, lo que conduce al uso de estructuras condicionales (`if`/`switch`) o comprobaciones dinámicas de tipo.
* **Necesidad de aplicar operaciones transversales o acumulativas** (como recorridos, cálculos, exportaciones o validaciones) sobre estructuras de objetos heterogéneas de forma consistente y centralizada.

## Cómo lo soluciona

El Visitor aporta estas soluciones:

* **Define una jerarquía de visitantes** que encapsula cada operación en una clase independiente, permitiendo añadir nuevas funcionalidades sin modificar la estructura de los elementos.
* **Introduce el mecanismo de doble despacho** mediante el método `accept(Visitor&)`, garantizando que la operación ejecutada dependa del tipo concreto del elemento visitado sin necesidad de comprobaciones de tipo.
* **Centraliza la lógica de cada operación** en un único visitante, mejorando la cohesión, la legibilidad y la mantenibilidad del código.
* **Facilita la implementación de operaciones transversales** sobre estructuras de objetos heterogéneas, permitiendo recorrerlas y procesarlas de forma uniforme y extensible.

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
