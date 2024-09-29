//
// Created by Jesus Emmanuel Garcia on 11/09/24.
//

#ifndef REGISTRODAO_H
#define REGISTRODAO_H
#include <string>
#include <list>

#include "Usuarios.h"

using namespace std;
inline Usuarios* usuario = new Usuarios;

//Linea generada por IA que no se que hace, segun es para el operador ' == '
bool operator==(const string& lhs, const pmr::string& rhs);

class RegistroDao{

    /*De la Creacion del proyecto, CRUD
     * CREATE
     * READ
     * UPDATE
     * DELET
     */

public:

    // FUNCION READ
    // Función para buscar un usuario por nombre

    static Usuarios buscarUsuarioPorNombre(const string& nombreBuscado, pmr::list<Usuarios> listaUsuarios) {
         //Lo ponemos dentro de un try catch por si no se encuentra el usuario, devolver un error (Excepcion)
         try {
             // Iteramos sobre la lista de usuarios
             for (Usuarios& usuario : listaUsuarios) {

                 // Si el nombre coincide, retornamos un puntero al usuario
                 if (usuario.getNombre() == nombreBuscado) {
                     //cout << "El ususario buscado desde DAO es " << &usuario;
                     cout << "El ususario buscado desde DAO es " << usuario.getNombre();
                     return usuario;  // Retornamos la dirección del objeto encontrado
                 }
             }
         }
         catch (const runtime_error& e) {
             cerr << "Usuario NO Encontrado: " << e.what() << endl;
         }
         return {};  // Retornamos un objeto vacío si no se encuentra el usuario
    }
};


#endif //REGISTRODAO_H
