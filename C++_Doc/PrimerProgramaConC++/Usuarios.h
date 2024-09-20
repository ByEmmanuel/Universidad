//
// Created by Jesus Emmanuel Garcia on 08/09/24.
//

#ifndef USUARIOS_H
#define USUARIOS_H
#include <set>
#include <string>




class Usuarios {

    std::string nombre;
    int edad;


public:
    Usuarios() = default;

    // Constructor para inicializar los atributos
    Usuarios(std::string n, int e) :
    nombre(std::move(n)), edad(e) {}

    // Getter para el atributo 'nombre'
    std::string getNombre() const {
        return nombre;
    }

    // Setter para el atributo 'nombre'
    void setNombre(const std::string& nuevoNombre) {
        nombre = nuevoNombre;
    }

    // Getter para el atributo 'edad'
    int getEdad() const {
        return edad;
    }

    // Setter para el atributo 'edad'
    void setEdad(int nuevaEdad) {
        if (nuevaEdad > 0) {  // Validación simple
            edad = nuevaEdad;
        }
    }
};

struct metaDatosUsuarios{
    std::string nombre;
    int edad;
};


#endif //USUARIOS_H
