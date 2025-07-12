#include <iostream>
#include <memory>
#include <vector>

// Clase base abstracta
class Instrumento {
public:
    virtual void tocar() const = 0; // Método virtual puro
    virtual ~Instrumento() = default; // Destructor virtual
};

// Clase derivada: Piano
class Piano final : public Instrumento {
public:
    void tocar() const final override { // Método final: no se puede sobrescribir más
        std::cout << "El piano está tocando una melodía clásica.\n";
    }
};

// Clase derivada: Guitarra
class Guitarra : public Instrumento {
public:
    void tocar() const override {
        std::cout << "La guitarra está tocando un solo de rock.\n";
    }
};

int main() {
    std::vector<std::unique_ptr<Instrumento>> orquesta;

    orquesta.push_back(std::make_unique<Piano>());
    orquesta.push_back(std::make_unique<Guitarra>());

    for (const auto& instrumento : orquesta) {
        instrumento->tocar();
    }

    return 0;
}
