#include <iostream>
using namespace std;

class Inversion {
public:
    virtual int convertirPesoAdolar() = 0;
    virtual int convertirDolarApeso() = 0;
};

class Divisa {
public:
    string tipoMoneda;
    int moneda;
};

class Moneda : public Divisa, public Inversion {
private:
    int peso = 0;
    int dolar = 0;

public:
    void pideDatos() {
        cout << "Ingrese moneda (1: Peso, 2: Dólar):" << endl;
        int opcUsr;
        cin >> opcUsr;
        switch (opcUsr) {
            case 1:
                cout << "Ingrese cantidad en pesos:" << endl;
                cin >> peso;
                tipoMoneda = "Peso";
                break;
            case 2:
                cout << "Ingrese cantidad en dólares:" << endl;
                cin >> dolar;
                tipoMoneda = "Dólar";
                break;
            default:
                cout << "Opción no válida" << endl;
                break;
        }
    }

    int convertirPesoAdolar() override {
        return static_cast<int>(peso / 20.3);
    }

    int convertirDolarApeso() override {
        return static_cast<int>(dolar * 20.3);
    }
};

class Temperatura {
private:
    double fahrenheit = 0;
    double celsius = 0;

public:
    void pideDatos() {
        cout << "Ingrese grados Fahrenheit:" << endl;
        cin >> fahrenheit;
        cout << "Ingrese grados Celsius:" << endl;
        cin >> celsius;
    }

    void muestraTemperatura() {
        cout << "Fahrenheit: " << fahrenheit << endl;
        cout << "Celsius: " << celsius << endl;
    }
};

class Clima {
private:
    Temperatura grado;

public:
    void pideDatos() {
        grado.pideDatos();
    }

    void muestraTemperatura() {
        grado.muestraTemperatura();
    }
};

int main() {
    bool bandera = true;
    
    while (bandera) {
        cout << "Ingrese opción usuario:" << endl;
        cout << "1: Divisas" << endl;
        cout << "2: Temperatura" << endl;
        cout << "3: Salir" << endl;
        int opcUsr;
        cin >> opcUsr;
        
        switch (opcUsr) {
            case 1: {
                Moneda moneda;
                moneda.pideDatos();
                cout << "Peso a dólar: " << moneda.convertirPesoAdolar() << endl;
                cout << "Dólar a peso: " << moneda.convertirDolarApeso() << endl;
                break;
            }
            case 2: {
                Clima clima;
                clima.pideDatos();
                clima.muestraTemperatura();
                break;
            }
            case 3:
                bandera = false;
                break;
            default:
                cout << "Opción no válida" << endl;
                break;
        }
    }
    return 0;
}

