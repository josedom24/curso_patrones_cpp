#include <iostream>
#include <string>

class Configuracion {
private:
    std::string parametros_;

    // Constructor privado: evita instanciación directa
    Configuracion(const std::string& p) : parametros_(p) {}

public:
    // Método para mostrar la configuración
    void mostrar() const {
        std::cout << "Parámetros: " << parametros_ << '\n';
    }

    // Prohibir copia y asignación
    Configuracion(const Configuracion&) = delete;
    Configuracion& operator=(const Configuracion&) = delete;

    // Función estática que actúa como "fábrica"
    static Configuracion cargarDesdeArchivo() {
        // Aquí simularíamos la lectura desde un archivo
        std::string datosSimulados = "modo=produccion;cache=true";
        std::cout << "Cargando configuración desde archivo...\n";
        return Configuracion(datosSimulados);
    }
};

int main() {
    // Configuracion c1("manual"); // Error: constructor privado

    // Crear objeto solo desde función controlada
    Configuracion cfg = Configuracion::cargarDesdeArchivo();
    cfg.mostrar();

    // Configuracion copia = cfg; // Error: copia eliminada
}
