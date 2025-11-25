# Patrón Observer

## Definición

El **Observer** es un patrón de diseño de comportamiento que establece una relación de **dependencia uno-a-muchos** entre objetos, de modo que cuando un objeto (“sujeto”) cambia de estado, **notifica automáticamente** a todos sus “observadores” asociados.
Su objetivo es permitir que múltiples componentes reaccionen a cambios sin acoplarse directamente entre sí.

## Problemas que intenta solucionar

El patrón Observer aborda principalmente estas situaciones:

* **Acoplamiento fuerte entre componentes** que necesitan reaccionar a cambios en otro objeto.
* Necesidad de **sincronizar el estado de múltiples objetos** ante un cambio ocurrido en un único punto del sistema.
* Código cliente lleno de llamadas explícitas para actualizar otros componentes, lo que dificulta la extensibilidad y el mantenimiento.
* Requisitos de **actualización automática** cuando se modifican datos compartidos.
* Situaciones donde el número de componentes interesados en un cambio **puede variar dinámicamente** (añadir o eliminar observadores en tiempo de ejecución).

## Cómo lo soluciona

El patrón Observer aporta estas soluciones:

* Define una **interfaz común de observador** que declara el método de actualización.
* Introduce un **sujeto** que mantiene una lista de observadores y proporciona métodos para registrarlos o eliminarlos.
* Cuando el estado del sujeto cambia, este **notifica automáticamente** a todos los observadores sin conocer sus clases concretas.
* Permite añadir nuevos observadores sin modificar el código del sujeto, reforzando el principio *Open/Closed*.
* Reduce el acoplamiento: el sujeto solo depende de la **abstracción** del observador, no de implementaciones particulares.
* Facilita la **reactividad** dentro del sistema: cada observador puede reaccionar de forma distinta al mismo evento.

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


