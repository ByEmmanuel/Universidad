package org.Alpha.JavaFX;

import java.io.IOException;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;

public class _2_Llamadas_API_Python {

    private static final String url_original = "http://127.0.0.1:8000/Snake_Game/";
    private static final StringBuilder API_URL = new StringBuilder(url_original);
    private static String resultado = "";
    private static HttpURLConnection conn;

    public void peticion_POST_Coordenadas(int x_coord, int y_coord) throws IOException {
        try{

            API_URL.append(x_coord);
            API_URL.append("&");
            API_URL.append(y_coord);
            URL url = new URL(API_URL.toString());
            conn = (HttpURLConnection) url.openConnection();
            System.out.println(url);
            conn.setRequestMethod("POST");
            conn.setRequestProperty("Accept", "application/json");

            if (conn.getResponseCode() != 200){
                throw new RuntimeException("Failed : HTTP ERROR CODE: " + conn.getResponseCode());
            }

            //BufferedReader br = new BufferedReader(new InputStreamReader((conn.getInputStream())));

            String output;
            //System.out.println("Output from server...\n");
            /*while ((output=br.readLine()) != null){
                resultado = output;
            }*/

            API_URL.delete(0,API_URL.length());
            API_URL.append(url_original);
        }catch (MalformedURLException e){
            System.out.println(e.getMessage());
        }
    }

    public void cerrar_conexion(){
        conn.disconnect();
    }

    public static String getResultado() {
        return resultado;
    }

    public static void setResultado(String resultado) {
        _2_Llamadas_API_Python.resultado = resultado;
    }
}
