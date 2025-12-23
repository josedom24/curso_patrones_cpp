# Patrón Bridge

## Definición

El **Bridge** es un patrón de diseño estructural cuyo objetivo es **desacoplar una abstracción de su implementación**, permitiendo que ambas evolucionen de manera independiente.
Para ello, la abstracción mantiene una referencia a un **implementador** (interfaz o jerarquía separada), delegando en él los detalles concretos.
De este modo, es posible combinar libremente múltiples variantes de abstracciones con múltiples variantes de implementaciones sin multiplicar el número de clases.

## Problemas que intenta solucionar

El patrón Bridge aborda principalmente estas situaciones:

* **Explosión combinatoria de clases**:
  Cuando existen múltiples variantes de una abstracción y múltiples variantes de su implementación, combinarlas mediante herencia produce jerarquías rígidas y demasiado grandes.

* **Fuerte acoplamiento entre capas**:
  La abstracción queda atada a una implementación concreta, dificultando el reemplazo, la extensión o la reutilización.

* **Necesidad de cambiar implementaciones en tiempo de ejecución**:
  Si la implementación está fijada por herencia, no es posible sustituirla dinámicamente.

* **Violación del principio Open/Closed**:
  Al mezclar variaciones conceptuales (qué hace) con variaciones técnicas (cómo lo hace), se termina modificando clases existentes en lugar de extenderlas.

* **Dependencia forzada de detalles específicos de plataforma o librería**:
  Código de alto nivel queda contaminado con detalles de bajo nivel.

## Cómo lo soluciona

El Bridge aporta estas soluciones:

* **Separa dos jerarquías independientes**:
  * La **Abstracción**: define la interfaz de alto nivel.
  * El **Implementador**: define los detalles de la operación básica.
* La abstracción **contiene una referencia** a un implementador y delega en él las operaciones de bajo nivel.
* Permite **extender cada jerarquía sin afectar a la otra**:
  Añadir una nueva abstracción no requiere modificar las implementaciones; añadir una nueva implementación no requiere modificar las abstracciones.
* Posibilita **cambiar implementaciones en tiempo de ejecución**, ya que el implementador es un atributo y no una clase base fija.

# Relación con los principios SOLID

* **Single Responsibility Principle (SRP)**: El patrón *Bridge* separa claramente dos responsabilidades que tienden a mezclarse: la **abstracción** (qué se hace) y la **implementación** (cómo se hace). Cada jerarquía evoluciona de forma independiente, evitando clases con múltiples motivos de cambio y manteniendo responsabilidades bien definidas.
* **Open/Closed Principle (OCP)**: El sistema puede extenderse tanto por el lado de las abstracciones como por el de las implementaciones sin modificar el código existente. Nuevas abstracciones refinadas o nuevas implementaciones concretas pueden añadirse sin afectar a las demás clases, respetando la apertura a extensión y el cierre a modificación.
* **Dependency Inversion Principle (DIP)**: La abstracción depende únicamente de la interfaz de implementación, no de implementaciones concretas. Tanto las abstracciones de alto nivel como los detalles de bajo nivel dependen de abstracciones, lo que reduce el acoplamiento y permite intercambiar implementaciones de manera transparente.
* **Liskov Substitution Principle (LSP)**: Las implementaciones concretas pueden sustituirse por la interfaz de implementación sin afectar a la abstracción.
* **Interface Segregation Principle (ISP)**: La interfaz de implementación se mantiene reducida y específica.

## Ejemplos concretos

* **Sistemas de ventanas gráficos (GUI)**:
  La abstracción es "Ventana" y las implementaciones son "VentanaWindows", "VentanaLinux", etc. Las ventanas avanzadas pueden combinarse con múltiples plataformas sin crear jerarquías enormes.

* **Dispositivos y controles remotos**:
  La abstracción es un control remoto (básico, avanzado,...) y las implementaciones son dispositivos concretos (TV, radio, proyector).

* **Sistemas de renderizado**:
  Abstracción: formas geométricas (círculo, rectángulo).
  Implementación: renderizadores (raster, vectorial, OpenGL, DirectX).

* **Persistencia de datos**:
  Abstracción: gestor de objetos o repositorio.
  Implementación: persistencia en archivo, en base de datos, en memoria.

* **Reportes o exportadores**:
  Abstracción: documento o informe.
  Implementación: exportación PDF, HTML, Markdown.

* **Motores de mensajes o notificaciones**:
  Abstracción: tipo de mensaje (alerta, informe, evento).
  Implementación: canal (email, SMS, webhook).

* **Aplicaciones multimedia**:
  Abstracción: reproductor.
  Implementación: backend (FFmpeg, GStreamer, API del SO).

* **Drivers y hardware**:
  Abstracción: interfaz de alto nivel del dispositivo.
  Implementación: driver específico del fabricante.

