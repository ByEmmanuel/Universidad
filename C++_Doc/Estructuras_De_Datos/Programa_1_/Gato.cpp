//
// Created by Jesus Emmanuel Garcia on 8/22/25.
//

#include "Gato.h"
#include <string>


using namespace std;

void Gato::hacer_ruido(){
    cout << "miau" << "\n";
};

void Gato::set_edad(int edad){
    this->edad_meses = edad;
};

void Gato::set_nombre_raza(string nombre, string raza){
    this->nombre = nombre;
    this->raza = raza;
};

void Gato::mostrar_caracteristicas(){
    cout << "Edad gato en meses: " << this->edad_meses << "\n";
    cout << "Nombre gato: " << this->nombre <<"\n";
    cout << "Raza gato: " << this->raza << "\n\n";
};

