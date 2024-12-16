https://github.com/Jaiime10/TINY-LISP-T4/

# Tiny Lisp Interpreter

Este proyecto es un **intérprete Tiny Lisp** que utiliza C++ para manejar múltiples tipos de datos y estructuras similares a las de un lenguaje Lisp. El núcleo del programa se basa en la clase `Variant`, que permite representar **símbolos**, **números**, **listas** y **procedimientos**.

## Propósito del programa

El programa:
- Permite manipular diferentes tipos de datos como números, símbolos, listas y procedimientos de forma dinámica.
- Proporciona métodos para convertir estos datos a **representaciones en cadenas de texto** y **formato JSON**.
- Incluye funciones para analizar cadenas en formato JSON y convertirlas a estructuras manejadas por el programa.
- Sirve como base para crear un intérprete funcional de Lisp en un entorno educativo o experimental.

## Funcionalidades principales

1. **Representación de datos con la clase Variant:**
    - Números (`double`).
    - Símbolos (`std::string`).
    - Listas (`std::vector<Variant>`).
    - Procedimientos (`std::function<void()>`).

2. **Conversión a formatos útiles:**
    - Convertir cualquier dato almacenado en `Variant` a texto (`to_string`).
    - Convertir a formato JSON (`json_string`).
    - Analizar cadenas JSON para crear instancias de `Variant` (`from_json_string`, `parse_json_string`).

3. **Pruebas y demostraciones integradas:**
    - La clase `TinyLispInterpreter` incluye un método `run_tests()` que muestra ejemplos de uso.

### Lenguaje y estándar
- **C++17 o superior:** El programa usa `std::variant`, `std::visit` y otras características modernas de C++.

### Librerías necesarias
1. **nlohmann/json:** Biblioteca para trabajar con JSON en C++.
    - [Repositorio oficial](https://github.com/nlohmann/json).
    - La biblioteca puede ser utilizada como un único archivo de encabezado (`json.hpp`).

### Entorno de desarrollo
- **CMake:** Para configurar y construir el proyecto.
- **CLion** (opcional): Entorno de desarrollo recomendado para editar y ejecutar el proyecto.



