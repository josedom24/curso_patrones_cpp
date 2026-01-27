# Patrón Composite

## Definición

El **Composite** es un patrón de diseño estructural que permite **tratar de manera uniforme objetos individuales y conjuntos de objetos organizados jerárquicamente**. Está pensado para modelar relaciones *parte-todo* mediante una **interfaz común**, de forma que el código cliente pueda trabajar con elementos simples y estructuras complejas sin necesidad de distinguir entre ellos.

## Objetivos del patrón

En el diseño de muchos sistemas aparecen dificultades comunes que el patrón Composite ayuda a resolver:

* La necesidad de representar **estructuras jerárquicas complejas**, como árboles de elementos que contienen otros elementos.
* La obligación del código cliente de **distinguir entre objetos simples y compuestos**, lo que introduce acoplamiento y aumenta la complejidad.
* La dependencia directa del cliente respecto a **clases concretas**, dificultando la evolución de la jerarquía.
* La complejidad de **recorrer y aplicar operaciones** de forma uniforme sobre todos los elementos, independientemente de su nivel en la estructura.

## Problemas que intenta solucionar

El patrón propone una solución basada en decisiones de diseño claras y coherentes:

* Definir una **interfaz común** que represente a todos los elementos de la jerarquía, tanto hojas como compuestos.
* Distinguir internamente entre **componentes hoja**, que no contienen otros elementos, y **componentes compuestos**, que gestionan colecciones de componentes.
* Utilizar **polimorfismo** para que el cliente pueda operar siempre sobre la abstracción, sin conocer la estructura interna del objeto.
* Aplicar **delegación recursiva**, de modo que los compuestos propaguen las operaciones a sus hijos y permitan procesar estructuras de cualquier profundidad.

## Cómo lo soluciona

El patrón Composite propone estas soluciones:

* Definir una **interfaz común** que represente a todos los elementos de la jerarquía, tanto hojas como compuestos.
* Distinguir internamente entre **componentes hoja**, que no contienen otros elementos, y **componentes compuestos**, que gestionan colecciones de componentes.
* Utilizar **polimorfismo** para que el cliente pueda operar siempre sobre la abstracción, sin conocer la estructura interna del objeto.
* Aplicar **delegación recursiva**, de modo que los compuestos propaguen las operaciones a sus hijos y permitan procesar estructuras de cualquier profundidad.

## Relación con los principios SOLID

* **Single Responsibility Principle (SRP)**: Facilita la separación entre el comportamiento de los elementos individuales y la gestión de la estructura jerárquica, ayudando a organizar responsabilidades de forma clara.
* **Open/Closed Principle (OCP)**: La jerarquía puede ampliarse añadiendo nuevos tipos de componentes sin modificar el código cliente, que trabaja siempre contra la abstracción común.
* **Liskov Substitution Principle (LSP)**:  Tanto los componentes hoja como los compuestos pueden sustituirse por la abstracción base sin alterar el comportamiento esperado por el cliente.
* **Interface Segregation Principle (ISP)**:  El uso de una interfaz común puede respetar ISP si se diseña con cuidado para no imponer operaciones innecesarias a los componentes hoja.
* **Dependency Inversion Principle (DIP)**:El código cliente depende únicamente de la abstracción del componente, no de implementaciones concretas ni de la estructura interna de la jerarquía.

## Ejemplos concretos

* **Sistemas de archivos**: Directorios que contienen archivos y otros directorios, todos manipulados por la misma interfaz.
* **Interfaces gráficas (GUI)**: Contenedores que agrupan botones, menús y otros widgets, cada uno tratado como un componente visual.
* **Escenas gráficas en motores 2D/3D**: Nodos que contienen otros nodos (luces, cámaras, objetos), formando un árbol de escena.
* **Documentos estructurados**: Párrafos que contienen líneas, que contienen palabras o elementos inline, todos tratados como componentes del documento.
* **Sistemas jerárquicos de organización**: Empleados, departamentos y divisiones representados bajo una interfaz común para cálculo de costes o notificaciones.
* **Árboles sintácticos y analizadores**: Nodos de expresiones y operadores compuestos usados de forma uniforme al recorrer o evaluar expresiones.
* **Menús y submenús**: Estructuras de navegación en aplicaciones, donde cada elemento puede contener otros elementos.
* **Componentes de juegos**: Entidades que contienen sub-entidades (por ejemplo, un vehículo con ruedas, puertas y accesorios).


