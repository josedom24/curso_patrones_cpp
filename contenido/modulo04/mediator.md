# Patrón Mediator

## Definición

El **Mediator** es un patrón de diseño conductual que centraliza la comunicación entre múltiples objetos, de modo que **no se comuniquen directamente entre sí**, sino a través de un mediador común. Su finalidad es **reducir el acoplamiento** entre componentes, encapsular la lógica de interacción y simplificar la colaboración entre objetos complejos.

## Problemas que intenta solucionar

El patrón aborda fundamentalmente estas situaciones:

* **Acoplamiento excesivo** entre objetos que se comunican directamente, dificultando la evolución del sistema.
* **Dependencias circulares** o difíciles de rastrear entre componentes que se conocen mutuamente.
* **Lógica de interacción dispersa** en múltiples clases, lo que complica mantenimiento, pruebas y extensibilidad.
* **Crecimiento descontrolado** de condicionales del tipo “si el objeto A hace X, entonces B y C deben reaccionar”.
* Necesidad de **coordinar varios objetos** cuyos comportamientos dependen de eventos o cambios producidos por otros.
* Requerimiento de **modificar reglas de interacción** sin tener que reescribir todos los participantes.

## Cómo lo soluciona

El patrón Mediator proporciona estas soluciones:

* Introduce un **objeto mediador** que actúa como centro de comunicación.
* Los objetos participantes (**colegas**) **ya no se refieren entre sí directamente**, sino al mediador.
* La lógica de coordinación queda **encapsulada en el mediador**, no distribuida entre los colegas.
* Facilita el **cambio de reglas de interacción** sustituyendo o extendiendo el mediador, en lugar de modificar múltiples clases.
* Reduce el acoplamiento y mejora la **cohesión** en cada clase: los colegas solo gestionan su propio comportamiento.
* Simplifica la **extensibilidad**: añadir un nuevo colega rara vez requiere modificar los demás.

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
