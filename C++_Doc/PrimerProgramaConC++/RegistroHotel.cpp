//
// Created by Jesus Emmanuel Garcia on 08/09/24.
//
#include <iostream>
#include <string>
#include <array>
#include <list>
#include "Usuarios.h"

using namespace std;

bool bandera = true;
int opcion;
pmr::list<Usuarios> listaUsuarios;
Usuarios* usuario = new Usuarios;
array<string, 10> arrayReservas;


// Función para buscar un usuario por nombre
Usuarios* buscarUsuarioPorNombre(const string& nombreBuscado) {

    // Iteramos sobre la lista de usuarios
    for (auto& usuario : listaUsuarios) {

        // Si el nombre coincide, retornamos un puntero al usuario
        if (usuario.getNombre() == nombreBuscado) {

            return &usuario;  // Retornamos la dirección del objeto encontrado
        }
    }
    return nullptr;  // Si no se encuentra el usuario, retornamos nullptr
}



inline int reservar(){
    //arrayReservas[0] = {"0","1","2","3","4","10"};
    cout << "Pulse 1 para cerrar la app, \nPulse 2 para continuar" << endl;
    cin >> opcion;
    cout << "opcion escogida : " << opcion << endl;

    if (opcion == 1){
        bandera = false;
    }else if (opcion == 2){

        cout << "Ingrese Nombre" << endl;
        string nombre ;
        cin >> nombre;;

        usuario->setNombre(nombre);
        usuario->setEdad(30);

        listaUsuarios.push_front(*usuario);
        Usuarios* usuarioEncontrado = buscarUsuarioPorNombre(nombre);
        cout << "La lista esta conformada por ; " << usuarioEncontrado->getNombre() << endl;

        bandera = false;
    }
    return 0;
}

inline int buscarReserva(){



    return 0;
}


inline void sistema(){
    while (bandera){

        array<string, 6> tramite = {"Reserva", "Alquilar", "Vender", "Comprar", "Cancelar una reserva", "Terminar de pagar una reserva"};


        cout << "Seleccione una opción (1-6):" << endl;
        for (int i = 0; i < tramite.size(); ++i) {
            cout << i + 1 << ". " << tramite[i] << endl;
        }

        cin >> opcion;

        switch (opcion)
        {
        case 1:
            cout << "Eligió Reserva" << std::endl;
            reservar();
            break;
        case 2:
            cout << "Eligió Alquilar" << endl;
            break;
        case 3:
            cout << "Eligió Vender" << endl;
            break;
        case 4:
            cout << "Eligió Comprar" << endl;
            break;
        case 5:
            cout << "Eligió Cancelar una reserva" << endl;
            break;
        case 6:
            cout << "Eligió Terminar de pagar una reserva" << endl;
        default:
            break;
            cout << "Opción no válida" << endl;
            bandera = false;
            break;
        }
    }
}


int main() {

    sistema();

    return 0;
}