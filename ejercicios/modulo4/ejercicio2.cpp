#include <iostream>
#include <memory>
#include <vector>

// Clase abstracta que representa un instrumento musical
class Instrumento {
public:
    virtual void tocar() const = 0;   // Método virtual puro → interfaz obligatoria
    virtual ~Instrumento() = default; // Destructor virtual obligatorio para jerarquías
};

// Clase concreta que representa un piano
class Piano : public Instrumento {
public:
    void tocar() const override {     // override asegura que se sobrescribe correctamente
        std::cout << "El piano toca una melodía clásica.\n";
    }
};

// Clase concreta que representa una guitarra
class Guitarra : public Instrumento {
public:
    void tocar() const override {     // override también aquí
        std::cout << "La guitarra toca un solo de rock.\n";
    }
};

int main() {
    // Creamos un vector de punteros inteligentes a Instrumento
    std::vector<std::unique_ptr<Instrumento>> orquesta;

    // Añadimos diferentes instrumentos a la colección
    orquesta.push_back(std::make_unique<Piano>());
    orquesta.push_back(std::make_unique<Guitarra>());

    // Recorremos la colección y tocamos cada instrumento
    for (const auto& instrumento : orquesta) {
        instrumento->tocar();  // Llamada polimórfica: se ejecuta la versión correcta
    }

    return 0;
}
