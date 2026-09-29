#include <iostream>
#include <cuda_runtime.h>

// 1. EL KERNEL: Esta función se ejecuta en la GPU.
// El prefijo __global__ le dice al compilador que la CPU llama a esta función,
// pero la GPU es quien la ejecuta.
__global__ void sumarVectores(const float *A, const float *B, float *C, int numElementos) {
    // Cada hilo calcula su propio índice global en la cuadrícula (grid)
    int i = blockDim.x * blockIdx.x + threadIdx.x;

    // Aseguramos que los hilos extra no lean fuera de los límites de la memoria
    if (i < numElementos) {
        C[i] = A[i] + B[i];
    }
}

int main() {
    int numElementos = 100000; // 100,000 elementos
    size_t tamaño = numElementos * sizeof(float);

    // =========================================================
    // PARTE 1: Configuración en el HOST (CPU / RAM normal)
    // =========================================================
    float *h_A = (float *)malloc(tamaño);
    float *h_B = (float *)malloc(tamaño);
    float *h_C = (float *)malloc(tamaño);

    // Inicializamos los vectores con datos de prueba
    for (int i = 0; i < numElementos; i++) {
        h_A[i] = 1.0f;
        h_B[i] = 2.0f;
    }

    // =========================================================
    // PARTE 2: Gestión de memoria en el DEVICE (GPU / VRAM)
    // =========================================================
    float *d_A, *d_B, *d_C;

    // cudaMalloc reserva memoria directamente en la VRAM de la GPU
    cudaMalloc((void **)&d_A, tamaño);
    cudaMalloc((void **)&d_B, tamaño);
    cudaMalloc((void **)&d_C, tamaño);

    // Copiamos los datos desde la RAM de la computadora a la VRAM de la GPU
    cudaMemcpy(d_A, h_A, tamaño, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, tamaño, cudaMemcpyHostToDevice);

    // =========================================================
    // PARTE 3: Ejecución Paralela
    // =========================================================
    // Definimos cuántos hilos trabajarán juntos en un "bloque" y cuántos bloques necesitamos
    int hilosPorBloque = 256;
    int bloquesPorGrid = (numElementos + hilosPorBloque - 1) / hilosPorBloque;

    // Lanzamos el kernel. La sintaxis <<<bloques, hilos>>> es exclusiva de CUDA.
    sumarVectores<<<bloquesPorGrid, hilosPorBloque>>>(d_A, d_B, d_C, numElementos);

    // Le pedimos a la CPU que espere a que la GPU termine de hacer todo el cálculo
    cudaDeviceSynchronize();

    // =========================================================
    // PARTE 4: Recuperar resultados y Limpiar
    // =========================================================
    // Traemos el vector de resultados (C) de vuelta a la RAM normal
    cudaMemcpy(h_C, d_C, tamaño, cudaMemcpyDeviceToHost);

    std::cout << "Suma exitosa. Ejemplo del índice 100000: " << h_C[100000-1] << " (Debería ser 3)" << std::endl;
    float* direccion = &h_C[100000-1];
    std::cout << "\t \n" <<  *direccion <<  std::endl;

    std::cout << "\t \n" <<  direccion <<  std::endl;

    // Liberamos la memoria en ambos lados
    cudaFree(d_A); cudaFree(d_B); cudaFree(d_C);
    free(h_A); free(h_B); free(h_C);

    return 0;
}