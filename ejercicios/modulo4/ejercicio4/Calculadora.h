#pragma once //Debe ser incluido solo una vez durante la compilación

class Calculadora {
public:
    virtual int calcular(int a, int b) const = 0; // Método virtual puro
    virtual ~Calculadora() = default;              // Destructor virtual
};