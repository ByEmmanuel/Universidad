package org.Alpha.JavaFX;

import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.control.*;
import javafx.scene.input.MouseButton;
import javafx.scene.layout.*;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import javafx.stage.Stage;

import java.util.*;

public class Grafo extends Application {

    // ── Modelo ──────────────────────────────────────────────────────────────
    static class Node {
        String id;
        double x, y;
        static final double RADIUS = 22;

        Node(String id, double x, double y) {
            this.id = id; this.x = x; this.y = y;
        }

        boolean contains(double px, double py) {
            double dx = px - x, dy = py - y;
            return dx * dx + dy * dy <= RADIUS * RADIUS;
        }
    }

    static class Edge {
        Node from, to;
        int weight;

        Edge(Node from, Node to, int weight) {
            this.from = from; this.to = to; this.weight = weight;
        }
    }

    // ── Estado del grafo ─────────────────────────────────────────────────────
    private final List<Node>  nodes = new ArrayList<>();
    private final List<Edge>  edges = new ArrayList<>();
    private Node dragging      = null;
    private Node edgeSource    = null;
    private double dragOffX, dragOffY;
    private Node hovered       = null;

    // ── Paleta dark ──────────────────────────────────────────────────────────
    private static final Color BG          = Color.web("#0d0d0f");
    private static final Color GRID        = Color.web("#1a1a1f");
    private static final Color NODE_FILL   = Color.web("#1e1e26");
    private static final Color NODE_STROKE = Color.web("#5e9ef7");
    private static final Color NODE_HOVER  = Color.web("#7fb3ff");
    private static final Color NODE_SEL    = Color.web("#f7c45e");
    private static final Color EDGE_COLOR  = Color.web("#3a3a50");
    private static final Color EDGE_WEIGHT = Color.web("#888aaa");
    private static final Color TEXT_COLOR  = Color.web("#e8eaf6");
    private static final Color ACCENT      = Color.web("#5e9ef7");

    private Canvas canvas;
    private Label statusLabel;
    private TextField nodeIdField, weightField, fromField, toField;

    // ── Modo ─────────────────────────────────────────────────────────────────
    private enum Mode { ADD_NODE, ADD_EDGE, DELETE, MOVE }
    private Mode mode = Mode.MOVE;

    @Override
    public void start(Stage stage) {
        canvas = new Canvas(860, 560);
        setupCanvasEvents();

        VBox sidebar  = buildSidebar();
        HBox root     = new HBox(sidebar, canvas);
        root.setStyle("-fx-background-color: #0d0d0f;");

        statusLabel = new Label("Modo: MOVER  |  Clic derecho = menú contextual");
        statusLabel.setStyle("-fx-text-fill: #5e9ef7; -fx-font-size: 11px; -fx-padding: 4 10;");

        BorderPane layout = new BorderPane();
        layout.setCenter(root);
        layout.setBottom(statusLabel);
        layout.setStyle("-fx-background-color: #0d0d0f;");

        // Grafo de ejemplo inicial
        seedGraph();
        redraw();

        stage.setScene(new Scene(layout, 1060, 590));
        stage.setTitle("Graph Visualizer — JavaFX");
        stage.show();
    }

