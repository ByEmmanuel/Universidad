/*
* Created By Jesus Emmanuel at 14/03/25
* */

/*
* Palabras clave de la actividad,
* "Empresa" Cuenta con Obreros Y Directivos
* Todos tienen un identificador unico (id)
* Obrero - Funciones Unicas
* Directivo - 4 tipos -> Validadores
* Cada directivo tiene una oficina -> validadores
*
* */

import java.util.ArrayList;
import java.util.Scanner;

public class EmpresaX {

    private long id_Usuario;

    public static void main(String[] args) {

        boolean bandera = true;

        while(bandera){
            System.out.println("Ingrese Opcion: ");
            System.out.println("1: Directivo.\n2: Obrero");
            Scanner scanner = new Scanner(System.in);
            int opcUsr = scanner.nextInt();
            Obrero obrero = new Obrero();
            Directivo directivo = new Directivo();
            if(opcUsr == 1){
                System.out.println("Ingrese tipo de puesto; ");
                int opcDirectivo = scanner.nextInt();
                directivo.definirOficina(opcDirectivo);
                System.out.println("Tu Oficina es; " + directivo.obtenerOficina());
                directivo.setId_Usuario();
                System.out.println("Tu ID DE USUARIO ES; " + directivo.getId_Usuario());
                System.out.println("Deseas repetir el proceso?\n 1; Si\n 2; NO");
                System.out.println("Deseas repetir el proceso?\n1: Si\n2: NO");
                if (scanner.nextInt() == 2) {
                    bandera = false;
                }
            } else if (opcUsr == 2) {
                obrero.asignarHoras(scanner);
                System.out.println("Deseas ver tus horas?\n 1: SI\n 2: NO ");
                if (scanner.nextInt() == 1){
                    obrero.imprimirHorasObrero();
                }
                System.out.println("Deseas repetir el proceso?\n 1; Si\n 2; NO");
                if (scanner.nextInt() == 2){
                    bandera = false;
                }
            }
            scanner.close();
        }
    }

    public long getId_Usuario() {
        return id_Usuario;
    }

    public void setId_Usuario() {
        this.id_Usuario +=1 ;
    }
}

class Directivo extends EmpresaX{
    public Directivo(){
        System.out.println(this.getClass());
    }
    int tipoDirectivo;
    String Oficina;
    public void definirOficina(int opcDir) {
        switch (opcDir) {
            case 1:
                this.Oficina = "oficinas privadas";
                break;
            case 2:
                this.Oficina = "cubículos compartidos";
                break;
            case 3:
                this.Oficina = "escritorios fuera de las ubicaciones A y B";
                break;
            default:
                this.Oficina = "Ubicación no definida";
                break;
        }
        this.tipoDirectivo = opcDir;
    }


    public String obtenerOficina(){
        return this.Oficina;
    }

}

class Obrero extends EmpresaX{
    ArrayList<Integer> horasPDObrero = new ArrayList<>();

    public void asignarHoras(Scanner scanner){
        for (int i = 0; i < 5; i++){
            System.out.println("Ingresa Horas para el dia " + (i+1) + "/5");
            horasPDObrero.add(scanner.nextInt());
        }
    }

    public void imprimirHorasObrero(){
        for (int i = 0; i < horasPDObrero.size(); i++){
            System.out.println("Dia: " + (i+1) + " ; " + horasPDObrero.get(i));
        }
    }

    public Obrero(){
        System.out.println(this.getClass());
    }

}
