cmake_minimum_required(VERSION 4.2)
project(CUDA CUDA)

set(CMAKE_CUDA_STANDARD 20)

add_executable(CUDA
        # main.cu
        GEMM.cu)

set_target_properties(CUDA PROPERTIES
        CUDA_SEPARABLE_COMPILATION ON)