    // ── Sidebar ───────────────────────────────────────────────────────────────
    private VBox buildSidebar() {
        VBox box = new VBox(12);
        box.setPrefWidth(190);
        box.setPadding(new Insets(16, 12, 16, 12));
        box.setStyle("-fx-background-color: #111116; -fx-border-color: #1e1e2e; -fx-border-width: 0 1 0 0;");

        Label title = new Label("GRAPH\nVISUALIZER");
        title.setStyle("-fx-text-fill: #5e9ef7; -fx-font-size: 15px; -fx-font-weight: bold; -fx-font-family: monospace;");

        Separator sep1 = styledSep();

        // Modo buttons
        Label modeLabel = sectionLabel("MODO");
        Button btnMove   = modeBtn("↖  Mover",   Mode.MOVE);
        Button btnAdd    = modeBtn("⊕  Nodo",    Mode.ADD_NODE);
        Button btnEdge   = modeBtn("⟶  Arista",  Mode.ADD_EDGE);
        Button btnDelete = modeBtn("✕  Eliminar", Mode.DELETE);

        Separator sep2 = styledSep();

        // Agregar nodo manual
        Label addNodeLabel = sectionLabel("AGREGAR NODO");
        nodeIdField = styledField("ID del nodo");
        Button btnAddNode = actionBtn("Agregar Nodo");
        btnAddNode.setOnAction(e -> addNodeManual());

        Separator sep3 = styledSep();

        // Agregar arista
        Label addEdgeLabel = sectionLabel("AGREGAR ARISTA");
        fromField   = styledField("Desde (ID)");
        toField     = styledField("Hasta (ID)");
        weightField = styledField("Peso (entero)");
        Button btnAddEdge = actionBtn("Agregar Arista");
        btnAddEdge.setOnAction(e -> addEdgeManual());

        Separator sep4 = styledSep();

        // Limpiar
        Button btnClear = dangerBtn("Limpiar Todo");
        btnClear.setOnAction(e -> { nodes.clear(); edges.clear(); edgeSource = null; redraw(); });

        box.getChildren().addAll(
                title, sep1,
                modeLabel, btnMove, btnAdd, btnEdge, btnDelete,
                sep2,
                addNodeLabel, nodeIdField, btnAddNode,
                sep3,
                addEdgeLabel, fromField, toField, weightField, btnAddEdge,
                sep4,
                btnClear
        );
        return box;
    }

    // ── Canvas events ─────────────────────────────────────────────────────────
    private void setupCanvasEvents() {
        canvas.setOnMouseMoved(e -> {
            Node prev = hovered;
            hovered = nodeAt(e.getX(), e.getY());
            if (hovered != prev) redraw();
        });

        canvas.setOnMousePressed(e -> {
            double x = e.getX(), y = e.getY();
            Node hit = nodeAt(x, y);

            if (e.getButton() == MouseButton.SECONDARY) {
                showContextMenu(hit, x, y);
                return;
            }

            switch (mode) {
                case MOVE -> {
                    if (hit != null) {
                        dragging = hit;
                        dragOffX = x - hit.x;
                        dragOffY = y - hit.y;
                    }
                }
                case ADD_NODE -> {
                    if (hit == null) {
                        String id = "N" + (nodes.size() + 1);
                        nodes.add(new Node(id, x, y));
                        redraw();
                        status("Nodo " + id + " creado");
                    }
                }
                case ADD_EDGE -> {
                    if (hit != null) {
                        if (edgeSource == null) {
                            edgeSource = hit;
                            status("Arista: selecciona nodo destino (origen=" + hit.id + ")");
                        } else if (hit != edgeSource) {
                            int w = askWeight();
                            edges.add(new Edge(edgeSource, hit, w));
                            status("Arista " + edgeSource.id + " → " + hit.id + " (w=" + w + ")");
                            edgeSource = null;
                        } else {
                            edgeSource = null;
                            status("Selección cancelada");
                        }
                        redraw();
                    }
                }
                case DELETE -> {
                    if (hit != null) {
                        edges.removeIf(ed -> ed.from == hit || ed.to == hit);
                        nodes.remove(hit);
                        status("Nodo " + hit.id + " eliminado");
                        redraw();
                    } else {
                        Edge edgeHit = edgeAt(x, y);
                        if (edgeHit != null) {
                            edges.remove(edgeHit);
                            status("Arista eliminada");
                            redraw();
                        }
                    }
                }
            }
        });

        canvas.setOnMouseDragged(e -> {
            if (dragging != null) {
                dragging.x = Math.max(Node.RADIUS, Math.min(canvas.getWidth()  - Node.RADIUS, e.getX() - dragOffX));
                dragging.y = Math.max(Node.RADIUS, Math.min(canvas.getHeight() - Node.RADIUS, e.getY() - dragOffY));
                redraw();
            }
        });

        canvas.setOnMouseReleased(e -> dragging = null);
    }

