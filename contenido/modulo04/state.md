# Patrón State

## Definición

El **State** es un patrón de diseño de comportamiento que permite que un objeto **modifique su comportamiento en tiempo de ejecución** según su estado interno. Desde fuera, parecerá que el objeto cambia de clase. Su propósito es encapsular los diferentes estados posibles en **clases separadas**, delegando en ellas la lógica asociada a cada estado.

## Problemas que intenta solucionar

El patrón aborda principalmente estas situaciones:

* Un objeto presenta **comportamientos diferentes** dependiendo de su estado interno (por ejemplo, “inicial”, “procesando”, “bloqueado”, “finalizado”), y mezclar toda la lógica en la misma clase provoca código complejo y difícil de mantener.
* Se ve la necesidad de múltiples condicionales (`if`/`switch`) que verifican el estado una y otra vez para decidir cómo actuar.
* Se requiere una **transición clara y controlada** entre estados, evitando que el código cliente tenga que gestionarlas manualmente.
* El comportamiento asociado a cada estado se vuelve suficientemente complejo como para justificar su separación en clases propias.
* Se desea **evitar violar el principio Open/Closed**, permitiendo añadir nuevos estados sin modificar la lógica del objeto principal.

## Cómo lo soluciona

El patrón State aporta estas soluciones:

* Encapsula cada estado en una **clase concreta** que implementa una interfaz común (p. ej., `Estado`).
* El objeto principal (el *contexto*) mantiene una **referencia al estado actual**, delegando en él las operaciones relevantes.
* Los estados pueden **cambiar el estado del contexto**, controlando así las transiciones de manera explícita y local.
* Se eliminan los condicionales repetitivos: el comportamiento varía automáticamente según el objeto estado activo.
* Mejora la mantenibilidad y extensibilidad: para añadir un nuevo estado basta con crear una nueva clase, sin modificar el resto del sistema.
* Refuerza el principio *Single Responsibility*: cada clase gestiona solo la lógica de un estado específico.

## Relación con los principios SOLID

* **Single Responsibility Principle (SRP)**: El patrón *State* separa la responsabilidad de **gestionar el comportamiento dependiente del estado** en clases de estado independientes. El contexto se limita a delegar, y cada estado se encarga exclusivamente de su propia lógica.
* **Open/Closed Principle (OCP)**: Nuevos estados pueden añadirse creando nuevas clases sin modificar el contexto ni los estados existentes. El sistema se extiende incorporando nuevos comportamientos sin alterar código ya probado.
* **Dependency Inversion Principle (DIP)**: El contexto depende de la **abstracción del estado**, no de estados concretos. Los estados concretos implementan dicha abstracción, reduciendo el acoplamiento entre contexto y comportamientos específicos.
* **Liskov Substitution Principle (LSP)**: Cualquier estado concreto puede sustituir a otro siempre que respete la interfaz del estado. El contexto puede cambiar de estado dinámicamente sin alterar su comportamiento esperado.
* **Interface Segregation Principle (ISP)**: La interfaz del estado define únicamente las operaciones relevantes para el comportamiento dependiente del estado, evitando que los estados implementen métodos innecesarios o ajenos a su responsabilidad.

## Ejemplos concretos

* **Máquinas expendedoras**: Estados como “esperando moneda”, “producto seleccionado”, “sin stock”, “entregando”.
* **Reproductores multimedia**: Estados como “reproduciendo”, “pausado”, “detenido”.
* **Edición de documentos**: Comportamientos distintos según si el documento está en modo “lectura”, “edición” o “solo lectura”.
* **Conexiones de red**: Estados “desconectado”, “conectando”, “conectado”, “fallo de conexión”.
* **Gestión de pedidos** en comercio electrónico: “pendiente”, “preparación”, “enviado”, “entregado”, “cancelado”.
* **Videojuegos**: Estados de un personaje (parado, caminando, atacando, herido, muerto) o estados del propio juego (menú, jugando, pausa, game over).
* **Sistemas de autenticación**: Estados “no autenticado”, “autenticado”, “token caducado”.
* **Procesos administrativos** o workflows: Estados que representan fases de un trámite, cada uno con reglas distintas.
* **Sistemas de impresión**: Estados “lista”, “imprimiendo”, “sin papel”, “atascada”, “offline”.
* **Automatismos industriales**: Estados de máquinas o robots (inicialización, activo, error, apagado), con comportamientos específicos.
