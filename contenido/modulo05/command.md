# Patrón Command

## Definición

El **Command** es un patrón de diseño de comportamiento que encapsula una petición u operación dentro de un objeto independiente, llamado *comando*. Este objeto contiene toda la información necesaria para ejecutar la acción: el receptor, los parámetros y la lógica asociada.
Su propósito es **desacoplar al emisor de una petición** (por ejemplo, un botón o un menú) del código que ejecuta realmente la operación.

## Problemas que intenta solucionar

El patrón Command aborda especialmente estas situaciones:

* Se quiere **desacoplar** el objeto que invoca una acción del objeto que la realiza.
* Existe la necesidad de **parametrizar acciones** en tiempo de ejecución, tratándolas como objetos de primera clase.
* Se requiere **deshacer o rehacer** operaciones, lo que exige registrar acciones ejecutadas.
* Se quiere **encolar, programar o registrar** peticiones para su ejecución diferida.
* Se necesita unificar el tratamiento de distintas operaciones bajo una **interfaz común**, evitando estructuras rígidas basadas en `if`/`switch`.
* Se desea permitir que nuevas operaciones puedan añadirse sin modificar el código existente, favoreciendo el cumplimiento del principio *Open/Closed*.

## Cómo lo soluciona C++ moderno

En C++ moderno, los problemas que aborda el patrón Command (desacoplar una acción del invocador, ejecutar comportamientos diferidos, almacenar operaciones, implementar undo/redo…) se resuelven de manera natural mediante **inyección de comportamiento**.
El comportamiento deseado se representa mediante:

* **lambdas** que capturan los datos necesarios,
* **`std::function<void()>`** como interfaz común para almacenar y ejecutar comandos,
* **contenedores estándar** como colas, vectores o pilas para gestionar la secuencia de operaciones.

Con este enfoque moderno:

* Las acciones se encapsulan fácilmente en lambdas, sin necesidad de clases de comando.
* El invocador solo mantiene funciones, no tipos concretos.
* La ejecución diferida es trivial: basta con almacenar la función para invocarla más tarde.
* Es sencillo implementar *undo/redo*: se guardan funciones que deshacen las operaciones.
* No se requiere herencia ni jerarquías complejas; la composición sustituye a la estructura clásica.
* Cualquier acción que pueda expresarse como invocable se convierte automáticamente en un "comando" moderno.


## Ejemplos concretos

* **Sistemas de interfaz gráfica**: Asociar distintos comandos a botones, menús o atajos de teclado sin acoplar la UI a la lógica de negocio.
* **Controladores remotos (IoT o domótica)**: Cada botón del mando se asocia a un comando distinto (encender luz, abrir puerta, ajustar temperatura).
* **Editores de texto o imagen**: Implementación de operaciones con *undo/redo*, donde cada acción del usuario se registra como un comando.
* **Motores de juegos**: Gestionar acciones del jugador (saltar, disparar, abrir inventario) mediante comandos reutilizables y parametrizables.
* **Sistemas de colas de tareas**: Encolar comandos para ejecución diferida, asincrónica o distribuida.
* **Automatización de procesos**: Registrar secuencias de comandos para crear macros o flujos repetibles.
* **Servidores o middleware**: Encapsular peticiones recibidas para que puedan ser procesadas por distintos manejadores.
* **Frameworks de pruebas**: Representar casos o pasos de prueba como comandos ejecutables y re-ejecutables.
* **Procesadores de órdenes o transacciones**: Encapsular acciones como “crear pedido”, “cancelar pedido”, “aplicar descuento” para permitir control transaccional.
* **Robótica**: Enviar comandos discretos a un robot (mover, girar, sujetar) y registrar su historial de ejecución.