    // ── Render ────────────────────────────────────────────────────────────────
    private void redraw() {
        GraphicsContext gc = canvas.getGraphicsContext2D();
        double W = canvas.getWidth(), H = canvas.getHeight();

        // Fondo
        gc.setFill(BG);
        gc.fillRect(0, 0, W, H);

        // Grid
        gc.setStroke(GRID);
        gc.setLineWidth(0.5);
        for (double gx = 0; gx < W; gx += 30) gc.strokeLine(gx, 0, gx, H);
        for (double gy = 0; gy < H; gy += 30) gc.strokeLine(0, gy, W, gy);

        // Aristas
        for (Edge ed : edges) drawEdge(gc, ed);

        // Preview arista en modo ADD_EDGE con origen seleccionado
        if (mode == Mode.ADD_EDGE && edgeSource != null) {
            gc.setStroke(NODE_SEL.deriveColor(0, 1, 1, 0.6));
            gc.setLineWidth(1.5);
            gc.setLineDashes(6, 4);
            gc.strokeLine(edgeSource.x, edgeSource.y, edgeSource.x, edgeSource.y);
            gc.setLineDashes(null);
        }

        // Nodos
        for (Node n : nodes) drawNode(gc, n);
    }

    private void drawEdge(GraphicsContext gc, Edge ed) {
        double x1 = ed.from.x, y1 = ed.from.y;
        double x2 = ed.to.x,   y2 = ed.to.y;

        // Línea
        gc.setStroke(EDGE_COLOR);
        gc.setLineWidth(2);
        gc.setLineDashes(null);
        gc.strokeLine(x1, y1, x2, y2);

        // Flecha
        double angle = Math.atan2(y2 - y1, x2 - x1);
        double ex = x2 - Node.RADIUS * Math.cos(angle);
        double ey = y2 - Node.RADIUS * Math.sin(angle);
        double arrowLen = 10, arrowAngle = Math.toRadians(25);
        gc.setFill(EDGE_COLOR);
        double[] ax = {
                ex,
                ex - arrowLen * Math.cos(angle - arrowAngle),
                ex - arrowLen * Math.cos(angle + arrowAngle)
        };
        double[] ay = {
                ey,
                ey - arrowLen * Math.sin(angle - arrowAngle),
                ey - arrowLen * Math.sin(angle + arrowAngle)
        };
        gc.fillPolygon(ax, ay, 3);

        // Peso
        double mx = (x1 + x2) / 2, my = (y1 + y2) / 2;
        gc.setFill(Color.web("#0d0d0f", 0.75));
        gc.fillRoundRect(mx - 12, my - 9, 24, 16, 6, 6);
        gc.setFill(EDGE_WEIGHT);
        gc.setFont(Font.font("Monospace", FontWeight.BOLD, 11));
        gc.fillText(String.valueOf(ed.weight), mx - 6, my + 4);
    }

    private void drawNode(GraphicsContext gc, Node n) {
        boolean isHovered  = n == hovered;
        boolean isSource   = n == edgeSource;
        double  r          = Node.RADIUS;

        // Glow exterior
        if (isHovered || isSource) {
            Color glow = isSource ? NODE_SEL : NODE_HOVER;
            gc.setFill(glow.deriveColor(0, 1, 1, 0.15));
            gc.fillOval(n.x - r - 8, n.y - r - 8, (r + 8) * 2, (r + 8) * 2);
        }

        // Relleno
        gc.setFill(NODE_FILL);
        gc.fillOval(n.x - r, n.y - r, r * 2, r * 2);

        // Borde
        Color stroke = isSource ? NODE_SEL : (isHovered ? NODE_HOVER : NODE_STROKE);
        gc.setStroke(stroke);
        gc.setLineWidth(isHovered || isSource ? 2.5 : 1.8);
        gc.strokeOval(n.x - r, n.y - r, r * 2, r * 2);

        // Texto ID
        gc.setFill(TEXT_COLOR);
        gc.setFont(Font.font("Monospace", FontWeight.BOLD, 12));
        double tw = n.id.length() * 7.2;
        gc.fillText(n.id, n.x - tw / 2, n.y + 4.5);
    }

