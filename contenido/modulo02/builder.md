# Patrón Builder

## Definición

El **Builder** es un patrón de diseño creacional que separa la **construcción compleja de un objeto** de su **representación final**, permitiendo crear objetos paso a paso y ofrecer múltiples configuraciones sin necesidad de constructores largos, difíciles de mantener o propensos a errores.
El patrón centraliza la lógica de construcción en un objeto *builder*, mientras que el objeto final (el *producto*) permanece independiente del procedimiento concreto seguido para generarlo.

## Problemas que intenta solucionar

El patrón Builder es especialmente útil cuando se presentan estas situaciones:

* El objeto a construir tiene **muchos parámetros opcionales**, condicionales o dependientes entre sí.
* Existen **múltiples configuraciones válidas de un mismo objeto**, lo que puede llevar a constructores difíciles de mantener o a un uso excesivo de parámetros por defecto.
* Se quiere mantener el **estado interno del objeto en construcción** consistente durante todas las fases del proceso.
* La creación del objeto involucra **varios pasos** (validaciones, cálculos intermedios, inicializaciones específicas) que no deberían quedar expuestos al cliente.
* La construcción del objeto debe ser **reutilizable** en distintos contextos o escenarios.
* Se desea permitir **diferentes representaciones** del mismo objeto siguiendo los mismos pasos de construcción (p.ej., construir un documento en formato HTML, texto o JSON).

## Cómo lo soluciona

El patrón Builder aborda estos problemas mediante:

* La definición de un **builder** que ofrece métodos para configurar el producto paso a paso.
* La existencia de un **director** (opcional) que orquesta la secuencia de pasos necesaria para construir productos complejos.
* La separación clara entre el **proceso de construcción** y el **producto final**, lo que permite que distintas implementaciones del builder generen objetos distintos.
* La encapsulación completa de la lógica de inicialización, validación y ensamblaje del objeto.
* La posibilidad de crear objetos **inmutables**, ya que el producto se configura completamente antes de ser construido.
* La flexibilidad para crear múltiples variantes del mismo producto sin modificar el código cliente ni saturar la clase del producto con múltiples constructores sobrecargados.

## Ejemplos concretos

* **Construcción de documentos**: Crear informes en HTML, JSON o texto plano usando los mismos pasos pero builders distintos.
* **Generación de objetos de configuración**: Sistemas donde distintos módulos requieren configuraciones detalladas pero opcionales.
* **Creación de entidades complejas en videojuegos**: Personajes, niveles o misiones que requieren muchos parámetros opcionales (atributos, inventario, IA, animaciones).
* **Sistemas de construcción de consultas**: *Query builders* que generan SQL, expresiones lógicas o pipelines de filtrado sin que el usuario deba escribir la sintaxis completa.
* **Inicialización de objetos de red**: Configurar conexiones complejas (TLS, certificados, políticas de reintentos, timeouts) paso a paso.
* **Procesamiento de datos**: Construcción de pipelines con pasos opcionales de validación, limpieza, normalización o transformación.
* **Serializadores**: Generar diversas representaciones del mismo conjunto de datos (p.ej., XML, JSON, YAML) desde un procedimiento de construcción común.
* **Interfaces fluidas (fluent interfaces)**: Objetos que se construyen encadenando métodos de forma expresiva y segura.
* **Builders de escenarios o configuraciones en tests**: Facilitan la creación de objetos con valores predeterminados, sobrescribibles y fiables para pruebas unitarias.
* **Montaje de interfaces gráficas**: Construcción incremental de ventanas, paneles y widgets, especialmente cuando la inicialización no es trivial.
