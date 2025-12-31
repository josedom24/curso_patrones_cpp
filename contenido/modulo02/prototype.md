# Patrón Prototype

## Definición

El **Prototype** es un patrón de diseño **creacional** que permite **crear nuevos objetos copiando (clonando) objetos existentes**, llamados *prototipos*, en lugar de construirlos desde cero.

Este patrón se apoya en dos tipos de copia:

* **Copia superficial**: duplica los valores de los miembros, pero **comparte los recursos dinámicos** (punteros, referencias).
* **Copia profunda**: duplica tanto los valores como los **recursos internos**, creando objetos totalmente independientes.

Cada clase decide **cómo debe copiarse** implementando un método de clonación (habitualmente `clone()`), lo que permite crear objetos complejos sin depender de constructores ni conocer detalles internos de su implementación.

## Objetivos del patrón

* **Crear objetos de forma eficiente**, evitando inicializaciones costosas repetidas.
* **Desacoplar al cliente** de las clases concretas que se están creando.
* **Controlar explícitamente el tipo de copia** (superficial o profunda) según las necesidades del objeto.
* **Facilitar la creación de objetos preconfigurados**, reduciendo código duplicado.

## Problemas que intenta solucionar

El uso de Prototype es especialmente útil cuando aparecen estas dificultades:

* **Creación compleja o costosa de objetos**: Objetos que requieren mucha configuración, cálculos previos o carga de recursos.
* **Necesidad de generar múltiples variaciones similares**: Cambios pequeños sobre una base común que no justifican múltiples constructores.
* **Dependencia del cliente de clases concretas**: El código necesita crear objetos sin conocer su tipo exacto en tiempo de compilación.
* **Copia de objetos con recursos dinámicos**: Se requiere decidir cuidadosamente si los recursos deben compartirse o duplicarse.

## Cómo lo soluciona el patrón

Prototype aborda estos problemas mediante las siguientes ideas clave:

* **Interfaz común de clonación**: Se define un método `clone()` que permite copiar objetos a través de una interfaz, sin conocer su clase concreta.
* **Lógica de copia delegada a cada clase**: Cada clase implementa su propia clonación, decidiendo si la copia es superficial o profunda.
* **Eliminación de dependencias con constructores**: El cliente no necesita saber cómo se construyen los objetos ni qué parámetros requieren.
* **Reutilización de prototipos preconfigurados**: Los objetos base pueden almacenarse y clonarse, evitando repetir código de inicialización.


## Relación con los principios SOLID

* **Single Responsibility Principle (SRP)**: Cada prototipo es responsable de definir cómo se copia a sí mismo. El cliente no gestiona detalles de construcción ni de clonación, lo que mantiene las responsabilidades bien separadas.
* **Open/Closed Principle (OCP)**: Se pueden añadir nuevos tipos de prototipos sin modificar el código cliente, ya que este trabaja siempre con la interfaz común de clonación.
* **Liskov Substitution Principle (LSP)**: Los prototipos concretos pueden sustituirse por la abstracción sin alterar el comportamiento esperado del cliente.
* **Interface Segregation Principle (ISP)**: La interfaz del prototipo define únicamente la operación necesaria para la clonación.
* **Dependency Inversion Principle (DIP)**: El cliente depende de la abstracción del prototipo y crea objetos mediante clonación polimórfica, no mediante constructores concretos.

## Ejemplos concretos

Casos reales donde el patrón Prototype resulta especialmente útil:

* **Aplicaciones de edición gráfica**: Duplicar formas, iconos o elementos estilizados conservando propiedades visuales y comportamientos.
* **Motores de videojuegos**: Crear enemigos, efectos, proyectiles o elementos repetitivos partiendo de prototipos con parámetros ya definidos.
* **Sistemas de documentos**: Replicar páginas, bloques de texto o plantillas complejas sin reconstruir toda su jerarquía interna.
* **Escenas y modelos 3D**: Generar copias de objetos geométricos o entidades con configuraciones base compartidas.
* **Aplicaciones empresariales**: Clonar estructuras de configuración o entidades con inicializaciones costosas.
* **Interfaces gráficas**: Reutilizar widgets preconfigurados o elementos compuestos.
* **Frameworks orientados a plugins**: Instanciar componentes registrados como prototipos sin depender de su tipo concreto.
* **Simulaciones científicas o de eventos**: Replicar entidades complejas para evaluar múltiples variantes de un escenario.

