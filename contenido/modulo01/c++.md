# Implementación de patrones de diseño con C++ moderno

Vamos a repasar los conceptos fundamentes de C++ moderno que utilizaremos en la implementación de los distintos patrones de diseño:

## Constructores

Los constructores garantizan que un objeto se crea siempre en un estado válido. En C++ moderno se utilizan para expresar dependencias obligatorias y establecer las invariantes de la clase desde el momento de la construcción.

Las **listas de inicialización** permiten construir los miembros directamente, evitando asignaciones posteriores. Son la forma correcta de inicializar referencias, miembros `const` y objetos gestionados por RAII o punteros inteligentes.

Un **constructor privado** impide la creación directa de objetos desde el exterior. Se usa para controlar el proceso de creación y forzar el uso de fábricas, *builders* o métodos estáticos.

Un **constructor explícito** es un constructor marcado con la palabra clave `explicit` que **impide las conversiones implícitas** desde otros tipos hacia el tipo de la clase. Su objetivo es evitar que un objeto se cree de forma accidental a partir de un solo argumento, obligando a que la construcción sea **intencional y explícita** por parte del programador.

## Encapsulación

**Encapsulación** es el principio que consiste en **controlar el acceso al estado y comportamiento de una clase** mediante los modificadores:

* **`public`**: interfaz accesible desde fuera
* **`private`**: detalles internos ocultos
* **`protected`**: acceso reservado a la clase y sus derivadas

Su objetivo es **proteger el estado interno** y garantizar un uso correcto del objeto.

## Clases amigas

Una **clase amiga** (*friend class*) es una clase a la que se le concede **acceso completo** a los miembros **privados y protegidos** de otra clase.

## RAII 

RAII (Resource Acquisition Is Initialization) es el principio fundamental de C++ para la gestión correcta de recursos. Un recurso, como memoria dinámica, un archivo, ..., se adquiere en el momento de construir un objeto y se libera automáticamente cuando dicho objeto se destruye. De esta forma, la duración del recurso queda ligada al ámbito del objeto que lo gestiona, lo que garantiza liberación correcta incluso en presencia de excepciones o retornos anticipados.

RAII convierte la gestión de recursos en una cuestión de **diseño de clases**, no de disciplina del programador. El compilador se encarga de ejecutar los destructores cuando los objetos salen de ámbito, eliminando la necesidad de llamadas manuales de liberación.

## Punteros inteligentes

Los punteros inteligentes son una aplicación directa del principio RAII a la gestión de memoria dinámica. Un puntero inteligente encapsula un puntero crudo y define un destructor que libera automáticamente el recurso cuando el objeto sale de ámbito.

* `std::unique_ptr` expresa propiedad exclusiva de un recurso y garantiza su liberación automática.
* `std::shared_ptr` gestiona propiedad compartida mediante conteo de referencias. 
* `std::weak_ptr` es un puntero inteligente no propietario que permite observar un objeto gestionado por std::shared_ptr sin incrementar el conteo de referencias, evitando ciclos de dependencia y permitiendo comprobar de forma segura si el recurso aún existe.

## Inicialización diferida

La **inicialización diferida** es una técnica en la que el **objeto real no se crea en el constructor**, sino **en el momento de la primera operación que lo requiere**.
En C++ moderno se implementa manteniendo un **`std::unique_ptr` inicialmente vacío** y creando el objeto bajo demanda, dejando que **RAII** gestione automáticamente su ciclo de vida.

## Contenedores de la STL

Los **contenedores de la STL** (Standard Template Library) son estructuras de datos genéricas que permiten almacenar y organizar colecciones de elementos de forma eficiente y segura. Proporcionan una interfaz común y se integran con algoritmos y utilidades del estándar, evitando la implementación manual de estructuras básicas.

Ejemplos: `std::vector`, `std::list`, ...

## Algoritmos de la STL

Los **algoritmos de la STL** son un conjunto de **funciones genéricas** del estándar de C++ que operan sobre rangos de elementos definidos por iteradores. Proporcionan operaciones comunes como búsqueda, recorrido, filtrado, ordenación o eliminación sin depender del tipo concreto del contenedor.

## Composición

La composición expresa una relación *tiene-un*, donde un objeto contiene a otro y delega en él parte de su comportamiento. Es la técnica preferida en C++ moderno para construir sistemas flexibles, ya que permite cambiar componentes en tiempo de ejecución y reduce el acoplamiento.

## Herencia

La herencia expresa una relación *es-un*, en la que una clase derivada amplía o especializa el comportamiento de una clase base. En C++ moderno se utiliza para definir jerarquías polimórficas, permitiendo que distintos tipos relacionados se traten de forma uniforme a través de una interfaz común y se sustituyan dinámicamente en tiempo de ejecución.

