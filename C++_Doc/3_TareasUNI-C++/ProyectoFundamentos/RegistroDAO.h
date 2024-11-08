//
// Created by Jesus Emmanuel Garcia on 11/09/24.
//

#pragma once
#ifndef REGISTRODAO_H
#define REGISTRODAO_H
#include <string>
#include <list>

#include "Controladores.h"


using namespace std;


//Linea generada por IA que no se que hace, segun es para el operador ' == '
bool operator==(const string& lhs, const pmr::string& rhs);

class RegistroDAO{

    /*De la Creacion del proyecto, CRUD
     * CREATE
     * READ
     * UPDATE
     * DELET
     */

public:

    // FUNCION READ
    // Función para buscar un usuario por nombre

    static UsuariosEntity buscarUsuarioPorNombre(const string& nombreBuscado, pmr::list<UsuariosEntity> listaUsuarios) {
         //Lo ponemos dentro de un try catch por si no se encuentra el usuario, devolver un error (Excepcion)
         try {
             // Iteramos sobre la lista de usuarios
             for (UsuariosEntity& usuario : listaUsuarios) {

                 // Si el nombre coincide, retornamos un puntero al usuario
                 if (usuario.getNombre() == nombreBuscado) {
                     //cout << "El ususario buscado desde DAO es " << &usuario;
                     cout << "El ususario buscado desde DAO es " << usuario.getNombre()
                            << "\n Codigo: " << usuario.getCodigo() << "\n Correo: " << usuario.getCorreo() << "\n";
                     return usuario;  // Retornamos la dirección del objeto encontrado
                 }
             }
         }
         catch (const runtime_error& e) {
             cerr << "Usuario NO Encontrado: " << e.what() << endl;
         }
         return {};  // Retornamos un objeto vacío si no se encuentra el usuario
    }

    static UsuariosEntity buscarUsuarioPorCorreo(const string& correo, pmr::list<UsuariosEntity> listaUsuarios) {
        //Lo ponemos dentro de un try catch por si no se encuentra el usuario, devolver un error (Excepcion)
        try {
            // Iteramos sobre la lista de usuarios
            for (UsuariosEntity& usuario : listaUsuarios) {

                // Si el nombre coincide, retornamos un puntero al usuario
                if (usuario.getCorreo() == correo) {
                    //cout << "El ususario buscado desde DAO es " << &usuario;
                    cout << "El ususario buscado desde DAO es " << usuario.getNombre()
                           << "\n Codigo: " << usuario.getCodigo() << "\n Correo: " << usuario.getCorreo() << "\n "
                            << "Y tu cita es el dia: " << usuario.getCita() << "\n\n";
                    return usuario;  // Retornamos la dirección del objeto encontrado
                }
                //esto hace que por cada usuario en la lista que no coincida imprima esto
                // pero como en la lista el metodo inserta en modo pushFront
                // cada que se agrega un usuario la funcion seria: [i + 1] donde i es el elemeneto recien agregado
            }
            cout << "\n     Usuario no encontrado\n\n";
        }
        catch (const runtime_error& e) {
            cerr << "Usuario NO Encontrado: " << e.what() << endl;
        }
        return {};  // Retornamos un objeto vacío si no se encuentra el usuario
    }

    static int buscarCitaYmodificar(const string& correo, pmr::list<UsuariosEntity> listaUsuarios, /*int& diaViejo,*/ int& diaNuevo, CalendarioTerminal& calendario){
        for (UsuariosEntity usuario : listaUsuarios){
            if(usuario.getCorreo() == correo){
                cout << "\nTu cita es el dia: " << usuario.getCita() << "\n";
                //Logica de nueva cita
                int diaNuevaCita = calendario.setNuevaFechaCal( diaNuevo,usuario.getCita());
                usuario.setDiaCita(diaNuevaCita);
                return usuario.getCita();
            }
        }
        cout << "Usuario no encontrado o no tiene cita\n";
        return 0;
    }

};


#endif //REGISTRODAO_H
