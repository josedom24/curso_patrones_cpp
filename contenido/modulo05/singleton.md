# Patrón Singleton

## Definición

El **Singleton** es un patrón de diseño creacional cuyo propósito es **garantizar que una clase tenga una única instancia en todo el programa** y proporcionar un **punto de acceso global** a dicha instancia, siendo la propia clase la responsable de controlar su creación y ciclo de vida.

## Objetivos

* Asegurar la existencia de **una única instancia** de una clase.
* Proporcionar un **acceso centralizado** a un recurso o servicio compartido.
* Evitar la creación descoordinada de múltiples instancias.
* Mantener un **estado global coherente** dentro del sistema.

## Cuándo usarlo

El Singleton puede parecer apropiado cuando:

* Se necesita representar un **recurso único** en todo el programa.
* El acceso al recurso debe estar **centralizado y controlado**.
* Múltiples instancias serían conceptualmente incorrectas.

## Cómo se implementa en C++ moderno

Aunque puede implementarse de forma segura usando características modernas del lenguaje, el Singleton se considera hoy **una solución técnicamente válida pero conceptualmente problemática**.

Una implementación típica en C++ moderno se basa en:

* Un **constructor privado** para impedir la creación directa de instancias.
* Un **método estático** que devuelve la única instancia.
* Inicialización controlada, normalmente mediante una **variable estática local**, cuya construcción es segura desde C++11.

Sin embargo, este enfoque:

* **Actúa como una variable global encubierta** porque es accesible desde cualquier punto del programa sin declararlo, con estado persistente durante toda la ejecución, pero disfrazado de clase.
* **Introduce dependencias ocultas difíciles de rastrear** porque al no aparecer en ninguna firma, solo se descubren leyendo el interior de cada método, fichero por fichero.
* **Complica la sustitución de la instancia en pruebas** porque su constructor privado impide crear instancias alternativas, forzando siempre a usar la instancia real.
* **Hace menos explícito el flujo de creación y uso de objetos** porque el objeto se crea automáticamente en el primer acceso y se usa desde cualquier sitio, sin un punto central que muestre su ciclo de vida.



Por este motivo, en C++ moderno se recomienda **evitar la implementación clásica de Singleton** y preferir **inyección de dependencias**.

* Una **dependencia** es cualquier objeto externo que una clase necesita para funcionar. 
* La **inyección de dependencias** consiste en que la clase no crea sus propias dependencias, sino que las **recibe desde fuera** a través del constructor, apoyándose en referencias, punteros inteligentes e interfaces.

Con este enfoque se consiguen los mismos objetivos que el Singleton (una única instancia, acceso centralizado y estado coherente), pero con las siguientes ventajas:

* **Elimina el estado global encubierto** porque el objeto se crea en un punto concreto y controlado del programa, y su alcance queda limitado a quien lo recibe explícitamente.
* **Hace las dependencias visibles y rastreables** porque aparecen en la firma del constructor, permitiendo saber de qué depende una clase sin leer su implementación.
* **Facilita la sustitución en pruebas** porque al recibir la dependencia desde fuera, basta con pasar una versión falsa en el contexto del test sin modificar nada de la clase.
* **Hace explícito el flujo de creación y uso** porque en un único punto central se crean todos los objetos y se pasan a quien los necesita, dejando su ciclo de vida visible de un vistazo.


## Ejemplos concretos

* **Gestores de configuración**: Un único objeto para cargar y exponer ajustes globales de la aplicación.
* **Sistemas de logging**: Un logger central que unifica la salida de mensajes, evitando inconsistencias.
* **Motores de juegos**: Un único gestor de recursos (texturas, sonidos, shaders).
* **Conexión o pool de conexiones** a bases de datos: La instancia controla la gestión común de recursos.
* **Planificadores o gestores de tareas** en sistemas concurrentes.
* **Controladores de acceso a hardware** cuando solo debe existir un punto de entrada (sensores, GPU, dispositivos especializados).
* **Registro global de eventos** o de estadísticas de ejecución.
* **Sistemas de configuración de frameworks**: Modalidad, rutas de archivos, preferencias globales.

