# Patrón Template Method

## Definición

El **Template Method** es un patrón de diseño de comportamiento que define el **esqueleto de un algoritmo**, fijando su secuencia general, mientras permite que **algunos pasos concretos varíen**. La idea central es mantener estable la estructura del proceso y delegar las partes variables sin alterar el flujo global.

## Objetivos

* Definir una **estructura común y estable** para un algoritmo.
* Evitar la **duplicación de código** en algoritmos con pasos compartidos.
* Permitir que ciertos pasos del proceso **varíen de forma controlada**.
* Garantizar que el **orden del algoritmo no pueda alterarse** accidentalmente.

## Cuándo usarlo

El patrón Template Method es adecuado cuando:

* Existe un algoritmo con una **secuencia fija**, pero con pasos que dependen del contexto.
* Varias implementaciones comparten la misma lógica general con **pequeñas variaciones**.
* Se quiere controlar el flujo del algoritmo y **restringir modificaciones estructurales**.
* Es importante reutilizar una lógica común manteniendo coherencia en el proceso.

En diseños modernos, estos escenarios no siempre requieren herencia explícita.

## Cómo se implementa en C++ moderno

En C++ moderno, el Template Method suele implementarse mediante **composición e inyección de comportamiento**, evitando jerarquías de clases y métodos virtuales.

La estructura del algoritmo se define en una función o clase que mantiene la **secuencia fija**, mientras que los pasos variables se proporcionan desde el exterior mediante:

* **Lambdas**
* **`std::function`**
* Otros objetos invocables

Este enfoque conserva el control del flujo, elimina la herencia innecesaria y permite personalizar partes del algoritmo de forma **más flexible, explícita y fácil de mantener**, reflejando mejor el estilo de diseño recomendado en C++ moderno.

## Ejemplos concretos

* **Procesamiento de archivos**: leer, parsear, procesar, donde distintos formatos implementan pasos concretos, pero la secuencia es siempre la misma.
* **Motores de juegos**: ciclo de actualización (update) con pasos fijos como entrada → lógica → física → render, permitiendo variaciones por entidad.
* **Generadores de reportes**: estructura de generación fija, pero cada tipo de informe implementa su formato concreto (HTML, PDF, CSV).
* **Algoritmos de IA o heurísticas**: un esqueleto común para búsqueda, donde las subclases redefinen la función de evaluación.
* **Frameworks web**: flujo de manejo de peticiones (antes → procesar → después), con hooks para personalizar comportamientos.
* **Sistemas de autenticación**: flujo general de validar credenciales, con métodos variables según el tipo (OAuth, LDAP, base de datos local).
* **Herramientas de análisis de datos**: pipelines con fases fijas (cargar → limpiar → transformar → exportar), pero con pasos especializados.
* **Motores de plantillas (templating)**: renderizado con pasos comunes (cargar contexto, aplicar transformaciones, producir salida), donde cada motor implementa detalles.
* **Procesos industriales simulados**: secuencias con etapas fijas (iniciar → ejecutar → verificar → finalizar) donde cada máquina implementa detalles.
* **Sistemas de pruebas automatizadas**: secuencia fija (setup → run → teardown), con variaciones según el tipo de prueba o entorno.
