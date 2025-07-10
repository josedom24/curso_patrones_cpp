#include <iostream>
#include <functional>

int aplicar_operacion(int a, int b, std::function<int(int, int)> operacion) {
    return operacion(a, b);
}

int main() {
    int x = 10;
    int y = 5;

    // Suma
    int suma = aplicar_operacion(x, y, [](int a, int b) {
        return a + b;
    });

    // Resta
    int resta = aplicar_operacion(x, y, [](int a, int b) {
        return a - b;
    });

    // Multiplicación
    int producto = aplicar_operacion(x, y, [](int a, int b) {
        return a * b;
    });

    std::cout << "Suma: " << suma << '\n';
    std::cout << "Resta: " << resta << '\n';
    std::cout << "Producto: " << producto << '\n';
}
