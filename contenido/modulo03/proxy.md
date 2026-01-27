# Patrón Proxy

## Definición

El **Proxy** es un patrón de diseño estructural que proporciona un **sustituto** o **representante** de otro objeto para controlar su acceso.
El proxy implementa la misma interfaz que el objeto real (llamado *sujeto real*), pero añade una capa intermedia que puede realizar tareas adicionales, como control de acceso, inicialización diferida, registro, validación o comunicación remota, antes o después de delegar la operación en el objeto real.

## Objetivos del patrón

* **Controlar el acceso a un objeto**, interponiendo una capa que permita validar, restringir o autorizar las operaciones antes de delegarlas en el objeto real.
* **Optimizar el uso de recursos**, posibilitando la creación diferida y la gestión bajo demanda de objetos costosos o de acceso limitado.
* **Añadir responsabilidades de forma transparente**, incorporando funcionalidades como registro, monitorización, caché o auditoría sin modificar la implementación del objeto real ni el código cliente.
* **Ocultar la complejidad del acceso al objeto real**, proporcionando al cliente una interfaz estable que abstrae detalles como acceso remoto, protección o inicialización interna.


## Problemas que intenta solucionar

* **Gestión eficiente de recursos costosos**, permitiendo la creación diferida, la carga bajo demanda y el control del ciclo de vida de objetos pesados o limitados.
* **Control y protección del acceso a recursos**, restringiendo operaciones, validando permisos o limitando modificaciones sin exponer estas reglas al cliente.
* **Acceso transparente a objetos remotos o complejos**, ocultando detalles de comunicación, ubicación o infraestructura tras una representación local.
* **Intercepción y ampliación de comportamiento sin modificar el objeto real**, incorporando funcionalidades como registro, métricas, caché o auditoría de forma transparente para el cliente.

## Cómo lo soluciona

* **Introduce un objeto intermediario con la misma interfaz**, de modo que el proxy y el objeto real sean intercambiables para el cliente.
* **Desacopla al cliente del objeto real**, ya que todas las interacciones se realizan a través del proxy sin conocer si existe lógica adicional o acceso indirecto.
* **Centraliza responsabilidades adicionales**, como creación diferida, control de acceso, comunicación remota, caché o registro, sin modificar la clase real.
* **Aísla cambios y complejidad interna**, proporcionando un punto de acceso estable que reduce el acoplamiento y facilita la evolución del objeto real.

## Relación con los principios SOLID

* **Single Responsibility Principle (SRP)**: El patrón *Proxy* contribuye a separar la responsabilidad de **implementar la funcionalidad principal** de la responsabilidad de **gestionar aspectos transversales** como control de acceso, inicialización diferida, registro o monitorización. El objeto real se centra en su lógica de negocio, mientras que el proxy encapsula estas responsabilidades adicionales.
* **Open/Closed Principle (OCP)**: Es posible introducir nuevos tipos de proxy (por ejemplo, proxy virtual, proxy de protección o proxy de registro) sin modificar la clase del objeto real ni el código cliente. El comportamiento adicional se incorpora mediante nuevas clases que respetan la interfaz común.
* **Liskov Substitution Principle (LSP)**: El proxy puede sustituir al objeto real de forma transparente, ya que ambos implementan la misma interfaz y mantienen el contrato esperado. El cliente no necesita distinguir si interactúa con el objeto real o con su proxy.
* **Interface Segregation Principle (ISP)**: El proxy expone la misma interfaz que el objeto real, evitando introducir métodos adicionales relacionados con la gestión interna del acceso. El cliente depende únicamente de las operaciones que realmente necesita.
* **Dependency Inversion Principle (DIP)**: El cliente depende de una **abstracción común** (la interfaz del sujeto), no de implementaciones concretas. Tanto el proxy como el objeto real dependen de esa abstracción, lo que reduce el acoplamiento y facilita la sustitución.

## Ejemplos concretos

* **Carga diferida de imágenes** en aplicaciones gráficas: mostrar un "placeholder" mientras la imagen real se carga bajo demanda.
* **Proxy virtual para objetos pesados**: construir el objeto real solo cuando el cliente lo necesita.
* **Control de acceso** a un recurso protegido: un proxy que verifica permisos antes de delegar la operación al objeto real.
* **Proxy remoto**: representar un objeto que realmente vive en un servidor remoto, manejando la comunicación de red de forma transparente.
* **Conexión a bases de datos**: abrir la conexión solo cuando se realiza la primera operación, no al crear el objeto.
* **Sistemas de archivos**: un proxy que verifica si un usuario puede leer o escribir un archivo antes de acceder al recurso real.
* **Sistemas de cacheo**: un proxy que guarda resultados de operaciones costosas y devuelve valores en caché si es posible.
* **Auditorías y logs transparentes**: un proxy que registra llamadas, tiempos de ejecución o patrones de acceso sin alterar el código del objeto real.
* **Interfaces gráficas**: un proxy para componentes que representan recursos remotos o pesados, permitiendo interacción fluida incluso cuando el recurso real aún no está disponible.
* **Frameworks de comunicación**: proxies que encapsulan protocolos complejos, proporcionando un punto de acceso simple y uniforme.

