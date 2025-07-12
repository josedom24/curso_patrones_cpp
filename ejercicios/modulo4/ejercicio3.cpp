#include <iostream>
#include <vector>
#include <memory>

// Interfaz pura: solo métodos virtuales puros
class Reproducible {
public:
    virtual void reproducir() const = 0;  // Método virtual puro
    virtual ~Reproducible() = default;    // Destructor virtual necesario
};

// Clase concreta que implementa la interfaz
class Radio : public Reproducible {
public:
    void reproducir() const override {    // override asegura correcta sobrescritura
        std::cout << "Reproduciendo música en la radio\n";
    }
};

// Otra clase concreta que implementa la interfaz
class Televisor : public Reproducible {
public:
    void reproducir() const override {
        std::cout << "Reproduciendo sonido del televisor\n";
    }
};

// Función que trabaja con la interfaz pura
void iniciarReproduccion(const std::vector<std::unique_ptr<Reproducible>>& dispositivos) {
    for (const auto& dispositivo : dispositivos) {
        dispositivo->reproducir();  // Llamada polimórfica al método reproducir()
    }
}

int main() {
    std::vector<std::unique_ptr<Reproducible>> aparatos;

    aparatos.push_back(std::make_unique<Radio>());
    aparatos.push_back(std::make_unique<Televisor>());

    iniciarReproduccion(aparatos);

    return 0;
}
