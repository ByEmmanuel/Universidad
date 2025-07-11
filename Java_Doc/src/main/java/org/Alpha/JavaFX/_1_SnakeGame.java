package org.Alpha.JavaFX;

import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.application.Application;
import javafx.application.Platform;
import javafx.scene.Scene;
import javafx.scene.input.KeyCode;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;
import javafx.stage.Stage;
import javafx.util.Duration;

import java.awt.*;
import java.util.*;

public class _1_SnakeGame extends Application {

    public static void main(String[] args) {
        launch(args);
    }

    // Para que la snake gire correctamente tendremos que guardar todos sus valores de los nodos inferiores a a la acabeza
    // en un vector, asi para que cuando quiera dar la vuelta vaciemos ese vector en la posicion que se esta moviendo
    // para cuando si la cabeza alcanza un valor que esta tapado (no esta vacio en el vector) ese se chocara y habra terminado el juego
    // tengo un problema y esque estoy alargando el cuerpo de mi cuadrado, no le estoy añadiendo mas cuadrados

    Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
    @Override
    public void start(Stage stage) throws InterruptedException {
        Pane main = new Pane();

        Scene scene = new Scene(main, screenSize.width - 800, screenSize.height - 500);
        iniciarJuego iniciarJuego = new iniciarJuego(scene, main, screenSize, new Rectangle(20,20, Color.RED));

        Runnable runnable = () -> {
            while (true){
                try {
                    Thread.sleep(10);
                    //System.out.println("Corriendo desde otro hilo");
                    double POS_X = iniciarJuego.obtenerPosiciones_X_Y()[0];
                    double POS_Y = iniciarJuego.obtenerPosiciones_X_Y()[1];
                    //System.out.printf(" X %d : Y %d \n" ,(int) POS_X ,(int) POS_Y );

                    //iniciarJuego.iterar_cuerpo(POS_X,POS_Y);

                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
                Platform.runLater(()-> {

                    iniciarJuego.subirVelocidad();
                    iniciarJuego.timeline.play();
                    iniciarJuego.iterar_cuerpo(iniciarJuego.obtenerPosiciones_X_Y()[0], iniciarJuego.obtenerPosiciones_X_Y()[1]);

                });
            }

        };

        Thread hilo_1_ = new Thread(runnable,"Hilo 1");
        hilo_1_.setDaemon(true);
        hilo_1_.start();


        stage.setTitle("Snake Game");
        stage.setScene(scene);
        stage.show();
    }
}

class iniciarJuego{
    int largo_cuadrado = 20;
    int ancho_cuadrado = 20;
    Rectangle rectangle ;
    int tick_tiempo = 20;

    private String direccion = "DERECHA";
    private final int VELOCIDAD = 10; // pixeles por frame
    private int velocidadCuadrado = 100;
    private int tiempoTranscurrido = 0;
    private Dimension dimension = null;
    private Scene scene = null;
    private Pane mainPane = null;

    private Vector<Rectangle> vector_snake = new Vector<>();

    private Queue< Rectangle > cola_snake = new LinkedList<>();
    //Logixa Manzana
    boolean hay_manzana = false;
    //0 == X, 1 == Y
    int[] POS_Manzana = new int[2];

    //private Queue<ArrayList> cola_snake_copia = cola_snake;



    int indice_vector = 0;


    KeyFrame keyFrame = new KeyFrame(Duration.millis(velocidadCuadrado), e -> {
        //moverSnake();
        //noSalirse();
        //subirVelocidad();
        //obtenerPosiciones_X_Y(rectangle);

    });
    Timeline timeline = new Timeline(keyFrame);

    iniciarJuego(Scene scene, Pane mainLayout, Dimension dimension, Rectangle rectangle){
        this.dimension = dimension;
        this.scene = scene;
        this.mainPane = mainLayout;
        this.rectangle = rectangle;

        rectangle.setLayoutX(100);
        rectangle.setLayoutY(100);

        mainLayout.getChildren().add(rectangle);

        // Cada que presiono SPACE se añade un cuadrado
        scene.setOnKeyPressed(event -> {
            KeyCode key = event.getCode();
            if (key == KeyCode.W) {
                direccion = "ARRIBA";

            }
            if (key == KeyCode.S) {
                direccion = "ABAJO";

            }
            if (key == KeyCode.A) {
                direccion = "IZQUIERDA";

            };
            if (key == KeyCode.D) {
                direccion = "DERECHA";

            };
            if (key == KeyCode.SPACE){
                snakelarge(new Rectangle(20,20, Color.RED));
                generarManzana();
            }
            if (key == KeyCode.C){
                salir();
            }
            if (key == KeyCode.F){

            }
            //Por el momento cada que toco una tecla se colocara un nuevo cuadro

        });
        System.out.println(timeline.getKeyFrames().get(0).getTime());
        timeline.setCycleCount(Timeline.INDEFINITE);
    }

