//
// Created by byemmanuel on 8/15/26.
// GENERAL MATRIX MULTIPLY

#include <iostream>
#include <cuda_runtime.h>

// Definimos el tamaño de la matriz (N x N)
#define N 65536
// Definimos el tamaño del bloque de hilos (16x16 = 256 hilos por bloque)
#define BLOCK_SIZE 16

// =========================================================
// EL KERNEL: Ejecutado en la GPU
// =========================================================
__global__ void multiplicarMatrices(const float *A, const float *B, float *C, int width) {
    // Calculamos la fila y la columna que este hilo específico debe procesar
    int fila = blockIdx.y * blockDim.y + threadIdx.y;
    int col  = blockIdx.x * blockDim.x + threadIdx.x;

    // Verificamos que el hilo esté dentro de los límites de la matriz
    if (fila < width && col < width) {
        float suma = 0.0f;

        // Producto punto: multiplicamos la fila de A por la columna de B
        for (int k = 0; k < width; k++) {
            // A se lee por filas: A[fila * width + k]
            // B se lee por columnas: B[k * width + col]
            suma += A[fila * width + k] * B[k * width + col];
        }

        // Guardamos el resultado en la matriz C
        C[fila * width + col] = suma;
    }
}

int main() {
    // Tamaño total en bytes para una matriz de N x N
    size_t tamañoBytes = N * N * sizeof(float);

    // 1. Asignar memoria en el HOST (CPU)
    float *h_A = (float *)malloc(tamañoBytes);
    float *h_B = (float *)malloc(tamañoBytes);
    float *h_C = (float *)malloc(tamañoBytes);

    // Inicializar matrices con valores de prueba
    for (int i = 0; i < N * N; i++) {
        h_A[i] = 1.0f; // Matriz llena de 1s
        h_B[i] = 2.0f; // Matriz llena de 2s
    }

    // 2. Asignar memoria en el DEVICE (GPU)
    float *d_A, *d_B, *d_C;
    cudaMalloc((void **)&d_A, tamañoBytes);
    cudaMalloc((void **)&d_B, tamañoBytes);
    cudaMalloc((void **)&d_C, tamañoBytes);

    // 3. Copiar datos: HOST -> DEVICE
    cudaMemcpy(d_A, h_A, tamañoBytes, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, tamañoBytes, cudaMemcpyHostToDevice);

    // 4. Configurar la topología de ejecución (Grilla 2D)
    // Definimos bloques de 16x16 hilos
    dim3 hilosPorBloque(BLOCK_SIZE, BLOCK_SIZE);

    // Calculamos cuántos bloques necesitamos en X y en Y para cubrir la matriz 1024x1024
    int numBloques = (N + BLOCK_SIZE - 1) / BLOCK_SIZE;
    dim3 bloquesPorGrid(numBloques, numBloques);

    std::cout << "Lanzando kernel con Grid de " << numBloques << "x" << numBloques
              << " bloques y " << BLOCK_SIZE << "x" << BLOCK_SIZE << " hilos por bloque." << std::endl;

    // 5. Lanzar el KERNEL
    multiplicarMatrices<<<bloquesPorGrid, hilosPorBloque>>>(d_A, d_B, d_C, N);

    // Esperar a que la GPU termine
    cudaDeviceSynchronize();

    // 6. Copiar resultados: DEVICE -> HOST
    cudaMemcpy(h_C, d_C, tamañoBytes, cudaMemcpyDeviceToHost);

    // Verificar un resultado. Si sumamos 1024 veces (1 * 2), el resultado debe ser 2048.
    // en teoria si hacemos 2*1 65536 seria 65536 * 2 = 131072 y ese seria el resultado
    std::cout << "Prueba de resultado en C[0][0]: " << h_C[0] << " (Debería ser 2048)" << std::endl;

    // 7. Liberar memoria
    cudaFree(d_A); cudaFree(d_B); cudaFree(d_C);
    free(h_A); free(h_B); free(h_C);

    return 0;
}