# Ejemplo: Integración de una API de pagos antigua

## Introducción

Para ilustrar el patrón **Adapter** en un contexto realista, construiremos un pequeño sistema que procesa pagos a través de una **interfaz moderna**, aunque internamente usemos una **API antigua** e incompatible.

El escenario es el siguiente:

* La aplicación cliente trabaja únicamente con la interfaz moderna `ProcesadorPago`, que define un método `pagar()`.
* Sin embargo, disponemos de una librería antigua llamada `ApiPagoAntigua` cuya interfaz es distinta: no tiene `pagar()`, sino `enviar_pago(monto)`.
* Queremos integrar esta API antigua sin modificarla y sin cambiar el código cliente.

El adaptador (`AdaptadorPago`) implementa la interfaz moderna y traduce las llamadas hacia la API antigua, permitiendo la coexistencia transparente de ambas interfaces.

A continuación se muestra el código completo dividido en:

* **Procesador.hpp**: interfaz moderna del sistema.
* **ApiAntigua.hpp**: clase adaptada (legado).
* **Adaptador.hpp**: adaptador que conecta ambas.
* **main.cpp**: código cliente.

## Procesador.hpp

```cpp
#pragma once
#include <iostream>

// ----------------------------------------
// Interfaz moderna (Target)
// ----------------------------------------
class ProcesadorPago {
public:
    virtual ~ProcesadorPago() = default;
    virtual void pagar(double cantidad) const = 0;
};
```

## ApiAntigua.hpp

```cpp
#pragma once
#include <iostream>

// ----------------------------------------
// Clase adaptada (Adaptee): API antigua
// ----------------------------------------
class ApiPagoAntigua {
public:
    void enviar_pago(double monto) const {
        std::cout << "[API antigua] Pago enviado por valor de " << monto << " euros.\n";
    }
};
```

## Adaptador.hpp

```cpp
#pragma once
#include <memory>
#include <utility>
#include "Procesador.hpp"
#include "ApiAntigua.hpp"

// ----------------------------------------
// Adaptador (Adapter)
// ----------------------------------------
class AdaptadorPago : public ProcesadorPago {
private:
    std::unique_ptr<ApiPagoAntigua> api_;

public:
    explicit AdaptadorPago(std::unique_ptr<ApiPagoAntigua> api)
        : api_(std::move(api)) {}

    void pagar(double cantidad) const override {
        // Traducción de la interfaz moderna a la antigua
        api_->enviar_pago(cantidad);
    }
};
```

## main.cpp

```cpp
#include <memory>
#include "Adaptador.hpp"

void cliente(const ProcesadorPago& procesador) {
    procesador.pagar(42.50);
}

int main() {
    auto api_antigua = std::make_unique<ApiPagoAntigua>();
    auto adaptador = std::make_unique<AdaptadorPago>(std::move(api_antigua));

    cliente(*adaptador);

    return 0;
}
```

## Añadir un nuevo sistema de pago incompatible

Supongamos que ahora debemos integrar un **nuevo proveedor de pagos**, por ejemplo un sistema bancario que ofrece una interfaz completamente distinta de la moderna `ProcesadorPago`.

Esta nueva API, llamada `ApiPagoBanco`, no dispone del método `pagar()`, sino de uno propio:

```cpp
void realizar_transferencia(double cantidad, const std::string& iban);
```

Queremos usar esta API sin modificar:

* la interfaz moderna `ProcesadorPago`,
* la API antigua ya adaptada,
* ni el código cliente.

El patrón **Adapter** permite hacerlo añadiendo únicamente dos clases nuevas:

1. Un **adaptador nuevo**, que traduce la interfaz moderna hacia la interfaz bancaria.
2. (Opcionalmente) un archivo con la clase **adaptada**, si el proveedor la entrega como librería separada.

### Nueva API incompatible: `ApiPagoBanco`

Creemos un archivo `ApiBanco.hpp`:

```cpp
#pragma once
#include <iostream>
#include <string>

// ----------------------------------------
// Nueva API incompatible (Adaptee #2)
// ----------------------------------------
class ApiPagoBanco {
public:
    void realizar_transferencia(double cantidad, const std::string& iban_destino) const {
        std::cout << "[Banco] Transferencia de " << cantidad
                  << " euros enviada al IBAN " << iban_destino << ".\n";
    }
};
```

Observa que esta API no tiene `pagar()`.
Su interfaz no coincide con la de `ProcesadorPago`, por lo que no es intercambiable directamente.

### Nuevo adaptador: `AdaptadorPagoBanco`

Creamos un archivo `AdaptadorBanco.hpp`:

```cpp
#pragma once
#include <memory>
#include <utility>
#include <string>
#include "Procesador.hpp"
#include "ApiBanco.hpp"

// ----------------------------------------
// Nuevo adaptador para la API bancaria
// ----------------------------------------
class AdaptadorPagoBanco : public ProcesadorPago {
private:
    std::string iban_destino_;
    std::unique_ptr<ApiPagoBanco> api_;

public:
    explicit AdaptadorPagoBanco(std::string iban, std::unique_ptr<ApiPagoBanco> api)
        : iban_destino_(std::move(iban)), api_(std::move(api)) {}

    void pagar(double cantidad) const override {
        // Traducción de la interfaz moderna hacia la interfaz bancaria
        api_->realizar_transferencia(cantidad, iban_destino_);
    }
};
```

Este adaptador:

* recibe el `iban_destino`, que el sistema bancario necesita,
* traduce `pagar(cantidad)` → `realizar_transferencia(cantidad, iban_destino_)`.

### Usar el nuevo sistema adaptado desde el cliente

El cliente **no se modifica**:

```cpp
void cliente(const ProcesadorPago& procesador) {
    procesador.pagar(42.50);
}
```

En `main.cpp` añadimos simplemente:

```cpp
#include "AdaptadorBanco.hpp"

// ...

int main() {
    auto api_antigua = std::make_unique<ApiPagoAntigua>();
    auto adaptador_antiguo = std::make_unique<AdaptadorPago>(std::move(api_antigua));

    auto api_banco = std::make_unique<ApiPagoBanco>();
    auto adaptador_banco = std::make_unique<AdaptadorPagoBanco>(
        "ES9820385778983000760236", 
        std::move(api_banco)
    );

    cliente(*adaptador_antiguo); // API antigua adaptada
    cliente(*adaptador_banco);   // Nueva API bancaria adaptada

    return 0;
}
```
### Qué no hemos modificado

* No se ha tocado la interfaz moderna `ProcesadorPago`.
* No se ha cambiado la API antigua ni su adaptador.
* El cliente permanece idéntico.
* No se han añadido `if`, `switch` ni lógica condicional.

Solo hemos añadido:

* Una nueva API incompatible (`ApiPagoBanco`).
* Un nuevo adaptador (`AdaptadorPagoBanco`).
* Unas líneas en `main.cpp` para usarlo.
