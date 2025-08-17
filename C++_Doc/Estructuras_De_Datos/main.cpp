#include <iostream>

using namespace std;
int main(){
    auto lang = "C++";
    cout << "Hello and welcome to " << lang << "!\n";

    int opc_usr;
    cout << "Ingrese numero de veces a ejecutar el for" << endl;
    cin >> opc_usr;
    for (int i = 1; i <= opc_usr; i++){
        cout << "i = " << i << endl;
    }

    return 0;
}
