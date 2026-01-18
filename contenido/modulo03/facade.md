# Patrón Facade

## Definición

El **Facade** es un patrón de diseño estructural cuyo propósito es **proporcionar una interfaz unificada y simplificada** a un conjunto de interfaces, componentes o subsistemas complejos. El objetivo es ocultar la complejidad interna y permitir al código cliente interactuar con un único punto de acceso, más simple y coherente, sin necesidad de conocer los detalles de implementación.

## Objetivos del patrón

* **Simplificar el acceso a subsistemas complejos**, ofreciendo una interfaz de alto nivel que oculte detalles internos innecesarios para el cliente.
* **Reducir el acoplamiento entre el cliente y la implementación interna**, evitando dependencias directas con múltiples clases del subsistema.
* **Centralizar la coordinación de operaciones**, encapsulando la lógica que combina varios componentes en un único punto de acceso.
* **Mejorar la claridad, legibilidad y mantenibilidad del código**, proporcionando una entrada coherente y expresiva a un sistema complejo.

## Problemas que intenta solucionar

El patrón aborda principalmente estas situaciones:

* El sistema expone **interfaces complejas y poco intuitivas**, formadas por múltiples subsistemas difíciles de usar directamente.
* El código cliente debe **coordinar varios objetos para realizar una operación**, provocando duplicación de lógica y dificultades de mantenimiento.
* Existe un **alto acoplamiento entre el cliente y los detalles internos** del sistema, generando dependencias frágiles y poco flexibles.
* Se necesita una **vista simplificada y coherente del sistema**, que mejore la legibilidad y organización del código y oculte detalles innecesarios.

## Cómo lo soluciona

El patrón *Facade* aporta estas soluciones:

* Define una **interfaz unificada y de alto nivel** mediante una clase fachada que representa operaciones completas y fáciles de usar.
* **Encapsula y centraliza la coordinación** de los subsistemas internos, ocultando la lógica compleja en un único punto.
* Aísla al cliente de la estructura interna del sistema, **reduciendo el acoplamiento** y mejorando la modularidad.
* Establece un **punto de entrada estable y coherente**, permitiendo que los subsistemas evolucionen sin afectar al código cliente y mejorando la mantenibilidad general.

## Relación con los principios SOLID

* **Single Responsibility Principle (SRP)**: El patrón *Facade* concentra la responsabilidad de **simplificar el acceso a un subsistema complejo** en una única clase. El cliente no asume la coordinación entre múltiples componentes, y cada clase del subsistema mantiene su responsabilidad específica.
* **Open/Closed Principle (OCP)**: El subsistema puede evolucionar internamente sin afectar al código cliente, siempre que la interfaz de la fachada se mantenga estable. Nuevas funcionalidades pueden añadirse al subsistema sin modificar a los clientes que usan la fachada.
* **Liskov Substitution Principle (LSP)**: Cuando la fachada se define mediante una interfaz o clase base, puede **sustituirse por otra implementación equivalente** (por ejemplo, una fachada alternativa o extendida) sin afectar al cliente, siempre que mantenga el mismo contrato público.
* **Interface Segregation Principle (ISP)**: La fachada expone una **interfaz específica y adaptada al cliente**, evitando que este dependa de la complejidad o de métodos innecesarios del subsistema subyacente.
* **Dependency Inversion Principle (DIP)**: El cliente depende de la abstracción que representa la fachada y no de las clases concretas del subsistema. Esto **reduce el acoplamiento** y limita la propagación de dependencias hacia los detalles internos.


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
