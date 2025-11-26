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

## Cómo lo soluciona C++ moderno

En C++ moderno, el patrón Singleton se considera un **antipatrón**, no porque funcione mal técnicamente, sino porque **crea más problemas de los que resuelve** cuando el software crece. Los motivos se pueden entender con ideas muy simples:

* **Crea una especie de “variable global disfrazada”**.
  El objeto único puede ser leído y usado desde cualquier parte del programa. Esto parece cómodo, pero hace que sea muy difícil saber **quién lo modifica** y **cuándo**, produciendo comportamientos inesperados.

* **Hace que el código dependa demasiado de un componente concreto**.
  Si muchas clases piden directamente “el Singleton”, entonces **todas ellas quedan atadas** a esa implementación específica, en vez de a una idea abstracta (una interfaz). Esa dependencia rígida dificulta mejorar o sustituir ese componente más adelante.

* **Complica muchísimo las pruebas**.
  En las pruebas queremos usar versiones simplificadas o falsas (“mocks”) de los componentes. Pero si el código usa un Singleton, no es posible **cambiarlo por uno de prueba**, porque el programa siempre acude a la misma instancia global.

* **Hace más difícil entender el flujo del programa**.
  Un Singleton puede inicializarse en momentos inesperados (por ejemplo, la primera vez que se usa). Esto introduce un orden oculto de inicialización que puede provocar errores difíciles de encontrar.

En resumen: aunque la idea de “tener un único objeto accesible desde todas partes” parece sencilla, **acaba generando programas difíciles de entender, mantener y probar**.

### Alternativa recomendada: Inyección de dependencias

La forma moderna de resolver estos problemas en C++ consiste en **pasar al objeto exactamente lo que necesita**, en lugar de buscarlo él mismo en un punto global.

Esto se llama **inyección de dependencias** y permite que el programa sea mucho más claro:

* El código que necesita un servicio lo recibe “desde fuera”, de forma explícita.
* Se puede sustituir fácilmente por otra implementación (por ejemplo, en pruebas).
* Se entiende claramente quién crea cada objeto y cuánto tiempo vive.
* El diseño se vuelve modular porque las clases ya no dependen de detalles concretos, sino de **interfaces**.

En C++ moderno, este estilo se apoya en:

* **Referencias** y **punteros inteligentes** (`std::unique_ptr`, `std::shared_ptr`) para controlar bien la propiedad de los objetos.
* **Interfaces basadas en clases abstractas**, que permiten cambiar una implementación por otra sin tocar el código que la usa.
* **Inicialización clara y explícita** desde el exterior (por ejemplo, desde `main` o desde un módulo de configuración).

El resultado es un programa más limpio, más fácil de extender, más fácil de probar y sin dependencias ocultas.


## Ejemplos concretos

* **Gestores de configuración**: Un único objeto para cargar y exponer ajustes globales de la aplicación.
* **Sistemas de logging**: Un logger central que unifica la salida de mensajes, evitando inconsistencias.
* **Motores de juegos**: Un único gestor de recursos (texturas, sonidos, shaders).
* **Conexión o pool de conexiones** a bases de datos: La instancia controla la gestión común de recursos.
* **Planificadores o gestores de tareas** en sistemas concurrentes.
* **Controladores de acceso a hardware** cuando solo debe existir un punto de entrada (sensores, GPU, dispositivos especializados).
* **Registro global de eventos** o de estadísticas de ejecución.
* **Sistemas de configuración de frameworks**: Modalidad, rutas de archivos, preferencias globales.

