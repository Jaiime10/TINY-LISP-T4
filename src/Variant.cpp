#include "variant.h"
#include <string>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <json.hpp> // Biblioteca JSON de nlohmann

using json = nlohmann::json;

// Constructor de la clase Variant para inicializar con diferentes tipos de datos
Variant::Variant(Simbolo simbolo) : valor(simbolo) {}
Variant::Variant(Numero numero) : valor(numero) {}
Variant::Variant(Lista lista) : valor(lista) {}
Variant::Variant(Procedimiento procedimiento) : valor(procedimiento) {}

// Metodo obtener: devuelve el valor almacenado como el tipo solicitado
template<typename T>
T Variant::obtener() const {
    return std::get<T>(valor);
}

// Metodo establecer: cambia el valor almacenado por un nuevo valor
template<typename T>
void Variant::establecer(T nuevoValor) {
    valor = nuevoValor;
}

// Metodo imprimir: imprime el contenido del objeto Variant segun el tipo almacenado
void Variant::imprimir() const {
    std::visit([](const auto& val) {
        using T = std::decay_t<decltype(val)>;
        if constexpr (std::is_same_v<T, Simbolo>) {
            std::cout << "Simbolo: " << val << '\n';
        } else if constexpr (std::is_same_v<T, Numero>) {
            std::cout << "Numero: " << val << '\n';
        } else if constexpr (std::is_same_v<T, Lista>) {
            std::cout << "Lista: [ ";
            for (const auto& item : val) {
                item.imprimir();
            }
            std::cout << "]\n";
        } else if constexpr (std::is_same_v<T, Procedimiento>) {
            std::cout << "Procedimiento: (puntero a funcion)\n";
        }
    }, valor);
}

// Metodo to_string: convierte el valor almacenado a una representacion en cadena
std::string Variant::to_string() const {
    std::string result;
    std::visit([&result](const auto& val) {
        using T = std::decay_t<decltype(val)>;
        if constexpr (std::is_same_v<T, Simbolo>) {
            result = val;
        } else if constexpr (std::is_same_v<T, Numero>) {
            result = std::to_string(val);
        } else if constexpr (std::is_same_v<T, Lista>) {
            result = "[ ";
            for (const auto& item : val) {
                result += item.to_string() + " ";
            }
            result += "]";
        } else if constexpr (std::is_same_v<T, Procedimiento>) {
            result = "Procedimiento";
        }
    }, valor);
    return result;
}

// Metodo json_string: convierte el valor almacenado a formato JSON
std::string Variant::json_string() const {
    std::string result;
    std::visit([&result](const auto& val) {
        using T = std::decay_t<decltype(val)>;
        if constexpr (std::is_same_v<T, Simbolo>) {
            result = '"' + val + '"';
        } else if constexpr (std::is_same_v<T, Numero>) {
            result = std::to_string(val);
        } else if constexpr (std::is_same_v<T, Lista>) {
            result = "[ ";
            for (const auto& item : val) {
                result += item.json_string() + ", ";
            }
            result += "]";
        } else if constexpr (std::is_same_v<T, Procedimiento>) {
            result = '"' + std::string("Procedimiento") + '"';
        }
    }, valor);
    return result;
}

// Metodo from_json_string: convierte una cadena en formato JSON a una instancia de Variant
Variant Variant::from_json_string(const std::string& json_str) {
    json parsed_json = json::parse(json_str);
    return convert_from_json(parsed_json);
}

// Metodo parse_json_string: convierte una cadena JSON a un objeto Variant
Variant Variant::parse_json_string(const std::string& json_str) {
    json parsed_json = json::parse(json_str);
    return convert_from_json(parsed_json);
}

// Metodo auxiliar para convertir un objeto JSON a Variant
Variant Variant::convert_from_json(const json& parsed_json) {
    if (parsed_json.is_number()) {
        return Variant(parsed_json.get<Numero>());
    } else if (parsed_json.is_string()) {
        return Variant(parsed_json.get<Simbolo>());
    } else if (parsed_json.is_array()) {
        Lista lista;
        for (const auto& item : parsed_json) {
            lista.push_back(convert_from_json(item));
        }
        return Variant(lista);
    } else {
        throw std::runtime_error("Tipo de JSON no soportado.");
    }
}

// Clase TinyLispInterpreter para encapsular la funcionalidad
class TinyLispInterpreter {
public:
    // Metodo de prueba
    static void run_tests() {
        Variant v1 = 42.0;
        v1.imprimir();

        Variant v2 = std::string("valor_simbolo");
        v2.imprimir();

        Variant::Lista lista = {Variant(1.0), Variant(std::string("elemento")), Variant(3.14)};
        Variant v3 = lista;
        v3.imprimir();

        Variant::Procedimiento procedimiento = []() { std::cout << "Ejecutando procedimiento." << '\n'; };
        Variant v4 = procedimiento;
        v4.imprimir();
        v4.obtener<Variant::Procedimiento>()();

        std::cout << "v1 to_string: " << v1.to_string() << '\n';
        std::cout << "v2 to_string: " << v2.to_string() << '\n';
        std::cout << "v3 to_string: " << v3.to_string() << '\n';

        std::cout << "v1 json_string: " << v1.json_string() << '\n';
        std::cout << "v2 json_string: " << v2.json_string() << '\n';
        std::cout << "v3 json_string: " << v3.json_string() << '\n';
    }
};