    public void subirVelocidad(){
        if (velocidadCuadrado > 50) { // límite mínimo de velocidad
            velocidadCuadrado -= 50;
            //System.out.println("Velocidad = " + velocidadCuadrado);

            timeline.stop(); // detener timeline actual
            timeline.getKeyFrames().clear(); // limpiar KeyFrames


            //Esto ejecuta que se mueva el snake
            KeyFrame nuevoFrame = new KeyFrame(Duration.millis(tick_tiempo), e -> {
                moverSnake();
                noSalirse();
                generarManzana();

                generarEstructuras();
                //generarCampoManzanas();
            });



            timeline.getKeyFrames().add(nuevoFrame);
            timeline.play(); // reiniciar
            System.out.println(timeline.getKeyFrames().get(0).getTime());
        }
    }

    public int[] obtenerPosiciones_X_Y(){
        return new int[]{(int) rectangle.getLayoutX(), (int) rectangle.getLayoutY()};
    }

    public int[] obtenerPosiciones_X_Y_body(Rectangle body){
        return new int[]{(int) body.getLayoutX(), (int) body.getLayoutY()};
    }

    private void noSalirse(){
        if (    rectangle.getLayoutX() < 0 ||
                rectangle.getLayoutX() > dimension.height + 20 ||
                rectangle.getLayoutY() < 0 ||
                rectangle.getLayoutY() > dimension.width - 1360
        ){
            System.out.println("Te saliste");
            salir();
            //reiniciarJuego();
        }
    }
    private void reiniciarJuego(){
        //rectangle.setLayoutX((double) Window.getWindows().size() );
        //rectangle.setLayoutY((double) Window.getWindows().size() );
        rectangle.setLayoutX((double) (dimension.width - 500) / 2);
        rectangle.setLayoutY((double) (dimension.height - 500) / 2 );
    };
    private void salir(){
        System.exit(1);
    }


    public void snakelarge(Rectangle cuerpo_snake){
        //Rectangle rectangle = new Rectangle(largo_cuadrado, 20, Color.RED); // Tamaño definido
        int current_pos_X = obtenerPosiciones_X_Y()[0];
        int current_pos_Y = obtenerPosiciones_X_Y()[1];
        cuerpo_snake.setLayoutX(current_pos_X);
        cuerpo_snake.setLayoutY(current_pos_Y);


        cola_snake.add(cuerpo_snake);
        mainPane.getChildren().add(cuerpo_snake);
    }

    public void snake_body(Rectangle rectangle){
        for (int pos_Head : obtenerPosiciones_X_Y() ){
            //rectangle1.setLayoutX(obtenerPosiciones_X_Y()[0] -= 10 );
            //rectangle1.setLayoutY(obtenerPosiciones_X_Y()[1] -= 10 );

            rectangle.setLayoutX(obtenerPosiciones_X_Y()[0]  );
            rectangle.setLayoutY(obtenerPosiciones_X_Y()[1]  );
        }
    }
    private void moverSnake() {
        switch (direccion) {
            case "ARRIBA":
                rectangle.setLayoutY(rectangle.getLayoutY() - VELOCIDAD);

                //System.out.printf("Hay %d rectangulos", vector_snake.size());
                break;
            case "ABAJO":
                rectangle.setLayoutY(rectangle.getLayoutY() + VELOCIDAD);

                break;
            case "IZQUIERDA":
                rectangle.setLayoutX(rectangle.getLayoutX() - VELOCIDAD);

                break;
            case "DERECHA":
                rectangle.setLayoutX(rectangle.getLayoutX() + VELOCIDAD);
                break;
        }

    }


