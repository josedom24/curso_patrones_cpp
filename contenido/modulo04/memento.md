# Patrón Memento

## Definición

El **Memento** es un patrón de diseño de comportamiento que permite capturar y almacenar el **estado interno** de un objeto en un instante dado, para poder **restaurarlo posteriormente** sin violar el principio de **encapsulamiento**. El patrón separa claramente los roles de originador (objeto cuyo estado se guarda), memento (objeto que almacena el estado) y cuidador (*caretaker*, encargado de gestionar las copias).

## Objetivos del patrón

* **Permitir la restauración segura del estado de un objeto**, facilitando volver a estados anteriores (por ejemplo, en operaciones de *undo/redo*) sin exponer detalles internos.
* **Preservar el encapsulamiento**, asegurando que el estado interno del objeto no sea accesible ni manipulable por componentes externos.
* **Separar la gestión del estado de la lógica del objeto**, manteniendo responsabilidades claras entre originador, memento y cuidador.
* **Soportar múltiples puntos de restauración**, permitiendo gestionar historiales de estado sin que el cliente dependa de la representación interna del objeto.

## Problemas que intenta solucionar

El patrón aborda principalmente estas situaciones:

* **Necesidad de deshacer y rehacer cambios en un objeto**, volviendo a estados anteriores de forma controlada, como en editores, formularios o sistemas interactivos.
* **Riesgo de romper el encapsulamiento al guardar el estado**, cuando se requieren copias del estado interno sin exponer la estructura ni los detalles de implementación del objeto.
* **Mezcla de responsabilidades en las clases**, al incorporar lógica de guardado, restauración o versionado dentro de la lógica principal del objeto.
* **Gestión compleja y acoplada del historial de estados**, especialmente cuando se necesitan múltiples puntos de restauración y el cliente no debería conocer cómo se representa internamente el estado.

## Cómo lo soluciona

El patrón Memento aporta estas soluciones:

* **Encapsula el estado en un objeto Memento**, que almacena una instantánea del estado interno sin exponer su representación ni permitir accesos indebidos.
* **Hace que el propio originador controle la creación y restauración del estado**, garantizando coherencia y evitando que otros objetos manipulen su información interna.
* **Introduce un cuidador (Caretaker) que gestiona los mementos**, manteniendo historiales o pilas de estados sin conocer ni depender de su contenido.
* **Permite mantener múltiples estados de forma desacoplada**, facilitando operaciones como *undo/redo* y la evolución del estado interno sin afectar al código cliente.

## Relación con los principios SOLID

* **Single Responsibility Principle (SRP)**: El patrón *Memento* separa claramente las responsabilidades involucradas en la gestión del estado. El **originador** se centra en su lógica de negocio y en definir cómo capturar y restaurar su estado, el **memento** encapsula una instantánea del estado, y el **cuidador (caretaker)** se encarga exclusivamente de gestionar el historial de estados.
* **Open/Closed Principle (OCP)**: El patrón permite **extender la forma en que se gestionan los estados** (por ejemplo, distintos tipos de historiales, políticas de almacenamiento o persistencia) sin modificar la implementación del originador. La extensibilidad se produce principalmente en la gestión de los mementos, no en su estructura interna.
* **Interface Segregation Principle (ISP)**: El memento expone una **interfaz mínima o incluso opaca**, evitando que otros componentes dependan de operaciones o detalles internos del estado. De este modo, solo el originador conoce y utiliza el contenido real del memento.
* **Liskov Substitution Principle (LSP) y Dependency Inversion Principle (DIP)**: Estos principios **no son el foco principal** del patrón *Memento*. No obstante, pueden aplicarse de forma complementaria si se definen interfaces comunes para originadores o cuidadores. En ese caso, distintas implementaciones pueden sustituirse y el código cliente puede depender de abstracciones, aunque esto no es un requisito inherente al patrón.
* **Dependency Inversion Principle (DIP)**: El código cliente depende de **abstracciones conceptuales** (originador y cuidador) y no del detalle concreto del estado almacenado. El estado queda completamente encapsulado dentro del memento.

## Ejemplos concretos

* **Sistemas de edición**: editores de texto, imágenes o diagramas que requieren operaciones *undo/redo*.
* **Simulaciones y videojuegos**: guardar estados intermedios para permitir retrocesos o puntos de control.
* **Máquinas de estados**: registrar configuraciones previas para volver atrás ante situaciones no deseadas.
* **Procesadores de formularios**: usuarios que navegan entre pasos de un asistente y pueden regresar sin perder datos.
* **Aplicaciones financieras**: restaurar configuraciones de carteras, filtros o indicadores a un estado previo.
* **Sistemas de configuración**: capturar y revertir cambios complejos sobre parámetros de un sistema.
* **Intérpretes o REPLs**: devolver el entorno a un estado previo tras evaluar comandos que fallan.
* **Gestores de documentos**: mantener versiones internas sin necesidad de persistencia inmediata en disco.
* **Herramientas de depuración**: recrear el estado de un componente para analizar fallos específicos.
* **Interfaces interactivas**: permitir que el usuario pruebe cambios (tema, layout, opciones) y los revierta fácilmente.

