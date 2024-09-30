class MiClase {
private:
    int numero_privado;
public:
    void setNumero(int n) {
        numero_privado = n;  // Acceso permitido dentro de la clase
    }
};

int main() {
    MiClase obj;
    //obj.numero_privado = 10;  // Error: acceso privado

    MiClase obj;
    obj.setNumero(10);  // Válido y desde otro método / archivo / funcion / clase
    
    return 0;
}

class miclase2{
private:
    /* 
    *   Atributos privados
    *  Métodos privados
    * Constructores privados
    * Destructores privados
    * 
     */
public:
    miclase2(/* args */);
    ~miclase2();

    /*
    *   Atributos publicos
    *   Métodos publicos
    *  Constructores publicos
    * Destructores publicos
    */

};

