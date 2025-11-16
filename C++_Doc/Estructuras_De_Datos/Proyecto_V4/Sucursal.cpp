#include "Sucursal.h"
#include <iostream>

using namespace std;

Sucursal::Sucursal() : nombre(""), direccion(""), telefono(""), horario("") {}

Sucursal::Sucursal(string nombre, string direccion, string telefono, string horario)
    : nombre(nombre), direccion(direccion), telefono(telefono), horario(horario) {}

Sucursal::~Sucursal() {}

string Sucursal::obtener_nombre() {
    return nombre;
}

string Sucursal::obtener_direccion() {
    return direccion;
}

string Sucursal::obtener_telefono() {
    return telefono;
}

string Sucursal::obtener_horario() {
    return horario;
}

void Sucursal::imprimir_info() {
    cout << "\nNombre: " << nombre << endl;
    cout << "Direccion: " << direccion << endl;
    cout << "Telefono: " << telefono << endl;
    cout << "Horario: " << horario << endl;
}