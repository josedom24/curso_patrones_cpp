# SOLID: Principios de diseño orientado a objetos

Los principios SOLID constituyen un conjunto de cinco directrices fundamentales para diseñar sistemas orientados a objetos que sean flexibles, extensibles y fáciles de mantener. Propuestos inicialmente por Robert C. Martin (Uncle Bob), estos principios forman una base esencial para el diseño de software robusto y preparado para el cambio.

El acrónimo **SOLID** representa los siguientes principios:

* **S** – *Single Responsibility Principle* (Principio de Responsabilidad Única)
* **O** – *Open/Closed Principle* (Principio Abierto/Cerrado)
* **L** – *Liskov Substitution Principle* (Principio de Sustitución de Liskov)
* **I** – *Interface Segregation Principle* (Principio de Segregación de Interfaces)
* **D** – *Dependency Inversion Principle* (Principio de Inversión de Dependencias)

## S — Principio de Responsabilidad Única (SRP)

**Motivación:**
Cuando una clase tiene múltiples responsabilidades, cualquier cambio en una de ellas puede afectar negativamente a las demás. Esto conduce a diseños frágiles, difíciles de mantener y propensos a errores.

**Principio:**

> Una clase debe tener una y solo una razón para cambiar.

**Aplicación en C++ moderno (en términos generales):**

* Diseñar clases que encapsulen una única función o responsabilidad claramente definida.
* Separar la lógica de presentación, lógica de negocio y lógica de acceso a datos en componentes distintos.
* Delegar tareas a colaboradores especializados en lugar de centralizar toda la funcionalidad en una clase.

**Ejemplo conceptual:**
Un gestor de informes no debería encargarse de generar datos, formatearlos y enviarlos por correo. Cada una de estas responsabilidades debería estar en componentes separados.

## O — Principio Abierto/Cerrado (OCP)

**Motivación:**
Modificar el código existente para incorporar nuevos comportamientos puede introducir errores y romper funcionalidades previamente correctas. Es preferible diseñar el sistema para que sea extensible sin modificar lo ya existente.

**Principio:**

> El software debe estar abierto a la extensión, pero cerrado a la modificación.

**Aplicación en C++ moderno (en términos generales):**

* Utilizar herencia o composición para agregar nuevos comportamientos sin alterar el código base.
* Diseñar componentes que permitan ser configurados o ampliados mediante parámetros, punteros inteligentes o funciones personalizables.
* Aplicar plantillas o patrones de diseño (como Strategy o Decorator) para permitir extensión modular.

**Ejemplo conceptual:**
Un sistema de facturación debería permitir agregar nuevos tipos de impuestos sin tener que reescribir el cálculo original.

## L — Principio de Sustitución de Liskov (LSP)

**Motivación:**

> Las clases derivadas deben poder sustituir a sus clases base sin alterar el comportamiento esperado del programa.

**Aplicación en C++ moderno (en términos generales):**

* Diseñar jerarquías de clases donde las subclases respeten las reglas y contratos definidos por la clase base.
* Evitar sobrescribir métodos de forma que cambien significativamente su semántica.
* Usar clases abstractas bien definidas que impongan requisitos claros a sus implementaciones.

**Ejemplo conceptual:**
Si un algoritmo espera que un objeto `Figura` tenga un método `calcularÁrea`, entonces cualquier clase derivada (como `Círculo` o `Rectángulo`) debe proporcionar un resultado coherente, sin generar efectos colaterales inesperados.

## I — Principio de Segregación de Interfaces (ISP)

**Principio:**

> Es mejor tener muchas interfaces específicas que una interfaz general y extensa.

**Aplicación en C++ moderno (en términos generales):**

* Dividir interfaces grandes en pequeñas unidades funcionales enfocadas.
* Diseñar clases abstractas con responsabilidades bien delimitadas.
* Utilizar múltiples interfaces o plantillas para describir capacidades independientes.

**Ejemplo conceptual:**
Una impresora multifunción no debería verse obligada a implementar métodos de fax si solo necesita imprimir. Es preferible tener interfaces separadas para impresión, escaneo y fax.

## D — Principio de Inversión de Dependencias (DIP)

**Motivación:**
El diseño tradicional hace que los módulos de alto nivel dependan de módulos de bajo nivel. Esto hace que el código sea rígido y difícil de probar o reutilizar. Invertir la dependencia permite desacoplar > Los módulos de alto nivel no deben depender de módulos de bajo nivel. Ambos deben depender de abstracciones.

**Aplicación en C++ moderno (en términos generales):**

* Inyectar dependencias mediante constructores, funciones o punteros inteligentes.
* Definir las dependencias del sistema como interfaces o funciones abstractas.
* Permitir que los componentes utilicen implementaciones concretas configurables desde el exterior.

**Ejemplo conceptual:**
Un sistema de notificaciones no debería depender directamente de una clase `Correo`. En su lugar, debería depender de una interfaz `Notificador`, permitiendo intercambiar correo, SMS o notificaciones push sin alterar la lógica de negocio.

## Resumen

| Principio | Nombre                    | Idea clave                                                    |
| --------- | ------------------------- | ------------------------------------------------------------- |
| S         | Responsabilidad Única     | Cada clase debe tener una única razón para cambiar.           |
| O         | Abierto/Cerrado           | Extiende el comportamiento sin modificar el código existente. |
| L         | Sustitución de Liskov     | Las subclases deben poder sustituir a las clases base.        |
| I         | Segregación de Interfaces | Prefiere interfaces pequeñas y específicas.                   |
| D         | Inversión de Dependencias | Los módulos deben depender de abstracciones, no de detalles.  |

