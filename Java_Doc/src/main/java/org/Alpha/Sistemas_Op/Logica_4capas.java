package org.Alpha.Sistemas_Op;

import java.util.Scanner;

public class Logica_4capas {
    // constantes globales
    final static String direccionIP = "192.180.192.12"; // Simulamos que es una IP en lista negra
    final static int puerto = 80;

    final static String firewall = "192.001.001.002";
    final static String[] Sistemas_Op = {"Linux VM", "Mac OS"};

    final static String sql_injection = "`select $user where `password` == 1";

    final static String[] direcciones_IP_Validas = new String[3];
    final static String password = "HolaMund01";

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        // llenar el vector de direcciones ip validas
        direcciones_IP_Validas[0] = "192.001.001.005";
        direcciones_IP_Validas[1] = "192.001.001.006";
        direcciones_IP_Validas[2] = "192.001.001.007";

        // 1. CAPA DE RED

        System.out.println("Primera capa ------ (RED)");
        System.out.println("Ingrese su direccion IP:");

        String direccion_ip = sc.nextLine();

        //  firewall de red bloquea IPs maliciosas conocidas antes de llegar al servidor
        if (direccion_ip.equals(direccionIP)){
            System.out.println("[Bloqueo] No estas autorizado. Conexión rechazada en el perímetro de red.");
            System.exit(0);
        }
        System.out.println("[Éxito] Tráfico de red permitido.\n");

        // 2. CAPA DE INFRAESTRUCTURA
        System.out.println("Segunda capa----------- (INFRAESTRUCTURA)");
        System.out.println("Ingresa la direccion DNS de tu proveedor:");

        String proveedor = sc.nextLine();
        // Verificamos que el tráfico provenga de nuestra infraestructura permitida
        if (!proveedor.equals(firewall)){
            System.out.println("[Bloqueo] DNS desconocido. Posible suplantación de infraestructura.");
            System.exit(0);
        }

        System.out.println("Ingresa el Sistema Operativo del servidor (Ej: Linux VM):");
        String so_actual = sc.nextLine();
        boolean osValido = false;

        // Verificamos que el sistema operativo esté reforzado y parcheado (en lista blanca)
        for (String os : Sistemas_Op) {
            if (os.equals(so_actual)) {
                osValido = true;
                break;
            }
        }
        if (!osValido) {
            System.out.println("[Bloqueo] Sistema operativo no compatible o vulnerable. Aislamiento activado.");
            System.exit(0);
        }
        System.out.println("[Éxito] Entorno de infraestructura verificado.\n");


        // 3. CAPA DE APLICACIÓN
        System.out.println("Tercera capa----------- (APLICACIÓN)");
        System.out.println("Ingresa tu contraseña para acceder al sistema:");
        String input_app = sc.nextLine();

        // El codigo sanitiza y valida los inputs para evitar inyecciones
        if (input_app.contains("select") || input_app.equals(sql_injection)) {
            System.out.println("[Bloqueo crítico] Intento de Inyección SQL detectado. Input neutralizado.");
            System.exit(0);
        }

        // Proceso de autenticación
        if (!input_app.equals(password)) {
            System.out.println("[Bloqueo] Credenciales incorrectas.");
            System.exit(0);
        }
        System.out.println("[Éxito] Autenticación válida. Sesión iniciada sin código malicioso.\n");


        // 4. CAPA DE DATOS (Cifrado y acceso final)
        System.out.println("Cuarta capa----------- (DATOS)");
        System.out.println("Accediendo al motor de bases de datos...");

        // Simulamos que el atacante (o usuario) ve el dato tal como está en el disco
        String dato_en_disco = "x8F9B!AES256#DatoProtegido";
        System.out.println("Dato en reposo (Cifrado): " + dato_en_disco);

        // Solo después de pasar las 3 capas anteriores se aplica la lógica de descifrado
        System.out.println("Desencriptando información utilizando llaves seguras en memoria...");
        String dato_real = "Información confidencial: Los servidores están en GDL.";

        System.out.println("[Éxito] Acceso concedido al dato en texto claro:");
        System.out.println("-> " + dato_real);

        sc.close();
    }
}