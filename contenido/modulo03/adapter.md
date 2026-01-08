# Patrón Adapter

## Definición

El **Adapter** es un patrón de diseño **estructural** cuyo propósito es **compatibilizar interfaces incompatibles**. Permite que clases que no fueron diseñadas para trabajar juntas puedan colaborar, ofreciendo al cliente una **interfaz objetivo** conocida y actuando como un **puente** hacia una interfaz existente diferente.

## Objetivos del patrón

* **Hacer compatibles interfaces distintas** sin modificar las clases existentes.
* **Reutilizar código** ya implementado, incluyendo código legado o de terceros.
* **Proteger al cliente** de cambios en implementaciones concretas.
* **Unificar el acceso** a distintas clases bajo una interfaz común y estable.

## Problemas que intenta solucionar

El patrón Adapter resulta útil en estas situaciones:

* Existe una **clase existente** cuya interfaz no coincide con la que espera el cliente.
* Es necesario integrar **código legado, librerías externas o APIs** que no se pueden modificar.
* Varias clases ofrecen funcionalidades similares pero con **interfaces diferentes**.
* El cliente queda **acoplado a implementaciones concretas**, dificultando la evolución del sistema.

## Cómo lo soluciona

El Adapter aporta estas soluciones:

* Define una **interfaz objetivo** que representa cómo el cliente quiere interactuar.
* Introduce una **clase adaptadora** que implementa esa interfaz.
* El adaptador **traduce las llamadas** del cliente a la interfaz real del objeto adaptado.
* Separa claramente la **interfaz del cliente** de la **implementación existente**, favoreciendo el desacoplamiento y la reutilización.

## Relación con los principios SOLID

* **SRP (Single Responsibility Principle)**:
* **OCP (Open/Closed Principle)**: se pueden añadir **nuevos adaptadores** para soportar nuevas interfaces o clases existentes **sin modificar** el cliente ni las clases ya implementadas.
* **LSP (Liskov Substitution Principle)**: cualquier adaptador que implemente la **interfaz objetivo** puede sustituirse por otro sin cambiar el comportamiento esperado por el cliente.
* **ISP (Interface Segregation Principle)**: la **interfaz objetivo** se diseña según lo que el cliente necesita, evitando forzarlo a depender de métodos innecesarios.
* **DIP (Dependency Inversion Principle)**: el cliente depende de la **abstracción** (interfaz objetivo), no de implementaciones concretas ni de APIs incompatibles; el adaptador actúa como intermediario que cumple esa abstracción.

## Ejemplos concretos

* **Sistemas gráficos o motores de juego**: Adaptar distintas librerías de renderizado para usar una misma interfaz de dibujo.
* **Acceso a archivos**: Unificar el uso de distintas APIs para manejar archivos (C, C++, POSIX, plataformas móviles) bajo una misma interfaz.
* **Servicios web o APIs externas**: Adaptar respuestas o clientes HTTP de distintas librerías para presentarlos con un formato homogéneo al resto del sistema.
* **Integración con código antiguo**: Reutilizar módulos legacy cuya interfaz no coincide con la arquitectura moderna.
* **Controladores de dispositivos**: Adaptar distintos drivers o protocolos de comunicación a una interfaz de control estándar.
* **Aplicaciones de logging**: Unificar múltiples librerías de logs externas bajo una única interfaz común.
* **Bases de datos**: Crear adaptadores para distintos conectores SQL/NoSQL, que ofrecen APIs incompatibles.
* **Sistemas de pago**: Adaptar distintos proveedores (Stripe, PayPal, Redsys,...) a una interfaz única del sistema de cobros.
* **Frameworks multimedia**: Permitir que distintos decodificadores de audio/vídeo se usen intercambiablemente.
* **Conversión de tipos o formatos**: Adaptar estructuras de datos antiguas a nuevos modelos de dominio sin reescribir toda la lógica.




