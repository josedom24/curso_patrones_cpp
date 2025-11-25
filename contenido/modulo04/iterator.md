# Patrón Iterator

## Definición

El **Iterator** es un patrón de diseño conductual que proporciona una forma uniforme de recorrer los elementos de una colección **sin exponer su representación interna**.
Permite acceder secuencialmente a los elementos de un contenedor (listas, árboles, colecciones personalizadas,...) mediante un objeto iterador dedicado, aislando al código cliente de los detalles estructurales.

## Problemas que intenta solucionar

El patrón aborda principalmente estas situaciones:

* El código cliente necesita recorrer una colección, pero **no debería depender** de cómo está implementada internamente (lista enlazada, vector dinámico, árbol, grafo...).
* Cada colección tiene su propia lógica de recorrido; mezclarla con el código cliente **incrementa el acoplamiento**.
* Se desea **unificar la forma de iterar** sobre tipos de colecciones distintas.
* Las colecciones pueden necesitar **distintos tipos de recorrido** (hacia adelante, hacia atrás, por niveles, en profundidad…), sin que el cliente deba conocer cómo se implementa cada uno.
* Se busca aplicar el principio *Single Responsibility*: la colección gestiona almacenamiento, el iterador gestiona recorrido.
* Se quiere evitar exponer métodos peligrosos o innecesarios que revelen detalles internos (como punteros o nodos específicos).

## Cómo lo soluciona

El patrón Iterator aporta estas soluciones:

* Define una interfaz común de iteración (por ejemplo, `first()`, `next()`, `is_done()`, `current()` o equivalentes modernos).
* Traslada la **lógica de recorrido** a un objeto iterador separado, manteniendo la colección encapsulada.
* Permite implementar varios iteradores para una misma colección, cada uno con una estrategia distinta de recorrido.
* Facilita sustituir o extender las estructuras internas de la colección **sin afectar al código cliente**.
* Unifica y hace explícito el proceso de iteración, mejorando la legibilidad y la mantenibilidad.
* Refuerza *Open/Closed*, ya que se pueden crear nuevos iteradores sin modificar la colección ni el código cliente.

## Ejemplos concretos

* **Recorrido de colecciones personalizadas**: Listas, árboles binarios, grafos, buffers circulares o estructuras no lineales definidas por el usuario.
* **Sistemas de archivos**: Iteradores que recorren directorios en profundidad (`DFS`) o en anchura (`BFS`).
* **Motores de juegos**: Recorrer entidades en una escena (por ejemplo, todos los objetos dibujables o todos los objetos con física).
* **Frameworks de UI**: Iterar sobre los elementos hijos de un widget compuesto.
* **Bases de datos en memoria**: Proveer iteradores para recorrer filas filtradas o agrupadas sin exponer estructuras internas.
* **Sistemas de escenas o gráficos**: Recorrido ordenado de nodos de un árbol de transformación o escena.
* **Aplicaciones de análisis**: Iterar sobre colecciones complejas de métricas, eventos o trazas utilizando distintos criterios.
* **Contenedores de red o protocolos**: Iterar sobre paquetes recibidos, segmentos o mensajes en orden de llegada o según prioridad.
* **Sistemas de configuración**: Recorrer claves y valores de configuraciones jerárquicas o anidadas mediante iteradores especializados.
* **Lenguajes de scripting embebidos**: Implementar iteradores propios que permitan a los scripts recorrer estructuras del core sin exponer su implementación.
