# Ejemplo: Sistema de monitoreo de temperatura

## Introducción

Para ilustrar el patrón **Observer** en un contexto realista, construiremos un pequeño sistema de **monitoreo de temperatura**.

El objetivo del sistema es permitir que distintos componentes reaccionen automáticamente cuando cambia la temperatura medida por un sensor, **sin que el sensor conozca los tipos concretos de observadores**.

Dependiendo de los observadores registrados, la temperatura podrá:

* mostrarse en una **pantalla**,
* registrarse en un **archivo de log**,
* generar **alertas** cuando supera ciertos valores.

Cada observador implementa la interfaz común `Observador`, que define el método `actualizar()`.
El **sujeto concreto**, `SensorTemperatura`, mantiene una lista de observadores y los notifica cuando cambia la temperatura.

A continuación se muestra el código completo dividido en:

* **Observadores.hpp** – interfaz `Observador` y observadores concretos
* **Sujetos.hpp** – interfaz `Sujeto` y sujeto concreto
* **main.cpp** – código cliente

## Observadores.hpp

```cpp
#pragma once
#include <iostream>
#include <fstream>
#include <memory>
#include <string>

// ----------------------------------------
// Interfaz base del observador
// ----------------------------------------
class Observador {
public:
    virtual ~Observador() = default;
    virtual void actualizar(int nueva_temperatura) = 0;
};

// ----------------------------------------
// Observador que muestra la temperatura en pantalla
// ----------------------------------------
class ObservadorPantalla : public Observador {
public:
    void actualizar(int nueva_temperatura) override {
        std::cout << "[Pantalla] Temperatura actual: "
                  << nueva_temperatura << "°C\n";
    }
};

// ----------------------------------------
// Observador que registra la temperatura en un archivo
// ----------------------------------------
class ObservadorArchivo : public Observador {
private:
    std::ofstream archivo_;

public:
    explicit ObservadorArchivo(const std::string& ruta)
        : archivo_(ruta, std::ios::app) {}

    void actualizar(int nueva_temperatura) override {
        if (archivo_.is_open()) {
            archivo_ << "[Archivo] Temperatura: "
                     << nueva_temperatura << "°C\n";
        }
    }
};

// ----------------------------------------
// Observador que lanza una alerta si la temperatura supera un umbral
// ----------------------------------------
class ObservadorAlerta : public Observador {
private:
    int umbral_;

public:
    explicit ObservadorAlerta(int umbral) : umbral_(umbral) {}

    void actualizar(int nueva_temperatura) override {
        if (nueva_temperatura > umbral_) {
            std::cout << "[ALERTA] Temperatura crítica: "
                      << nueva_temperatura << "°C\n";
        }
    }
};
```

## Sujetos.hpp

```cpp
#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include "Observadores.hpp"

// ----------------------------------------
// Interfaz base del sujeto (observable)
// ----------------------------------------
class Sujeto {
public:
    virtual ~Sujeto() = default;

    virtual void adjuntar(const std::shared_ptr<Observador>& obs) = 0;
    virtual void desadjuntar(const std::shared_ptr<Observador>& obs) = 0;

protected:
    virtual void notificar(int nueva_temperatura) = 0;
};

// ----------------------------------------
// Sujeto concreto: un sensor de temperatura
// ----------------------------------------
class SensorTemperatura : public Sujeto {
private:
    int temperatura_actual_{0};
    std::vector<std::weak_ptr<Observador>> observadores_;

public:
    void establecer_temperatura(int nueva_temp) {
        if (nueva_temp != temperatura_actual_) {
            temperatura_actual_ = nueva_temp;
            notificar(nueva_temp);
        }
    }

    void adjuntar(const std::shared_ptr<Observador>& obs) override {
        observadores_.push_back(obs);
    }

    void desadjuntar(const std::shared_ptr<Observador>& obs) override {
        observadores_.erase(
            std::remove_if(
                observadores_.begin(),
                observadores_.end(),
                [&obs](std::weak_ptr<Observador>& w) {
                    auto fuerte = w.lock();
                    return !fuerte || fuerte == obs;
                }
            ),
            observadores_.end()
        );
    }

protected:
    void notificar(int nueva_temperatura) override {
        observadores_.erase(
            std::remove_if(
                observadores_.begin(),
                observadores_.end(),
                [nueva_temperatura](std::weak_ptr<Observador>& w) {
                    auto fuerte = w.lock();
                    if (!fuerte)
                        return true;
                    fuerte->actualizar(nueva_temperatura);
                    return false;
                }
            ),
            observadores_.end()
        );
    }
};
```

## main.cpp

```cpp
#include "Sujetos.hpp"

int main() {
    SensorTemperatura sensor;

    auto pantalla = std::make_shared<ObservadorPantalla>();
    auto archivo  = std::make_shared<ObservadorArchivo>("temperaturas.txt");
    auto alerta   = std::make_shared<ObservadorAlerta>(30);

    sensor.adjuntar(pantalla);
    sensor.adjuntar(archivo);
    sensor.adjuntar(alerta);

    sensor.establecer_temperatura(22);
    sensor.establecer_temperatura(31);

    // Desconectamos la pantalla
    sensor.desadjuntar(pantalla);

    sensor.establecer_temperatura(35);

    return 0;
}
```

## Añadir un nuevo observador

Para añadir un nuevo observador no modificamos la interfaz `Observador` ni la interfaz `Sujeto`, solo añadimos clases nuevas y opcionalmente una línea en `main.cpp`. Veamos un nuevo observador que envía la temperatura por red.

### Nuevo observador (`ObservadorRed`) en `Observadores.hpp`:

```cpp
// Observador que simula enviar la temperatura por red
class ObservadorRed : public Observador {
public:
    void actualizar(int nueva_temperatura) override {
        std::cout << "[Red] Enviando temperatura: "
                  << nueva_temperatura << "°C al servidor...\n";
    }
};
```

### Usarlo en `main.cpp`:

```cpp
auto red = std::make_shared<ObservadorRed>();
sensor.adjuntar(red);
```

### Qué no hemos modificado

* No hemos modificado la interfaz `Observador`.
* No hemos modificado la interfaz `Sujeto`.
* No hemos modificado `SensorTemperatura` ni los observadores ya existentes.

Solo hemos:

1. añadido un **nuevo observador concreto**,
2. registrado ese observador en el sujeto,
3. y opcionalmente añadido una línea en `main.cpp` para probarlo.
