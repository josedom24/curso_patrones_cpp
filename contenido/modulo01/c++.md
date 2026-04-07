# Conceptos de C++ Moderno para Patrones de Diseño

## Constructores
Garantizan un estado válido desde la construcción. Las **listas de inicialización** inicializan miembros directamente. Los **constructores privados** controlan la creación. Los **constructores explícitos** evitan conversiones implícitas accidentales.

## Encapsulación
Controla el acceso mediante `public`, `private` y `protected`.  

## Clases amigas
Conceden acceso a miembros privados/protegidos. Permite acceso privilegiado entre objetos sin exponer la interfaz pública.

## RAII
Los recursos se adquieren en construcción y liberan automáticamente en destrucción. Garantiza gestión segura de recursos.

## Punteros inteligentes
Los punteros inteligentes son una aplicación directa del principio RAII a la gestión de memoria dinámica. 

- `std::unique_ptr`: propiedad exclusiva.
- `std::shared_ptr`: propiedad compartida.
- `std::weak_ptr`: evita ciclos de dependencia.

## Inicialización diferida
Técnica en la que el objeto real no se crea en el constructor, sino en el momento de la primera operación que lo requiere. Crea objetos bajo demanda con `std::unique_ptr` vacío. 

## Contenedores  de la STL
Los **contenedores de la STL** (Standard Template Library) son estructuras de datos genéricas que permiten almacenar y organizar colecciones de elementos de forma eficiente y segura. Proporcionan una interfaz común y se integran con algoritmos y utilidades del estándar, evitando la implementación manual de estructuras básicas.

Ejemplos: `std::vector`, `std::list`, ...

## Algoritmos de la STL

Los **algoritmos de la STL** son un conjunto de **funciones genéricas** del estándar de C++ que operan sobre rangos de elementos definidos por iteradores. Proporcionan operaciones comunes como búsqueda, recorrido, filtrado, ordenación o eliminación sin depender del tipo concreto del contenedor.

## Composición

Relación *tiene-un*. Construye sistemas flexibles mediante cooperación de objetos independientes.

## Herencia

Relación *es-un*. Define jerarquías de tipos relacionados para reutilización y polimorfismo. Se usa principalmente para definir interfaces.

## Clases abstractas y métodos virtuales puros
Definen interfaces comunes sin implementación. Contienen métodos virtuales puros, sin implementación.

El especificador `override` se utiliza en las clases derivadas para indicar explícitamente que un método redefine un método virtual de la clase base. El especificador `final` cierra puntos de extensión.

## Polimorfismo dinámico
El polimorfismo dinámico permite que una llamada a un método virtual se resuelva en tiempo de ejecución según el tipo real del objeto. Esto hace posible tratar distintos objetos derivados de forma uniforme a través de punteros o referencias a la clase base.

## Destructor virtual
Imprescindible cuando una clase se usa polimórficamente, garantiza liberación correcta de objetos derivados.

## Interfaces puras
Clases abstractas solo con métodos virtuales puros y destructor virtual. Define exclusivamente qué operaciones están disponibles.

## Copia profunda y superficial
El **constructor de copia** define cómo se crea un objeto a partir de otro objeto existente del mismo tipo. 
* **Copia profunda**: duplica todos los recursos independientemente.
* **Copia superficial**: solo copia referencias. Puede causar interferencias.

## Movimiento de objetos
Transfiere recursos sin copiar mediante constructores/operadores de movimiento y `std::move`. Mejora eficiencia.

## Clonación de objetos
Método `clone()` polimórfico que devuelve una copia sin conocer el tipo concreto.

## Fluidez de métodos
Es una técnica de diseño que permite encadenar llamadas consecutivas sobre un mismo objeto. Encadena llamadas devolviendo `*this` por referencia. Mejora legibilidad en configuraciones progresivas.

## Abstracción del comportamiento
Separa *qué se hace* de *cómo se hace*. Encapsula algoritmos detrás de interfaces para flexibilidad. Permite intercambiar comportamientos.