    //Esta funcion hace que el cuerpo generado se itere y una posicion siga a la otra
    ArrayDeque<int[]> pos_rectangle = new ArrayDeque<>();
    public void iterar_cuerpo(int POS_X, int POS_Y){
        // Posicion de la cabeza
        pos_rectangle.addFirst(new int[]{POS_X, POS_Y});
        if (pos_rectangle.size() > cola_snake.size() + 1){
            pos_rectangle.removeLast();
        }
        //Mueve cada parte del cuerpo a una posicion anterior en el historial
        int i = 1; //se empieza desde 1 porque 0 es la cabeza actual
        for (Rectangle rectangle1 : cola_snake){
            if (i < pos_rectangle.size()){
                int[] pos = (int[]) pos_rectangle.toArray()[i];
                rectangle1.setLayoutX(pos[0]);
                rectangle1.setLayoutY(pos[1]);
                i++;
            }
        }
        if (tick_tiempo <= 20 )tick_tiempo -= 100;
    }

    Deque<Rectangle> cola_manzanas = new ArrayDeque();
    public void generarManzana(){

        Rectangle manzana = new Rectangle(40,40, Color.GREEN);
        if (!hay_manzana){
            //System.out.println("Dimension : " + (int)(Math.random()*scene.getHeight()));

            int valor_random_X = (int) (Math.random() * (mainPane.getWidth() - 50 ));
            int valor_random_Y = (int) (Math.random() * (mainPane.getHeight() - 100));
            int main_layour_width = (int) mainPane.getWidth();
            int main_layour_height = (int) mainPane.getHeight();
            if ( valor_random_X > main_layour_width || valor_random_Y > main_layour_height){
                return;
            }

            POS_Manzana[0] = valor_random_X;
            POS_Manzana[1] = valor_random_Y;

            manzana.setLayoutX(valor_random_X);
            manzana.setLayoutY(valor_random_Y);
            mainPane.getChildren().add(manzana);
            cola_manzanas.add(manzana);

            System.out.println(POS_Manzana[0]);
            System.out.println(POS_Manzana[1]);


            hay_manzana = true;
        }

        //por cada posicion en X si esta en el rango de la posicion de la manzana
        // aumentar uno

        int pos_head_X = obtenerPosiciones_X_Y()[0];
        int pos_head_Y = obtenerPosiciones_X_Y()[1];
        // supongamos que la posicion de la manzana es 100, 100 (x,y)
        //entonces seria >= 80, <= 120

        Rectangle apl = cola_manzanas.peekFirst();
        if (apl != null && rectangle.getBoundsInParent().intersects(apl.getBoundsInParent())) {
            snakelarge(new Rectangle(20,20, Color.RED));
            hay_manzana = false;
            mainPane.getChildren().remove(apl);
            cola_manzanas.pollFirst();
        }

        //System.out.println(obtenerPosiciones_X_Y()[0]);
        //System.out.println(obtenerPosiciones_X_Y()[1]);
    }

    public void generarCampoManzanas(){
        int valor_random_X = (int) (Math.random() * (mainPane.getWidth() - 50 ));
        int valor_random_Y = (int) (Math.random() * (mainPane.getHeight() - 100));
        int main_layour_width = (int) mainPane.getWidth();
        int main_layour_height = (int) mainPane.getHeight();
        if ( valor_random_X > main_layour_width || valor_random_Y > main_layour_height){
            return;
        }

        Rectangle manzana = new Rectangle(40,40, Color.CADETBLUE);
        POS_Manzana[0] = valor_random_X;
        POS_Manzana[1] = valor_random_Y;

        manzana.setLayoutX(valor_random_X);
        manzana.setLayoutY(valor_random_Y);
        mainPane.getChildren().add(manzana);
        cola_manzanas.add(manzana);

    }

    boolean hay_pared = false;
    private ArrayList<Integer> lista_ubi_objetos = new ArrayList<>();
    public void generarEstructuras(){
        int valor_random_Y = (int) (Math.random() * (mainPane.getHeight() - 100));
        int valor_random_X = (int) (Math.random() * (mainPane.getWidth() - 50 ));

        Rectangle pared = new Rectangle(20,70, Color.gray(0.8));
        pared.setLayoutX(valor_random_X);
        pared.setLayoutY(valor_random_Y);

        if (!hay_pared){
            int system_time = (int) System.nanoTime();
            if (system_time % 3 == 0){
                mainPane.getChildren().add(pared);
            }

            hay_pared = true;
        }


    }

}