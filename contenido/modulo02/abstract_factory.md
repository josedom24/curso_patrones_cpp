# Factory Method (Método fábrica)

## Introducción y propósito del patrón

El patrón **Factory Method** es un patrón de diseño creacional que tiene como objetivo definir una **interfaz para la creación de objetos**, delegando en las **subclases** la decisión de qué clase concreta instanciar. A pesar de que el objeto sigue creándose mediante una operación de construcción (`new`), el patrón encapsula esa creación dentro de un método especial llamado **método fábrica**.

Este patrón permite al código cliente **trabajar con objetos a través de su interfaz común**, sin acoplarse directamente a sus clases concretas, facilitando la extensibilidad y el mantenimiento del software.

## Problema que resuelve

En aplicaciones complejas, a menudo es necesario crear objetos que comparten una interfaz común, pero cuyas **implementaciones concretas pueden variar** según el contexto, configuración o plataforma.

Un caso típico ocurre cuando se empieza con una única clase concreta, y más adelante se desea **incorporar nuevas variantes de un objeto** (por ejemplo, distintos tipos de transporte, botones gráficos, o conexiones a diferentes bases de datos). Si el código cliente está fuertemente acoplado a las clases concretas mediante instanciaciones directas (`new`), **modificar o extender el comportamiento implica alterar el código existente**, violando principios como el de *abierto/cerrado*.

Además, mantener múltiples ramas condicionales (`if` o `switch`) para decidir qué clase instanciar puede ensuciar el código, hacerlo difícil de mantener y propenso a errores.

## Solución que propone

El patrón Factory Method propone mover la lógica de creación de objetos a una **jerarquía de clases creadoras**, donde:

* La **clase base (creadora)** declara un método fábrica que retorna un objeto de una interfaz común.
* Las **subclases** sobrescriben ese método para **instanciar una clase concreta** del producto deseado.

De esta forma:

* El **código cliente depende únicamente de la interfaz de la clase base**, sin acoplarse a las implementaciones concretas.
* La **extensión de nuevos tipos de objetos** se logra mediante subclases, sin modificar el código existente.
* Se favorece la **reutilización y flexibilidad**.

## Diagrama y estructura conceptual

**Estructura conceptual del patrón Factory Method:**

```
  +------------------------+
  |      Creador           |<-------------------------+
  |------------------------|                          |
  | + factoryMethod()      |                          |
  | + lógicaNegocio()      |                          |
  +------------------------+                          |
            ^                                         |
            |                                         |
  +------------------------+             +--------------------------+
  | CreadorConcretoA       |             |  CreadorConcretoB        |
  |------------------------|             |--------------------------|
  | + factoryMethod()      |             | + factoryMethod()        |
  +------------------------+             +--------------------------+

        |                                          |
        |                                          |
        v                                          v
+------------------+                    +------------------+
| ProductoConcretoA|                    | ProductoConcretoB|
+------------------+                    +------------------+
        ^                                          ^
        |                                          |
    +-------------------- Interfaz Producto --------------------+
    | +operación()                                            |
    +---------------------------------------------------------+
```

**Elementos principales:**

* **Producto (interfaz)**: Define una interfaz común para todos los objetos que puede producir el creador.
* **Productos concretos**: Implementan la interfaz del producto.
* **Creador**: Declara el método fábrica (`factoryMethod`) y contiene la lógica de negocio que depende del producto.
* **Creadores concretos**: Sobrescriben el método fábrica para devolver instancias de productos concretos.

## Relación con los principios SOLID

El patrón Factory Method se alinea con varios principios de diseño orientado a objetos, en particular:

* **Principio de responsabilidad única (SRP)**: Separa la responsabilidad de crear objetos del resto de la lógica de negocio.
* **Principio de abierto/cerrado (OCP)**: Permite agregar nuevos tipos de productos mediante nuevas subclases, sin modificar el código existente.
* **Principio de sustitución de Liskov (LSP)**: Los productos concretos pueden ser utilizados por el cliente a través de su interfaz sin que este conozca su tipo concreto.
* **Principio de inversión de dependencias (DIP)**: El código cliente depende de abstracciones (interfaces) en lugar de clases concretas.

## 6. Ventajas y desventajas

### Ventajas

* **Desacopla el código cliente de las clases concretas**, lo que facilita el mantenimiento y la evolución del sistema.
* **Permite la extensión del sistema** sin modificar el código cliente, simplemente creando nuevas subclases creadoras.
* **Centraliza la creación de objetos** complejos o que requieren lógica de inicialización particular.
* **Fomenta el uso de polimorfismo**, permitiendo cambiar dinámicamente el tipo de producto utilizado.

### Desventajas

* Puede **aumentar la complejidad del diseño**, ya que requiere definir múltiples clases: una jerarquía de productos y otra de creadores.
* En aplicaciones sencillas, su uso puede ser **innecesariamente sofisticado**.
* Si el número de variantes de producto es muy grande, el número de subclases creadoras puede crecer considerablemente, generando cierta **sobrecarga estructural**.

## Aplicaciones reales 

* **Interfaces gráficas multiplataforma**: donde los componentes UI (botones, menús, diálogos) deben adaptarse a distintos entornos (Windows, Linux, Web), pero compartir un comportamiento común.
* **Aplicaciones de logística**: diferentes medios de transporte (camión, barco, avión) con una interfaz común y lógica de envío diferente.
* **Motores de videojuegos**: donde distintos objetos del juego (enemigos, armas, obstáculos) pueden crearse a través de métodos fábrica según el nivel o entorno.
* **Conexiones a bases de datos**: selección dinámica del tipo de conexión (MySQL, PostgreSQL, SQLite) mediante una interfaz común y un método fábrica.
* **Aplicaciones empresariales extensibles**: frameworks que permiten a los usuarios extender el comportamiento mediante la sobrescritura de métodos de creación.
