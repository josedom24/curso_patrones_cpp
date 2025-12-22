# Patrón Adapter

## Definición

El **Adapter** es un patrón de diseño estructural cuyo propósito es **compatibilizar interfaces incompatibles**. Permite que objetos que no fueron diseñados para trabajar juntos puedan colaborar, proporcionando una **interfaz objetivo** que el cliente espera y traduciendo internamente las llamadas hacia el objeto adaptado.

Su función esencial es actuar como un **puente** entre dos interfaces distintas: la que el cliente conoce y la que realmente ofrece una clase existente.

## Problemas que intenta solucionar

El patrón Adapter resulta útil en estas situaciones:

* Se dispone de una **clase existente** cuya interfaz no coincide con la que espera el código cliente.
* Es necesario integrar **código legado**, librerías de terceros o APIs externas que no se pueden modificar.
* Varias clases ofrecen la misma funcionalidad pero con **interfaces distintas**, y se quiere unificar su uso.
* El cliente debería depender de una **interfaz estable**, aunque las implementaciones concretas cambien con el tiempo.
* Se busca **evitar reescribir** o duplicar lógica que ya existe, reutilizando componentes sin alterar su código.

## Cómo lo soluciona

El Adapter aporta estas soluciones:

* Define una **interfaz objetivo** que representa cómo el cliente quiere interactuar con el objeto.
* Proporciona una clase **adaptadora** que implementa esa interfaz y contiene (por composición) una instancia del objeto incompatible.
* Traduce las llamadas del cliente a métodos compatibles con la interfaz del adaptado.
* Permite reutilizar clases externas sin modificarlas, cumpliendo así el principio *Open/Closed*.
* Separa claramente la **interfaz cliente** de la **implementación interna o legado**, favoreciendo el desacoplamiento.

# Relación con los principios SOLID

* **Single Responsibility Principle (SRP)**: El patrón *Adapter* encapsula la lógica de adaptación entre interfaces incompatibles en una clase específica. De este modo, ni la clase cliente ni la clase adaptada asumen responsabilidades adicionales relacionadas con la conversión de interfaces, manteniendo cada componente enfocado en una única tarea bien definida.

* **Open/Closed Principle (OCP)**: El sistema puede extenderse para soportar nuevas interfaces o clases existentes mediante la incorporación de nuevos adaptadores, sin modificar el código del cliente ni el de las clases ya implementadas. Las abstracciones permanecen cerradas a cambios y abiertas a extensión a través de adaptadores adicionales.

* **Dependency Inversion Principle (DIP)**: El cliente depende exclusivamente de la interfaz objetivo (*Target*), no de implementaciones concretas ni de clases externas con interfaces incompatibles. El adaptador actúa como intermediario que implementa dicha abstracción, invirtiendo la dependencia y permitiendo sustituir o introducir nuevas adaptaciones sin afectar al código cliente.


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
