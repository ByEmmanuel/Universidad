//
// Created by Jesus Emmanuel Garcia on 2/13/25.
//

//  Para el maestro se quiere calcular su sueldo quincenal de acuerdo
//  a la hora clase que se le paga. Si el maestro tiene más de 10 años de
//  antigüedad recibe 120.00 la hora, si tiene más de 20 años de antigüedad recibe 210.00 y si
//  tiene menos de 10 años recibe 95.00 la hora. Tomar en cuenta que el maestro trabaja de lunes a viernes.
//  El maestro cuenta con código, nombre y número de grupos a los que da clase. Imprimir
//  todos los datos más el sueldo quincenal.


#include <iostream>
#include <ostream>
#include <string>

using namespace std;

class Persona{
    public :
    int codigo;
    string nombre;

    Persona(){
        cout << "Hola desde la clase alumno" << endl;
    }

    [[nodiscard]] int codigo1() const
    {
        return codigo;
    }

    void set_codigo()
    {
        int codigo;
        cin >> codigo;
        this->codigo = codigo;
    }

    [[nodiscard]] string nombre1() const
    {
        return nombre;
    }

    void set_nombre(/*const string& nombre*/)
    {
        string nombre;
        cin >> nombre;
        this->nombre = nombre;
    }
};

class Alumno:Persona{
    private:

    public:
    static inline double calcularPromedio(double calificaciones, int numeroSem){
        return  calificaciones/numeroSem;
    }

};

class Maestro:Persona{
    private:
    public:

    static inline int calucularSalario(int tiempoAntiguedad, int numeroGrupos){
        //Definir el numero de horas por grupo
        // 1  grupo = 5 hrs a la semana , 2 grupos = 10 hrs, 3 grupos = 15
        // entonces 1 grupo = 10 hrs por quincena
        // 5 grupos = 50 hrs por quincena
        // Operacion aritmetica seria, (numGrupos ) * n donde n representa la constante de pago por hora
        if (tiempoAntiguedad > 20){

            return (numeroGrupos * 10) * 220 ;
        }else if (tiempoAntiguedad < 20 && tiempoAntiguedad > 10){
            return (numeroGrupos * 10) * 220 ;
        }
        return (numeroGrupos * 10) * 95 ;

    }
};

int main(){
    auto persona = new Persona();
    auto maestro = new Maestro;

    cout << "Ingrese nombre Usuario" << endl;
    persona->set_nombre();

    cout << "Ingrese Codigo Usuario" << endl;
    persona->set_codigo();

    int bandera = 1;
    while (bandera){
        cout << "Ingrese opcion del menu" << endl;
        cout << "1; Maestros " << endl;
        cout << "2; Alumnos " << endl;
        cout << "3; Salir " << endl;

        int opcUsr;
        cin >> opcUsr;
        if (opcUsr == 3){
            bandera = 0;
        }
        switch (opcUsr){
            case 1:

                int tiempoAntiguedad, numeroGrupos;
                cout << "Ingrese TIempo antiguedad" << endl;
                cin >> tiempoAntiguedad;
                cout << "Ingrese numero de grupos" << endl;
                cin >> numeroGrupos;

                cout << "Tu salario quincenal es; " << Maestro::calucularSalario(tiempoAntiguedad,numeroGrupos) << endl;

                break;
            case 2:

                int calificacioPS = 0, numeroSemestre ;
                cout << "Ingrese numero semestre actual" << endl;
                cin >> numeroSemestre;
                for (int i = 0; i < numeroSemestre; i++){
                    int a;
                    cout << "Ingrese numero de calificacion total en el semestre: " << i + 1 << endl;
                    cin >> a;

                    calificacioPS = calificacioPS + a ;
                }
                cout << "Tu promedio escolar es; " << Alumno::calcularPromedio(calificacioPS, numeroSemestre) << endl;

                break;

        }

    };

    return 0;
}