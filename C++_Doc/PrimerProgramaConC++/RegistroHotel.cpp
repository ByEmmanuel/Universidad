//
// Created by Jesus Emmanuel Garcia on 08/09/24.
//
//Parte del codigo absolutamente necesaria e importante :v
#include <iostream>
#include <string>
#include <list>
#include <array>

#include "CalcularTiempo.h"
#include "Usuarios.h"
#include "RegistroDAO.h"
#include "Controladores.h"

using namespace std;

bool bandera = true;
int opcion;
pmr::list<Usuarios> listaUsuarios;
//Usuarios* usuario = new Usuarios;
RegistroDao* dao = new RegistroDao;
Controladores* controlador = new Controladores;



inline void sistema(){

    int banderaAuxiliar;
    while (bandera){


        /*
         * reservar = Create
         * consultar = Read
         * cancelar = Delete
         * modificar = Update
         */
        array<string, 5> tramite = {"Reservar", "Consultar una Reserva", "Cancelar Una Reserva", "Modificar Una Reserva", "Eliminar una reserva"};

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