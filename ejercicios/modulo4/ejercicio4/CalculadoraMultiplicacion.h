#include "Calculadora.h"

// Implementación concreta de la interfaz Calculadora
class CalculadoraMultiplicacion : public Calculadora {
public:
    int calcular(int a, int b) const override {
        return a * b;
    }
};