//
// Created by Jesus Emmanuel Garcia on 08/09/24.
//

#ifndef USUARIOS_H
#define USUARIOS_H
#include <set>
#include <string>

using namespace std;

class UsuariosEntity {

int id_usuario;
    string nombre;
    int codigo;
    string correo;
    string llave_acceso;
    //long numero_de_tarjeta;


public:
    UsuariosEntity() = default;

    // Constructor para inicializar los atributos
    UsuariosEntity(string n, int e): id_usuario(0),
                                     nombre(std::move(n)), codigo(e){
    }

    // Getter para el atributo 'nombre'
    string getNombre() const {
        return nombre;
    }

    // Setter para el atributo 'nombre'
    void setNombre(string& nuevoNombre) {
        this->nombre = nuevoNombre;
    }

    // Getter para el atributo 'codigo'
    int getCodigo() const {
        return codigo;
    }

    // Setter para el atributo 'codigo'
    void setCodigo(string& nuevoCodigo) {
        int codigoInt = stoi(nuevoCodigo);
        if (codigoInt > 0) {  // Validación simple
            this->codigo = codigoInt;
        }
    }

    string getCorreo() const{
        return correo;
    }

    void setCorreo(const string& correo){
        this->correo = correo;
    }
};

struct metaDatosUsuarios{
    std::string nombre;
    int edad;
};


#endif //USUARIOS_H
