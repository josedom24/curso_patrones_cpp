# Patrón Prototype

## Definición

El **Prototype** es un patrón de diseño creacional que permite **crear nuevos objetos mediante la clonación de instancias existentes**, denominadas *prototipos*. Para ello se basa en mecanismos de copia —**superficial** y **profunda**—:
*La copia superficial* duplica únicamente los valores de los miembros, pero mantiene compartidos los recursos dinámicos;
*la copia profunda*, en cambio, crea duplicados independientes de dichos recursos.

En lugar de instanciar objetos directamente mediante constructores, el patrón delega la creación a un método de clonación que cada clase concreta implementa según sus necesidades. Su propósito es **desacoplar y simplificar la creación** de objetos configurados, costosos o estructuralmente complejos.

## Problemas que intenta solucionar

El patrón Prototype resulta adecuado en los siguientes escenarios:

* **Creación costosa de objetos**: Inicializaciones complejas, cálculos intensivos o cargas desde archivos o bases de datos.
* **Generación repetida de variaciones** de un mismo tipo de objeto sin recurrir a múltiples constructores ni configuraciones duplicadas.
* **Sistemas que deben operar con objetos sin conocer su clase concreta**, cumpliendo el principio de *programar a una interfaz*.
* **Necesidad de copiar estructuras con agregación o composición**, donde se requiere un control explícito sobre el tipo de copia.
* **Eliminación de condicionales extensos (`if`/`switch`)** implicados en la selección del tipo a crear.
* **Extensibilidad** del sistema sin modificar código cliente, respetando el principio *Open/Closed*.

## Cómo lo soluciona

El Prototype aporta estas soluciones esenciales:

* Define una **interfaz común de clonación** (típicamente un método virtual `clone()`).
* Cada clase concreta implementa su **propia lógica de copia**, ya sea superficial o profunda.
* Evita que el código cliente conozca detalles sobre **constructores concretos** o sobre cómo se crean internamente los objetos.
* Simplifica la **duplicación de objetos complejos** con estado interno o múltiples dependencias.
* Permite almacenar y gestionar un **catálogo de prototipos** para crear nuevas instancias de manera uniforme.
* Facilita la creación de instancias **preconfiguradas**, eliminando código repetido de inicialización.

## Ejemplos concretos

Casos reales donde el patrón Prototype resulta especialmente útil:

* **Aplicaciones de edición gráfica**: Duplicar formas, iconos o elementos estilizados conservando propiedades visuales y comportamientos.
* **Motores de videojuegos**: Crear enemigos, efectos, proyectiles o elementos repetitivos partiendo de prototipos con parámetros ya definidos.
* **Sistemas de documentos**: Replicar páginas, bloques de texto o plantillas complejas sin reconstruir toda su jerarquía interna.
* **Escenas y modelos 3D**: Generar copias de objetos geométricos o entidades con configuraciones base compartidas.
* **Aplicaciones empresariales**: Clonar estructuras de configuración o entidades con inicializaciones costosas.
* **Interfaces gráficas**: Reutilizar widgets preconfigurados o elementos compuestos.
* **Frameworks orientados a plugins**: Instanciar componentes registrados como prototipos sin depender de su tipo concreto.
* **Simulaciones científicas o de eventos**: Replicar entidades complejas para evaluar múltiples variantes de un escenario.

