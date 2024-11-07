#include <iostream>
#include <vector>
#include <iomanip> // para std::setw

using namespace std;

class CalendarioTerminal {
private:
    vector<int> calendarioActual;
    vector<int> diaOcupado;

    // Función que determina si un año es bisiesto
    static bool esBisiesto(int year) {
        return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
    }

    // Función que devuelve el número de días en un mes dado
    static int obtenerDiasEnMes(int mes, int year) {
        vector<int> diasPorMes = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (mes == 2 && esBisiesto(year)) {
            return 29;
        }
        return diasPorMes[mes - 1];
    }

    // Función para calcular el día de la semana del primer día del mes
    static int obtenerPrimerDiaDelMes(int mes, int year) {
        int d = 1, m = (mes < 3) ? mes + 12 : mes, y = (mes < 3) ? year - 1 : year;
        int k = y % 100;
        int j = y / 100;
        int h = (d + (13 * (m + 1)) / 5 + k + k / 4 + j / 4 - 2 * j) % 7;
        return (h + 5) % 7;
    }

public:
    // Función para generar el calendario y marcar el día seleccionado
    vector<int> mostrarCalendario(int seleccionDia, int mes, int year) {
        calendarioActual.clear();
        vector<std::string> diasSemana = {"Dom", "Lun", "Mar", "Mie", "Jue", "Vie", "Sab"};
        int primerDia = obtenerPrimerDiaDelMes(mes, year);
        int diasEnMes = obtenerDiasEnMes(mes, year);

        cout << "Calendario de " << mes << "/" << year << "\n";
        for (const auto& dia : diasSemana) {
            cout << setw(4) << dia;
        }
        cout << "\n";

        // Espacios iniciales antes del primer día del mes
        for (int i = 0; i < primerDia; ++i) {
            calendarioActual.push_back(0);  // Usa 0 como marcador de espacio vacío
            cout << setw(4) << " ";
        }

        for (int dia = 1; dia <= diasEnMes; ++dia) {
            calendarioActual.push_back(dia);
            if (seleccionDia == dia) {
                diaOcupado.push_back(dia);
            }
            cout << setw(4) << dia;
            if ((primerDia + dia) % 7 == 0) {
                cout << "\n";
            }
        }
        cout << "\n";
        return calendarioActual;
    }

    // Función estática para mostrar el calendario guardado
    static void mostrarCalendario(const vector<int>& calendarioGuardado, int seleccionDia) {
        int diaSemana = 0;
        for (int dia : calendarioGuardado) {
            if (dia == 0) {
                cout << setw(4) << " ";
            } else if (dia == seleccionDia) {
                cout << setw(3) << dia << "x";
            } else {
                cout << setw(4) << dia;
            }
            diaSemana++;

            if (diaSemana % 7 == 0) {
                cout << "\n";
            }
        }
        cout << "\n";
    }
};
