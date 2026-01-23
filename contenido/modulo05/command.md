# Patrón Command

## Definición

El **Command** es un patrón de diseño de comportamiento que encapsula una **operación o petición como un objeto independiente**, permitiendo que una acción se trate como una entidad separada del objeto que la invoca. Su objetivo principal es **desacoplar al emisor de la acción del código que la ejecuta**, facilitando la parametrización, el almacenamiento y la ejecución diferida de operaciones.

## Objetivos

* **Desacoplar el objeto que invoca una acción del objeto que la ejecuta**, evitando dependencias directas entre ambos.
* **Encapsular acciones como entidades intercambiables**, permitiendo tratarlas de forma uniforme y parametrizable.
* **Permitir la ejecución diferida y el almacenamiento de operaciones**, facilitando su encolado, registro o programación.
* **Soportar funcionalidades como undo/redo**, manteniendo un historial de acciones ejecutadas sin acoplar la lógica al invocador.

## Cuándo usarlo

El patrón Command es adecuado cuando:

* Un objeto debe invocar acciones **sin conocer cómo se implementan**.
* Las operaciones deben **almacenarse, programarse o deshacerse**.
* Se quiere parametrizar objetos con **acciones intercambiables**.
* Es necesario desacoplar interfaces de usuario (botones, menús, eventos) de la lógica de negocio.

En muchos casos modernos, el patrón no se aplica de forma explícita, sino mediante **funciones y lambdas**.

## Cómo se implementa en C++ moderno

En C++ moderno, Command se implementa de forma natural mediante **inyección de comportamiento**, sin necesidad de jerarquías de clases.

Las técnicas habituales son:

* **Lambdas**, que encapsulan la acción y capturan el estado necesario.
* **`std::function<void()>`** como tipo común para almacenar y ejecutar comandos.
* **Contenedores estándar** (`std::vector`, `std::queue`, `std::stack`) para gestionar secuencias de acciones.

Con este enfoque:

* El invocador almacena y ejecuta funciones, no clases concretas.
* La ejecución diferida se logra almacenando el callable.
* *Undo/redo* se implementa guardando funciones inversas.
* Se elimina la herencia en favor de composición.
* Cualquier acción invocable se convierte en un **comando moderno**.

Este estilo refleja mejor el uso real de Command en C++ moderno: **simple, flexible y expresivo**, apoyado directamente por el lenguaje.

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
