#include <iostream>
#include <vector>
#include <string>
#include <functional>

class FiltroMensajes {
public:
    FiltroMensajes(std::vector<std::string> mensajes,
                   std::function<bool(const std::string&)> filtro)
        : mensajes_(std::move(mensajes)), filtro_(std::move(filtro)) {}

    void mostrarFiltrados() const {
        for (const auto& mensaje : mensajes_) {
            if (filtro_(mensaje)) {
                std::cout << mensaje << '\n';
            }
        }
    }

private:
    std::vector<std::string> mensajes_;
    std::function<bool(const std::string&)> filtro_;
};


int main() {
    std::vector<std::string> mensajes = {
        "Error: conexión fallida",
        "Aviso: batería baja",
        "Info: actualización completada",
        "Error: disco lleno",
        "Info: sesión iniciada"
    };

    // Mostrar solo mensajes de error
    FiltroMensajes soloErrores(mensajes, [](const std::string& msg) {
        return msg.find("Error") == 0;  // Comienza con "Error"
    });

    std::cout << "Mensajes de error:\n";
    soloErrores.mostrarFiltrados();

    // Mostrar solo mensajes informativos
    FiltroMensajes soloInfo(mensajes, [](const std::string& msg) {
        return msg.find("Info") == 0;  // Comienza con "Info"
    });

    std::cout << "\nMensajes informativos:\n";
    soloInfo.mostrarFiltrados();
}
