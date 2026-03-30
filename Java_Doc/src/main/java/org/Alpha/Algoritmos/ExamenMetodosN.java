package org.Alpha.Algoritmos;

import java.util.*;
import java.util.function.Function;

public class ExamenMetodosN {

    // ================================================================
    //   ESTRUCTURA PRINCIPAL DE CACHÉ
    // ================================================================
    static List<List<double[][]>> l = new ArrayList<>();

    static final String[] NOMBRES = {
            "LU Doolittle", "Crout", "Jacobi",
            "Gauss-Seidel", "Punto Fijo Multiv.", "Newton-Raphson Multiv."
    };

    static final double TOL         = 1e-10;
    static final int    MAX_DEFAULT = 1000;

    static double[][] matrizActiva    = null;
    static int        nActiva         = 0;
    static boolean    tieneVectorB    = true;   // FIX 1 — campo declarado

    static double[] x0NL = null;
    static int      nNL  = 0;

    static int iteracionesPedidas = MAX_DEFAULT;

    // ================================================================
    //   UTILIDADES
    // ================================================================
    static void printMatrix(String label, double[][] M) {
        System.out.println("\n  ── " + label + " ──");
        for (int i = 0; i < M.length; i++) {
            System.out.printf("  a%d· [ ", i + 1);
            for (double v : M[i]) System.out.printf("%12.6f ", v);
            System.out.println("]");
        }
    }

    static void printVector(String label, double[] v) {
        System.out.println("  ── " + label + " ──");
        for (int i = 0; i < v.length; i++)
            System.out.printf("    x[%d] = %.8f%n", i + 1, v[i]);
    }

    static double normInf(double[] a, double[] b) {
        double max = 0;
        for (int i = 0; i < a.length; i++) max = Math.max(max, Math.abs(a[i] - b[i]));
        return max;
    }

    /** Ly = b  →  y_i = (b_i - Σ_{j<i} L[i][j]·y[j]) / L[i][i] */
    static double[] forwardSub(double[][] L, double[] b) {
        int n = b.length;
        double[] y = new double[n];
        for (int i = 0; i < n; i++) {
            y[i] = b[i];
            for (int j = 0; j < i; j++) y[i] -= L[i][j] * y[j];
            y[i] /= L[i][i];
        }
        return y;
    }

    /** Ux = y  →  x_i = (y_i - Σ_{j>i} U[i][j]·x[j]) / U[i][i] */
    static double[] backSub(double[][] U, double[] y) {
        int n = y.length;
        double[] x = new double[n];
        for (int i = n - 1; i >= 0; i--) {
            x[i] = y[i];
            for (int j = i + 1; j < n; j++) x[i] -= U[i][j] * x[j];
            x[i] /= U[i][i];
        }
        return x;
    }

