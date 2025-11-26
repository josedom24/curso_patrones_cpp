# Patrón Strategy

## Definición

El **Strategy** es un patrón de diseño de comportamiento que permite encapsular **algoritmos intercambiables** dentro de objetos independientes, proporcionando una interfaz común para todos ellos. Su objetivo es permitir que un objeto cambie su comportamiento en tiempo de ejecución delegando la operación a una estrategia seleccionada dinámicamente.

## Problemas que intenta solucionar

El patrón aborda principalmente estas situaciones:

* Un objeto necesita realizar una tarea cuyo **algoritmo puede variar**, pero mezclar todas las variantes dentro de la misma clase genera código rígido y difícil de mantener.
* Existen múltiples **condicionales (`if`/`switch`) que seleccionan una variante del algoritmo**, dispersos por el código cliente.
* Se quiere **evitar duplicación** de lógica cuando varias clases necesitan comportamientos similares pero con pequeñas variaciones.
* Es necesario **cambiar el comportamiento de un objeto en tiempo de ejecución**, sin reconstruirlo completamente ni usar herencia múltiple.
* El sistema debe ser **extensible**, permitiendo añadir nuevos algoritmos sin modificar el código ya existente, cumpliendo el principio *Open/Closed*.
* Se desea separar claramente la **lógica del algoritmo** de la clase que lo utiliza, favoreciendo la cohesión y la reutilización.

## Cómo lo soluciona C++ moderno

En C++ moderno, el patrón Strategy se implementa mediante **inyección de comportamiento**, evitando la necesidad de jerarquías de clases. El contexto recibe un *callable* que representa la estrategia, y ese callable puede adoptar distintas formas, todas intercambiables mientras cumplan la misma firma. Las técnicas principales, entre otras, son:

* **Lambdas**: expresiones concisas que permiten definir el comportamiento directamente en el lugar donde se necesita, con capacidad de capturar estado de forma controlada.
* **`std::function`**: contenedor genérico que permite almacenar cualquier callable compatible con la firma requerida, proporcionando polimorfismo dinámico sin necesidad de clases base.
* **Functores (objetos función)**: objetos que implementan `operator()`, útiles cuando la estrategia requiere mantener estado interno o cuando se busca mayor eficiencia evitando el coste de `std::function`.

En este enfoque, el contexto simplemente almacena y ejecuta el callable recibido, sin depender de una interfaz ni de una jerarquía de clases, lo que resulta en un diseño más flexible, más simple y más eficiente en C++ moderno.

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

