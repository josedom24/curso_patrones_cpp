# Patrón Strategy

## Definición

El **Strategy** es un patrón de diseño de comportamiento que permite **definir algoritmos intercambiables** y encapsularlos de forma independiente, de modo que un objeto pueda **variar su comportamiento en tiempo de ejecución** delegando la operación en una estrategia seleccionada dinámicamente.


## Objetivos

* Permitir cambiar el **algoritmo o comportamiento** de un objeto sin modificar su código.
* Eliminar **condicionales** que seleccionan variantes de un algoritmo.
* Separar la **lógica del algoritmo** de la clase que lo utiliza.
* Facilitar la **extensión del sistema** añadiendo nuevos comportamientos sin alterar el código existente.

## Cuándo usarlo

El patrón Strategy es adecuado cuando:

* Un objeto puede realizar una operación de **distintas maneras** según el contexto.
* Existen varias variantes de un algoritmo que se seleccionan dinámicamente.
* Se quiere evitar herencia o grandes bloques de `if` / `switch`.
* El comportamiento debe poder **cambiarse en tiempo de ejecución**.

En muchos casos, especialmente en **C++ moderno**, no es necesario aplicar Strategy como patrón formal, sino simplemente **inyectar comportamiento** de forma flexible.

## Cómo se implementa en C++ moderno

En C++ moderno, Strategy se implementa habitualmente **sin jerarquías de clases**, utilizando mecanismos del lenguaje para pasar comportamiento como un objeto de primera clase.

Las formas más comunes son:

* **Lambdas**, para definir estrategias de forma concisa y local.
* **`std::function`**, para almacenar y cambiar dinámicamente cualquier callable con la firma adecuada.
* **Functores**, cuando la estrategia necesita estado interno o se busca mayor control sobre rendimiento.

El objeto que utiliza la estrategia (**contexto**) se limita a **almacenar y ejecutar el comportamiento recibido**, sin conocer su implementación concreta.

Este enfoque suele ser **más simple, más flexible y más eficiente** que la versión clásica basada en clases abstractas, y refleja mejor el estilo de diseño recomendado en C++ moderno.

## Ejemplos concretos

* **Cálculo de rutas**: Elegir entre rutas más rápidas, más cortas o que eviten autopistas en un sistema de navegación.
* **Compresión de archivos**: Seleccionar dinámicamente entre ZIP, RAR, TAR, GZIP u otros algoritmos.
* **Sistemas de pago**: Cambiar entre pago con tarjeta, PayPal, criptomonedas o transferencia bancaria.
* **Motores de IA en juegos**: Permitir que los personajes usen distintos comportamientos (agresivo, defensivo, evasivo) según la situación.
* **Validación de datos**: Usar diferentes estrategias de validación dependiendo del contexto o del tipo de entrada.
* **Formateadores de salida**: Convertir datos a JSON, XML, CSV o texto plano usando estrategias distintas.
* **Motores de ordenación**: Elegir algoritmos de ordenación óptimos según el tamaño o tipo de colección.
* **Sistemas de autenticación**: Probar distintos mecanismos (OAuth, JWT, contraseñas locales, certificados) mediante estrategias configurables.
* **Aplicaciones de análisis o simulación**: Permitir que cada experimento o escenario seleccione su algoritmo específico sin afectar al resto del sistema.
* **Frameworks de filtrado o transformación**: Aplicar filtros de imagen, audio o datos como estrategias intercambiables.

