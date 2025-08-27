#include <iostream>
#include "Gato.h"
#include "Carro.h"

/*
*   Debera de hacer un proyecto con las siguentes especificaciones:
    Realizar dos clases cada uno: con 3 atributos, y 4 metodos
    El nivel de acceso de todos sus elementos debera ser publico
    Realice dos instancias/objetos en el archivo main.cpp
    Utilice todos los metodos de las dos instacias que creo en el main
 */

using namespace std;
int main(){

    Gato* gato = new Gato();

    gato->set_edad(12);
    gato->hacer_ruido();
    gato->set_nombre_raza("Pepe", "siammes");
    gato->mostrar_caracteristicas();

    Carro* carro = new Carro();

    carro->set_año(2032);
    carro->set_marca("TESLA");
    carro->set_modelo("Y3");
    carro->imprimir();

    delete gato;
    delete carro;

    return 0;
}
