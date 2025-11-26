# Patrón Flyweight

## Definición

El **Flyweight** es un patrón de diseño estructural que permite **compartir objetos de manera eficiente** cuando son necesarios en grandes cantidades, especialmente cuando contienen partes **intrínsecas** (invariables y compartibles) y partes **extrínsecas** (variables y dependientes del contexto).
Su propósito principal es **reducir el consumo de memoria** y el coste de creación de objetos cuando muchas instancias comparten datos idénticos.

## Problemas que intenta solucionar

El patrón Flyweight aborda principalmente estas situaciones:

* Se necesitan **miles o millones de objetos** que comparten la mayor parte de su estado.
* El sistema presenta **problemas de rendimiento o memoria** debido a la creación repetida de objetos idénticos.
* El estado común entre objetos está **duplicado sin necesidad**, aumentando el coste de almacenamiento.
* Se quiere **separar el estado invariable del estado variable**, evitando que cada instancia almacene información redundante.
* Es necesario **reutilizar** objetos ya existentes para minimizar la carga sobre el recolector de memoria o el gestor de recursos del sistema.

## Cómo lo soluciona

El Flyweight aporta estas soluciones:

* Divide el estado de un objeto en dos partes:

  * **Estado intrínseco**: inmutable, compartido por muchas instancias.
  * **Estado extrínseco**: provisto externamente según el contexto.
* Centraliza la creación de objetos intrínsecos mediante un **Flyweight Factory** que:

  * Devuelve un objeto ya existente si coincide su estado intrínseco.
  * Crea uno nuevo solo cuando es estrictamente necesario.
* Permite que el código cliente **utilice los objetos como si fueran independientes**, aunque internamente estén compartidos.
* Disminuye drásticamente:

  * El número de instancias creadas.
  * El uso de memoria.
  * El tiempo de creación y destrucción de objetos.
* Facilita el cumplimiento del **principio de reutilización de objetos**, un precursor conceptual del *object pooling*.

## Ejemplos concretos

* **Motores gráficos**: Sprites, texturas, partículas o caracteres renderizados (p. ej., cada letra en un editor de texto).
* **Representación de texto** (*glyphs*): Cada carácter del alfabeto es un flyweight; su posición y estilo concreto son extrínsecos.
* **Juegos**: Enemigos genéricos con apariencia compartida; lo único que cambia es su posición o estado de vida.
* **Sistemas de mapas**: Elementos repetidos (árboles, rocas, edificios) cuyos gráficos son idénticos.
* **Modelado 3D o CAD**: Piezas estándar reutilizadas en múltiples conjuntos.
* **Compiladores e intérpretes**: Internación de cadenas (*string interning*) para evitar duplicados.
* **Aplicaciones con grandes conjuntos de datos**: Nodos de árboles o grafos masivos que comparten etiquetas o tipos comunes.
* **Documentos estructurados**: Estilos o formatos que se aplican a elementos múltiples sin duplicar información.

