# Implementación de Proxy con C++

## Estructura general

La implementación del **Proxy** en C++ moderno permite **controlar el acceso a un objeto** proporcionando un intermediario que implementa la misma interfaz que el objeto real. El cliente interactúa con la interfaz; en tiempo de ejecución puede recibir un proxy o el objeto real.

Este enfoque permite introducir control de acceso, inicialización diferida o lógica adicional sin modificar la implementación original del objeto real.

## Elementos de C++ moderno utilizados

* **Clases abstractas e interfaces puras** para definir un contrato común entre proxy y objeto real.
* **Métodos virtuales y virtuales puros** para permitir sustitución transparente.
* **Polimorfismo dinámico** para que el cliente no distinga entre proxy y objeto real.
* **Destructores virtuales** para destrucción segura mediante punteros a la interfaz.
* **Composición** para encapsular el objeto real dentro del proxy.
* **`std::unique_ptr`** para expresar propiedad exclusiva del objeto real.
* **RAII** para gestionar correctamente los recursos asociados al objeto real.
* **Inicialización diferida** del objeto real mediante creación bajo demanda.

## Componentes del patrón y responsabilidades

### 1. Interfaz común (**Sujeto**)

* Define las operaciones que deben implementar tanto el proxy como el objeto real.
* Establece un contrato único e independiente de las implementaciones concretas.
* Permite al cliente trabajar sin conocer la clase concreta utilizada.
* Se utiliza de forma polimórfica mediante punteros o referencias.

### 2. **Objeto real**

* Implementa la funcionalidad completa del sistema.
* Puede representar un recurso costoso, remoto o restringido.
* Encapsula el comportamiento real sin conocer la existencia del proxy.
* Gestiona sus recursos de forma segura mediante RAII.

### 3. **Proxy**

* Implementa la misma interfaz que el objeto real.
* Contiene internamente una referencia o puntero al objeto real.
* Controla el acceso y decide cuándo delegar la operación.
* Puede añadir lógica adicional antes o después de la delegación.

### 4. **Código cliente**

* Trabaja exclusivamente con la interfaz común.
* No conoce si está utilizando un proxy o el objeto real.
* Permanece independiente de la estrategia de acceso utilizada.
* Gestiona el ciclo de vida de los objetos de forma segura.

## Diagrama UML

![uml](uml/proxy.png)

## Ejemplo genérico

```cpp
#include <iostream>
#include <memory>
#include <string>

// ----------------------------------------
// Interfaz común (Sujeto)
// ----------------------------------------
class ISujeto {
public:
    virtual ~ISujeto() = default;
    virtual void realizar_operacion(const std::string& usuario) = 0;
};

// ----------------------------------------
// Objeto Real
// ----------------------------------------
class ObjetoReal : public ISujeto {
public:
    void realizar_operacion(const std::string& usuario) override {
        std::cout << "ObjetoReal: ejecutando operación para '"
                  << usuario << "'.\n";
    }
};

// ----------------------------------------
// Proxy
// ----------------------------------------
class Proxy : public ISujeto {
private:
    // Ahora el proxy depende de la abstracción, no del tipo concreto
    std::unique_ptr<ISujeto> sujeto_real_;

    bool comprobar_acceso(const std::string& usuario) const {
        std::cout << "Proxy: comprobando acceso para '"
                  << usuario << "'...\n";
        return usuario == "admin";
    }

    void registrar_acceso(const std::string& usuario) const {
        std::cout << "Proxy: registrando uso del servicio por '"
                  << usuario << "'.\n";
    }

    // Factoría interna para crear el sujeto real (sigue siendo ObjetoReal aquí,
    // pero el resto del proxy no depende de su tipo)
    static std::unique_ptr<ISujeto> crear_sujeto_real() {
        return std::make_unique<ObjetoReal>();
    }

public:
    void realizar_operacion(const std::string& usuario) override {
        if (!sujeto_real_) {
            std::cout << "Proxy: inicializando ObjetoReal bajo demanda...\n";
            sujeto_real_ = crear_sujeto_real();
        }

        if (comprobar_acceso(usuario)) {
            registrar_acceso(usuario);
            sujeto_real_->realizar_operacion(usuario);
        } else {
            std::cout << "Proxy: acceso denegado a '"
                      << usuario << "'.\n";
        }
    }
};

// ----------------------------------------
// Código cliente
// ----------------------------------------
void cliente(ISujeto& servicio, const std::string& usuario) {
    std::cout << "Cliente: intentando usar el servicio como '"
              << usuario << "'.\n";
    servicio.realizar_operacion(usuario);
    std::cout << "----------------------------------------\n";
}

// ----------------------------------------
// main
// ----------------------------------------
int main() {
    Proxy servicio_proxy;

    cliente(servicio_proxy, "invitado");
    cliente(servicio_proxy, "admin");

    return 0;
}
```

## Puntos clave del ejemplo

* **El cliente nunca conoce el ObjetoReal**: solo usa `ISujeto`.
* El **proxy controla el acceso**, registra las actividades y crea el objeto real solo cuando es necesario.
* El uso de **`std::unique_ptr`** garantiza una gestión de recursos clara y segura.
* El patrón permite añadir capacidades extra (logs, permisos, caché…) sin modificar la clase del objeto real.
* Ejemplo híbrido: Virtual Proxy (lazy), Protection Proxy (acceso) y Logging (registro)

