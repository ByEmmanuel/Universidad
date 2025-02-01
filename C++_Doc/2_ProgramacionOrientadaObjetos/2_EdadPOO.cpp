//
// Created by Jesus Emmanuel Garcia on 1/31/25.
//
#include <iostream>
#include <time.h>
#include <ctime>
#include <stdlib.h>
#include <stdio.h>
#include <string>

using namespace std;

class MensajeUsuario{
public :
    string mensaje;
    string nombreUsuario;
    int edadUsuario;

    MensajeUsuario(string mensaje, string nombreUsuario, int edadUsuario){
        this->mensaje = mensaje;
        this->nombreUsuario = nombreUsuario;
        this->edadUsuario = edadUsuario;
    };
    MensajeUsuario(){

    };

    inline void imprimir() const{
    cout << mensaje << endl;
    cout <<  nombreUsuario << endl;
    cout << edadUsuario << endl;
    };
    inline void imprimirEdad(string& mensaje, string &nombreUsuario, int &edadUsuario){
    cout << mensaje << endl;
    cout <<  nombreUsuario << endl;
    cout << edadUsuario << endl;
    }
    inline void calcularEdad(int &añoNacimiento, int &añoActual){
        cout << "Edad Actual Del Usuario es: " << (añoActual-añoNacimiento) << endl;
    };
private:



};

int main()
{
    string opc1;
    string opc2;
    int opc3;
    int opc4;
    bool bandera = true;

    time_t t = time(nullptr);
    tm* now = localtime(&t);
    int añoActual = now->tm_year + 1900;

    // Muestra el año actual
    cout << "El año actual es: " << añoActual << endl;

    //Iniciar la clase
    MensajeUsuario* mensajeUsuario = new MensajeUsuario();
    cout << "Ingrese Mensaje Para imprimr" << endl;
    cin >> opc1;
    cout << "Ingrese Nombre Usuario" << endl;
    cin >> opc2;
    cout << "Ingrese Año Nacimiento Usuario" << endl;
    cin >> opc3;

    //PASO DE VALORES POR ASIGNACION
    mensajeUsuario->mensaje = opc1;
    mensajeUsuario->nombreUsuario = opc2;
    mensajeUsuario->edadUsuario = opc3;
    mensajeUsuario->imprimir();

    while (bandera){
        cout << "Desea volver a imprimir? \n 1: SI \n 2: NO" << endl;
        cin >> opc4;
        if(opc4 == 1){
            //PASO DE VALORES POR PASO DE PARAMETROS
            mensajeUsuario->imprimirEdad(opc1, opc2, opc3);
            mensajeUsuario->calcularEdad(opc3, añoActual);
        }else{
            bandera = false;
            cout << "!Hasta luego¡" <<endl;
        }
    }



    return 0;
}
