#include <iostream>
#include <vector>
#include <functional>

// Función general para filtrar enteros según una condición
std::vector<int> filtrar(const std::vector<int>& datos, std::function<bool(int)> condicion) {
    std::vector<int> resultado;

    for (int valor : datos) {int main() {
    std::vector<int> datos = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Filtrar los pares
    auto pares = filtrar(datos, [](int x) {
        return x % 2 == 0;
    });

    std::cout << "Números pares: ";
    for (int n : pares) {
        std::cout << n << ' ';
    }
    std::cout << '\n';

    // Filtrar los mayores que 5
    auto mayores = filtrar(datos, [](int x) {
        return x > 5;
    });

    std::cout << "Mayores que 5: ";
    for (int n : mayores) {
        std::cout << n << ' ';
    }
    std::cout << '\n';
}

        if (condicion(valor)) {
            resultado.push_back(valor);
        }
    }

    return resultado;
}


