# Patrón Bridge

## Definición

El **Bridge** es un patrón de diseño **estructural** cuyo propósito es **desacoplar una abstracción de su implementación**, permitiendo que **ambas evolucionen de forma independiente**. El patrón separa dos ejes de variación distintos, el **qué hace** un objeto y el **cómo lo hace**, evitando que queden ligados en una única jerarquía rígida y difícil de extender.

## Objetivos del patrón

* **Separar responsabilidades** entre la lógica de alto nivel y los detalles de implementación.
* **Evitar la proliferación de clases** cuando existen múltiples variantes conceptuales y técnicas.
* **Permitir sustituir implementaciones** sin afectar al código que usa la abstracción.
* **Facilitar la evolución independiente** de abstracciones e implementaciones a lo largo del tiempo.

## Problemas que intenta solucionar

El patrón Bridge aborda principalmente estas situaciones:

* **Explosión combinatoria de clases**: Cuando existen múltiples variantes de una abstracción y múltiples variantes de su implementación, combinarlas mediante herencia genera jerarquías grandes, rígidas y difíciles de mantener.
* **Acoplamiento fuerte entre capas**: La abstracción queda ligada a detalles concretos de implementación, plataformas o librerías, contaminando el código de alto nivel con decisiones de bajo nivel.
* **Rigidez en el cambio de comportamiento**: Al fijar la implementación mediante herencia, resulta difícil o imposible sustituirla sin modificar la jerarquía existente.
* **Dificultad para reutilizar y mantener el código**: La mezcla de decisiones conceptuales y técnicas provoca duplicación, poca reutilización y mayor coste de mantenimiento y pruebas.

## Cómo lo soluciona

El Bridge aporta estas soluciones:

* **Separa el sistema en dos jerarquías independientes**, una centrada en la abstracción y otra en la implementación, cada una con una responsabilidad bien definida.
* **Conecta ambas jerarquías mediante una relación flexible**, evitando dependencias directas entre conceptos de alto nivel y detalles concretos.
* **Permite extender cada parte de forma independiente**, añadiendo nuevas abstracciones o nuevas implementaciones sin afectar a las existentes.
* **Facilita la sustitución de implementaciones**, incluso dinámicamente, sin alterar la interfaz visible para el cliente.

## Relación con los principios SOLID

* **Single Responsibility Principle (SRP)**: el Bridge separa claramente la responsabilidad de la abstracción y la de la implementación, evitando clases con múltiples motivos de cambio.
* **Open/Closed Principle (OCP)**: el sistema puede extenderse por ambos ejes, abstracciones e implementaciones, sin modificar código existente.
* **Liskov Substitution Principle (LSP)**: cualquier implementación concreta puede sustituirse por la interfaz de implementación sin afectar al comportamiento esperado.
* **Interface Segregation Principle (ISP)**: la interfaz de implementación se mantiene reducida y específica, ajustada a las necesidades reales de la abstracción.
* **Dependency Inversion Principle (DIP)**: la abstracción depende de una interfaz y no de implementaciones concretas; tanto el alto nivel como el bajo nivel dependen de abstracciones.

## Ejemplos concretos

* **Sistemas de ventanas gráficos (GUI)**: La abstracción es "Ventana" y las implementaciones son "VentanaWindows", "VentanaLinux", etc. Las ventanas avanzadas pueden combinarse con múltiples plataformas sin crear jerarquías enormes.
* **Dispositivos y controles remotos**: La abstracción es un control remoto (básico, avanzado,...) y las implementaciones son dispositivos concretos (TV, radio, proyector).
* **Sistemas de renderizado**: Abstracción: formas geométricas (círculo, rectángulo). Implementación: renderizadores (raster, vectorial, OpenGL, DirectX).
* **Persistencia de datos**: Abstracción: gestor de objetos o repositorio. Implementación: persistencia en archivo, en base de datos, en memoria.
* **Reportes o exportadores**: Abstracción: documento o informe. Implementación: exportación PDF, HTML, Markdown.
* **Motores de mensajes o notificaciones**: Abstracción: tipo de mensaje (alerta, informe, evento). Implementación: canal (email, SMS, webhook).
* **Aplicaciones multimedia**: Abstracción: reproductor. Implementación: backend (FFmpeg, GStreamer, API del SO).
* **Drivers y hardware**: Abstracción: interfaz de alto nivel del dispositivo. Implementación: driver específico del fabricante.

