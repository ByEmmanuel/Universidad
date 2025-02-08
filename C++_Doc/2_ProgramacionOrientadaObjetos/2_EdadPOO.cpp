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
    int añoNacimiento;
    int mesNacimiento;

    MensajeUsuario(string mensaje, string nombreUsuario, int añoNacimiento){
        this->mensaje = mensaje;
        this->nombreUsuario = nombreUsuario;
        this->añoNacimiento = añoNacimiento;
    };
    MensajeUsuario(){

    };
    inline void imprimir() const{
    cout << mensaje << " "<<  nombreUsuario << " Del año: " << añoNacimiento << endl;
    };
    static inline void imprimirEdad(string& mensaje, string &nombreUsuario, int &edadUsuario){
    cout << mensaje << endl;
    cout <<  nombreUsuario << endl;
    cout << edadUsuario << endl;
    }
    static inline void calcularEdad(int &añoNacimiento, int &añoActual, int &mesNacimiento, int &mesActual ){
        if (mesActual < mesNacimiento){
            cout << "Edad Actual Del Usuario es: " << (añoActual-añoNacimiento) - 1 << endl;
            return;
        }
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
    int opc5;
    bool bandera = true;

    time_t t = time(nullptr);
    tm* now = localtime(&t);
    int añoActual = now->tm_year + 1900;
    int mesActual = now->tm_mon + 1;


    // Muestra el año actual
    cout << "El año actual es: " << añoActual << endl;



    while (bandera){

        //Iniciar la clase
        MensajeUsuario* mensajeUsuario = new MensajeUsuario();
        cout << "Ingrese Mensaje Para imprimr" << endl;
        cin >> opc1;
        cout << "Ingrese Nombre Usuario" << endl;
        cin >> opc2;
        cout << "Ingrese Año Nacimiento Usuario" << endl;
        cin >> opc3;
        cout << "Ingrese mes Nacimiento Usuario" << endl;
        cin >> opc5;
        //PASO DE VALORES POR ASIGNACION
        mensajeUsuario->mensaje = opc1;
        mensajeUsuario->nombreUsuario = opc2;
        mensajeUsuario->añoNacimiento = opc3;
        mensajeUsuario->mesNacimiento = opc5;
        mensajeUsuario->imprimir();

        cout << "Desea Calcular la edad? \n 1: SI \n 2: NO" << endl;
        cin >> opc4;
        if(opc4 == 1){
            //PASO DE VALORES POR PASO DE PARAMETROS POR REFERENCIA
            MensajeUsuario::imprimirEdad(opc1, opc2, opc3);
            MensajeUsuario::calcularEdad(opc3, añoActual, opc5, mesActual);
        }else{
            bandera = false;
            cout << "!Hasta luego¡" <<endl;
            delete mensajeUsuario;
        }

    }





    return 0;
}
