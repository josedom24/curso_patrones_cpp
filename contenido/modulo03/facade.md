# Patrón Facade

## Definición

El **Facade** es un patrón de diseño estructural cuyo propósito es **proporcionar una interfaz unificada y simplificada** a un conjunto de interfaces, componentes o subsistemas complejos. El objetivo es ocultar la complejidad interna y permitir al código cliente interactuar con un único punto de acceso, más simple y coherente, sin necesidad de conocer los detalles de implementación.

## Problemas que intenta solucionar

El patrón aborda principalmente estas situaciones:

* El sistema está formado por múltiples subsistemas o componentes con **interfaces complejas o difíciles de usar**.
* El código cliente necesita realizar **operaciones que requieren coordinar varios objetos**, lo que lleva a código repetido y difícil de mantener.
* Se desea **reducir el acoplamiento** entre el cliente y los subsistemas internos, evitando dependencias directas innecesarias.
* Un módulo externo necesita una **vista simplificada** de un sistema más grande, manteniendo ocultos los detalles que no necesita conocer.
* Es necesario mejorar la **legibilidad**, la cohesión y la organización** del código agrupando operaciones relacionadas detrás de una interfaz clara.

## Cómo lo soluciona

El patrón Facade aporta estas soluciones:

* Define una **clase fachada** que ofrece métodos simples que representan operaciones de alto nivel.
* Esta clase coordina internamente las llamadas a los **subsistemas reales**, encapsulando la lógica compleja en un único punto.
* El cliente interactúa únicamente con la fachada, sin conocer la existencia ni la estructura interna de los subsistemas.
* Se reduce la dependencia directa entre el cliente y los componentes internos, mejorando la modularidad.
* Facilita la **evolución del sistema**: los subsistemas pueden cambiar sin afectar al código cliente siempre que la fachada mantenga su contrato.
* Proporciona un **punto de entrada estándar** a un sistema complejo, mejorando la experiencia de uso y la mantenibilidad.

## Relación con los principios SOLID

* **Single Responsibility Principle (SRP)**: El patrón *Facade* concentra la responsabilidad de **simplificar el acceso a un subsistema complejo** en una única clase. El cliente no asume la coordinación entre múltiples componentes, y cada clase del subsistema mantiene su responsabilidad específica.
* **Open/Closed Principle (OCP)**: El subsistema puede evolucionar internamente sin afectar al código cliente, siempre que la interfaz de la fachada se mantenga estable. Nuevas funcionalidades pueden añadirse al subsistema sin modificar a los clientes que usan la fachada.
* **Liskov Substitution Principle (LSP)**: La fachada puede sustituirse por otra implementación equivalente (por ejemplo, una fachada alternativa o extendida) sin afectar al cliente, siempre que mantenga el mismo contrato público.
* **Interface Segregation Principle (ISP)**: La fachada expone una **interfaz específica y adaptada al cliente**, evitando que este dependa de la complejidad o de métodos innecesarios del subsistema subyacente.
* **Dependency Inversion Principle (DIP)**: El cliente depende únicamente de la fachada y no de las clases concretas del subsistema. La fachada actúa como punto de inversión de dependencias, reduciendo el acoplamiento entre cliente y detalles internos.

## Ejemplos concretos

* **Sistema multimedia**: Reproducir vídeo o audio mediante un método simple (`reproducir_archivo()`), pese a requerir decodificadores, buffers, controladores de audio, etc.
* **Librerías gráficas**: Un método de alto nivel que configura ventanas, carga texturas y crea shaders, sin exponer la complejidad de OpenGL o Vulkan.
* **Frameworks de redes**: Una fachada que ofrece `enviar_mensaje()` mientras gestiona sockets, serialización, colas y reintentos.
* **Sistemas de compilación**: Un único comando (p. ej., `compilar_proyecto()`) que invoca preprocessors, compiladores, enlazadores y empaquetadores.
* **APIs de bases de datos**: Métodos como `consultar()` o `guardar()` que internamente gestionan conexiones, transacciones y validaciones.
* **Motores de videojuegos**: Una fachada de “motor de juego” que coordina subsistemas de física, IA, renderizado y audio con llamadas simples.
* **Sistemas de domótica**: Un método “poner_modo_noche()” que coordina luces, persianas, alarmas y sensores con una única acción del usuario.
* **Envío de correos electrónicos**: Un método `enviar_email_simple()` que oculta la autenticación SMTP, el formateo MIME y la gestión de adjuntos.
* **Automatización industrial**: Métodos de control que simplifican la interacción con múltiples sensores, actuadores y sistemas de seguridad.
* **Servicios en la nube**: SDKs que exponen operaciones simples mientras gestionan internamente autenticación, red, formatos y errores distribuidos.
