cmake_minimum_required(VERSION 3.28)
project(ProblemasC__)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
include_directories(C++_Doc)

add_executable(ProblemasC__
    #esto coloca los archivos de la carpeta C++_Doc en la carpeta de salida
    # los que va a ejecutar el programa CMake()
    #Los archivos que se van a ejecutar no tienen que tener los mismos metodos, nombres ni variables que los otros archivos
    #Si quiero correr toda la aplicacion, tengo que comentar los archivos que no quiero que se ejecuten
    # En Cambio si quiero solo correr un archivo tengo que compilar ese archivo en la carpeta build con el siguiente comando
    # g++ -o 1_PrimerTest C++_Doc/1_Introduccion-C++/1_PrimerTest.cpp


       #[[

        C++_Doc/1_Introduccion-C++/1_PrimerTest.cpp
        C++_Doc/1_Introduccion-C++/2_TiposDeDatos.cpp
        C++_Doc/1_Introduccion-C++/3_Arrays.cpp
        C++_Doc/1_Introduccion-C++/4_EstructurasDeControl.cpp
        C++_Doc/1_Introduccion-C++/5_Operadores.cpp
        C++_Doc/1_Introduccion-C++/6_PalabrasReservadasC++.cpp
        C++_Doc/PrimerProgramaConC++/RegistroHotel.cpp

        ]]

        C++_Doc/PrimerProgramaConC++/RegistroHotel.cpp
        C++_Doc/PrimerProgramaConC++/Usuarios.h
        C++_Doc/1_Introduccion-C++/6_PalabrasReservadasC++.cpp
        C++_Doc/PrimerProgramaConC++/RegistroDAO.h
        C++_Doc/PrimerProgramaConC++/Controladores.h
        C++_Doc/CalcularTiempo.h
<<<<<<< HEAD
<<<<<<< HEAD
=======
        #C++_Doc/1_Introduccion-C++/1_PrimerTest.cpp
>>>>>>> 00b8e58 (Reemplazando Archivos corruptos)
=======
        #C++_Doc/1_Introduccion-C++/1_PrimerTest.cpp
=======
>>>>>>> 0485a80 (Añadiendo algoritmo De Lunh y Calculadores de tiempo (Solo Afecta a local))
>>>>>>> 6b37e4e (Añadiendo algoritmo De Lunh y Calculadores de tiempo (Solo Afecta a local))
        #Archivo para calcular el tiempo de ejecucion de un programa
        #C++_Doc/CalcularTiempoTest.cpp

)

