# Ejercicios sobre 

## Ejercicio 1: Control de creación y prohibición de copia en una clase de configuración

Implemente una clase `Configuracion` que represente los parámetros de configuración de un sistema. Esta clase debe cumplir los siguientes requisitos:

1. No debe poder ser instanciada directamente desde `main`, solo a través de una función estática `Configuracion::cargarDesdeArchivo()`, que simula la carga desde un archivo de configuración.
2. Debe prohibirse la copia y la asignación de objetos `Configuracion`.
3. Debe contener un método `mostrar()` que imprima los parámetros cargados (por simplicidad, solo una cadena descriptiva).

## Ejercicio 2: Jerarquía de clases

Define una jerarquía de clases para representar diferentes tipos de **instrumentos musicales**. Todos los instrumentos deben poder "tocar", pero cada uno lo hará de manera diferente.

1. Define una **clase abstracta** `Instrumento` que contenga un método virtual puro llamado `tocar() const`.
2. Deriva dos clases concretas: `Piano` y `Guitarra`, que implementen el método `tocar()` con un mensaje específico para cada instrumento.
3. Crea una colección de instrumentos (usando `std::vector<std::unique_ptr<Instrumento>>`) e incluye instancias de `Piano` y `Guitarra`.
4. Recorre la colección y llama al método `tocar()` de cada instrumento.
5. Usa correctamente `override` y un destructor virtual en la clase base.

## Ejercicios 3: Interfaces puras

Crea una interfaz pura llamada `Reproducible` que defina la capacidad de reproducir sonidos mediante un método `reproducir() const`.

1. Define la interfaz pura `Reproducible` con un método virtual puro `reproducir() const`.
2. Implementa dos clases concretas que implementen esta interfaz:

   * `Radio` que imprima `"Reproduciendo música en la radio"`.
   * `Televisor` que imprima `"Reproduciendo sonido del televisor"`.
3. Crea un vector de punteros inteligentes a `Reproducible` y almacena instancias de `Radio` y `Televisor`.
4. Implementa una función `iniciarReproduccion` que reciba una referencia a este vector y llame a `reproducir()` en cada objeto.
5. Asegúrate de usar `override` y un destructor virtual adecuado.

## Ejercicio 4: Separación entre interfaz y detalle de implementación

Organiza el diseño de una interfaz pura `Calculadora` y una clase concreta `CalculadoraMultiplicacion` que implemente esta interfaz, separando la declaración y la implementación en archivos `.h` y `.cpp` según las buenas prácticas.

1. En el archivo `Calculadora.h` declara la interfaz pura `Calculadora` con un método virtual puro `calcular(int a, int b) const`.
2. En el archivo `CalculadoraMultiplicacion.cpp` implementa la clase `CalculadoraMultiplicacion` que herede de `Calculadora` y devuelva el producto de los dos enteros.
3. En un archivo `main.cpp`, crea un objeto `CalculadoraMultiplicacion` a través de un puntero a `Calculadora` y muestra el resultado de multiplicar dos números.

