# Principios básicos de diseño

Los principios básicos de diseño orientado a objetos son guías conceptuales que ayudan a construir software **mantenible**, **flexible** y **reutilizable**. Son anteriores a la formalización de SOLID, pero siguen siendo esenciales para entender el valor de los patrones de diseño y cómo aplicarlos eficazmente, especialmente en C++ moderno.

## 1. Encapsula lo que varía

### Motivación
El software cambia con el tiempo: se añaden requisitos, se modifican reglas de negocio y se sustituyen tecnologías. Si la parte cambiante está mezclada con el resto del código, cualquier modificación puede producir efectos colaterales no deseados y hacer el sistema difícil de mantener.

### Principio

Identifica los aspectos de tu aplicación que varían y sepáralos del resto del código que permanece estable.

### Ejemplo conceptual

Si una clase realiza un cálculo que depende de una regla de negocio cambiante (por ejemplo, una política de descuento), esta política debe extraerse en un objeto independiente o una función inyectada, de modo que pueda modificarse sin alterar la clase principal.

## 2. Programa a una interfaz, no a una implementación

### Motivación

Acoplar el código directamente a clases concretas dificulta el cambio y la reutilización: sustituir una implementación exige modificar el código cliente. Si el cliente trabaja con abstracciones, es posible sustituir implementaciones sin alterar el uso.

### Principio

Define las dependencias en términos de abstracciones, no de clases concretas.

### Ejemplo conceptual

Si un módulo necesita enviar notificaciones, no debe depender de `EmailSender` o `SmsSender`. En su lugar, depende de una interfaz abstracta `Notifier`, y la implementación concreta se inyecta cuando se construye el módulo.


## 3. Favorece la composición sobre la herencia

### Motivación
La herencia crea vínculos fuertes entre clases y puede generar jerarquías rígidas. La composición permite combinar comportamientos cambiantes mediante objetos independientes y sustituibles.

### Principio

Construye sistemas a partir de objetos que cooperan entre sí, en lugar de depender de jerarquías rígidas.

### Ejemplo conceptual

Si una clase debe registrar operaciones, no debería heredar de `Logger`. Es mejor recibir o almacenar un objeto `Logger` que se encargue del registro; así puede reemplazarse fácilmente por otro tipo de logger.


## 4. Favorece el acoplamiento débil

### Motivación
Un sistema donde los componentes conocen demasiados detalles internos es frágil y difícil de modificar. Reducir el acoplamiento facilita el mantenimiento, las pruebas y la reutilización.

### Principio

Diseña componentes que dependan lo menos posible de los detalles internos de otros componentes.

### Ejemplo conceptual

Si un componente necesita valores de configuración, no debe leer archivos directamente. En su lugar, recibe una abstracción que proporciona la configuración. Así puede cambiar la fuente (archivo, red, memoria, valores por defecto) sin modificar el componente.

