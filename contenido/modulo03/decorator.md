# Patrón Decorator

## Definición

El **Decorator** es un patrón de diseño estructural que permite **añadir funcionalidades adicionales a un objeto de forma dinámica**, sin modificar su clase original. Para lograrlo, el objeto se **envuelve** dentro de otro objeto (el decorador) que implementa la misma interfaz y que **delegará el comportamiento base**, añadiendo funcionalidad extra antes o después de dicha delegación.

## Objetivos del patrón

El patrón Decorator persigue principalmente los siguientes objetivos:

* **Extender el comportamiento de un objeto** sin alterar su implementación original.
* **Evitar la proliferación de subclases**, ofreciendo una alternativa flexible a la herencia.
* **Permitir combinaciones dinámicas de funcionalidades**, incluso en tiempo de ejecución.
* **Mantener el código cliente desacoplado**, trabajando siempre contra una interfaz común.

## Problemas que intenta solucionar

* **Explosión de clases por herencia**, cuando cada nueva funcionalidad o combinación de ellas obliga a crear subclases adicionales, haciendo el diseño difícil de mantener y escalar.
* **Falta de flexibilidad en la extensión de comportamiento**, ya que la herencia fija las variaciones en tiempo de compilación y no permite combinarlas dinámicamente.
* **Necesidad de aplicar responsabilidades de forma selectiva**, donde no todos los objetos deben tener el mismo conjunto de funcionalidades adicionales.
* **Imposibilidad o riesgo de modificar código existente**, especialmente cuando las clases base ya están probadas, reutilizadas o forman parte de librerías externas.

## Cómo lo soluciona

* **Uso de una interfaz común**, de modo que tanto el componente base como los decoradores pueden tratarse de forma uniforme por el código cliente.
* **Encapsulación del objeto original**, envolviéndolo dentro de un decorador que delega el comportamiento principal sin alterarlo.
* **Adición incremental de funcionalidades**, permitiendo que cada decorador añada una responsabilidad concreta antes o después de la delegación.
* **Composición flexible de decoradores**, que pueden encadenarse entre sí para construir comportamientos complejos sin recurrir a herencia múltiple.

## Relación con los principios SOLID

* **Single Responsibility Principle (SRP)**: El patrón *Decorator* separa la responsabilidad del **comportamiento base** (componente concreto) de las **responsabilidades adicionales** (decoradores). Cada decorador introduce una única variación funcional, manteniendo clases pequeñas y con un solo motivo de cambio.
* **Open/Closed Principle (OCP)**: El comportamiento de un objeto puede ampliarse mediante nuevos decoradores sin modificar el código existente ni la clase original. El sistema queda abierto a extensión a través de composición y cerrado a modificación.
* **Liskov Substitution Principle (LSP)**: Un objeto decorado puede sustituir a un componente no decorado sin alterar la corrección del programa. Los decoradores respetan el contrato definido por la interfaz común y mantienen el comportamiento esperado por el cliente.
* **Interface Segregation Principle (ISP)**: El patrón promueve interfaces simples y cohesivas. Los decoradores implementan exactamente la misma interfaz que el componente, sin forzar al cliente a depender de métodos adicionales o innecesarios.
* **Dependency Inversion Principle (DIP)**: El cliente depende únicamente de la abstracción común del componente. Tanto el objeto base como los decoradores concretos se manipulan a través de la misma interfaz, evitando dependencias directas con implementaciones específicas.


## Ejemplos concretos

* **Streams y filtros de E/S** (similar al diseño de iostreams en C++): añadir compresión, cifrado, buffering, o logging a un flujo sin alterar su implementación base.
* **Interfaz de usuario**: agregar bordes, barras de desplazamiento o sombreado a widgets de forma dinámica.
* **Sistemas de notificación**: enviar un mensaje y decorarlo con notificación por email, SMS, o logging adicional.
* **Validación de datos**: añadir validaciones progresivas (longitud, formato, unicidad) sobre un validador base.
* **Sistemas de autenticación**: agregar capas adicionales como caching, auditoría o limitación de intentos.
* **Modelado de precios o impuestos**: aplicar recargos, descuentos o impuestos adicionales envolviendo un cálculo base.
* **Formatos de salida**: añadir características como numeración, resaltado o documentación adicional a un generador de texto.
* **Decoración en juegos**: aplicar efectos a un personaje (fuerza extra, defensa, invisibilidad) combinando decoradores de habilidades.

