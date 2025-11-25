# Principios básicos de diseño

Los principios básicos de diseño orientado a objetos son guías conceptuales que ayudan a construir software **mantenible**, **flexible** y **reutilizable**. Son anteriores a la formalización de SOLID, pero siguen siendo esenciales para entender el valor de los patrones de diseño y cómo aplicarlos eficazmente, especialmente en C++ moderno.

En este curso nos centraremos en cuatro ideas clave:

## 1. Encapsula lo que varía

**Motivación**
El software cambia con el tiempo: se añaden requisitos, se modifican reglas de negocio y se sustituyen tecnologías. Si la parte cambiante está mezclada con el resto del código, cualquier modificación puede producir efectos colaterales no deseados y hacer el sistema difícil de mantener.

**Principio**

> Identifica los aspectos de tu aplicación que varían y sepáralos del resto del código que permanece estable.

**Aplicación en C++ moderno**

* Representar el comportamiento variable mediante:

  * funciones virtuales (jerarquías clásicas),
  * expresiones lambda,
  * o técnicas de *type erasure* (`std::function`, interfaces abstractas).
* Utilizar clases base abstractas para definir interfaces que oculten los detalles de implementación concreta.
* Separar la lógica cambiante en componentes específicos, gestionados mediante punteros inteligentes (`std::unique_ptr`, `std::shared_ptr`) u objetos función (`std::function`).

Este principio está en la base de patrones como **Strategy**, **Command**, **State** o **Template Method**, donde el comportamiento que puede cambiar se encapsula en una entidad propia.

## 2. Programa a una interfaz, no a una implementación

**Motivación**
Acoplar el código directamente a clases concretas dificulta el cambio y la reutilización: sustituir una implementación exige modificar el código cliente. En cambio, si el cliente trabaja con interfaces o abstracciones, es posible cambiar la implementación sin tocar el uso.

**Principio**

> Define las dependencias en términos de abstracciones, no de clases concretas.

**Aplicación en C++ moderno**

* Uso de **clases abstractas** para expresar contratos estables con implementaciones intercambiables.
* Uso de **plantillas genéricas** para definir algoritmos que operan sobre tipos que cumplan ciertos requisitos (y, en C++20, conceptos para expresarlos de forma explícita).
* Uso de `std::function` y objetos función para representar comportamientos genéricos inyectables.
* Prácticas de inversión de dependencias: las clases de alto nivel dependen de interfaces o abstracciones, no de detalles concretos.

Este principio sustenta patrones como **Factory Method**, **Abstract Factory**, **Strategy**, **Observer** o **Mediator**, donde el código cliente desconoce las clases concretas que se utilizan internamente.

## 3. Favorece la composición sobre la herencia

**Motivación**
La herencia crea una relación fuerte entre clases: cambios en la superclase pueden afectar de forma inesperada a todas las subclases. Además, las jerarquías profundas tienden a ser rígidas y difíciles de refactorizar. La composición, en cambio, permite construir comportamientos complejos combinando objetos más simples y reemplazables.

**Principio**

> Construye sistemas a partir de objetos que cooperan entre sí, en lugar de depender de jerarquías rígidas.

**Aplicación en C++ moderno**

* Composición mediante **atributos** y **punteros inteligentes** a colaboradores (`std::unique_ptr`, `std::shared_ptr`), en lugar de heredar indiscriminadamente.
* Inyección de **políticas** o **estrategias** como objetos o lambdas para extender el comportamiento dinámicamente sin modificar la clase que las usa.
* Clases pequeñas con responsabilidades claras, que delegan en colaboradores especializados.
* Uso de patrones como **Strategy**, **Decorator**, **Composite** o **Bridge**, que se basan en composición para extender o combinar comportamientos.

La composición hace más sencillo reemplazar componentes, probarlos de forma aislada y reutilizarlos en otros contextos.

## 4. Favorece el acoplamiento débil

**Motivación**
Un sistema donde los componentes conocen demasiados detalles unos de otros es frágil y costoso de modificar. Cualquier cambio en un módulo puede obligar a tocar muchos otros. Reducir el acoplamiento facilita la evolución del software y mejora su capacidad de prueba y reutilización.

**Principio**

> Diseña componentes que dependan lo menos posible de los detalles internos de otros componentes.

**Aplicación en C++ moderno**

* Depender de **interfaces** (clases abstractas, conceptos) en lugar de tipos concretos.
* Separar claramente las responsabilidades entre módulos y limitar el número de dependencias directas.
* Usar **inyección de dependencias** (por constructor, por parámetros de función, mediante lambdas u objetos función) en lugar de crear directamente los objetos dentro de las clases.
* Encapsular detalles de implementación en archivos fuente y exponer solo las interfaces públicas necesarias.

Este principio se relaciona estrechamente con el **Principio de Inversión de Dependencias (D de SOLID)** y es central en patrones como **Observer, Mediator, Facade o Adapter**, que buscan reducir el acoplamiento entre partes del sistema.