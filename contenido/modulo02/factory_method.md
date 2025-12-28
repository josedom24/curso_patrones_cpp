# Patrón Factory Method

## Definición

El **Factory Method** es un patrón de diseño creacional que delega la creación de objetos a una interfaz o clase base, permitiendo que las subclases decidan qué tipo concreto de objeto instanciar. Su objetivo es desacoplar el código cliente del proceso exacto de creación de los objetos.

## Problemas que intenta solucionar

El patrón aborda principalmente estas situaciones:

* El código cliente depende de clases concretas cuya creación debería estar oculta.
* La lógica de creación puede variar según el contexto, y mezclarla con el código cliente reduce la flexibilidad.
* Se requiere extender el sistema con nuevos tipos de productos sin modificar el código existente (evitando violar *Open/Closed Principle*).
* Se quiere centralizar o controlar la creación de objetos, por ejemplo para aplicar inicializaciones específicas.
* Se busca evitar el uso extensivo de `if`/`switch` para seleccionar la clase concreta a instanciar.

## Cómo lo soluciona

El Factory Method aporta estas soluciones:

* Define un **método de creación** (factory method) en una interfaz o clase base.
* Permite que las **subclases sobrescriban** ese método para crear el tipo concreto de producto necesario.
* Aísla el código cliente del conocimiento de qué clases específicas se están instanciando.
* Facilita la **extensibilidad**: añadir un nuevo tipo concreto solo requiere crear una nueva subclase con su propio método de creación.
* Refuerza el principio *Open/Closed* y la separación clara entre **uso** y **creación** de objetos.

## Relación con los principios SOLID

* **Single Responsibility Principle (SRP)**: El patrón separa la responsabilidad de creación de la responsabilidad de uso. Las fábricas crean; los productos actúan. Aunque no es el objetivo principal del patrón, esta separación refuerza el SRP de manera natural.
* **Open/Closed Principle (OCP)**: El patrón permite extender el sistema añadiendo nuevos productos concretos sin modificar el código existente. Basta con crear una nueva subclase que redefina el método de creación. Esto convierte al *Factory Method* en uno de los patrones que mejor ejemplifican OCP.
* **Liskov Substitution Principle (LSP)**: Las fábricas y productos concretos pueden sustituirse por sus abstracciones sin alterar el comportamiento esperado por el cliente.
* **Interface Segregation Principle (ISP)**: Las interfaces de producto y de fábrica se mantienen simples y específicas, evitando obligar a los clientes a depender de métodos que no utilizan.
* **Dependency Inversion Principle (DIP)**: El cliente depende de abstracciones —interfaces de fábrica y de producto— en lugar de depender directamente de clases concretas. La lógica de creación se invierte: el cliente no instancia los objetos, sino que delega esa responsabilidad en una fábrica que implementa una interfaz común. Esta inversión del control de creación refleja fuertemente el DIP.

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
