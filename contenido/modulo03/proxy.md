# Patrón Proxy

## Definición

El **Proxy** es un patrón de diseño estructural que proporciona un **sustituto** o **representante** de otro objeto para controlar su acceso.
El proxy implementa la misma interfaz que el objeto real (llamado *sujeto real*), pero añade una capa intermedia que puede realizar tareas adicionales, como control de acceso, inicialización diferida, registro, validación o comunicación remota, antes o después de delegar la operación en el objeto real.

## Problemas que intenta solucionar

El patrón Proxy resulta útil en las siguientes situaciones:

* El objeto real es **costoso de crear o cargar**, y se desea una inicialización diferida (*lazy loading*).
* Se necesita **controlar el acceso** a un recurso sensible, restringiendo o validando las operaciones del cliente.
* El objeto real se encuentra **en otra máquina o proceso** y se requiere una representación local para comunicarse con él sin exponer la complejidad (proxy remoto).
* Es necesario **añadir responsabilidades adicionales** (por ejemplo, logs, métricas, conteo de referencias) sin modificar la clase real y sin que el cliente lo note.
* Se quiere **proteger un recurso** de modificaciones no autorizadas (por ejemplo, un proxy que solo permita lectura).
* Se deben gestionar recursos que requieren **carga bajo demanda** o liberación controlada (imágenes, conexiones, archivos, grandes estructuras de datos).
* En bibliotecas o frameworks, se busca **interceptar llamadas** sin que el cliente conozca los detalles internos de la implementación.

## Cómo lo soluciona

El Proxy aporta estas soluciones:

* Define un **objeto intermediario** que implementa la misma interfaz que el objeto real.
* El cliente interactúa **solo con el proxy**, sin saber si la llamada llega directamente al objeto real o si está siendo interceptada.
* Permite realizar tareas adicionales como:

  * **Creación diferida** del objeto real (Virtual Proxy).
  * **Control de acceso** y validaciones (Protection Proxy).
  * **Comunicación remota transparente** (Remote Proxy).
  * **Gestión de caché** o almacenamiento temporal (Cache Proxy).
  * **Registro o auditoría** sin modificar el sujeto real (Logging Proxy).
* Aísla la complejidad del objeto real, permitiendo mantener un **bajo acoplamiento** y cumplir el principio *Open/Closed*.
* Facilita que el objeto real cambie sin afectar al cliente, ya que el proxy actúa como punto estable de acceso.

## Ejemplos concretos

* **Carga diferida de imágenes** en aplicaciones gráficas: mostrar un “placeholder” mientras la imagen real se carga bajo demanda.
* **Proxy virtual para objetos pesados**: construir el objeto real solo cuando el cliente lo necesita.
* **Control de acceso** a un recurso protegido: un proxy que verifica permisos antes de delegar la operación al objeto real.
* **Proxy remoto**: representar un objeto que realmente vive en un servidor remoto, manejando la comunicación de red de forma transparente.
* **Conexión a bases de datos**: abrir la conexión solo cuando se realiza la primera operación, no al crear el objeto.
* **Sistemas de archivos**: un proxy que verifica si un usuario puede leer o escribir un archivo antes de acceder al recurso real.
* **Sistemas de cacheo**: un proxy que guarda resultados de operaciones costosas y devuelve valores en caché si es posible.
* **Auditorías y logs transparentes**: un proxy que registra llamadas, tiempos de ejecución o patrones de acceso sin alterar el código del objeto real.
* **Interfaces gráficas**: un proxy para componentes que representan recursos remotos o pesados, permitiendo interacción fluida incluso cuando el recurso real aún no está disponible.
* **Frameworks de comunicación**: proxies que encapsulan protocolos complejos, proporcionando un punto de acceso simple y uniforme.

