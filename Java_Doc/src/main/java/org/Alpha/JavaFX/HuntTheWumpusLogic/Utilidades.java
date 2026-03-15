package org.Alpha.JavaFX.HuntTheWumpusLogic;

import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;
import javafx.scene.layout.VBox;

public class Utilidades {

    // creo que una de las mejores estrategias para ahorrar lineas de codigo es hacer algo tal que
    // var a funcion(parametros) (Retorna elemento)
    // linea 2
    // pane.getchildren().add(a);

    public record ConfigVBox(int espaciado, int insets, Pos alineacion, String texto, int pos_X, int pos_Y){}
    public record ConfigHeader(int espaciado, int insets, Pos pos, String texto_1, String texto_2, int[] tamaño) {}
    public record ConfigBoton(int espaciado, int insets, Pos pos, String texto, int pos_X, int pos_Y){}
    public record ConfigBoton_01(int espaciado, int insets, Pos pos, String texto, String color, String pane_id, int size_X, int size_Y, String boton_id){}

    public VBox barraSuperior(ConfigHeader c) {

        VBox vBox = new VBox(c.espaciado());
        vBox.setPadding(new Insets(c.espaciado()));
        vBox.setStyle("-fx-background-color: #2c3e50;");
        vBox.setId("Vbox_01");

        // ── Textos centrados ──────────────────────────────────
        Label title = new Label(c.texto_1());
        title.setStyle("-fx-text-fill: #c00f0f; -fx-font-size: " + c.tamaño()[0] + "px; -fx-font-weight: bold;");
        title.setId("label_01");

        Label eventLabel = new Label(c.texto_2());
        eventLabel.setStyle("-fx-text-fill: #1fbbe1; -fx-font-size: " + c.tamaño()[1] + "px;");
        eventLabel.setId("label_02");

        VBox textos = new VBox(4, title, eventLabel);
        textos.setAlignment(Pos.CENTER);

        // ── Botón arriba izquierda ────────────────────────────
        Button btnMenu = new Button("MENU");
        btnMenu.setId("BotonMenu");
        btnMenu.setPrefSize(90, 30);
        btnMenu.setStyle("-fx-background-color: #e74c3c; -fx-text-fill: white; -fx-font-size: 11px;");

        Button btnSalir = new Button("SALIR");
        btnSalir.setId("BotonSalir");
        btnSalir.setPrefSize(90, 30);
        btnSalir.setStyle("-fx-background-color: #e74c3c; -fx-text-fill: white; -fx-font-size: 11px;");

        // ── BorderPane interno que los combina ────────────────
        BorderPane fila = new BorderPane();
        fila.setLeft(btnMenu);       // izquierda
        fila.setRight(btnSalir);
        fila.setCenter(textos);      // centro
        BorderPane.setAlignment(btnMenu, Pos.CENTER_LEFT);
        BorderPane.setMargin(btnMenu, new Insets(0, 0, 0, 5)); // margen izquierdo

        vBox.getChildren().add(fila);
        return vBox;
    }

    public VBox botonInferior(ConfigBoton c){
        VBox vBox = new VBox(c.espaciado());
        vBox.setPadding(new Insets(c.insets()));
        vBox.setStyle("-fx-background-color: #2c3e50;");
        vBox.setAlignment(c.pos());
        vBox.setId("Vbox_02");
        Button boton = new Button(c.texto());
        boton.setLayoutX(c.pos_X());
        boton.setLayoutY(c.pos_Y());
        boton.setId("Boton_01");

        /*boton.setOnAction(event -> {
            System.out.println("Hola");
        });*/

        vBox.getChildren().add(boton);
        return vBox;
    }

    // botones dificultad


    public HBox botones(ConfigBoton_01... botones){
        HBox pane = new HBox(10);
        pane.setPadding(new Insets(5));
        pane.setStyle("-fx-background-color: #"+botones[0].color()+";");
        pane.setAlignment(Pos.CENTER);
        //pane.setId(c.pane_id());

        for (ConfigBoton_01 c : botones){
            Button boton = new Button(c.texto());
            boton.setPrefSize(c.size_X(),c.size_Y());

            boton.setId(c.boton_id());
            pane.getChildren().add(boton);
        }

        return pane;
    }

}
