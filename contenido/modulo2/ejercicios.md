# Ejercicios sobre abstracción de comportamiento

## Ejercicio 1
 
Escriba una función `filtrar` que reciba un vector de enteros y una lambda como condición. La función debe devolver un nuevo vector que contenga solo los elementos que cumplen la condición.

En el programa principal, utiliza la función para filtrar los números pares y los números mayores de 5.

## Ejercicio 2

Implementa una clase `FiltroMensajes` que recibe un vector de strings y una función lambda que decide si un mensaje debe mostrarse. El método `mostrarFiltrados` imprime solo los mensajes que pasan el filtro.

## Ejercicio 3

Implemente una función `aplicar_operacion` que reciba dos enteros y una operación (sumar, restar, etc.) como `std::function<int(int,int)>`, y devuelva el resultado.

## Ejercicio 4

Implemente una clase `FiltroMultiplo` que sea una functora que filtre e imprima solo los valores múltiplos de un número dado. Luego, utilice una lambda equivalente para hacer lo mismo.