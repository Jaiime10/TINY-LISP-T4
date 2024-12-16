#ifndef VARIANT_H
#define VARIANT_H

#include <string>
#include <variant>
#include <vector>
#include <functional>
#include <json.hpp> // Biblioteca JSON de nlohmann

// Definiciones de tipos
using Simbolo = std::string;
using Numero = double;
class Variant;
using Lista = std::vector<Variant>;
using Procedimiento = std::function<void()>;

class Variant {
private:
    std::variant<Simbolo, Numero, Lista, Procedimiento> valor;

    // Método auxiliar para convertir un objeto JSON a Variant
    static Variant convert_from_json(const nlohmann::json& parsed_json);

public:
    // Constructores
    Variant(Simbolo simbolo);
    Variant(Numero numero);
    Variant(Lista lista);
    Variant(Procedimiento procedimiento);

    // Métodos
    template<typename T>
    T obtener() const;

    template<typename T>
    void establecer(T nuevoValor);

    void imprimir() const;
    std::string to_string() const;
    std::string json_string() const;

    // Métodos estáticos
    static Variant from_json_string(const std::string& json_str);
    static Variant parse_json_string(const std::string& json_str);
};

class TinyLispInterpreter {
public:
    // Método de prueba
    static void run_tests();
};

#endif // VARIANT_H
