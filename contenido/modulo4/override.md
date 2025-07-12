# Uso de `override` y `final`

## Uso de `override`

`override` es una **palabra clave** (especificador) introducida en C++11 que se utiliza para **marcar explícitamente que una función miembro está sobrescribiendo una función virtual heredada**.

El uso correcto de `override`:

* **Verifica en tiempo de compilación** que se está sobrescribiendo correctamente una función virtual de la clase base.
* **Previene errores sutiles** debidos a diferencias en la firma del método (por ejemplo, olvidar el `const` o un parámetro por referencia).
* Mejora la **legibilidad** y el **mantenimiento** del código, dejando claro al lector que la función forma parte de una jerarquía polimórfica.

Podemos usar `override` cuando:

* La función debe tener la **misma firma** que la versión virtual en la clase base (mismo nombre, parámetros y calificaciones como `const`).
* La función de la clase base debe ser **virtual**.

Veamos une ejemplo:


```cpp
class Figura {
public:
    virtual void dibujar() const = 0;  // Método virtual puro
    virtual ~Figura() = default;
};

class Circulo : public Figura {
public:
    void dibujar() const override {  // uso correcto de override
        std::cout << "Dibujando un círculo\n";
    }
};
```

Si escribieras mal la firma, como por ejemplo:

```cpp
void dibujar() override { ... }  //  Error: falta `const`
```

El compilador te mostraría un error gracias al uso de `override`.

Si no usamos `override`, ciertos errores pasan desapercibidos, pero en realidad estaríamos ocultando la función de la clase base en lugar de sobrescribirla correctamente, lo que impediría el funcionamiento del polimorfismo.

```cpp
class Circulo : public Figura {
public:
    void dibujar() {  //  No se sobrescribe realmente, solo se oculta
        std::cout << "Error: esto no se llama polimórficamente\n";
    }
};
```

## Uso de `final`

En programación orientada a objetos (OOP) en C++ moderno, la cláusula `final` se utiliza para **prohibir la sobrescritura (override) de un método virtual** o **impedir que una clase sea derivada**. Esta cláusula fue introducida en C++11 como una mejora de seguridad y claridad en la jerarquía de clases.
 
### Aplicada a un método virtual

 Indica que una función **no puede ser sobrescrita** en clases derivadas. Esto tiene **mucho sentido**, especialmente en jerarquías de herencia profundas o en bibliotecas que definen APIs extendibles hasta cierto punto. En realidad el objetivo es **permitir sobrescritura solo hasta cierto nivel** de la jerarquía:

* El `virtual` permite que una clase base declare un comportamiento **personalizable**.
* El `override` permite que una clase derivada lo **especialice**.
* El `final` **prohíbe** que clases derivadas de esa especialización lo vuelvan a cambiar.

Veamos un ejemplo:

Imagina una API que define cómo debe funcionar un sistema de plugins:

```cpp
class Plugin {
public:
    virtual void inicializar() {
        std::cout << "Inicialización por defecto del plugin\n";
    }
    virtual ~Plugin() = default;
};

class PluginSeguro : public Plugin {
public:
    void inicializar() final override {
        std::cout << "Inicialización segura y verificada del plugin\n";
    }
};
```

Supón que `PluginSeguro` **debe garantizar esa inicialización segura**. Si otra clase derivada la sobrescribe:

```cpp
class PluginHackeado : public PluginSeguro {
public:
    //  Esto sería un problema de seguridad
    void inicializar() override {
        std::cout << "Inicialización modificada para evitar verificación\n";
    }
};
```

Con `final`, **el compilador evitará este error** en tiempo de compilación.

### Aplicada a una clase

Impide que la clase sea utilizada como base de otra clase:

```cpp
class NoHeretable final {
    // ...
};

class Intento : public NoHeretable {
    //  Error: NoHeretable está marcada como final
};
```

Esto es útil cuando quieres dejar explícito que una clase no está diseñada para ser extendida (por ejemplo, clases de utilidad o de implementación cerrada).
