# Patrón Chain of Responsibility

## Definición

El **Chain of Responsibility** es un patrón de diseño de comportamiento que organiza una secuencia de objetos (manejadores) por la que circulan peticiones. Cada objeto de la cadena decide si **procesar** la petición o **delegarla** al siguiente manejador. Su propósito es **desacoplar el emisor de la petición del receptor final**, permitiendo que múltiples objetos tengan la oportunidad de gestionarla sin que el código cliente conozca cuál será el responsable último.

## Problemas que intenta solucionar

El patrón aborda principalmente estas situaciones:

* El código cliente depende directamente de un receptor específico y se desea eliminar ese acoplamiento.
* Es necesario otorgar a **varios objetos** la posibilidad de procesar una petición, sin imponer un orden rígido en el código cliente.
* Se busca evitar estructuras extensas de `if`/`else if`/`switch` en las que se comprueban condiciones para decidir qué objeto debe manejar la petición.
* La responsabilidad de procesar una petición puede **cambiar dinámicamente** en tiempo de ejecución o según la configuración.
* Se requiere añadir nuevos manejadores sin modificar el código que emite o distribuye las peticiones, respetando el principio *Open/Closed*.
* Se quiere permitir cadenas de procesamiento flexible, donde una petición pueda ser absorbida por un manejador, modificada, transformada o propagada.

## Cómo lo soluciona

El Chain of Responsibility aporta estas soluciones:

* Define una **interfaz común de manejador**, que incluye un método para procesar peticiones y un enlace al **siguiente manejador** de la cadena.
* Permite construir cadenas **dinámicas**, en las que los manejadores pueden conectarse, desconectarse o reordenarse sin afectar al cliente.
* Cada manejador decide si procesa la petición o si la **pasa al siguiente**, reduciendo drásticamente el acoplamiento entre emisor y receptor.
* Facilita la **extensibilidad**: nuevos manejadores pueden añadirse sin tocar el código existente, solo insertándolos en la cadena.
* Encapsula condiciones de manejo dentro de cada objeto, eliminando estructuras condicionales masivas en el código cliente.
* Refuerza el principio *Open/Closed* y promueve una arquitectura modular donde se pueden combinar responsabilidades mediante composición.

## Ejemplos concretos

* **Sistemas de validación**: Validadores encadenados donde cada uno comprueba un aspecto (formato, permisos, límites, existencia). Si uno falla, detiene la cadena.
* **Procesadores de eventos en interfaces gráficas**: Un evento (clic, teclado) se propaga por una jerarquía de widgets hasta que uno lo consume.
* **Filtros en servidores web**: Módulos que procesan una petición HTTP (autenticación, logging, compresión) antes de llegar al controlador principal.
* **Sistemas de logging**: Distintos manejadores (consola, archivo, red) pueden recibir un mensaje y decidir si lo procesan o lo pasan al siguiente.
* **Manejo de excepciones en tiempo de ejecución**: Cadena de bloques o componentes que intentan gestionar un error específico.
* **Procesamiento de comandos en juegos**: Una acción del jugador se transmite a distintos subsistemas (inventario, combate, diálogo) hasta que uno la reconoce.
* **Sistemas de permisos y autorización**: Cada manejador examina un nivel de autorización distinto y decide si concede acceso o pasa la petición a niveles superiores.
* **Procesamiento de datos en pipelines**: Cada etapa transforma o filtra los datos antes de pasar al siguiente paso del pipeline.
* **Routers o middleware en frameworks web**: Cada componente examina la ruta o cabeceras y decide si atiende la petición o delega más adelante.
* **Frameworks de análisis y depuración**: Módulos que inspeccionan, anotan o transforman trazas o mensajes en una cadena de responsabilidad configurable.
