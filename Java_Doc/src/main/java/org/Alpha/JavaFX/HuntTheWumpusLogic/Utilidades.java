package org.Alpha.JavaFX.HuntTheWumpusLogic;

import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;
import javafx.scene.layout.VBox;

public class Utilidades {

    // creo que una de las mejores estrategias para ahorrar lineas de codigo es hacer algo tal que
    // var a funcion(parametros) (Retorna elemento)
    // linea 2
    // pane.getchildren().add(a);

    public VBox barraSuperior(int espaciado, int insets, Pos pos, String texto_1, String texto_2, int[] tamaño){

        VBox vBox = new VBox(espaciado);
        vBox.setPadding(new Insets(insets));
        vBox.setStyle("-fx-background-color: #2c3e50;");
        vBox.setAlignment(pos);
        // ID importante
        vBox.setId("Vbox_01");


        Label title = new Label(texto_1);
        title.setStyle("-fx-text-fill: #c00f0f; -fx-font-size: +"+tamaño[0]+"px; -fx-font-weight: bold;");
        title.setId("label_01");

        Label eventLabel = new Label(texto_2);
        eventLabel.setStyle("-fx-text-fill: #1fbbe1; -fx-font-size: "+tamaño[1]+"px;");
        eventLabel.setId("label_02");


        vBox.getChildren().addAll(title, eventLabel);
        return vBox;
    }

    public VBox botonInferior(int espaciado, int insets, Pos pos, String texto, int pos_X, int pos_Y){
        VBox vBox = new VBox(espaciado);
        vBox.setPadding(new Insets(insets));
        vBox.setStyle("-fx-background-color: #2c3e50;");
        vBox.setAlignment(pos);
        vBox.setId("Vbox_02");

        Button boton = new Button(texto);
        boton.setLayoutX(pos_X);
        boton.setLayoutY(pos_Y);
        boton.setId("Boton_01");

        /*boton.setOnAction(event -> {
            System.out.println("Hola");
        });*/

        vBox.getChildren().add(boton);
        return vBox;
    }

    // botones dificultad
    public HBox botones(int espaciado, int insets, Pos pos ){
        HBox pane = new HBox(espaciado);
        pane.setPadding(new Insets(insets));
        pane.setStyle("-fx-background-color: #2c3e50;");
        pane.setAlignment(pos);
        pane.setId("Pane menu");

        Button botonFacil = new Button("Facil");
        botonFacil.setPrefSize(200,100);
        //botonFacil.setMaxWidth(400);
        botonFacil.setId("BotonFacil");

        Button botonMedio = new Button("Medio");
        botonMedio.setPrefSize(200,100);
        botonMedio.setId("BotonMedio");

        Button botonDificil = new Button("Dificil");
        botonDificil.setPrefSize(200,100);
        botonDificil.setId("BotonDificil");

        /*boton.setOnAction(event -> {
            System.out.println("Hola");
        });*/

        pane.getChildren().addAll(botonFacil, botonMedio, botonDificil);
        return pane;
    }

}
