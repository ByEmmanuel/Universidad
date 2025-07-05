package org.Alpha.JavaFX;

import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.input.KeyCode;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;
import javafx.stage.Stage;
import javafx.stage.Window;
import javafx.util.Duration;

import java.awt.*;
import java.util.Date;

public class _1_SnakeGame extends Application {

    public static void main(String[] args) {
        launch(args);
    }

    private String direccion = "DERECHA";
    private final Rectangle rectangle = new Rectangle(20, 20, Color.RED); // Tamaño definido
    private final int VELOCIDAD = 10; // pixeles por frame
    Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();

    @Override
    public void start(Stage stage) {

        rectangle.setLayoutX(100);
        rectangle.setLayoutY(100);

        Pane main = new Pane();
        main.getChildren().add(rectangle);


        Scene scene = new Scene(main, screenSize.width - 500, screenSize.height - 500);

        scene.setOnKeyPressed(event -> {
            KeyCode key = event.getCode();
            if (key == KeyCode.W) direccion = "ARRIBA";
            if (key == KeyCode.S) direccion = "ABAJO";
            if (key == KeyCode.A) direccion = "IZQUIERDA";
            if (key == KeyCode.D) direccion = "DERECHA";
        });


        Timeline timeline = new Timeline(new KeyFrame(Duration.millis(10), e -> {
                moverSnake();
                noSalirse();
                subirVelocidad();
                obtenerPosiciones_X_Y();

            }
        ));

        timeline.setCycleCount(Timeline.INDEFINITE);
        timeline.play();


        stage.setTitle("Snake Game");
        stage.setScene(scene);
        stage.show();
    }

    int tiempoTranscurrido = 0;
    private void subirVelocidad(){
        //Long timepo = System.nanoTime() / 1_000_000_000l;
        Long timepo = System.nanoTime() / 1_000_000_000;
        if (timepo % 5 == 0){
            //System.out.println("Pasaron 10 segundos");

            //System.out.println();
            if (tiempoTranscurrido == 5){
                salir();
            };

            tiempoTranscurrido++;
        }
            System.out.println();
            System.out.println(rectangle.getLayoutY());
        //System.out.println(timepo);
    }

    public void obtenerPosiciones_X_Y(){

    }

    private void noSalirse(){
        if (    rectangle.getLayoutX() <= 0 ||
                rectangle.getLayoutX() > screenSize.height + 320 ||
                rectangle.getLayoutY() <= 0 ||
                rectangle.getLayoutY() > screenSize.width - 1000

        ){
            salir();
        }
    }

    private void salir(){
        System.exit(1);
    }

    private void moverSnake() {
        switch (direccion) {
            case "ARRIBA":
                rectangle.setLayoutY(rectangle.getLayoutY() - VELOCIDAD);
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
}