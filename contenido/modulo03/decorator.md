# Patrón Decorator

## Definición

El **Decorator** es un patrón de diseño estructural que permite **añadir responsabilidades o funcionalidades adicionales a un objeto de manera dinámica**, sin modificar su clase ni afectar a otros objetos de la misma jerarquía.
Para ello, encapsula el objeto original dentro de una estructura envolvente (*decorador*) que implementa la misma interfaz, delega en él la funcionalidad principal y añade comportamiento extra antes o después de esa delegación.

## Problemas que intenta solucionar

El patrón aborda principalmente estas situaciones:

* Se necesita **extender funcionalidades** de un objeto sin crear una gran cantidad de subclases mediante herencia (evitando la “explosión de clases”).
* La funcionalidad adicional debe poder aplicarse **selectivamente**, combinando decoradores de forma flexible.
* Se requiere añadir responsabilidades **en tiempo de ejecución**, no solo al momento de compilación.
* Se quiere evitar modificar código existente del componente base o de sus subclases (respetando el principio *Open/Closed*).
* Existen múltiples variantes de un mismo objeto que comparten comportamiento, pero se diferencian por pequeñas responsabilidades adicionales.
* Se busca una alternativa más flexible a la herencia para extender comportamientos, evitando acoplamiento rígido.

## Cómo lo soluciona

El Decorator proporciona estas soluciones:

* Define una **interfaz común** para el componente y sus decoradores, permitiendo que estos se intercambien sin romper el código cliente.
* Cada **decorador envuelve** un componente concreto y **delegará** en él la operación principal.
* Los decoradores pueden **añadir comportamiento antes o después** de llamar al componente envuelto.
* Los decoradores pueden **componerse entre sí**, creando cadenas flexibles de funcionalidad sin necesidad de herencia múltiple o proliferación de clases.
* Facilita el cumplimiento de *Open/Closed*: se agregan nuevas capacidades creando nuevos decoradores, sin modificar las clases base.
* Reduce el acoplamiento entre nuevas funcionalidades y los componentes originales.

## Ejemplos concretos

* **Streams y filtros de E/S** (similar al diseño de iostreams en C++): añadir compresión, cifrado, buffering, o logging a un flujo sin alterar su implementación base.
* **Interfaz de usuario**: agregar bordes, barras de desplazamiento o sombreado a widgets de forma dinámica.
* **Sistemas de notificación**: enviar un mensaje y decorarlo con notificación por email, SMS, o logging adicional.
* **Validación de datos**: añadir validaciones progresivas (longitud, formato, unicidad) sobre un validador base.
* **Sistemas de autenticación**: agregar capas adicionales como caching, auditoría o limitación de intentos.
* **Modelado de precios o impuestos**: aplicar recargos, descuentos o impuestos adicionales envolviendo un cálculo base.
* **Formatos de salida**: añadir características como numeración, resaltado o documentación adicional a un generador de texto.
* **Decoración en juegos**: aplicar efectos a un personaje (fuerza extra, defensa, invisibilidad) combinando decoradores de habilidades.

