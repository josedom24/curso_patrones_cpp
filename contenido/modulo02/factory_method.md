# Patrón Factory Method

## Definición

El **Factory Method** es un patrón de **diseño creacional** cuyo propósito es **separar la responsabilidad de crear objetos de la responsabilidad de usarlos**. Con esto conseguimos:

## Objetivos

* **Separar creación y uso de objetos**: La lógica de creación no forma parte del código que utiliza los objetos.
* **Reducir el acoplamiento**: El sistema depende de abstracciones, no de clases concretas.
* **Facilitar la extensibilidad**: Nuevos tipos de objetos pueden incorporarse sin modificar el código cliente existente.
* **Centralizar y controlar la creación**: La creación deja de estar dispersa en el código cliente y pasa a estar estructurada y controlada.

## Problemas que intenta solucionar

El patrón aborda principalmente estas situaciones:

* El código cliente **depende de clases concretas y de su creación**, generando un alto acoplamiento.
* La **lógica de creación puede variar** y se desea **encapsularla y controlarla en un punto bien definido**, separándola del uso de los objetos.
* Se necesita **extender el sistema con nuevos tipos de objetos** sin modificar el código existente, respetando el **principio Open/Closed**.
* La selección del tipo concreto se realiza mediante **condicionales explícitos (if / switch)**, dando lugar a código rígido y poco extensible.

## Cómo lo soluciona

El **Factory Method** estructura la creación de objetos de la siguiente forma:

* Introduce una **clase creadora abstracta** que declara un **método de creación** (*factory method*), encargado de devolver un producto a través de su **abstracción**.
* Define una **jerarquía de productos**, compuesta por una **abstracción de producto** y varias **clases concretas** que implementan dicha abstracción.
* Las **clases creadoras concretas** heredan de la creadora abstracta y **implementan el método de creación**, decidiendo qué producto concreto instanciar.
* El código cliente interactúa únicamente con la **abstracción del creador** y con la **abstracción del producto**, sin conocer las clases concretas involucradas en la creación.

## Relación con los principios SOLID

* **Single Responsibility Principle (SRP)**: El patrón separa claramente la **responsabilidad de crear objetos** de la **responsabilidad de utilizarlos**. Las clases creadoras se encargan del proceso de creación, mientras que los productos encapsulan el comportamiento. Esta separación reduce motivos de cambio en cada clase.
* **Open/Closed Principle (OCP)**:  El sistema puede **extenderse mediante nuevos productos y nuevos creadores concretos** sin modificar el código existente. Podemos extender creando nuevas clases concretas que implementan el método de creación.
* **Liskov Substitution Principle (LSP)**: Los creadores concretos y los productos concretos **pueden sustituirse por sus abstracciones** sin afectar al código cliente, que opera exclusivamente a través de contratos comunes.
* **Interface Segregation Principle (ISP)**: El patrón favorece la definición de **abstracciones simples y específicas** tanto para los productos como para los creadores. No obstante, el cumplimiento de ISP **depende del diseño concreto** de las abstracciones, más que del patrón en sí.
* **Dependency Inversion Principle (DIP)**: El código cliente depende de **abstracciones**, tanto para los productos como para los creadores. La decisión sobre qué objeto concreto crear no está en el cliente, sino delegada a una abstracción que encapsula la creación.

## Ejemplos concretos

* **Sistema de registros o logs**: Crear diferentes tipos de *loggers* (a consola, a archivo, a red) sin que el código cliente sepa cuál instancia concreta usa.
* **Motores gráficos o juegos**: Crear distintos tipos de enemigos, proyectiles o elementos del escenario dependiendo del nivel o dificultad.
* **Lectores y escritores de archivos**: Seleccionar automáticamente un parser distinto (JSON, XML, CSV,...) según el tipo de archivo detectado.
* **Aplicaciones con interfaz gráfica**: Crear widgets específicos según el sistema operativo (Windows, macOS, Linux) sin cambiar el código de la interfaz común.
* **Conexiones a bases de datos**: Elegir el conector concreto (SQLite, PostgreSQL, MySQL) en función de la configuración.
* **Sistemas de notificación**: Crear objetos que envían mensajes por distintos canales (email, SMS, webhooks) dependiendo del contexto.
* **Frameworks de comunicación en red**: Instanciar diferentes clases para gestionar protocolos concretos (HTTP, TCP, UDP) sin exponer los detalles.
* **Sistemas de plugins o extensiones**: Permitir que nuevas funcionalidades se añadan registrando nuevas fábricas sin modificar el core.
* **Aplicaciones de trazado o análisis**: Crear distintos algoritmos o estrategias de procesamiento a partir de una interfaz común, elegidos según parámetros de configuración.
* **Generadores de reportes**: Producir informes PDF, HTML o texto plano usando diferentes clases, todas creadas a partir de un único punto de entrada.

