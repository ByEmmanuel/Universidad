package org.Alpha.JavaFX;

import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.geometry.Rectangle2D;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;
import javafx.scene.layout.VBox;
import javafx.stage.Screen;
import javafx.stage.Stage;
import javafx.util.Duration;
import org.Alpha.JavaFX.HuntTheWumpusLogic.Utilidades;

public class _3_HuntTheWumpus extends Application {

    private Pane mainPane = new Pane();

    Utilidades utilidades = new Utilidades();

    @Override
    public void start(Stage stage) {

        Rectangle2D screen = Screen.getPrimary().getVisualBounds();

        // MENU --------------------------
        BorderPane menuPane = new BorderPane();
        Scene menuScene = new Scene(menuPane, screen.getWidth()-400, screen.getHeight()-150);

        VBox barraSuperior = utilidades.barraSuperior(new Utilidades.ConfigHeader(8,5,Pos.CENTER,"Hunt The Wumpus", "Seleccione dificultad", new int[]{35,30}));
        HBox hBox_01 = new HBox(
                utilidades.botones(new Utilidades.ConfigBoton_01(100,50, Pos.CENTER, "Facil", "009900","PaneBotonesDificultad", 200, 100, "BotonFacil")),
                utilidades.botones(new Utilidades.ConfigBoton_01(100,50, Pos.CENTER, "Medio", "FFD000","PaneBotonesDificultad", 200, 100, "BotonMedio")),
                utilidades.botones(new Utilidades.ConfigBoton_01(100,50, Pos.CENTER, "Dificil", "CC0000","PaneBotonesDificultad", 200, 100, "BotonDificil"))
        );
        hBox_01.setAlignment(Pos.BASELINE_CENTER);
        hBox_01.setMaxWidth(Double.MAX_VALUE);  // esto abarca todo el ancho
        hBox_01.setPadding(new Insets(15));
        hBox_01.setStyle("-fx-background-color: #2c3e50;");
        menuPane.setTop(barraSuperior);
        menuPane.setBottom(hBox_01);

        // GAME ESCENE  -> EASY -----------------------
        BorderPane easyPane = new BorderPane();
        Scene easyEscene = new Scene(easyPane, screen.getWidth() - 400, screen.getHeight() - 150);

        VBox vBox_1_facil = utilidades.barraSuperior (
                new Utilidades.ConfigHeader(8,5,Pos.CENTER,"Hunt The Wumpus", "Dificultad Facil", new int[]{30,25})
        );

        /*Button b_salir = (Button) vBox_1_facil.lookup("#BotonSalir");
        b_salir.setOnAction(e -> System.exit(-1));*/

        VBox vBox_2_facil = utilidades.botonInferior(new Utilidades.ConfigBoton(8,5, Pos.CENTER, "Presione", 100, 200));
        easyPane.setTop(vBox_1_facil);
        easyPane.setBottom(vBox_2_facil);
        easyPane.setCenter(this.mainPane);



        //Scene mediumEscene = new Scene(easyPane, screen.getWidth() - 400, screen.getHeight() - 150);

        //Scene hardEscene = new Scene(easyPane, screen.getWidth() - 400, screen.getHeight() - 150);

        stage.setTitle("Hunt The Wumpus");
        stage.setScene(menuScene);
        stage.show();

        // botones de dificultad (lookup seguro, ya está en Scene visible)
        ((Button) hBox_01.lookup("#BotonFacil")).setOnAction(e -> {
            stage.setScene(easyEscene);

            System.out.println("HOAKSd");
        });

        ((Button) hBox_01.lookup("#BotonMedio")).setOnAction(e -> {
            System.out.println("Dificultad media — pendiente");
        });

        ((Button) hBox_01.lookup("#BotonDificil")).setOnAction(e -> {
            System.out.println("Dificultad difícil — pendiente");
        });

        ((Button) vBox_2_facil.lookup("#Boton_01")).setOnAction(e -> {
            System.out.println("Botón inferior presionado");
        });

        ((Button) vBox_1_facil.lookup("#BotonMenu")).setOnAction(e -> {
            stage.setScene(menuScene);
        });

        ((Button) barraSuperior.lookup("#BotonSalir")).setOnAction(e -> {
            System.exit(0);
        });

        timeline.setCycleCount(Timeline.INDEFINITE);
        timeline.play();

    }


    // abstraer elementos para que este archivo se vea limpio
    // Instancia a una clase de objetos

    KeyFrame keyFrame = new KeyFrame(Duration.millis(300), e -> {
        // lógica del juego aquí
    });
    Timeline timeline = new Timeline(keyFrame);



    public static void main(String[] args) {
        launch(args);
    }
}