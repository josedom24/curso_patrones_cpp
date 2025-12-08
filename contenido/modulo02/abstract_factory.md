# Abstract Factory

## Definición

El **Abstract Factory** es un patrón de diseño creacional que proporciona una **interfaz para crear familias de objetos relacionados entre sí**, sin especificar sus clases concretas.

Cuando hablamos de **familia de productos**, nos referimos a un **conjunto coherente de tipos** que están pensados para usarse juntos porque comparten un contexto común. Por ejemplo:

* En una interfaz gráfica: *Botón*, *Ventana* y *Cuadro de texto* para un mismo sistema operativo o tema visual.
* En un motor de bases de datos: *Conexión*, *Comando* y *Transacción* para un mismo tipo de base de datos.

El objetivo del patrón es que el código cliente pueda trabajar con **familias completas de productos compatibles** (p.ej., todos “estilo Windows” o todos “estilo Linux”) sin conocer las clases concretas ni mezclar productos de familias diferentes.

## Problemas que intenta solucionar

El patrón Abstract Factory resulta útil cuando:
A
* Se necesitan crear **conjuntos completos de objetos relacionados** (familias) que deben ser coherentes entre sí.
* Se quiere **evitar mezclar productos de distintas familias**, por ejemplo un botón “tema oscuro” con una ventana “tema claro”.
* El código cliente **no debería depender de clases concretas**, sino solo de interfaces o tipos abstractos.
* Se prevé que en el futuro se necesitarán **nuevas familias completas** (por ejemplo, un nuevo tema visual o un nuevo proveedor de base de datos).
* Se quiere centralizar la **selección de la familia activa** (p.ej., según configuración, sistema operativo, modo “light/dark”, etc.) en un único punto del sistema.

## Cómo lo soluciona

Abstract Factory aporta las siguientes ideas:

* Define una **fábrica abstracta** que declara métodos para crear **cada producto de la familia**
  (por ejemplo: `createButton()`, `createWindow()`, `createCheckbox()`).
* Cada **fábrica concreta** implementa esos métodos devolviendo **variantes concretas pero compatibles** de la familia
  (por ejemplo: `WindowsButton`, `WindowsWindow`, `WindowsCheckbox` frente a `LinuxButton`, `LinuxWindow`, `LinuxCheckbox`).
* El código cliente **solo conoce la fábrica abstracta y las interfaces de los productos**, no las clases concretas.
* Cambiar de familia (por ejemplo, “Windows” a “Linux”, o “tema claro” a “tema oscuro”) se reduce a **cambiar la fábrica concreta** que se instancia.
* La incorporación de una nueva familia se hace creando una **nueva fábrica concreta** y los productos correspondientes, sin modificar el código cliente, respetando el principio de *Open/Closed*.

## Relación con los principios SOLID

* **Open/Closed Principle (OCP)**:
  *Abstract Factory* facilita la extensión de familias completas de productos sin modificar el código cliente ni las fábricas ya existentes. Para introducir una nueva familia, basta con definir una nueva implementación concreta de la fábrica y sus productos asociados. La estructura del patrón permite que el sistema evolucione por **extensión** y no por **modificación**, ejemplificando de forma muy directa el OCP.

* **Dependency Inversion Principle (DIP)**:
  El cliente trabaja exclusivamente con **interfaces abstractas** tanto de fábrica como de productos. Nunca depende de clases concretas.
  La lógica de selección de la familia de productos se invierte: el cliente no decide qué tipos concretos instanciar, sino que recibe o construye una fábrica que cumple una interfaz abstracta.
  Este desacoplamiento profundo entre cliente y productos concretos convierte a *Abstract Factory* en uno de los patrones que más claramente refuerzan el DIP.

* **Single Responsibility Principle (SRP)**:
  El patrón distribuye las responsabilidades de forma nítida:

  * La fábrica concreta se responsabiliza de **crear objetos compatibles** pertenecientes a la misma familia.
  * El cliente se limita a **usar** los productos abstractos sin conocer su implementación.
    Esta separación de responsabilidades reduce el acoplamiento y garantiza que los cambios en la creación de objetos no afecten al código que los utiliza, lo cual es coherente con el SRP.

## Ejemplos concretos

En todos los ejemplos, se indican explícitamente las **familias de productos** implicadas:

* **Interfaces gráficas multi-plataforma**
  *Familias:*

  * Familia “Windows”: `WindowsButton`, `WindowsWindow`, `WindowsMenu`.
  * Familia “Linux”: `LinuxButton`, `LinuxWindow`, `LinuxMenu`.
    Una fábrica abstracta de widgets permite crear todos los componentes de interfaz para un sistema operativo concreto, manteniendo coherencia visual y de comportamiento.

* **Sistemas de temas visuales (light/dark theme)**
  *Familias:*

  * Familia “Tema claro”: `LightButton`, `LightDialog`, `LightScrollbar`.
  * Familia “Tema oscuro”: `DarkButton`, `DarkDialog`, `DarkScrollbar`.
    Cambiando la fábrica de temas se generan automáticamente todos los controles con el estilo apropiado sin tocar el resto del código.

* **Acceso a bases de datos con múltiples proveedores**
  *Familias:*

  * Familia “SQLite”: `SQLiteConnection`, `SQLiteCommand`, `SQLiteTransaction`.
  * Familia “PostgreSQL”: `PgConnection`, `PgCommand`, `PgTransaction`.
    La fábrica abstracta de acceso a datos crea objetos adecuados para cada proveedor, evitando mezclar, por ejemplo, una conexión MySQL con un comando PostgreSQL.

* **Motores de juegos con estilos de mundo diferentes**
  *Familias:*

  * Familia “Fantasía medieval”: `MedievalEnemy`, `MedievalWeapon`, `MedievalEnvironmentObject`.
  * Familia “Ciencia ficción”: `SciFiEnemy`, `SciFiWeapon`, `SciFiEnvironmentObject`.
    Cada fábrica crea el conjunto completo de elementos del mundo coherentes con una ambientación concreta.

* **Sistemas de generación de documentos en diferentes formatos**
  *Familias:*

  * Familia “HTML”: `HtmlParagraph`, `HtmlTable`, `HtmlImage`.
  * Familia “PDF”: `PdfParagraph`, `PdfTable`, `PdfImage`.
    Una fábrica abstracta de componentes de documento permite construir informes usando una misma interfaz, generando luego toda la salida en el formato elegido.

* **Frameworks de notificación multi-canal con estilos coherentes**
  *Familias:*

  * Familia “Notificación básica”: `BasicEmailNotification`, `BasicSmsNotification`, `BasicPushNotification`.
  * Familia “Notificación corporativa”: `CorporateEmailNotification`, `CorporateSmsNotification`, `CorporatePushNotification`.
    Cada fábrica crea una familia de canales con el mismo estilo de contenido y formato (por ejemplo, textos más formales en la familia corporativa).

