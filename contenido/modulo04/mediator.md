# Patrón Mediator

## Definición

El **Mediator** es un patrón de diseño de comportamiento que centraliza la comunicación entre múltiples objetos, de modo que **no se comuniquen directamente entre sí**, sino a través de un mediador común. Su finalidad es **reducir el acoplamiento** entre componentes, encapsular la lógica de interacción y simplificar la colaboración entre objetos complejos.

### Objetivos del patrón

* **Reducir el acoplamiento** entre objetos colaboradores, evitando que se comuniquen directamente entre sí.
* **Centralizar la lógica de interacción** entre componentes en un único mediador, facilitando su comprensión y mantenimiento.
* **Simplificar la evolución del sistema**, permitiendo modificar las reglas de comunicación sin alterar las clases participantes.
* **Mejorar la cohesión de los objetos**, haciendo que cada uno se concentre en su comportamiento propio y no en la coordinación con otros.

## Problemas que intenta solucionar

El patrón aborda fundamentalmente estas situaciones:

* **Acoplamiento elevado entre componentes**, provocado por comunicaciones directas y dependencias mutuas que dificultan la evolución del sistema.
* **Dependencias complejas y difíciles de mantener**, como referencias cruzadas o circulares entre objetos que se conocen entre sí.
* **Lógica de interacción dispersa**, repartida en múltiples clases mediante condicionales y reglas implícitas, lo que complica el mantenimiento y las pruebas.
* **Dificultad para modificar o extender las reglas de colaboración**, ya que cualquier cambio en la coordinación requiere alterar varias clases simultáneamente.

## Cómo lo soluciona

El patrón Mediator proporciona estas soluciones:

* **Centraliza la comunicación** entre objetos en un mediador único, evitando referencias directas entre los componentes colaboradores.
* **Encapsula la lógica de coordinación** en una clase especializada, eliminando la dispersión de reglas de interacción en múltiples clases.
* **Reduce el acoplamiento y mejora la cohesión**, haciendo que cada objeto se concentre únicamente en su comportamiento propio.
* **Facilita la modificación y extensión de las interacciones**, permitiendo cambiar las reglas de colaboración mediante nuevos mediadores sin alterar los colegas existentes.

## Relación con los principios SOLID

* **Single Responsibility Principle (SRP)**: El patrón *Mediator* concentra la responsabilidad de **coordinar la comunicación entre objetos** en una clase mediadora. Los colegas se centran exclusivamente en su comportamiento propio, sin asumir lógica de interacción con otros componentes.
* **Open/Closed Principle (OCP)**: Es posible extender o modificar las reglas de comunicación creando nuevos mediadores concretos sin cambiar las clases de los colegas. Las interacciones evolucionan sin alterar los componentes existentes.
* **Liskov Substitution Principle (LSP)**: Un mediador concreto puede sustituirse por otro que respete la misma interfaz sin afectar al funcionamiento de los colegas, siempre que mantenga el contrato de coordinación esperado.
* **Interface Segregation Principle (ISP)**: El mediador expone una **interfaz específica y orientada a la coordinación**, evitando que los colegas dependan de métodos que no necesitan o de responsabilidades ajenas a la comunicación.
* **Dependency Inversion Principle (DIP)**: Los colegas dependen de la **abstracción del mediador**, no de otros colegas concretos. La comunicación se realiza a través de interfaces, reduciendo el acoplamiento entre componentes.

## Ejemplos concretos

* **Interfaces gráficas**: Coordinación entre widgets (botones, listas, cuadros de texto) mediante un mediador que gestiona eventos y actualizaciones.
* **Chats y sistemas de mensajería**: Usuarios que envían mensajes a través de un servidor o canal centralizado que reenvía y gestiona participantes.
* **Sistemas de control de tráfico aéreo**: Torres de control que coordinan aviones sin que estos necesiten comunicarse directamente entre sí.
* **Motores de videojuegos**: Coordinación de entidades o componentes (física, IA, sonido) a través de un coordinador central.
* **Automatización del hogar (domótica)**: Sensores y actuadores que interactúan mediante un controlador central que decide las acciones apropiadas.
* **Frameworks de comunicación interna**: Módulos independientes que intercambian mensajes mediante un bus o mediador.
* **Formularios avanzados**: Campos que activan o desactivan otros campos dependiendo de reglas gestionadas por el mediador.
* **Orquestadores en sistemas distribuidos**: Servicios que coordinan múltiples microservicios sin que estos se conozcan entre sí.
* **Sistemas de workflow**: Componentes que realizan pasos coordinados por un módulo que gestiona las transiciones y reglas del flujo.
* **Aplicaciones modulares**: Plugins que interactúan entre sí a través de un gestor central, evitando referencias mutuas entre módulos.
