#include <iostream>
#include <cmath>
#include <random>

using namespace std;

class Holamundo{
public: 
    int saludar(){
        cout << "hola mundo" << "\n";
        return 0;
    }
    Holamundo(){
        cout << random()/100000000 << "\n";
    }

};

int main(){

    
    for (int i = 0; i < 10; i++){
        cout << " " << "\n";
        Holamundo* hola = new Holamundo();
        //hola->saludar();
    }

    return 0;

};