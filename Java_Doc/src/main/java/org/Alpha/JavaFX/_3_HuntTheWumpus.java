package org.Alpha.JavaFX;

import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.application.Application;
import javafx.geometry.Pos;
import javafx.geometry.Rectangle2D;
import javafx.scene.Node;
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

import java.util.HashMap;

public class _3_HuntTheWumpus extends Application {

    private Pane mainPane = new Pane();

    Utilidades utilidades = new Utilidades();

    HashMap<Node, String> mapaElementosPane_1 = new HashMap<>();

    @Override
    public void start(Stage stage) {

        Rectangle2D screen = Screen.getPrimary().getVisualBounds();

        // game escene
        VBox vBox_1_facil = utilidades.barraSuperior (8,5,Pos.CENTER,"Hunt The Wumpus", "Dificultad Facil", new int[]{30,25});
        VBox vBox_2_facil = utilidades.botonInferior(8,5, Pos.CENTER, "Presione", 100, 200);

        BorderPane mainPane = new BorderPane();
        mainPane.setTop(vBox_1_facil);
        mainPane.setBottom(vBox_2_facil);
        mainPane.setCenter(this.mainPane);

        // menu
        BorderPane menuPane = new BorderPane();
        Scene menuScene = new Scene(menuPane, screen.getWidth()-400, screen.getHeight()-150);

        VBox vBox_1_menu = utilidades.barraSuperior (8,5,Pos.CENTER,"Hunt The Wumpus", "Seleccione dificultad", new int[]{40,30});
        VBox vBox_2_menu = utilidades.botonInferior(8,5, Pos.CENTER, "Presione", 100, 200);
        HBox hBox_01 = utilidades.botones(50,50, Pos.CENTER);

        menuPane.setTop(vBox_1_menu);
        menuPane.setCenter(hBox_01);


        Scene easyEscene = new Scene(mainPane, screen.getWidth() - 400, screen.getHeight() - 150);

        //Scene mediumEscene = new Scene(mainPane, screen.getWidth() - 400, screen.getHeight() - 150);

        //Scene hardEscene = new Scene(mainPane, screen.getWidth() - 400, screen.getHeight() - 150);

        stage.setTitle("Hunt The Wumpus");
        stage.setScene(menuScene);
        stage.show();

        Button b_01 = (Button) hBox_01.lookup("#BotonFacil");
        b_01.setOnAction( e -> {
            System.out.println("DIficiltad facil");
            stage.setScene(easyEscene);
            stage.show();
        });


        Button bo = (Button) vBox_2_facil.lookup("#Boton_01");
        bo.setOnAction(
                e -> {
                    System.out.println("ASJDkJA");
                    //stage.setScene(scene);
                    stage.show();
                }
        );

        timeline.setCycleCount(Timeline.INDEFINITE);
        timeline.play();

    }

    // aqui van todos los elementos a mostrar en el pane
    /*private void cargarElementosPanePrincipal(BorderPane pane){
        pane.setStyle("-fx-background-color: #fff;");

        Label title = new Label("Hunt The Wumpus");
        title.setStyle("-fx-text-fill: #c20d0d; -fx-font-size: 20px; -fx-font-weight: bold;");
        pane.setTop(eventLabel);

        //mapaElementosPane_1.put(title, "");


        eventLabel = new Label("Evento actual: 0");
        eventLabel.setStyle("-fx-text-fill: #11caf8; -fx-font-size: 14px;");
        pane.setLeft(eventLabel);
        //mapaElementosPane_1.put(eventLabel, "");

        //pane.setTop(utilidades.newVbox(8, 5,"FF0000FF",Pos.CENTER_LEFT, eventLabel));
    }*/

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