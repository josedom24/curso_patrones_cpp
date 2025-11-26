# Patrón Template Method

## Definición

El **Template Method** es un patrón de diseño **de comportamiento** que define el *esqueleto* de un algoritmo en una clase base, delegando a las subclases la implementación de ciertos pasos concretos.
El objetivo es **fijar la estructura general del proceso**, permitiendo al mismo tiempo que partes específicas puedan variar sin alterar la secuencia global del algoritmo.

## Problemas que intenta solucionar

El patrón se emplea para resolver situaciones como:

* Se tiene un **algoritmo cuya estructura es estable**, pero algunos pasos pueden variar según el contexto o tipo concreto.
* La implementación del algoritmo en diferentes clases produce **duplicación de código**, ya que todas comparten la misma secuencia general.
* Se desea **controlar** los pasos críticos de un proceso, impidiendo que las subclases modifiquen el orden del algoritmo.
* Se quiere aplicar el principio *Open/Closed*: permitir variaciones sin cambiar la lógica general establecida en la clase base.
* Se necesita garantizar un conjunto de pasos obligatorios, combinados con otros opcionales o redefinibles.

#Aquí tienes el apartado **“Cómo lo soluciona C++ moderno”** reescrito de forma **más breve**, **sin ejemplos**, y centrado exclusivamente en la idea moderna.

## Cómo lo soluciona C++ moderno

En C++ moderno, los problemas que aborda el Template Method se resuelven mediante **composición** e **inyección de comportamiento**, evitando herencia y métodos virtuales.
En lugar de definir un método plantilla en una clase base, la estructura del algoritmo se implementa en una única función o clase ligera, y los pasos variables se proporcionan desde fuera mediante: **lambdas**, **`std::function`** u otros objetos invocables.

El algoritmo principal mantiene la **secuencia fija**, mientras que los pasos concretos se pasan como parámetros invocables.
Esto elimina jerarquías complejas, centraliza la lógica común y permite personalizar pasos sin modificar el esqueleto del proceso, logrando una solución más flexible, expresiva y fácil de extender.

## Ejemplos concretos

* **Procesamiento de archivos**: leer–parsear–procesar, donde distintos formatos implementan pasos concretos, pero la secuencia es siempre la misma.
* **Motores de juegos**: ciclo de actualización (update) con pasos fijos como entrada → lógica → física → render, permitiendo variaciones por entidad.
* **Generadores de reportes**: estructura de generación fija, pero cada tipo de informe implementa su formato concreto (HTML, PDF, CSV).
* **Algoritmos de IA o heurísticas**: un esqueleto común para búsqueda, donde las subclases redefinen la función de evaluación.
* **Frameworks web**: flujo de manejo de peticiones (antes → procesar → después), con hooks para personalizar comportamientos.
* **Sistemas de autenticación**: flujo general de validar credenciales, con métodos variables según el tipo (OAuth, LDAP, base de datos local).
* **Herramientas de análisis de datos**: pipelines con fases fijas (cargar → limpiar → transformar → exportar), pero con pasos especializados.
* **Motores de plantillas (templating)**: renderizado con pasos comunes (cargar contexto, aplicar transformaciones, producir salida), donde cada motor implementa detalles.
* **Procesos industriales simulados**: secuencias con etapas fijas (iniciar → ejecutar → verificar → finalizar) donde cada máquina implementa detalles.
* **Sistemas de pruebas automatizadas**: secuencia fija (setup → run → teardown), con variaciones según el tipo de prueba o entorno.
