# Patrón Composite

## Definición

El **Composite** es un patrón de diseño estructural que permite tratar de forma uniforme a objetos individuales y a composiciones de objetos. Su objetivo es representar jerarquías *parte-todo* de manera que el código cliente pueda manipular elementos simples y estructuras complejas mediante una interfaz común, sin necesidad de distinguir explícitamente entre ambos casos.

## Problemas que intenta solucionar

El patrón aborda principalmente estas situaciones:

* Se necesita modelar **estructuras jerárquicas** (como árboles) donde ciertos elementos son agregaciones de otros.
* El código cliente se ve obligado a **distinguir manualmente** entre objetos simples y objetos compuestos, introduciendo condicionales innecesarios.
* Se dificulta la **extensibilidad** del sistema cuando la jerarquía crece o cambia, porque el cliente depende de múltiples tipos concretos.
* Se requiere una forma clara y coherente de **recorrer**, **operar** y **modificar** elementos estructurados en niveles (por ejemplo, carpetas que contienen carpetas y archivos).
* Se quiere mantener un diseño limpio donde cada elemento de la jerarquía se trate a través de una **interfaz unificada**.

## Cómo lo soluciona

El patrón Composite propone estas soluciones:

* Define una **interfaz común** para todos los elementos de la jerarquía, ya sean simples o compuestos.
* Se introducen **componentes hoja**, que representan objetos indivisibles, y **componentes compuestos**, que gestionan colecciones de otros componentes.
* Los objetos compuestos implementan la misma interfaz que las hojas, permitiendo que el cliente los use de manera homogénea.
* Se reduce la necesidad de condicionales en el cliente: la **polimorfia** y la interfaz común encapsulan la diferencia entre “parte” y “todo”.
* Facilita la **recursividad**: los objetos compuestos delegan operaciones a sus hijos, permitiendo procesar estructuras de profundidad arbitraria.
* Favorece el principio *Open/Closed*, ya que se pueden añadir nuevos tipos de componentes sin modificar el código cliente.

# Relación con los principios SOLID

* **Single Responsibility Principle (SRP)**: El patrón *Composite* separa la responsabilidad del **comportamiento individual** (componentes hoja) de la **gestión de estructuras jerárquicas** (componentes compuestos). Cada tipo de clase tiene un único motivo de cambio, manteniendo responsabilidades bien definidas.
* **Open/Closed Principle (OCP)**: El sistema puede ampliarse incorporando nuevos tipos de componentes sin modificar el código cliente ni las clases existentes. Al trabajar siempre contra la abstracción común, la estructura queda abierta a extensión y cerrada a modificación.
* **Dependency Inversion Principle (DIP)**: El cliente depende exclusivamente de la abstracción del componente, no de implementaciones concretas ni de si el objeto es hoja o compuesto. Tanto estructuras simples como jerárquicas se manipulan a través de la misma interfaz.
* **Liskov Substitution Principle (LSP)**: Los componentes hoja y los compuestos pueden sustituirse por la abstracción común sin alterar el comportamiento esperado por el cliente.
* **Interface Segregation Principle (ISP)**: La interfaz del componente se mantiene uniforme y específica para las operaciones que el cliente necesita, evitando dependencias innecesarias.


## Ejemplos concretos

* **Sistemas de archivos**: Directorios que contienen archivos y otros directorios, todos manipulados por la misma interfaz.
* **Interfaces gráficas (GUI)**: Contenedores que agrupan botones, menús y otros widgets, cada uno tratado como un componente visual.
* **Escenas gráficas en motores 2D/3D**: Nodos que contienen otros nodos (luces, cámaras, objetos), formando un árbol de escena.
* **Documentos estructurados**: Párrafos que contienen líneas, que contienen palabras o elementos inline, todos tratados como componentes del documento.
* **Sistemas jerárquicos de organización**: Empleados, departamentos y divisiones representados bajo una interfaz común para cálculo de costes o notificaciones.
* **Árboles sintácticos y analizadores**: Nodos de expresiones y operadores compuestos usados de forma uniforme al recorrer o evaluar expresiones.
* **Menús y submenús**: Estructuras de navegación en aplicaciones, donde cada elemento puede contener otros elementos.
* **Componentes de juegos**: Entidades que contienen sub-entidades (por ejemplo, un vehículo con ruedas, puertas y accesorios).

