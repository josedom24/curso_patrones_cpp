# Patrón Memento

## Definición

El **Memento** es un patrón de diseño de comportamiento que permite capturar y almacenar el **estado interno** de un objeto en un instante dado, para poder **restaurarlo posteriormente** sin violar el principio de **encapsulamiento**. El patrón separa claramente los roles de originador (objeto cuyo estado se guarda), memento (objeto que almacena el estado) y cuidador (*caretaker*, encargado de gestionar las copias).

## Problemas que intenta solucionar

El patrón aborda principalmente estas situaciones:

* Necesidad de **deshacer cambios** en un objeto, volviendo a un estado anterior, como en un *undo/redo*.
* Se requiere **guardar estados complejos** de un objeto sin exponer detalles internos ni romper el encapsulamiento.
* El proceso de guardar y restaurar estado no debe estar mezclado con la lógica principal del objeto.
* Mantener el estado mediante copias manuales o serialización puede introducir **acoplamiento indeseado** o errores.
* Se necesitan **múltiples puntos de restauración** sin que el cliente conozca la estructura interna del objeto.

## Cómo lo soluciona

El patrón Memento aporta estas soluciones:

* Define un objeto **Memento** que almacena el estado interno del originador de forma segura y encapsulada.
* Introduce un **Originador** que crea mementos y sabe restaurar su propio estado a partir de ellos.
* El **Caretaker** gestiona los mementos sin acceder a su contenido, manteniendo la separación de responsabilidades.
* Permite mantener un historial de estados (por ejemplo, una pila de *undo*) sin romper la encapsulación del objeto original.
* Facilita la extensibilidad al añadir nuevos elementos internos al estado sin afectar al código externo.

## Relación con los principios SOLID

* **Single Responsibility Principle (SRP)**: El patrón *Memento* separa la responsabilidad de **gestionar el estado interno** del objeto de la responsabilidad de **almacenarlo y restaurarlo**. El originador gestiona su lógica, el memento encapsula el estado y el cuidador administra el historial.
* **Open/Closed Principle (OCP)**: Es posible extender la forma en que se almacenan o gestionan los mementos (por ejemplo, nuevos cuidadores o historiales) sin modificar la implementación del originador ni del memento.
* **Liskov Substitution Principle (LSP)**: Distintas implementaciones compatibles de originadores o cuidadores pueden sustituirse sin alterar el comportamiento esperado, siempre que respeten el contrato de creación y restauración del estado.
* **Interface Segregation Principle (ISP)**: El memento no expone una interfaz pública rica; solo ofrece lo estrictamente necesario para preservar el estado, evitando que otros componentes dependan de operaciones innecesarias o del contenido interno del estado.
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

