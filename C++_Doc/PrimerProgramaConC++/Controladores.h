#pragma once
#include <iostream>
#include <string>
#include <list>
#include <array>
#include "Usuarios.h"
#include "RegistroDAO.h"
#include "Controladores.h"



using namespace std;
inline CalcularTiempo* tiempo = new CalcularTiempo;

class Controladores{
private:
    /* data */
public:
    Controladores(/* args */);



static int reservar(int opcion, pmr::list<Usuarios> listaUsuarios){
    cout << "Pulse 1 para cerrar la app, \nPulse 2 para continuar" << endl;
    cin >> opcion;
    cout << "opcion escogida : " << opcion << endl;
<<<<<<< HEAD
    string primerNombre, segundoNombre, primerApellido, segundoApellido, codigoALumno, correoAlumno;
=======
    string primerNombre, segundoNombre, primerApellido, segundoApellido;
>>>>>>> 0485a80 (Añadiendo algoritmo De Lunh y Calculadores de tiempo (Solo Afecta a local))

    switch (opcion){
        case 1:
            return 0;
        case 2:
<<<<<<< HEAD
        for (int i = 0; i <= 5; i++){
=======
        for (int i = 0; i <= 4; i++){
>>>>>>> 0485a80 (Añadiendo algoritmo De Lunh y Calculadores de tiempo (Solo Afecta a local))
            switch (i){
                case 0:
                    cout << "Ingrese Primer Nombre\n" << endl;
                    cin >> primerNombre;
                    break;
                case 1:
                    cout << "Ingrese Segundo Nombre, En caso de no tener dar enter\n" << endl;
                    cin >> segundoNombre;
                    break;
                case 2:
                    cout << "Ingrese Primer Apellido\n" << endl;
                    cin >> primerApellido;
                    break;
                case 3:
                    cout << "Ingrese Segundo Apellido\n" << endl;
                    cin >> segundoApellido;
                    break;
<<<<<<< HEAD
                case 4:
                    cout << "Ingrese Codigo Alumno\n" << endl;
                    cin >> codigoALumno;
                    break;
                case 5:
                    cout << "Ingrese Codigo Alumno\n" << endl;
                    cin >> correoAlumno;
                    break;
=======
>>>>>>> 0485a80 (Añadiendo algoritmo De Lunh y Calculadores de tiempo (Solo Afecta a local))
                default:
                    cout << "Error" << endl;
                    break;
            }
        }

        tiempo->init();

        if (primerNombre.empty() || segundoNombre.empty() || primerApellido.empty() || segundoApellido.empty()){
            cout << "Nombre vacio" << endl;
        } else if (primerNombre.length() > 20 || segundoNombre.length() > 20 || primerApellido.length() > 20 || segundoApellido.length() > 20){
            cout << "Nombre muy largo" << endl;
        } else if (primerNombre.length() < 3 || segundoNombre.length() < 3 || primerApellido.length() < 3 || segundoApellido.length() < 3){
            cout << "Nombre muy corto" << endl;
        }



        string nombreCompletoUsuario = primerNombre + " " + segundoNombre + " " + primerApellido + " " +  segundoApellido + "\n";
<<<<<<< HEAD
        //Validar si el nombre contiene numeros
=======
>>>>>>> 0485a80 (Añadiendo algoritmo De Lunh y Calculadores de tiempo (Solo Afecta a local))
        for (int i = 0; i < nombreCompletoUsuario.length(); i++){
            if (isdigit(nombreCompletoUsuario[i])){
                cout << "Nombre no puede contener numeros" << endl;
            }
        }
        usuario->setNombre(nombreCompletoUsuario);
<<<<<<< HEAD
        usuario->setEdad();
=======
        usuario->setEdad(30);
>>>>>>> 0485a80 (Añadiendo algoritmo De Lunh y Calculadores de tiempo (Solo Afecta a local))

        listaUsuarios.push_front(*usuario);


        Usuarios usuarioEncontrado =  RegistroDao::buscarUsuarioPorNombre(nombreCompletoUsuario,listaUsuarios);
        //cout << usuarioEncontrado;
        cout << "La lista esta conformada por ; " << usuarioEncontrado.getNombre();

        tiempo->end();
        tiempo->retornarTiempo("Tiempo desde la clase Controladores");

        return 1;

    }
}


    ~Controladores();
};

Controladores::Controladores(/* args */){

}

Controladores::~Controladores(){

}
