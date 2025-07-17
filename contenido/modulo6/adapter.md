# Adapter

## Introducción y propósito

El patrón de diseño **Adapter** tiene como propósito **permitir que dos interfaces incompatibles colaboren entre sí** sin necesidad de modificar su implementación original. Su función es actuar como un “traductor” entre clases que, aunque ofrecen funcionalidades útiles, no pueden comunicarse directamente por tener interfaces distintas.

## Problemas que resuelve

El patrón Adapter se utiliza cuando:

* Deseamos **usar una clase existente** cuyo interfaz **no coincide** con lo que espera nuestro sistema.
* Queremos **integrar bibliotecas de terceros** o código legado **sin modificar su fuente**.
* Necesitamos desacoplar sistemas **altamente cohesionados**, favoreciendo la **extensibilidad** y **reutilización**.
* Es fundamental en contextos como:

  * **Sistemas de GUI**, donde componentes visuales tienen interfaces diferentes.
  * **Sistemas de archivos o bases de datos**, para unificar acceso a distintos motores.
  * **Servicios de red o APIs**, donde diferentes protocolos deben interactuar con una capa común.

## Diagrama UML y estructura

```plaintext
         +---------------------+
         |     Target          |<-------------------+
         | (interfaz esperada) |                    |
         +---------------------+                    |
                    ^                               |
                    |                               |
         +----------+----------+          +---------+--------+
         |      Adapter         | ------> |     Adaptee       |
         | (traduce interfaz)   |         | (interfaz real)   |
         +----------------------+         +-------------------+
```

* **Target**: interfaz que espera el cliente.
* **Adaptee**: clase existente con interfaz incompatible.
* **Adapter**: clase que implementa la interfaz `Target` y usa internamente una instancia de `Adaptee`, delegando llamadas y adaptándolas.

## Implementación en C++ moderno

Un sistema espera una interfaz `AudioPlayer`, pero disponemos de una clase `LegacySpeaker` que no implementa dicha interfaz.

```cpp
#include <iostream>
#include <memory>

// Interfaz esperada por el sistema
class AudioPlayer {
public:
    virtual void play_sound() const = 0;
    virtual ~AudioPlayer() = default;
};

// Clase existente con interfaz incompatible
class LegacySpeaker {
public:
    void emit_audio() const {
        std::cout << "Reproduciendo audio desde LegacySpeaker.\n";
    }
};

// Adaptador que traduce la interfaz
class LegacySpeakerAdapter : public AudioPlayer {
public:
    explicit LegacySpeakerAdapter(std::shared_ptr<LegacySpeaker> speaker)
        : legacy_speaker_(std::move(speaker)) {}

    void play_sound() const override {
        legacy_speaker_->emit_audio(); // adaptación de interfaz
    }

private:
    std::shared_ptr<LegacySpeaker> legacy_speaker_;
};

// Uso del adaptador
void test_audio(std::shared_ptr<AudioPlayer> player) {
    player->play_sound();
}

int main() {
    auto legacy = std::make_shared<LegacySpeaker>();
    auto adapter = std::make_shared<LegacySpeakerAdapter>(legacy);

    test_audio(adapter); // Usa LegacySpeaker como si fuera un AudioPlayer
}
```

* **`AudioPlayer`** es la interfaz esperada por el sistema.
* **`LegacySpeaker`** representa una clase preexistente con una interfaz no compatible (`emit_audio` en vez de `play_sound`).
* **`LegacySpeakerAdapter`** implementa `AudioPlayer` y traduce la llamada a `play_sound()` en una llamada a `emit_audio()` del objeto adaptado.
* Se utilizan `std::shared_ptr` para gestionar los recursos de forma segura y moderna.

## Ventajas

* Permite **reutilizar código existente** sin modificarlo.
* Favorece el **desacoplamiento** entre componentes.
* Facilita la **integración de bibliotecas externas o código legado**.
* Compatible con los principios SOLID: en particular, el Principio de Abierto/Cerrado (Open/Closed).

## Desventajas

* Introduce **una capa adicional de complejidad** y mantenimiento.
* Puede provocar **sobrecarga de código** si se abusa del patrón.
* En casos de adaptación compleja, puede ocultar problemas de diseño subyacentes.

No deberíamos usarlo cuando:

* Cuando el cambio de interfaz original es factible y no afecta negativamente.
* Si el adaptador es demasiado complejo, quizás sea mejor reescribir o refactorizar el componente.

## Buenas prácticas

* Utilice punteros inteligentes (`std::shared_ptr`, `std::unique_ptr`) para manejar la propiedad y evitar fugas.
* Prefiera adaptar mediante interfaces abstractas (`Target`) y composición, no herencia múltiple directa.
* Documente claramente el propósito del adaptador.

