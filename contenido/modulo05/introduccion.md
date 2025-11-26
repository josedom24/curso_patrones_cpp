# Por qué algunos patrones se simplifican en C++ moderno

Muchos patrones clásicos del catálogo GoF surgieron en un contexto de lenguajes con importantes limitaciones: ausencia de funciones anónimas o lambdas, falta de un sistema de tipos genérico y flexible, gestión manual de memoria sin RAII, escasa capacidad de abstracción y poca expresividad en la composición de comportamientos.
En C++ moderno (C++11 en adelante), estas limitaciones desaparecen gracias a sus nuevas características.

Como consecuencia, algunos patrones clásicos pueden implementarse de forma mucho más simple o incluso resultar innecesarios en casos comunes.
Este apartado presenta brevemente estos patrones y explica por qué, en C++ moderno, existen alternativas idiomáticas más adecuadas.


## Patrones con alternativas modernas en C++

Los siguientes patrones forman parte del catálogo clásico, pero su implementación tradicional puede ser reemplazada —en muchos casos— por mecanismos del propio lenguaje o de la STL.

### Singleton

El patrón Singleton es un patrón creacional, que garantiza que solo exista una instancia global de una clase.
En C++ moderno se considera un **antipatrón**, pues dificulta la testabilidad, rompe el principio de inversión de dependencias y genera acoplamiento global.
Las alternativas actuales, como la **inyección de dependencias**, permiten lograr el mismo efecto sin sus inconvenientes.

### Strategy

Es un patrón de comportamiento que define una familia de algoritmos intercambiables mediante herencia y polimorfismo dinámico.
En C++ moderno, este esquema puede expresarse de forma natural mediante inyección de comportamiento mediante distintas técnicas, como **funciones lambda o `std::function`**, reduciendo considerablemente la infraestructura necesaria.

### Command

Patrón de comportamiento que encapsula una operación como un objeto, separando la acción del invocador.
Hoy es común que esta función se represente directamente con **`std::function<void()>`** o con una **lambda capturando estado**, evitando clases jerárquicas enteras.

### Template Method

Patrón de comportamiento que establece la estructura de un algoritmo, delegando pasos concretos en métodos virtuales sobreescribibles.
En C++ moderno, las **plantillas**, la **composición de funciones** y la **inyección de comportamiento** permiten expresar esta idea sin depender de herencia.

## Otros patrones de diseño

A continuación se describen brevemente tres patrones que no se estudiarán de forma completa en el curso, pero cuya comprensión conceptual es útil para situarlos dentro del panorama general del diseño orientado a objetos.

### Flyweight

El patrón estructural **Flyweight** busca **reducir el coste de memoria** compartiendo partes inmutables del estado de múltiples objetos.
Su uso era habitual en contextos donde la creación masiva de objetos idénticos resultaba prohibitiva.

### Iterator

El patrón de comportamiento **Iterator** define un objeto que permite recorrer elementos de una colección sin exponer su representación interna. La **STL ya integra esta idea como rasgo esencial**: cada contenedor define su propio tipo de iterador, y estos funcionan con un gran conjunto de algoritmos genéricos.
En C++ moderno, el patrón se considera **histórico**, pues su función está plenamente absorbida por la biblioteca estándar.

### Interpreter

**Interpreter** es un patrón con valor principalmente histórico.
La implementación clásica basada en una jerarquía extensa de clases para representar una gramática sencilla se considera obsoleta en el desarrollo moderno, especialmente en C++, donde existen alternativas más expresivas y eficientes como `std::variant` + `std::visit`, árboles sintácticos personalizados, y herramientas de análisis sintáctico externas.


