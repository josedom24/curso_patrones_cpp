# Patrón Observer

## Definición

El **Observer** es un patrón de diseño de comportamiento que establece una relación de **dependencia uno-a-muchos** entre objetos, de modo que cuando un objeto (“sujeto”) cambia de estado, **notifica automáticamente** a todos sus “observadores” asociados.
Su objetivo es permitir que múltiples componentes reaccionen a cambios sin acoplarse directamente entre sí.

## Objetivos del patrón

* **Desacoplar el sujeto de sus dependientes**, permitiendo que el objeto que cambia de estado no conozca las implementaciones concretas de los componentes que reaccionan a dicho cambio.
* **Notificar automáticamente cambios de estado**, garantizando que todos los observadores registrados se mantengan sincronizados sin necesidad de llamadas explícitas desde el código cliente.
* **Permitir la extensión dinámica del comportamiento**, facilitando la adición o eliminación de observadores en tiempo de ejecución sin modificar la lógica del sujeto.
* **Centralizar y simplificar la gestión de reacciones a eventos**, evitando duplicación de código y mejorando la mantenibilidad y escalabilidad del sistema.

## Problemas que intenta solucionar

El patrón Observer aborda principalmente estas situaciones:

* **Acoplamiento fuerte entre componentes**, cuando varios objetos dependen directamente de otro para reaccionar a sus cambios de estado.
* **Dificultad para sincronizar múltiples objetos**, especialmente cuando un cambio en un único punto del sistema debe reflejarse en varios componentes.
* **Código cliente complejo y poco extensible**, debido a la presencia de llamadas explícitas para actualizar manualmente a otros objetos.
* **Gestión rígida de dependientes**, donde el conjunto de componentes interesados en un cambio no puede variar fácilmente en tiempo de ejecución.

## Cómo lo soluciona

El patrón Observer aporta estas soluciones:

* **Define una interfaz común para los observadores**, de modo que el sujeto solo dependa de una abstracción y no de implementaciones concretas.
* **Centraliza la gestión de observadores en el sujeto**, permitiendo registrarlos y eliminarlos dinámicamente mediante una lista interna.
* **Automatiza la notificación de cambios**, haciendo que el sujeto avise a todos los observadores cuando su estado se modifica, sin intervención del código cliente.
* **Facilita la extensión del sistema sin modificaciones**, permitiendo añadir nuevos observadores y nuevas reacciones a los cambios respetando el principio *Open/Closed*.

## Relación con los principios SOLID

* **Single Responsibility Principle (SRP)**: El patrón *Observer* separa la responsabilidad de **gestionar el estado del sujeto** de la responsabilidad de **reaccionar a sus cambios**. El sujeto se encarga de notificar, y cada observador se encarga de su propia respuesta.
* **Open/Closed Principle (OCP)**: Nuevos observadores pueden añadirse sin modificar la implementación del sujeto. El sistema puede extenderse incorporando nuevas reacciones ante cambios sin alterar el código existente.
* **Liskov Substitution Principle (LSP)**: Cualquier observador concreto puede sustituir a otro siempre que respete la interfaz de observador. El sujeto puede notificar a distintos observadores sin alterar su comportamiento.
* **Interface Segregation Principle (ISP)**: La interfaz del observador es **mínima y específica**, normalmente limitada a un método de notificación, evitando que los observadores dependan de operaciones que no necesitan.
* **Dependency Inversion Principle (DIP)**: El sujeto depende de la **abstracción del observador**, no de sus implementaciones concretas, reduciendo el acoplamiento. Los observadores reaccionan a los cambios sin requerir conocimiento interno del sujeto, lo que favorece una arquitectura más flexible.

## Ejemplos concretos

* **Interfaces gráficas (GUI)**: Actualizar diferentes widgets cuando cambia un modelo de datos (ej. MVC).
* **Sistemas de eventos**: Suscriptores que reciben notificaciones cuando ocurre un evento en un publicador.
* **Modelos de datos compartidos**: Varios componentes visuales sincronizados con un mismo estado (tablas, gráficos, paneles).
* **Notificaciones en aplicaciones móviles**: Múltiples módulos reaccionan cuando cambian las preferencias del usuario.
* **Sensores o dispositivos IoT**: Varios procesos se actualizan automáticamente cuando un sensor registra un nuevo valor.
* **Sistemas de trading o bolsa**: Observadores que reaccionan a cambios en precios, volúmenes o alertas.
* **Motores de juegos**: Entidades que se suscriben a eventos del motor (colisiones, entrada del usuario, scripts).
* **Aplicaciones colaborativas**: Varios clientes sincronizados reaccionan a cambios en documentos compartidos.
* **Sistemas de logging o métricas**: Múltiples registradores reciben notificaciones cuando ocurre un evento relevante.
* **Compiladores o analizadores**: Distintos módulos reaccionan cuando se detectan cambios en el árbol sintáctico o semántico.


