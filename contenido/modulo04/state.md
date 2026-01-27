# Patrón State

## Definición

El **State** es un patrón de diseño de comportamiento que permite que un objeto **modifique su comportamiento en tiempo de ejecución** según su estado interno. Desde fuera, parecerá que el objeto cambia de clase. Su propósito es encapsular los diferentes estados posibles en **clases separadas**, delegando en ellas la lógica asociada a cada estado.

## Objetivos del patrón

* **Permitir que un objeto varíe su comportamiento en función de su estado interno**, sin recurrir a grandes estructuras condicionales ni a comprobaciones explícitas del estado en el código cliente.
* **Encapsular la lógica asociada a cada estado en clases independientes**, mejorando la legibilidad, mantenibilidad y cohesión del diseño.
* **Centralizar y controlar las transiciones entre estados**, evitando que el código cliente tenga que conocer o gestionar los cambios de estado del objeto.
* **Facilitar la extensión del sistema mediante la incorporación de nuevos estados**, respetando el principio *Open/Closed* y minimizando el impacto sobre el código existente.

## Problemas que intenta solucionar

El patrón aborda principalmente estas situaciones:

* Un objeto cuyo **comportamiento depende de su estado interno**, lo que provoca que una única clase acumule múltiples variantes de comportamiento difíciles de comprender y mantener.
* La presencia de **estructuras condicionales repetitivas** (`if` / `switch`) para comprobar el estado antes de cada operación, generando código rígido, poco legible y propenso a errores.
* La necesidad de **gestionar transiciones entre estados de forma explícita y segura**, evitando que el código cliente tenga que conocer los estados posibles o decidir cuándo y cómo cambiar entre ellos.
* La dificultad para **extender el comportamiento del objeto con nuevos estados** sin modificar código existente, lo que puede derivar en violaciones del principio *Open/Closed* y en un aumento del acoplamiento.

## Cómo lo soluciona

El patrón *State* aporta las siguientes soluciones:

* **Encapsula cada estado en una clase independiente**, que implementa una interfaz común y concentra exclusivamente el comportamiento asociado a ese estado concreto.
* El objeto principal (*contexto*) **mantiene una referencia al estado actual y delega en él su comportamiento**, eliminando la necesidad de condicionales basados en el estado interno.
* **Las transiciones entre estados se definen de forma explícita y localizada**, normalmente dentro de las propias clases de estado, manteniendo el control del ciclo de vida del objeto.
* **Facilita la extensibilidad del sistema**, ya que añadir un nuevo estado implica crear una nueva clase sin modificar el contexto ni los estados existentes, mejorando la mantenibilidad y el cumplimiento del principio *Open/Closed*.

## Relación con los principios SOLID

* **Single Responsibility Principle (SRP)**: El patrón *State* separa la responsabilidad de **gestionar el comportamiento dependiente del estado** en clases de estado independientes. El contexto se limita a delegar, y cada estado se encarga exclusivamente de su propia lógica.
* **Open/Closed Principle (OCP)**: Nuevos estados pueden añadirse creando nuevas clases sin modificar el contexto ni los estados existentes. El sistema se extiende incorporando nuevos comportamientos sin alterar código ya probado.
* **Liskov Substitution Principle (LSP)**: Cualquier estado concreto puede sustituir a otro siempre que respete la interfaz del estado. El contexto puede cambiar de estado dinámicamente sin alterar su comportamiento esperado.
* **Interface Segregation Principle (ISP)**: La interfaz del estado define únicamente las operaciones relevantes para el comportamiento dependiente del estado, evitando que los estados implementen métodos innecesarios o ajenos a su responsabilidad.
* **Dependency Inversion Principle (DIP)**: El contexto depende de la **abstracción del estado**, no de estados concretos. Los estados concretos implementan dicha abstracción, reduciendo el acoplamiento entre contexto y comportamientos específicos.


## Ejemplos concretos

* **Máquinas expendedoras**: Estados como "esperando moneda", "producto seleccionado", "sin stock", "entregando".
* **Reproductores multimedia**: Estados como "reproduciendo", "pausado", "detenido".
* **Edición de documentos**: Comportamientos distintos según si el documento está en modo "lectura", "edición" o "solo lectura".
* **Conexiones de red**: Estados "desconectado", "conectando", "conectado", "fallo de conexión".
* **Gestión de pedidos** en comercio electrónico: "pendiente", "preparación", "enviado", "entregado", "cancelado".
* **Videojuegos**: Estados de un personaje (parado, caminando, atacando, herido, muerto) o estados del propio juego (menú, jugando, pausa, game over).
* **Sistemas de autenticación**: Estados "no autenticado", "autenticado", "token caducado".
* **Procesos administrativos** o workflows: Estados que representan fases de un trámite, cada uno con reglas distintas.
* **Sistemas de impresión**: Estados "lista", "imprimiendo", "sin papel", "atascada", "offline".
* **Automatismos industriales**: Estados de máquinas o robots (inicialización, activo, error, apagado), con comportamientos específicos.
