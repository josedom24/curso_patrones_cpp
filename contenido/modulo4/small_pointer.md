# Uso práctico de `std::unique_ptr` y `std::shared_ptr` en clases

En programas complejos, la gestión manual de memoria es propensa a errores y fugas. El uso de **punteros inteligentes** permite delegar la liberación de memoria al sistema de tipos, reduciendo errores y simplificando la lógica de destrucción.

Este apartado se enfoca en el **uso práctico** de `std::unique_ptr` y `std::shared_ptr` como miembros de clases, explicando cuándo usar cada uno, cómo gestionar la propiedad y cómo implementar clases RAII robustas.

## Uso de `std::unique_ptr` en composición

```cpp
#include <iostream>
#include <memory>

class Motor {
public:
    void arrancar() { std::cout << "Motor en marcha\n"; }
};

class Coche {
public:
    Coche() : motor_(std::make_unique<Motor>()) {}

    void iniciar() {
        motor_->arrancar();
    }

private:
    std::unique_ptr<Motor> motor_; // Composición exclusiva
};
```

* `motor_` es de tipo `std::unique_ptr<Motor>`, lo que garantiza que el `Coche` es dueño único del `Motor`.
* No hay necesidad de definir un destructor manual: el `unique_ptr` libera el recurso automáticamente.
* La clase no es copiable por defecto, lo cual **refuerza la unicidad de la propiedad**.

## Uso de `std::shared_ptr` para propiedad compartida

```cpp
#include <iostream>
#include <memory>
#include <vector>

class Documento {
public:
    Documento(const std::string& texto) : texto_(texto) {}
    void imprimir() const { std::cout << texto_ << '\n'; }

private:
    std::string texto_;
};

class Usuario {
public:
    Usuario(std::shared_ptr<Documento> doc) : doc_(doc) {}
    void leer() const { doc_->imprimir(); }

private:
    std::shared_ptr<Documento> doc_;
};
```

```cpp
int main() {
    auto documento = std::make_shared<Documento>("Contenido compartido");

    Usuario u1(documento);
    Usuario u2(documento); // Ambos comparten el documento

    u1.leer();
    u2.leer(); // El documento sigue existiendo
}
```

* `documento` es un recurso compartido entre múltiples instancias de `Usuario`.
* El uso de `std::shared_ptr` permite que varios objetos compartan el mismo recurso, y que este se destruya automáticamente cuando ya nadie lo necesita.
* Es especialmente útil en estructuras **grafo-like**, **modelos vista-controlador** o cuando se desea pasar recursos sin transferir la propiedad exclusiva.

