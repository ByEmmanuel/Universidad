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
    //Retornar un mini calendario en terminal para que el usuario registre su cita
    //long numero_de_tarjeta;


public:
    UsuariosEntity() = default;

    // Constructor para inicializar los atributos
    UsuariosEntity(string n, int e): id_usuario(0),
                                     nombre(std::move(n)), codigo(e){
    }


    string getNombre() const {
        return nombre;
    }


    void setNombre(string& nuevoNombre) {
        this->nombre = nuevoNombre;
    }


    int getCodigo() const {
        return codigo;
    }


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
    string nombre;
    int edad;
};


#endif //USUARIOS_H
