# Principios básicos de diseño

Los principios básicos de diseño orientado a objetos son guías conceptuales que ayudan a construir software **mantenible**, **flexible** y **reutilizable**. Son anteriores a la formalización de SOLID, pero siguen siendo esenciales para entender el valor de los patrones de diseño y cómo aplicarlos eficazmente, especialmente en C++ moderno.

En este apartado presentamos cuatro principios clásicos que sirven como fundamento para el uso y comprensión de los patrones de diseño. Estos principios no sustituyen a SOLID ni se superponen a él; más bien constituyen una perspectiva complementaria y atemporal que ayuda a entender por qué los patrones existen y cuándo conviene aplicarlos, especialmente en el contexto de C++ moderno.


## 1. Encapsula lo que varía

### Motivación
El software cambia con el tiempo: se añaden requisitos, se modifican reglas de negocio y se sustituyen tecnologías. Si la parte cambiante está mezclada con el resto del código, cualquier modificación puede producir efectos colaterales no deseados y hacer el sistema difícil de mantener.

### Principio

Identifica los aspectos de tu aplicación que varían y sepáralos del resto del código que permanece estable.

### Aplicación en C++ moderno

* Abstraer el comportamiento variable mediante:
  * **polimorfismo dinámico** (interfaces y funciones virtuales),
  * **expresiones lambda** para comportamientos específicos y ligeros,
  * **objetos función (functores)** que encapsulan lógica,
  * **`std::function`** para almacenar cualquier *callable* mediante borrado de tipo.
* Inyectar dicho comportamiento en clases o funciones en lugar de codificarlo de forma fija.
* Separar la lógica cambiante en componentes propios y combinarlos mediante **composición**, gestionados con punteros inteligentes (`std::unique_ptr`, `std::shared_ptr`).

### Ejemplo conceptual

Si una clase realiza un cálculo que depende de una regla de negocio cambiante (por ejemplo, una política de descuento), esta política debe extraerse en un objeto independiente o una función inyectada, de modo que pueda modificarse sin alterar la clase principal.

## 2. Programa a una interfaz, no a una implementación

### Motivación
Acoplar el código directamente a clases concretas dificulta el cambio y la reutilización: sustituir una implementación exige modificar el código cliente. Si el cliente trabaja con abstracciones, es posible sustituir implementaciones sin alterar el uso.

### Principio

Define las dependencias en términos de abstracciones, no de clases concretas.

### Aplicación en C++ moderno

* Uso de **clases abstractas** para definir contratos que admiten múltiples implementaciones.
* Uso de **plantillas genéricas** como mecanismo de abstracción en tiempo de compilación.
* Inyección de comportamiento mediante `std::function`, funtores o lambdas.
* Aplicación coherente de la inversión de dependencias: los módulos de alto nivel dependen de abstracciones y reciben el comportamiento desde fuera.

### Ejemplo conceptual

Si un módulo necesita enviar notificaciones, no debe depender de `EmailSender` o `SmsSender`. En su lugar, depende de una interfaz abstracta `Notifier`, y la implementación concreta se inyecta cuando se construye el módulo.


## 3. Favorece la composición sobre la herencia

### Motivación
La herencia crea vínculos fuertes entre clases y puede generar jerarquías rígidas. La composición permite combinar comportamientos cambiantes mediante objetos independientes y sustituibles.

### Principio

Construye sistemas a partir de objetos que cooperan entre sí, en lugar de depender de jerarquías rígidas.

### Aplicación en C++ moderno

* Componer clases con colaboradores gestionados mediante punteros inteligentes.
* Extender comportamientos mediante **inyección de comportamiento** (objetos o lambdas), en lugar de crear subclases.
* Modularizar responsabilidades en componentes especializados que se agregan o sustituyen con facilidad.

### Ejemplo conceptual

Si una clase debe registrar operaciones, no debería heredar de `Logger`. Es mejor recibir o almacenar un objeto `Logger` que se encargue del registro; así puede reemplazarse fácilmente por otro tipo de logger.


## 4. Favorece el acoplamiento débil

### Motivación
Un sistema donde los componentes conocen demasiados detalles internos es frágil y difícil de modificar. Reducir el acoplamiento facilita el mantenimiento, las pruebas y la reutilización.

### Principio

Diseña componentes que dependan lo menos posible de los detalles internos de otros componentes.

### Aplicación en C++ moderno

* Depender de **interfaces** o **abstracciones de comportamiento**, no de tipos concretos.
* Inyectar dependencias y comportamientos (interfaces, lambdas, `std::function`) en lugar de crearlos internamente.
* Encapsular los detalles en archivos fuente y exponer únicamente la interfaz pública necesaria.
* Combinar módulos mediante composición, no mediante dependencia explícita de detalles concretos.

### Ejemplo conceptual

Si un componente necesita valores de configuración, no debe leer archivos directamente. En su lugar, recibe una abstracción que proporciona la configuración. Así puede cambiar la fuente (archivo, red, memoria, valores por defecto) sin modificar el componente.

