# Abstract Factory

## Definición


El **Abstract Factory** es un patrón de diseño creacional que proporciona una **interfaz para crear familias de objetos relacionados y coherentes entre sí**, sin especificar sus clases concretas, garantizando que los productos creados sean compatibles entre ellos.

Cuando hablamos de **familia de productos**, nos referimos a un **conjunto coherente de tipos** que están pensados para usarse juntos porque comparten un contexto común. Por ejemplo:

* En una interfaz gráfica: *Botón*, *Ventana* y *Cuadro de texto* para un mismo sistema operativo o tema visual.
* En un motor de bases de datos: *Conexión*, *Comando* y *Transacción* para un mismo tipo de base de datos.

## Objetivos

* Permitir al **código cliente crear y utilizar familias completas de productos relacionados**, garantizando su **compatibilidad interna**.
* **Aislar al cliente de las clases concretas**, haciendo que dependa únicamente de interfaces o clases abstractas.
* Facilitar el **cambio de una familia de productos por otra** (por ejemplo, cambiar de estilo "Windows" a "Linux") sin modificar el código cliente.
* Evitar la **mezcla accidental de productos pertenecientes a distintas familias**, manteniendo la coherencia del sistema.

## Problemas que intenta solucionar

El patrón **Abstract Factory** resulta adecuado cuando:

* Es necesario crear **familias completas de objetos relacionados**, que deben ser coherentes y compatibles entre sí.
* Se quiere **evitar la combinación de productos de distintas familias**, preservando la consistencia del sistema.
* El código cliente debe **permanecer desacoplado de las clases concretas**, trabajando únicamente con interfaces o abstracciones.
* Se prevé la necesidad de **incorporar nuevas familias de productos** sin modificar el código cliente existente.

## Cómo lo soluciona

El patrón **Abstract Factory** aporta las siguientes ideas:

* Define una **fábrica abstracta** que declara los métodos de creación para **cada producto de una familia**.
* Cada **fábrica concreta** implementa esos métodos creando **variantes concretas pero compatibles** de los productos.
* El código cliente **depende únicamente de la fábrica abstracta y de las interfaces de los productos**, permaneciendo desacoplado de las clases concretas.
* El **cambio o ampliación de familias completas** se logra sustituyendo o añadiendo fábricas concretas, **sin modificar el código cliente**.

## Relación con los principios SOLID

* **Single Responsibility Principle (SRP)**: La responsabilidad de crear productos compatibles se concentra en las fábricas, mientras que el cliente se limita a utilizar interfaces abstractas.
* **Open/Closed Principle (OCP)**: Permite añadir nuevas familias de productos mediante nuevas fábricas concretas, sin modificar el código cliente ni las abstracciones existentes.
* **Liskov Substitution Principle (LSP)**: Las fábricas y productos concretos pueden sustituirse por sus abstracciones sin alterar el comportamiento esperado por el cliente.
* **Interface Segregation Principle (ISP)**: El patrón favorece interfaces de producto específicas y cohesionadas, evitando que los clientes dependan de métodos innecesarios.
* **Dependency Inversion Principle (DIP)**: El cliente depende únicamente de interfaces abstractas de fábricas y productos, no de clases concretas, logrando un fuerte desacoplamiento.

## Ejemplos concretos

En todos los ejemplos, se indican explícitamente las **familias de productos** implicadas:

* **Interfaces gráficas multi-plataforma**
  *Familias:*

  * Familia "Windows": `WindowsButton`, `WindowsWindow`, `WindowsMenu`.
  * Familia "Linux": `LinuxButton`, `LinuxWindow`, `LinuxMenu`.
    Una fábrica abstracta de widgets permite crear todos los componentes de interfaz para un sistema operativo concreto, manteniendo coherencia visual y de comportamiento.

* **Sistemas de temas visuales (light/dark theme)**
  *Familias:*

  * Familia "Tema claro": `LightButton`, `LightDialog`, `LightScrollbar`.
  * Familia "Tema oscuro": `DarkButton`, `DarkDialog`, `DarkScrollbar`.
    Cambiando la fábrica de temas se generan automáticamente todos los controles con el estilo apropiado sin tocar el resto del código.

* **Acceso a bases de datos con múltiples proveedores**
  *Familias:*

  * Familia "SQLite": `SQLiteConnection`, `SQLiteCommand`, `SQLiteTransaction`.
  * Familia "PostgreSQL": `PgConnection`, `PgCommand`, `PgTransaction`.
    La fábrica abstracta de acceso a datos crea objetos adecuados para cada proveedor, evitando mezclar, por ejemplo, una conexión MySQL con un comando PostgreSQL.

* **Motores de juegos con estilos de mundo diferentes**
  *Familias:*

  * Familia "Fantasía medieval": `MedievalEnemy`, `MedievalWeapon`, `MedievalEnvironmentObject`.
  * Familia "Ciencia ficción": `SciFiEnemy`, `SciFiWeapon`, `SciFiEnvironmentObject`.
    Cada fábrica crea el conjunto completo de elementos del mundo coherentes con una ambientación concreta.

* **Sistemas de generación de documentos en diferentes formatos**
  *Familias:*

  * Familia "HTML": `HtmlParagraph`, `HtmlTable`, `HtmlImage`.
  * Familia "PDF": `PdfParagraph`, `PdfTable`, `PdfImage`.
    Una fábrica abstracta de componentes de documento permite construir informes usando una misma interfaz, generando luego toda la salida en el formato elegido.

* **Frameworks de notificación multi-canal con estilos coherentes**
  *Familias:*

  * Familia "Notificación básica": `BasicEmailNotification`, `BasicSmsNotification`, `BasicPushNotification`.
  * Familia "Notificación corporativa": `CorporateEmailNotification`, `CorporateSmsNotification`, `CorporatePushNotification`.
    Cada fábrica crea una familia de canales con el mismo estilo de contenido y formato (por ejemplo, textos más formales en la familia corporativa).