    /** Eliminación gaussiana con pivoteo parcial */
    static double[] gaussSolve(double[][] A, double[] b) {
        int n = b.length;
        double[][] M = new double[n][n + 1];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) M[i][j] = A[i][j];
            M[i][n] = b[i];
        }
        for (int col = 0; col < n; col++) {
            int pivot = col;
            for (int row = col + 1; row < n; row++)
                if (Math.abs(M[row][col]) > Math.abs(M[pivot][col])) pivot = row;
            double[] tmp = M[col]; M[col] = M[pivot]; M[pivot] = tmp;
            for (int row = col + 1; row < n; row++) {
                double f = M[row][col] / M[col][col];
                for (int k = col; k <= n; k++) M[row][k] -= f * M[col][k];
            }
        }
        double[] y = new double[n];
        for (int i = 0; i < n; i++) y[i] = M[i][n];
        return backSub(Arrays.copyOf(M, n), y);
    }

    // ================================================================
    //   INGRESO DE MATRIZ
    // ================================================================
    static void ingresarMatriz(Scanner sc) {
        System.out.println("\n╔══════════════════════════════╗");
        System.out.println("║   INGRESO DE MATRIZ [A | b]  ║");
        System.out.println("╚══════════════════════════════╝");

        System.out.print("  Dimensión n (sistema n×n): ");
        int n = Integer.parseInt(sc.next().trim());
        nActiva = n;

        System.out.print("  ¿Tienes vector b? (s/n): ");
        tieneVectorB = sc.next().trim().equalsIgnoreCase("s");

        matrizActiva = new double[n][tieneVectorB ? n + 1 : n];

        System.out.println("\n  ── Coeficientes de A ──");
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                System.out.printf("  a%d%d = ", i + 1, j + 1);
                matrizActiva[i][j] = Double.parseDouble(sc.next().trim());
            }

        if (tieneVectorB) {
            System.out.println("\n  ── Términos independientes b ──");
            for (int i = 0; i < n; i++) {
                System.out.printf("  b%d  = ", i + 1);
                matrizActiva[i][n] = Double.parseDouble(sc.next().trim());
            }
        }

        l.clear();
        for (int k = 0; k < NOMBRES.length; k++) l.add(new ArrayList<>());
        System.out.println("\n  ✓ Matriz ingresada.");
        printMatrix("A" + (tieneVectorB ? " aumentada [A|b]" : " (sin b)"), matrizActiva);
    }

    // ================================================================
    //   PARÁMETROS NO LINEALES
    // ================================================================
    static void ingresarNoLineal(Scanner sc) {
        System.out.println("\n╔══════════════════════════════════════╗");
        System.out.println("║   PARÁMETROS — SISTEMAS NO LINEALES  ║");
        System.out.println("╚══════════════════════════════════════╝");
        System.out.print("  Dimensión del sistema (número de variables): ");
        nNL = Integer.parseInt(sc.next().trim());
        x0NL = new double[nNL];
        System.out.println("\n  ── Punto inicial x^(0) ──");
        for (int i = 0; i < nNL; i++) {
            System.out.printf("  x0[%d] = ", i + 1);
            x0NL[i] = Double.parseDouble(sc.next().trim());
        }
        System.out.println("  ✓ Punto inicial registrado.");
    }

    // ================================================================
    //   SELECCIÓN DE ITERACIONES
    // ================================================================
    static void seleccionarIteraciones(Scanner sc) {
        System.out.print("\n  Número de iteraciones a ejecutar: ");
        iteracionesPedidas = Integer.parseInt(sc.next().trim());
        System.out.printf("  ✓ Se ejecutarán hasta %d iteraciones (paro si ||err|| < %.0e).%n",
                iteracionesPedidas, TOL);
    }

    // ================================================================
    //   VERSIONADO
    // ================================================================
    static void mostrarVersionado() {
        System.out.println("\n╔═══════════════════════════════════════════════════╗");
        System.out.println("║              VERSIONADO DE SNAPSHOTS              ║");
        System.out.println("║   l[método][t] = S^{(t)} guardado en iteración t ║");
        System.out.println("╚═══════════════════════════════════════════════════╝");

        if (l.isEmpty()) {
            System.out.println("  (Sin datos — ejecuta al menos un método primero)");
            return;
        }

        for (int m = 0; m < l.size(); m++) {
            List<double[][]> snaps = l.get(m);
            if (snaps.isEmpty()) continue;

            System.out.printf("%n  ┌─ Método [%d] %-26s ─ %d snapshot(s) ─┐%n",
                    m + 1, NOMBRES[m], snaps.size());

            for (int t = 0; t < snaps.size(); t++) {
                double[][] S = snaps.get(t);
                System.out.printf("  │  S^(%d):%n", t);
                for (double[] row : S) {
                    System.out.print("  │    [ ");
                    for (double v : row) System.out.printf("%12.6f ", v);
                    System.out.println("]");
                }
            }
            System.out.println("  └────────────────────────────────────────────────┘");
        }
    }

    // ================================================================
    //   1 — LU DOOLITTLE
    //       u_{ij} = a_{ij} - Σ_{k<i} l_{ik}·u_{kj}
    //       l_{ij} = (a_{ij} - Σ_{k<j} l_{ik}·u_{kj}) / u_{jj},  l_{ii}=1
    // ================================================================
    static void factorizacionLU() {
        if (matrizActiva == null) { System.out.println("  ✗ Ingresa primero una matriz [m]."); return; }
        if (!tieneVectorB)        { System.out.println("  ✗ LU Doolittle requiere vector b."); return; } // FIX 2

        int n = nActiva;
        double[][] A = new double[n][n];
        double[] b   = new double[n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) A[i][j] = matrizActiva[i][j];
            b[i] = matrizActiva[i][n];
        }

        double[][] Lo = new double[n][n];
        double[][] U  = new double[n][n];

        for (int j = 0; j < n; j++) {
            for (int i = 0; i <= j; i++) {
                U[i][j] = A[i][j];
                for (int k = 0; k < i; k++) U[i][j] -= Lo[i][k] * U[k][j];
            }
            Lo[j][j] = 1.0;
            for (int i = j + 1; i < n; i++) {
                Lo[i][j] = A[i][j];
                for (int k = 0; k < j; k++) Lo[i][j] -= Lo[i][k] * U[k][j];
                Lo[i][j] /= U[j][j];
            }
            double[][] snap = new double[n][2 * n];
            for (int i = 0; i < n; i++)
                for (int k = 0; k < n; k++) { snap[i][k] = Lo[i][k]; snap[i][n + k] = U[i][k]; }
            l.get(0).add(snap);
        }

        double[] y = forwardSub(Lo, b);
        double[] x = backSub(U, y);

        System.out.println("\n╔══════════════════════════════╗");
        System.out.println("║   Factorización LU Doolittle  ║");
        System.out.println("╚══════════════════════════════╝");
        printMatrix("L", Lo);
        printMatrix("U", U);
        printVector("Solución x", x);
        System.out.printf("  [snapshots guardados en l[0]: %d]%n", l.get(0).size());
    }

    // ================================================================
    //   2 — CROUT
    //       l_{ij} = a_{ij} - Σ_{k<j} l_{ik}·u_{kj}
    //       u_{ij} = (a_{ij} - Σ_{k<i} l_{ik}·u_{kj}) / l_{ii},  u_{ii}=1
    // ================================================================
    static void metodoCrout() {
        if (matrizActiva == null) { System.out.println("  ✗ Ingresa primero una matriz [m]."); return; }

        int n = nActiva;
        double[][] A = new double[n][n];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) A[i][j] = matrizActiva[i][j];

        double[][] Lo = new double[n][n];
        double[][] U  = new double[n][n];

        for (int j = 0; j < n; j++) {
            for (int i = j; i < n; i++) {
                Lo[i][j] = A[i][j];
                for (int k = 0; k < j; k++) Lo[i][j] -= Lo[i][k] * U[k][j];
            }
            U[j][j] = 1.0;
            for (int i = j + 1; i < n; i++) {
                U[j][i] = A[j][i];
                for (int k = 0; k < j; k++) U[j][i] -= Lo[j][k] * U[k][i];
                U[j][i] /= Lo[j][j];
            }
            double[][] snap = new double[n][2 * n];
            for (int i = 0; i < n; i++)
                for (int k = 0; k < n; k++) { snap[i][k] = Lo[i][k]; snap[i][n + k] = U[i][k]; }
            l.get(1).add(snap);
        }

        System.out.println("\n╔════════════════════╗");
        System.out.println("║   Método de Crout   ║");
        System.out.println("╚════════════════════╝");
        printMatrix("L (Crout)", Lo);
        printMatrix("U (Crout)", U);

        if (tieneVectorB) {
            double[] b = new double[n];
            for (int i = 0; i < n; i++) b[i] = matrizActiva[i][n];
            double[] y = forwardSub(Lo, b);
            double[] x = backSub(U, y);
            printVector("Solución x", x);
        } else {
            System.out.println("\n  [Sin vector b — factorización A = LU completada]");
            System.out.println("  [Para resolver, reingresa la matriz con b usando [m]]");
        }

        System.out.printf("  [snapshots guardados en l[1]: %d]%n", l.get(1).size());
    }

    // ================================================================
    //   3 — JACOBI
    //       x_i^{(k+1)} = (b_i - Σ_{j≠i} a_{ij}·x_j^{(k)}) / a_{ii}
    // ================================================================
    static void metodoJacobi() {
        if (matrizActiva == null) { System.out.println("  ✗ Ingresa primero una matriz [m]."); return; }
        if (!tieneVectorB)        { System.out.println("  ✗ Jacobi requiere vector b.");        return; } // FIX 3

        int n = nActiva;
        double[] x = {2.5,0.5,1.5};
        int maxIter = iteracionesPedidas;

        System.out.println("\n╔═══════════════════╗");
        System.out.println("║   Método de Jacobi ║");
        System.out.println("╚═══════════════════╝");

        for (int iter = 0; iter < maxIter; iter++) {
            double[] xNew = new double[n];
            for (int i = 0; i < n; i++) {
                xNew[i] = matrizActiva[i][n];
                for (int j = 0; j < n; j++)
                    if (j != i) xNew[i] -= matrizActiva[i][j] * x[j];
                xNew[i] /= matrizActiva[i][i];
            }
            double[][] snap = new double[1][n];
            snap[0] = xNew.clone();
            l.get(2).add(snap);

            double err = normInf(xNew, x);
            System.out.printf("  k=%3d | x = [ ", iter + 1);
            for (double v : xNew) System.out.printf("%10.6f ", v);
            System.out.printf("] | ||err||∞ = %.4e%n", err);
            x = xNew;
            if (err < TOL) { System.out.println("  ✓ Convergencia alcanzada."); break; }
        }

        printVector("Solución x^(k)", x);
        System.out.printf("  [snapshots guardados en l[2]: %d]%n", l.get(2).size());
    }

    // ================================================================
    //   4 — GAUSS-SEIDEL
    //       x_i^{(k+1)} = (b_i - Σ_{j<i} a_{ij}·x_j^{(k+1)}
    //                             - Σ_{j>i} a_{ij}·x_j^{(k)}) / a_{ii}
    // ================================================================
    static void metodoGaussSeidel(Scanner sc) {
        if (matrizActiva == null) { System.out.println("  ✗ Ingresa primero una matriz [m]."); return; }
        if (!tieneVectorB)        { System.out.println("  ✗ Gauss-Seidel requiere vector b.");  return; }

        int n = nActiva;

        // ── Ingreso de x^{(0)} ────────────────────────────────────
        double[] x = new double[n];
        System.out.println("\n  ── Vector inicial x^(0) ──");
        System.out.println("  (presiona Enter en cada valor; ingresa 0 para usar el vector cero)");
        for (int i = 0; i < n; i++) {
            System.out.printf("  x0[%d] = ", i + 1);
            x[i] = Double.parseDouble(sc.next().trim());
        }
        // ──────────────────────────────────────────────────────────

        int maxIter = iteracionesPedidas;

        System.out.println("\n╔═════════════════════╗");
        System.out.println("║   Gauss-Seidel       ║");
        System.out.println("╚═════════════════════╝");
        System.out.printf("  x^(0) = [ ");
        for (double v : x) System.out.printf("%10.6f ", v);
        System.out.println("]");

        for (int iter = 0; iter < maxIter; iter++) {
            double[] xOld = x.clone();                 // guarda x^{(k)} completo
            for (int i = 0; i < n; i++) {
                x[i] = matrizActiva[i][n];             // parte con b_i
                for (int j = 0; j < n; j++)
                    if (j != i) x[i] -= matrizActiva[i][j] * x[j];
                // j < i → usa x_j^{(k+1)} ya actualizado en este mismo ciclo
                // j > i → usa x_j^{(k)}  del array x, aún sin actualizar
                x[i] /= matrizActiva[i][i];
            }

            double[][] snap = new double[1][n];
            snap[0] = x.clone();
            l.get(3).add(snap);

            double err = normInf(x, xOld);
            System.out.printf("  k=%3d | x = [ ", iter + 1);
            for (double v : x) System.out.printf("%10.6f ", v);
            System.out.printf("] | ||err||∞ = %.4e%n", err);
            if (err < TOL) { System.out.println("  ✓ Convergencia alcanzada."); break; }
        }

        printVector("Solución x^(k)", x);
        System.out.printf("  [snapshots guardados en l[3]: %d]%n", l.get(3).size());
    }

    // ================================================================
    //   5 — PUNTO FIJO MULTIVARIABLE
    //       x^{(k+1)} = g(x^{(k)})
    // ================================================================
    static void puntoFijoMultivariable() {
        if (x0NL == null) { System.out.println("  ✗ Ingresa primero los parámetros no lineales [n]."); return; }

        // ── EDITA AQUÍ tu función g ────────────────────────────────
        Function<double[], double[]> g = v -> new double[]{
                (Math.pow(v[0],2) + v[1] - Math.sin(v[1])) / 2,
                (Math.pow(v[1],2) + v[0] + Math.cos(v[0]) / 2)
        };
        // ───────────────────────────────────────────────────────────

        double[] x = x0NL.clone();
        int maxIter = iteracionesPedidas;

        System.out.println("\n╔════════════════════════════════╗");
        System.out.println("║   Punto Fijo Multivariable      ║");
        System.out.println("╚════════════════════════════════╝");

        for (int iter = 0; iter < maxIter; iter++) {
            double[] xNew = g.apply(x);
            double[][] snap = new double[1][nNL];
            snap[0] = xNew.clone();
            l.get(4).add(snap);

            double err = normInf(xNew, x);
            System.out.printf("  k=%3d | x = [ ", iter + 1);
            for (double v : xNew) System.out.printf("%10.6f ", v);
            System.out.printf("] | ||err||∞ = %.4e%n", err);
            x = xNew;
            if (err < TOL) { System.out.println("  ✓ Convergencia alcanzada."); break; }
        }

        printVector("Solución x^(k)", x);
        System.out.printf("  [snapshots guardados en l[4]: %d]%n", l.get(4).size());
    }

    // ================================================================
    //   6 — NEWTON-RAPHSON MULTIVARIABLE (diferencias finitas)
    //       x^{(k+1)} = x^{(k)} - J_F^{-1}(x^{(k)}) · F(x^{(k)})
    //       J_F[i][j] ≈ (F_i(x + h·e_j) - F_i(x)) / h
    // ================================================================
    static void newtonRaphsonMultivariable() {
        if (x0NL == null) { System.out.println("  ✗ Ingresa primero los parámetros no lineales [n]."); return; }

        // ── EDITA AQUÍ tu sistema F ────────────────────────────────
        Function<double[], double[]> F = v -> new double[]{
                2*(v[0]*v[0]) + 3* v[0] * v[1] + (v[1] * v[1]) -6,
                3*v[0]-v[0]*v[1] -3*v[1] +1
        };
        // ───────────────────────────────────────────────────────────

        final double h = 1e-7;
        double[] x = x0NL.clone();
        int maxIter = iteracionesPedidas;

        System.out.println("\n╔══════════════════════════════════════╗");
        System.out.println("║   Newton-Raphson Multivariable        ║");
        System.out.println("╚══════════════════════════════════════╝");

        for (int iter = 0; iter < maxIter; iter++) {
            double[] Fx = F.apply(x);
            double[][] J = new double[nNL][nNL];
            for (int j = 0; j < nNL; j++) {
                double[] xh = x.clone(); xh[j] += h;
                double[] Fxh = F.apply(xh);
                for (int i = 0; i < nNL; i++) J[i][j] = (Fxh[i] - Fx[i]) / h;
            }
            double[] negFx = new double[nNL];
            for (int i = 0; i < nNL; i++) negFx[i] = -Fx[i];
            double[] delta = gaussSolve(J, negFx);

            double[] xNew = new double[nNL];
            for (int i = 0; i < nNL; i++) xNew[i] = x[i] + delta[i];

            double[][] snap = new double[1][nNL];
            snap[0] = xNew.clone();
            l.get(5).add(snap);

            double err = normInf(xNew, x);
            System.out.printf("  k=%3d | x = [ ", iter + 1);
            for (double v : xNew) System.out.printf("%10.6f ", v);
            System.out.printf("] | ||err||∞ = %.4e%n", err);
            x = xNew;
            if (err < TOL) { System.out.println("  ✓ Convergencia alcanzada."); break; }
        }

        printVector("Solución x^(k)", x);
        System.out.printf("  [snapshots guardados en l[5]: %d]%n", l.get(5).size());
    }

    // ================================================================
    //   7 — NEWTON-RAPHSON 2×2 (inversa analítica del Jacobiano)
    //       x1^{k+1} = x1 - (F1·∂f2/∂x2 - F2·∂f1/∂x2) / det(J)
    //       x2^{k+1} = x2 - (F2·∂f1/∂x1 - F1·∂f2/∂x1) / det(J)
    //       det(J) = j11·j22 - j12·j21
    // ================================================================
    static void newtonRaphson2x2(Scanner sc) {
        System.out.println("\n╔══════════════════════════════════════╗");
        System.out.println("║   Newton-Raphson 2×2 (analítico)     ║");
        System.out.println("╚══════════════════════════════════════╝");

        System.out.print("  x1^(0) = "); double x1 = Double.parseDouble(sc.next());
        System.out.print("  x2^(0) = "); double x2 = Double.parseDouble(sc.next());
        System.out.print("  Iteraciones máximas: ");
        int maxIter = Integer.parseInt(sc.next().trim());

        // ── EDITA AQUÍ tu sistema ─────────────────────────────────
        java.util.function.BiFunction<Double,Double,Double>
                f1     = (a, b) -> a*a + b*b - 4,
                f2     = (a, b) -> a*b - 1,
                df1dx1 = (a, b) -> 2*a,
                df1dx2 = (a, b) -> 2*b,
                df2dx1 = (a, b) -> b,
                df2dx2 = (a, b) -> a;
        // ───────────────────────────────────────────────────────────

        List<double[][]> snapshots = new ArrayList<>();

        System.out.printf("%n  %5s | %14s | %14s | %14s%n", "k", "x1", "x2", "||err||∞");
        System.out.println("  " + "─".repeat(55));

        for (int k = 0; k < maxIter; k++) {
            double F1  = f1.apply(x1, x2);
            double F2  = f2.apply(x1, x2);
            double j11 = df1dx1.apply(x1, x2);
            double j12 = df1dx2.apply(x1, x2);
            double j21 = df2dx1.apply(x1, x2);
            double j22 = df2dx2.apply(x1, x2);
            double det = j11*j22 - j12*j21;

            if (Math.abs(det) < 1e-14) {
                System.out.println("  ✗ Jacobiano singular — det(J) ≈ 0. Elige otro punto inicial.");
                return;
            }

            double x1New = x1 - (F1*j22 - F2*j12) / det;
            double x2New = x2 - (F2*j11 - F1*j21) / det;

            double[][] snap = {{ x1New, x2New, det, F1, F2 }};
            snapshots.add(snap);

            double err = Math.max(Math.abs(x1New - x1), Math.abs(x2New - x2));
            System.out.printf("  %5d | %14.8f | %14.8f | %14.4e%n", k + 1, x1New, x2New, err);

            x1 = x1New;
            x2 = x2New;

            if (err < TOL) { System.out.println("\n  ✓ Convergencia alcanzada."); break; }
        }

        l.get(5).addAll(snapshots);

        System.out.println("\n  ── Solución ──");
        System.out.printf("    x1 = %.8f%n", x1);
        System.out.printf("    x2 = %.8f%n", x2);
        System.out.printf("  [snapshots guardados en l[5]: %d]%n", l.get(5).size());
    }

    // ================================================================
    //   MAIN
    // ================================================================
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        for (int k = 0; k < NOMBRES.length; k++) l.add(new ArrayList<>());

        System.out.println("╔══════════════════════════════════════════════════════╗");
        System.out.println("║           MÉTODOS NUMÉRICOS — MENÚ PRINCIPAL         ║");
        System.out.println("╠══════════════════════════════════════════════════════╣");
        System.out.println("║  [m] → Ingresar matriz A (con o sin vector b)        ║");
        System.out.println("║  [n] → Ingresar parámetros sistema no lineal         ║");
        System.out.println("║  [i] → Seleccionar número de iteraciones             ║");
        System.out.println("║  [v] → Ver versionado de snapshots                   ║");
        System.out.println("╠══════════════════════════════════════════════════════╣");
        System.out.println("║  [1] → LU Doolittle      [4] → Gauss-Seidel          ║");
        System.out.println("║  [2] → Crout             [5] → Punto Fijo Multiv.    ║");
        System.out.println("║  [3] → Jacobi            [6] → Newton-Raphson Multiv.║");
        System.out.println("║  [7] → Newton-Raphson 2×2 (analítico)                ║");
        System.out.println("║  [q] → Salir                                         ║");
        System.out.println("╚══════════════════════════════════════════════════════╝");

        String opc;
        while (true) {
            System.out.print("\n  Opción: ");
            opc = sc.next().trim().toLowerCase();

            switch (opc) {
                case "m" -> ingresarMatriz(sc);
                case "n" -> ingresarNoLineal(sc);
                case "i" -> seleccionarIteraciones(sc);
                case "v" -> mostrarVersionado();
                case "1" -> factorizacionLU();
                case "2" -> metodoCrout();
                case "3" -> metodoJacobi();
                case "4" -> metodoGaussSeidel(sc);
                case "5" -> puntoFijoMultivariable();
                case "6" -> newtonRaphsonMultivariable();
                case "7" -> newtonRaphson2x2(sc);
                case "q" -> { System.out.println("  Saliendo..."); return; }
                default  -> System.out.println("  ✗ Opción no reconocida.");
            }

            System.out.printf("%n  ─ caché: %d método(s) con datos | total snapshots: %d ─%n",
                    (int) l.stream().filter(s -> !s.isEmpty()).count(),
                    l.stream().mapToInt(List::size).sum());
        }
    }
}