## Clases abstractas y métodos virtuales puros

Una clase abstracta define una interfaz común y no puede instanciarse directamente. Los métodos virtuales puros especifican operaciones que las clases derivadas deben implementar, estableciendo un contrato claro entre la abstracción y sus implementaciones.

El especificador `override` se utiliza en las clases derivadas para indicar explícitamente que un método redefine un método virtual de la clase base. Su uso mejora la seguridad del código, ya que el compilador detecta errores de firma o sobreescrituras incorrectas.

El especificador `final` se emplea para impedir que un método virtual sea sobrescrito en clases derivadas o para evitar que una clase sea heredada. Permite cerrar puntos de extensión del diseño y expresar de forma explícita qué partes de la jerarquía no deben modificarse.

## Polimorfismo dinámico

El polimorfismo dinámico permite que una llamada a un método virtual se resuelva en tiempo de ejecución según el tipo real del objeto. Esto hace posible tratar distintos objetos derivados de forma uniforme a través de punteros o referencias a la clase base.

Los **punteros inteligentes** gestionan automáticamente la vida de objetos usados de forma polimórfica. En particular, `std::unique_ptr<Base>` y `std::shared_ptr<Base>` permiten almacenar y destruir objetos derivados de manera segura, siempre que la clase base tenga un destructor virtual, integrando polimorfismo dinámico con RAII.

Un **destructor virtual** garantiza que al destruir un objeto a través de un puntero a la clase base se ejecute correctamente el destructor de la clase derivada. Es imprescindible cuando una clase se utiliza de forma polimórfica.


## Interfaces puras

Una interfaz pura es una clase abstracta formada únicamente por métodos virtuales puros y un destructor virtual. Define exclusivamente qué operaciones están disponibles, sin imponer ninguna implementación concreta, y es la base de muchos patrones de diseño.

## Copia superficial y copia profunda

El **constructor de copia** define cómo se crea un objeto a partir de otro objeto existente del mismo tipo. Se utiliza cuando un objeto se inicializa a partir de otro, y es el punto donde se decide si la copia debe ser superficial o profunda. En C++ moderno, este constructor permite controlar la duplicación del estado interno y de los recursos asociados, garantizando que el nuevo objeto cumpla las mismas invariantes que el original.

La **copia superficial** duplica únicamente los valores de los miembros del objeto, incluyendo direcciones o manejadores de recursos, sin crear copias independientes de los recursos a los que apuntan. Como resultado, varios objetos pueden compartir el mismo recurso subyacente, lo que puede provocar interferencias o liberaciones incorrectas si no se gestiona cuidadosamente.

La **copia profunda** crea copias independientes de todos los recursos gestionados por el objeto, de modo que cada instancia mantiene su propio estado y su propio ciclo de vida. En C++ moderno, la copia profunda se implementa de forma explícita cuando una clase posee recursos y necesita garantizar independencia entre copias, y es un concepto clave para comprender patrones como *Prototype* y el diseño seguro de clases con semántica de copia.

## Movimiento de objetos

En **C++ moderno**, el **movimiento** permite **transferir recursos de un objeto a otro sin copiarlos**. Se basa en constructores y operadores de movimiento y en `std::move`, que indica que un objeto puede ceder sus recursos. Tras mover un objeto, el destino adquiere la propiedad y el origen queda en un estado válido pero no especificado.

## Clonación de objetos

La **clonación** es el proceso de crear una copia de un objeto sin conocer su tipo concreto, delegando la responsabilidad de la copia en el propio objeto. El método `clone` permite realizar esta operación de forma polimórfica a través de una interfaz común, devolviendo una nueva instancia que mantiene el mismo estado lógico que el original. En C++ moderno, `clone` se utiliza para implementar copias profundas cuando es necesario y suele devolver un puntero inteligente para garantizar una gestión segura del ciclo de vida del objeto.


## Fluidez de métodos

La **fluidez de métodos** es una técnica de diseño que permite encadenar llamadas consecutivas sobre un mismo objeto devolviendo una referencia a él mismo. Este estilo mejora la legibilidad del código y expresa de forma natural configuraciones progresivas o construcciones paso a paso. En C++ moderno se implementa normalmente devolviendo `*this` por referencia.

## Abstracción del comportamiento

La abstracción del comportamiento consiste en separar **qué se hace** de **cómo se hace**, encapsulando una acción o algoritmo detrás de una interfaz común. Este enfoque permite variar el comportamiento de un objeto sin modificar su estructura, intercambiando distintas implementaciones de forma transparente. En C++ moderno, la abstracción del comportamiento se apoya en interfaces, polimorfismo dinámico y, en muchos casos, composición, y es una idea clave para comprender patrones que favorecen la flexibilidad y la extensión del sistema.




