#include <iostream>
#include <vector>

class FiltroMultiplo {
public:
    explicit FiltroMultiplo(int divisor) : divisor_(divisor) {}

    bool operator()(int valor) const {
        return valor % divisor_ == 0;
    }

private:
    int divisor_;
};


int main() {
    std::vector<int> numeros = {3, 4, 5, 6, 7, 8, 9, 10, 12};

    FiltroMultiplo esMultiploDe3(3);

    std::cout << "Múltiplos de 3 (functora): ";
    for (int n : numeros) {
        if (esMultiploDe3(n)) {
            std::cout << n << ' ';
        }
    }
    std::cout << '\n';
