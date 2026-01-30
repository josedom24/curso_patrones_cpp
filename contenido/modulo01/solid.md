## SOLID: Principios de diseño orientado a objetos

Los principios SOLID constituyen un conjunto de cinco directrices fundamentales para diseñar sistemas orientados a objetos que sean **flexibles**, **extensibles** y **fáciles de mantener**. Propuestos originalmente por Robert C. Martin (Uncle Bob), estos principios permiten reducir el acoplamiento, mejorar la cohesión y facilitar la evolución del software.

El acrónimo **SOLID** representa los siguientes principios:

* **S**: *Single Responsibility Principle* (Responsabilidad Única)
* **O**: *Open/Closed Principle* (Abierto/Cerrado)
* **L**: *Liskov Substitution Principle* (Sustitución de Liskov)
* **I**: *Interface Segregation Principle* (Segregación de Interfaces)
* **D**: *Dependency Inversion Principle* (Inversión de Dependencias)


## S: Principio de Responsabilidad Única (SRP)

### Motivación
Una clase con múltiples responsabilidades tiende a volverse frágil: cambios en una de sus funciones afectan a otras y dificultan la evolución del sistema. La cohesión se debilita y aumenta la complejidad accidental.

### Principio

Una clase debe tener una y solo una razón para cambiar.

### Ejemplo conceptual

Un componente que genera informes no debería encargarse también de enviarlos o almacenarlos. Cada responsabilidad corresponde a un módulo distinto.

## O: Principio Abierto/Cerrado (OCP)

### Motivación
Modificar código existente para añadir nuevos comportamientos aumenta el riesgo de introducir errores y romper funcionalidad previa. Los sistemas deben estar diseñados para poder **extenderse sin modificar** su código base.

### Principio

Los componentes deben estar abiertos a la extensión, pero cerrados a la modificación.

### Ejemplo conceptual

Un módulo de cálculo de impuestos debería permitir añadir nuevos tipos impositivos mediante nuevas clases o funciones, sin modificar el cálculo original.

## L: Principio de Sustitución de Liskov (LSP)

### Motivación

Las clases derivadas deben poder reemplazar a sus clases base sin alterar el comportamiento esperado del programa.

Este principio asegura que una jerarquía de clases sea coherente: si un cliente trabaja con una interfaz o clase base, debe poder utilizar cualquier implementación concreta sin sorpresas.

### Ejemplo conceptual

Si un algoritmo espera un objeto `Figura` con `calcular_area()`, entonces `Circulo`, `Rectangulo` o cualquier otra figura deben cumplir esa interfaz sin producir efectos inesperados.

## I: Principio de Segregación de Interfaces (ISP)

### Motivación

Las interfaces demasiado grandes obligan a las clases que las implementan a depender de métodos que no necesitan. Esto aumenta el acoplamiento y reduce la cohesión.

### Principio

Es preferible tener muchas interfaces pequeñas y específicas antes que una interfaz general y extensa.

### Ejemplo conceptual

Una impresora multifunción no debería estar obligada a implementar métodos de fax si solo imprime. Separar interfaces de impresión, escaneo y fax permite implementaciones más limpias.

## D: Principio de Inversión de Dependencias (DIP)

### Motivación

En un diseño tradicional, los módulos de alto nivel dependen directamente de módulos de bajo nivel. Esto produce un sistema rígido, difícil de probar y de extender. El principio DIP invierte esta tendencia. 

### Principio

Los módulos de alto nivel no deben depender de módulos de bajo nivel. Ambos deben depender de abstracciones. Las abstracciones deben mantenerse estables y no depender de implementaciones concretas.

### Ejemplo conceptual

Un sistema de notificaciones debería depender de una interfaz `Notificador`, no de una clase concreta `Correo`. Esto permite sustituir correo por SMS o notificaciones push sin modificar la lógica de negocio.

