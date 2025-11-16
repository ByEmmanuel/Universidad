#ifndef SUCURSAL_H
#define SUCURSAL_H

#include <string>
using namespace std;

class Sucursal {
private:
    string nombre;
    string direccion;
    string telefono;
    string horario;

public:
    Sucursal();
    Sucursal(string nombre, string direccion, string telefono, string horario);
    ~Sucursal();
    
    string obtener_nombre();
    string obtener_direccion();
    string obtener_telefono();
    string obtener_horario();
    
    void imprimir_info();
};

#endif // SUCURSAL_H