#pragma once
#include <iostream>
#include <string>
#include <list>
#include <array>
#include <vector>
#include <utility>

#include "Controladores.h"
#include "Usuarios.h"
#include "RegistroDAO.h"
#include "CalendarioTerminal.cpp"


class CalendarioTerminal;
using namespace std;
inline CalcularTiempo* tiempo = new CalcularTiempo;
CalendarioTerminal* calendario = new CalendarioTerminal(); // Crear instancia de Calendario
pmr::list<UsuariosEntity> listaUsuarios;  // Cambiado pmr::list a std::list
//pmr::vector<int> arrayCalendario;
inline vector<int> calendarioDB;
inline int opcDia;

class Controladores{
private:

public:
        /*Controladores(CalendarioTerminal* calendario): calendario(calendario) {

        };*/
    Controladores();



    static int reservar(int opcion ){
        cout << "Pulse 1 para cerrar la app, \nPulse 2 para continuar" << endl;
        cin >> opcion;
        cout << "opcion escogida : " << opcion << endl;
        string primerNombre, segundoNombre, primerApellido, segundoApellido, codigoALumno, correoAlumno;

        switch (opcion){
            case 1:
                return 0;
            case 2:
            for (int i = 0; i <= 6; i++){
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
                    case 4:
                        cout << "Ingrese Codigo Alumno\n" << endl;
                        cin >> codigoALumno;
                        break;
                    case 5:
                        cout << "Ingrese Correo Alumno\n" << endl;
                        cin >> correoAlumno;
                        break;
                    case 6:
                        cout << "Ingrese Fecha para Cita\n" << endl;

                        cin >> opcDia;

                    calendarioDB = calendario->generarCalendario(opcDia, 11, 2024);
                    if (!calendarioDB.empty()) {
                        CalendarioTerminal::mostrarCalendario(calendarioDB, calendario->obtenerDiasOcupados());
                    }

                        break;
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
            //Validar si el nombre contiene numeros
            for (int i = 0; i < nombreCompletoUsuario.length(); i++){
                if (isdigit(nombreCompletoUsuario[i])){
                    cout << "Nombre no puede contener numeros" << endl;
                }
            }
            usuario->setNombre(nombreCompletoUsuario);
            usuario->setCodigo(codigoALumno);
            usuario->setCorreo(correoAlumno);
            usuario->setDiaCita(opcDia);


            listaUsuarios.push_front(*usuario);


            UsuariosEntity usuarioEncontrado =  RegistroDao::buscarUsuarioPorNombre(nombreCompletoUsuario,listaUsuarios);
            //cout << usuarioEncontrado;
            cout << "La lista esta conformada por ; " << usuarioEncontrado.getNombre() ;

            tiempo->end();
            tiempo->retornarTiempo("Tiempo desde la clase Controladores");

            return 1;

            }

    }
        static int consultar(){
                cout << "Ingrese correo alumno" << endl;
                string correo;
                cin >> correo;
                UsuariosEntity usuario = RegistroDao::buscarUsuarioPorCorreo(correo, listaUsuarios);
                /*
                 *Esta funcion apaga el programa si el objeto devuelto esta vacio
                 *if (usuario.getNombre().empty()){
                    return 0;
                }
                */
                return 1;

        }


    ~Controladores();
};

Controladores::Controladores(/* args */){


}

Controladores::~Controladores(){

}
