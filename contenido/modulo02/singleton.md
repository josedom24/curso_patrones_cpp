# Patrón Singleton

## Definición

El **Singleton** es un patrón de diseño creacional cuyo objetivo es **garantizar que una clase tenga una única instancia en todo el programa** y, además, **proporcionar un punto de acceso global y controlado** a dicha instancia.

La clase controla por completo su ciclo de vida: impide la creación arbitraria de objetos, asegura la existencia de una única instancia y coordina el acceso seguro a ella.

## Problemas que intenta solucionar

El patrón Singleton surge como respuesta a situaciones en las que:

* Es necesario **garantizar que un recurso exista una sola vez**, por ejemplo, un manejador de configuración global o un registro de logs.
* Se requiere un **punto de acceso único y centralizado** para un servicio o recurso compartido.
* La creación repetida de instancias sería costosa, insegura o conceptualmente incorrecta.
* Se quiere **evitar la dispersión de instancias** que podrían descoordinar el estado global.
* Se necesita que la instancia se **cree bajo demanda** (lazy initialization) o al inicio del programa (eager initialization).

## Cómo lo soluciona

El Singleton ofrece un conjunto de mecanismos precisos:

* **Constructor privado o protegido** para impedir la creación directa de objetos desde el exterior.
* Una **función estática de acceso** (generalmente `instance()`) que devuelve la única instancia existente.
* **Almacenamiento estático interno** para conservar la instancia.
* Opcionalmente, garantiza la **creación perezosa** y la **seguridad en entornos multihilo**.
* Aísla la gestión de la instancia de manera que el resto del código no necesita saber si se inicializa al principio o la primera vez que se pide.

## Ejemplos concretos

* **Gestores de configuración**: Un único objeto para cargar y exponer ajustes globales de la aplicación.
* **Sistemas de logging**: Un logger central que unifica la salida de mensajes, evitando inconsistencias.
* **Motores de juegos**: Un único gestor de recursos (texturas, sonidos, shaders).
* **Conexión o pool de conexiones** a bases de datos: La instancia controla la gestión común de recursos.
* **Planificadores o gestores de tareas** en sistemas concurrentes.
* **Controladores de acceso a hardware** cuando solo debe existir un punto de entrada (sensores, GPU, dispositivos especializados).
* **Registro global de eventos** o de estadísticas de ejecución.
* **Sistemas de configuración de frameworks**: Modalidad, rutas de archivos, preferencias globales.

