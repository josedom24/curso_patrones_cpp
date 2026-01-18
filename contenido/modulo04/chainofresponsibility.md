# Patrón Chain of Responsibility

## Definición

El **Chain of Responsibility** es un patrón de diseño de comportamiento que organiza una secuencia de objetos (manejadores) por la que circulan peticiones. Cada objeto de la cadena decide si **procesar** la petición o **delegarla** al siguiente manejador. Su propósito es **desacoplar el emisor de la petición del receptor final**, permitiendo que múltiples objetos tengan la oportunidad de gestionarla sin que el código cliente conozca cuál será el responsable último.

## Objetivos del patrón

* **Desacoplar el emisor de una petición de su receptor concreto**, evitando que el código cliente tenga conocimiento explícito de qué objeto es responsable de procesarla.
* **Permitir que múltiples objetos tengan la oportunidad de manejar una misma petición**, estableciendo una cadena flexible en la que cada manejador decide si procesa o delega.
* **Eliminar lógica condicional compleja en el código cliente**, encapsulando los criterios de decisión dentro de los propios manejadores.
* **Facilitar la extensibilidad y reconfiguración del flujo de procesamiento**, permitiendo añadir, eliminar o reordenar manejadores sin modificar el código existente, respetando el principio *Open/Closed*.


## Problemas que intenta solucionar

El patrón aborda principalmente estas situaciones:

* **Acoplamiento fuerte entre el emisor de una petición y su receptor**, cuando el cliente necesita conocer explícitamente qué objeto debe procesar la solicitud.
* **Gestión rígida de responsabilidades**, donde una petición solo puede ser tratada por un único objeto o el orden de decisión está codificado directamente en el cliente.
* **Presencia de lógica condicional compleja** (`if`/`else`, `switch`) para decidir qué objeto debe manejar una petición, dificultando la legibilidad, el mantenimiento y la extensión del sistema.
* **Dificultad para extender o reconfigurar el procesamiento de peticiones**, cuando es necesario añadir nuevos criterios, cambiar el orden de evaluación o introducir nuevos manejadores sin modificar código existente.

## Cómo lo soluciona

El Chain of Responsibility aporta estas soluciones:

* **Define una interfaz común de manejador**, que declara la operación de procesamiento de la petición y la referencia al siguiente elemento de la cadena, unificando el modo de تعاملar con todos los manejadores.
* **Encapsula la lógica de decisión dentro de cada manejador**, permitiendo que cada objeto determine si procesa la petición o la delega, eliminando la lógica condicional del código cliente.
* **Permite construir y modificar cadenas dinámicas de procesamiento**, donde los manejadores pueden conectarse, reordenarse o sustituirse sin afectar al emisor de la petición.
* **Facilita la extensibilidad del sistema mediante composición**, permitiendo añadir nuevos manejadores simplemente incorporándolos a la cadena, sin modificar el código existente y respetando el principio *Open/Closed*.

## Relación con los principios SOLID

* **Single Responsibility Principle (SRP)**: Cada manejador **encapsula una responsabilidad concreta** (un paso/criterio) dentro del proceso, evitando concentrar la lógica de decisión y procesamiento en un único bloque.
* **Open/Closed Principle (OCP)**: La cadena puede extenderse añadiendo nuevos manejadores sin modificar los existentes ni el código cliente.
* **Liskov Substitution Principle (LSP)**: Cualquier manejador concreto puede sustituir a otro dentro de la cadena sin alterar el comportamiento esperado.
* **Interface Segregation Principle (ISP)**: La interfaz del manejador es mínima y específica, evitando dependencias innecesarias.
* **Dependency Inversion Principle (DIP)**: El cliente interactúa con una **abstracción de manejador** y la delegación se realiza también sobre esa abstracción; las dependencias a concretos quedan confinadas al c**ódigo de composición/configuración** de la cadena.

## Ejemplos concretos

* **Sistemas de validación**: Validadores encadenados donde cada uno comprueba un aspecto (formato, permisos, límites, existencia). Si uno falla, detiene la cadena.
* **Procesadores de eventos en interfaces gráficas**: Un evento (clic, teclado) se propaga por una jerarquía de widgets hasta que uno lo consume.
* **Filtros en servidores web**: Módulos que procesan una petición HTTP (autenticación, logging, compresión) antes de llegar al controlador principal.
* **Sistemas de logging**: Distintos manejadores (consola, archivo, red) pueden recibir un mensaje y decidir si lo procesan o lo pasan al siguiente.
* **Manejo de excepciones en tiempo de ejecución**: Cadena de bloques o componentes que intentan gestionar un error específico.
* **Procesamiento de comandos en juegos**: Una acción del jugador se transmite a distintos subsistemas (inventario, combate, diálogo) hasta que uno la reconoce.
* **Sistemas de permisos y autorización**: Cada manejador examina un nivel de autorización distinto y decide si concede acceso o pasa la petición a niveles superiores.
* **Procesamiento de datos en pipelines**: Cada etapa transforma o filtra los datos antes de pasar al siguiente paso del pipeline.
* **Routers o middleware en frameworks web**: Cada componente examina la ruta o cabeceras y decide si atiende la petición o delega más adelante.
* **Frameworks de análisis y depuración**: Módulos que inspeccionan, anotan o transforman trazas o mensajes en una cadena de responsabilidad configurable.
