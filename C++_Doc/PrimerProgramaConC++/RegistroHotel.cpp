//
// Created by Jesus Emmanuel Garcia on 08/09/24.
//
//Parte del codigo absolutamente necesaria e importante :v
#include <iostream>
#include <string>
#include <list>
#include <array>
<<<<<<< HEAD
<<<<<<< HEAD

#include "CalcularTiempo.h"
=======
>>>>>>> 3b87006 (Añadiendo estructuras de control y Contador de tiempo JAVA)
=======

#include "CalcularTiempo.h"
>>>>>>> 0485a80 (Añadiendo algoritmo De Lunh y Calculadores de tiempo (Solo Afecta a local))
#include "Usuarios.h"
#include "RegistroDAO.h"
#include "Controladores.h"

using namespace std;

bool bandera = true;
int opcion;
pmr::list<Usuarios> listaUsuarios;
//Usuarios* usuario = new Usuarios;
RegistroDao* dao = new RegistroDao;
<<<<<<< HEAD
<<<<<<< HEAD
Controladores* controlador = new Controladores;
=======


inline int reservar(){
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


        Usuarios usuarioEncontrado =  RegistroDao::buscarUsuarioPorNombre(nombre,listaUsuarios);
        //cout << usuarioEncontrado;
        cout << "La lista esta conformada por ; " << usuarioEncontrado.getNombre();

        bandera = false;
    }
    return 0;
}
=======
Controladores* controlador = new Controladores;
>>>>>>> 0485a80 (Añadiendo algoritmo De Lunh y Calculadores de tiempo (Solo Afecta a local))

>>>>>>> 8bc55eb (Añadiendo JAVA)


inline void sistema(){

    int banderaAuxiliar;
    while (bandera){

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> 0485a80 (Añadiendo algoritmo De Lunh y Calculadores de tiempo (Solo Afecta a local))

        /*
         * reservar = Create
         * consultar = Read
         * cancelar = Delete
         * modificar = Update
         */
        array<string, 5> tramite = {"Reservar", "Consultar una Reserva", "Cancelar Una Reserva", "Modificar Una Reserva", "Eliminar una reserva"};
<<<<<<< HEAD
=======
        array<string, 7> tramite = {"Reserva", "Alquilar", "Vender", "Comprar", "Cancelar una reserva", "Terminar de pagar una reserva"};
>>>>>>> 3b87006 (Añadiendo estructuras de control y Contador de tiempo JAVA)
=======
>>>>>>> 0485a80 (Añadiendo algoritmo De Lunh y Calculadores de tiempo (Solo Afecta a local))

        cout << "Seleccione una opción (1-6):" << endl;
        for (int i = 0; i < tramite.size(); ++i) {
            cout << i + 1 << ". " << tramite[i] << endl;
        }

        cin >> opcion;

        switch (opcion)
        {
        case 1:
            cout << "Eligió Reserva" << std::endl;
            banderaAuxiliar = Controladores::reservar(opcion, listaUsuarios);
            if (banderaAuxiliar == 0){
                bandera = false;
            }
            break;
        case 2:
            cout << "Eligio Consultar una Reserva" << endl;
            break;
        case 3:
            cout << "Eligio Cancelar Una Reserva" << endl;
            break;
        case 4:
            cout << "Eligio Modificar Una Reserva" << endl;
            break;
        case 5:
            cout << "Eligio Eliminar una reserva" << endl;
            break;
        default:

            cout << "Opción no válida" << endl;
            bandera = false;
            break;
        }
    }


}


int main() {
    tiempo->init();

    sistema();

    tiempo->end();
    tiempo->retornarTiempo("Tiempo en clase principal");

    return 0;
}