    // ── Helpers ───────────────────────────────────────────────────────────────
    private Node nodeAt(double x, double y) {
        for (int i = nodes.size() - 1; i >= 0; i--)
            if (nodes.get(i).contains(x, y)) return nodes.get(i);
        return null;
    }

    private Edge edgeAt(double x, double y) {
        for (Edge ed : edges) {
            double dx = ed.to.x - ed.from.x, dy = ed.to.y - ed.from.y;
            double len = Math.sqrt(dx * dx + dy * dy);
            if (len < 1) continue;
            double t = ((x - ed.from.x) * dx + (y - ed.from.y) * dy) / (len * len);
            if (t < 0 || t > 1) continue;
            double px = ed.from.x + t * dx - x;
            double py = ed.from.y + t * dy - y;
            if (px * px + py * py < 64) return ed;
        }
        return null;
    }

    private int askWeight() {
        String txt = weightField.getText().trim();
        try { return Integer.parseInt(txt); } catch (NumberFormatException e) { return 1; }
    }

    private void addNodeManual() {
        String id = nodeIdField.getText().trim();
        if (id.isEmpty()) { status("Ingresa un ID"); return; }
        if (nodes.stream().anyMatch(n -> n.id.equals(id))) { status("ID ya existe"); return; }
        double x = 80 + Math.random() * (canvas.getWidth()  - 160);
        double y = 80 + Math.random() * (canvas.getHeight() - 160);
        nodes.add(new Node(id, x, y));
        nodeIdField.clear();
        redraw();
        status("Nodo " + id + " agregado");
    }

    private void addEdgeManual() {
        String from = fromField.getText().trim();
        String to   = toField.getText().trim();
        Node f = nodes.stream().filter(n -> n.id.equals(from)).findFirst().orElse(null);
        Node t = nodes.stream().filter(n -> n.id.equals(to)).findFirst().orElse(null);
        if (f == null || t == null) { status("Nodo no encontrado"); return; }
        int w = askWeight();
        edges.add(new Edge(f, t, w));
        fromField.clear(); toField.clear(); weightField.clear();
        redraw();
        status("Arista " + from + " → " + to + " (w=" + w + ")");
    }

    private void showContextMenu(Node hit, double x, double y) {
        ContextMenu cm = new ContextMenu();
        cm.setStyle("-fx-background-color: #111116; -fx-border-color: #2a2a3a;");
        if (hit != null) {
            MenuItem rename = new MenuItem("Renombrar " + hit.id);
            rename.setOnAction(e -> {
                TextInputDialog d = new TextInputDialog(hit.id);
                d.setTitle("Renombrar nodo"); d.setHeaderText(null);
                d.showAndWait().ifPresent(s -> { if (!s.isEmpty()) { hit.id = s; redraw(); } });
            });
            MenuItem del = new MenuItem("Eliminar " + hit.id);
            del.setOnAction(e -> { edges.removeIf(ed -> ed.from == hit || ed.to == hit); nodes.remove(hit); redraw(); });
            cm.getItems().addAll(rename, del);
        } else {
            MenuItem addN = new MenuItem("Nuevo nodo aquí");
            addN.setOnAction(e -> {
                String id = "N" + (nodes.size() + 1);
                nodes.add(new Node(id, x, y));
                redraw();
            });
            cm.getItems().add(addN);
        }
        cm.show(canvas, x + canvas.localToScreen(0,0).getX(), y + canvas.localToScreen(0,0).getY());
    }

