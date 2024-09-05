cmake_minimum_required(VERSION 3.29)
project(ProblemasC__)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
include_directories(C++_Doc)

add_executable(ProblemasC__
    #esto coloca los archivos de la carpeta C++_Doc en la carpeta de salida
    # los que va a ejecutar el programa CMake()
    #Los archivos que se van a ejecutar no tienen que tener los mismos metodos, nombres ni variables que los otros archivos
        C++_Doc/1_PrimerTest.cpp
        C++_Doc/4_EstructurasDeControl.cpp
        #C++_Doc/3_Arrays.cpp
    #C++_Doc/2_TiposDeDatos.cpp
)

