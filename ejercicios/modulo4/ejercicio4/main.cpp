#include "CalculadoraMultiplicacion.h"  //  Incluir la clase concreta
#include <iostream>
#include <memory>

// Declaramos la clase aquí para poder crear instancias, o se podría incluir otro .h
class CalculadoraMultiplicacion;  // Declaración anticipada para que compile

int main() {
    // Creamos un puntero a la interfaz, pero instanciamos la implementación concreta
    std::unique_ptr<Calculadora> calc = std::make_unique<CalculadoraMultiplicacion>();

    int resultado = calc->calcular(6, 7);
    std::cout << "Resultado: " << resultado << '\n';  // Salida: Resultado: 42

    return 0;
}