    private void seedGraph() {
        Node a = new Node("A", 150, 150);
        Node b = new Node("B", 380, 100);
        Node c = new Node("C", 600, 200);
        Node d = new Node("D", 500, 380);
        Node e = new Node("E", 250, 380);
        nodes.addAll(Arrays.asList(a, b, c, d, e));
        edges.add(new Edge(a, b, 4));
        edges.add(new Edge(b, c, 7));
        edges.add(new Edge(c, d, 3));
        edges.add(new Edge(d, e, 5));
        edges.add(new Edge(e, a, 2));
        edges.add(new Edge(b, d, 9));
        edges.add(new Edge(a, d, 6));
    }

    private void status(String msg) {
        statusLabel.setText("→  " + msg);
    }

    // ── Botones estilizados ───────────────────────────────────────────────────
    private Button modeBtn(String text, Mode m) {
        Button btn = new Button(text);
        btn.setMaxWidth(Double.MAX_VALUE);
        btn.setStyle("""
            -fx-background-color: #1a1a22;
            -fx-text-fill: #9ca3c9;
            -fx-font-family: monospace;
            -fx-font-size: 12px;
            -fx-border-color: #2a2a3a;
            -fx-border-width: 1;
            -fx-cursor: hand;
            -fx-padding: 6 10;
        """);
        btn.setOnMouseEntered(e -> btn.setStyle(btn.getStyle().replace("#1a1a22", "#22223a")));
        btn.setOnMouseExited(e  -> btn.setStyle(btn.getStyle().replace("#22223a", "#1a1a22")));
        btn.setOnAction(e -> {
            mode = m;
            edgeSource = null;
            status("Modo: " + m.name());
            redraw();
        });
        return btn;
    }

    private Button actionBtn(String text) {
        Button btn = new Button(text);
        btn.setMaxWidth(Double.MAX_VALUE);
        btn.setStyle("""
            -fx-background-color: #1a2a3a;
            -fx-text-fill: #5e9ef7;
            -fx-font-family: monospace;
            -fx-font-size: 11px;
            -fx-border-color: #3a5a8a;
            -fx-border-width: 1;
            -fx-cursor: hand;
            -fx-padding: 6 10;
        """);
        return btn;
    }

    private Button dangerBtn(String text) {
        Button btn = new Button(text);
        btn.setMaxWidth(Double.MAX_VALUE);
        btn.setStyle("""
            -fx-background-color: #2a1a1a;
            -fx-text-fill: #e07070;
            -fx-font-family: monospace;
            -fx-font-size: 11px;
            -fx-border-color: #7a3a3a;
            -fx-border-width: 1;
            -fx-cursor: hand;
            -fx-padding: 6 10;
        """);
        return btn;
    }

    private TextField styledField(String prompt) {
        TextField tf = new TextField();
        tf.setPromptText(prompt);
        tf.setStyle("""
            -fx-background-color: #1a1a22;
            -fx-text-fill: #e8eaf6;
            -fx-prompt-text-fill: #444466;
            -fx-font-family: monospace;
            -fx-font-size: 11px;
            -fx-border-color: #2a2a3a;
            -fx-border-width: 1;
            -fx-padding: 4 8;
        """);
        return tf;
    }

    private Label sectionLabel(String text) {
        Label l = new Label(text);
        l.setStyle("-fx-text-fill: #444466; -fx-font-size: 9px; -fx-font-family: monospace; -fx-font-weight: bold;");
        return l;
    }

    private Separator styledSep() {
        Separator s = new Separator();
        s.setStyle("-fx-background-color: #1e1e2e;");
        return s;
    }

    public static void main(String[] args) { launch(args); }
}