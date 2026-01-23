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

En **C++ moderno**, estos casos suelen resolverse mejor con otras técnicas, ya que el Singleton introduce **dependencias globales**, dificulta las pruebas y aumenta el acoplamiento entre componentes.

## Cómo se implementa en C++ moderno

Aunque puede implementarse de forma segura usando características modernas del lenguaje, el Singleton se considera hoy **una solución técnicamente válida pero conceptualmente problemática**.

Una implementación típica en C++ moderno se basa en:

* Un **constructor privado** para impedir la creación directa de instancias.
* Un **método estático** que devuelve la única instancia.
* Inicialización controlada, normalmente mediante una **variable estática local**, cuya construcción es segura desde C++11.

Sin embargo, este enfoque:

* Actúa como una **variable global encubierta**.
* Introduce dependencias ocultas difíciles de rastrear.
* Complica la sustitución de la instancia en pruebas.
* Hace menos explícito el flujo de creación y uso de objetos.

Por este motivo, en C++ moderno se recomienda **evitar Singleton** y preferir **inyección de dependencias**, utilizando referencias, punteros inteligentes e interfaces para expresar de forma clara quién crea cada objeto y cómo se comparte.


## Ejemplos concretos

* **Gestores de configuración**: Un único objeto para cargar y exponer ajustes globales de la aplicación.
* **Sistemas de logging**: Un logger central que unifica la salida de mensajes, evitando inconsistencias.
* **Motores de juegos**: Un único gestor de recursos (texturas, sonidos, shaders).
* **Conexión o pool de conexiones** a bases de datos: La instancia controla la gestión común de recursos.
* **Planificadores o gestores de tareas** en sistemas concurrentes.
* **Controladores de acceso a hardware** cuando solo debe existir un punto de entrada (sensores, GPU, dispositivos especializados).
* **Registro global de eventos** o de estadísticas de ejecución.
* **Sistemas de configuración de frameworks**: Modalidad, rutas de archivos, preferencias globales.

