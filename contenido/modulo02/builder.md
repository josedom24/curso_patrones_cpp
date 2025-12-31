# Patrón Builder

## Definición

El **Builder** es un patrón de diseño creacional que **separa la construcción de un objeto complejo de su representación final**, delegando el proceso de creación en un objeto especializado (*builder*).
Este enfoque permite **construir objetos paso a paso**, manteniendo el producto final independiente del procedimiento concreto de construcción y evitando inicializaciones rígidas, difíciles de leer o propensas a errores.

## Objetivos del patrón

* **Simplificar la creación de objetos complejos**, evitando inicializaciones con muchos parámetros difíciles de interpretar.
* **Separar la lógica de construcción** de la clase del objeto, reduciendo acoplamiento y mejorando la mantenibilidad.
* **Permitir múltiples configuraciones válidas** de un mismo objeto mediante un proceso claro y reutilizable.
* **Garantizar la consistencia del objeto final**, asegurando que solo se construyan instancias en estados válidos.

## Problemas que intenta solucionar

El patrón Builder es especialmente útil cuando se presentan estas situaciones:

* La necesidad de construir objetos con **numerosos parámetros opcionales o dependientes**, complicados de manejar en una única llamada de creación.
* El uso de **inicializaciones extensas y poco legibles**, donde el significado de cada argumento no es evidente para el cliente.
* La existencia de procesos de creación **formados por varios pasos internos** (validaciones, cálculos, inicializaciones) que no deberían exponerse al código cliente.
* El requisito de generar **distintas configuraciones o representaciones** de un mismo objeto sin duplicar lógica ni modificar su implementación.

## Cómo lo soluciona

El patrón Builder resuelve estos problemas mediante:

* La definición de un **builder** que permite **configurar el objeto de forma incremental**, encapsulando toda la lógica de inicialización, validación y ensamblaje.
* La **separación clara entre el proceso de construcción y el producto final**, lo que permite generar distintas variantes sin modificar la clase del producto.
* El uso opcional de un **director**, responsable de **coordinar y reutilizar la secuencia de pasos** necesarios para construir objetos complejos.
* La creación del objeto final **solo cuando el proceso de construcción ha concluido**, garantizando que el producto se entregue en un estado completo y coherente.

## Relación con los principios SOLID 

* **Single Responsibility Principle (SRP)**: El patrón separa claramente la **lógica de construcción** del objeto final, evitando que la clase del producto asuma responsabilidades adicionales. El *builder* se centra en la creación, mientras que el producto representa únicamente el resultado construido.
* **Open/Closed Principle (OCP)**: Es posible añadir **nuevas variantes de construcción** mediante nuevos *builders* concretos, sin modificar el código existente ni las abstracciones ya definidas.
* **Liskov Substitution Principle (LSP)**: Las implementaciones concretas del *builder* pueden utilizarse a través de su **interfaz abstracta**, sin alterar el proceso de construcción definido por el cliente o el director.
* **Interface Segregation Principle (ISP)**: La interfaz del *builder* expone **solo las operaciones necesarias para la construcción**, evitando interfaces infladas o dependencias innecesarias.
* **Dependency Inversion Principle (DIP)**: El cliente y el director dependen de **abstracciones**, no de implementaciones concretas de *builders*, lo que reduce el acoplamiento y facilita la sustitución de estrategias de construcción.

## Ejemplos concretos

* **Construcción de documentos**: Crear informes en HTML, JSON o texto plano usando los mismos pasos pero builders distintos.
* **Generación de objetos de configuración**: Sistemas donde distintos módulos requieren configuraciones detalladas pero opcionales.
* **Creación de entidades complejas en videojuegos**: Personajes, niveles o misiones que requieren muchos parámetros opcionales (atributos, inventario, IA, animaciones).
* **Sistemas de construcción de consultas**: *Query builders* que generan SQL, expresiones lógicas o pipelines de filtrado sin que el usuario deba escribir la sintaxis completa.
* **Inicialización de objetos de red**: Configurar conexiones complejas (TLS, certificados, políticas de reintentos, timeouts) paso a paso.
* **Procesamiento de datos**: Construcción de pipelines con pasos opcionales de validación, limpieza, normalización o transformación.
* **Serializadores**: Generar diversas representaciones del mismo conjunto de datos (p.ej., XML, JSON, YAML) desde un procedimiento de construcción común.
* **Interfaces fluidas (fluent interfaces)**: Objetos que se construyen encadenando métodos de forma expresiva y segura.
* **Builders de escenarios o configuraciones en tests**: Facilitan la creación de objetos con valores predeterminados, sobrescribibles y fiables para pruebas unitarias.
* **Montaje de interfaces gráficas**: Construcción incremental de ventanas, paneles y widgets, especialmente cuando la inicialización no es trivial.
