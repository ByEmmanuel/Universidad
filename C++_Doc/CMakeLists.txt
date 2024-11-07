cmake_minimum_required(VERSION 3.29)
project(C___Doc)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
include_directories(PrimerProgramaConC++)

add_executable(C___Doc
    #[[1_Introduccion-C++/1_PrimerTest.cpp
    1_Introduccion-C++/2_TiposDeDatos.cpp
    1_Introduccion-C++/3_Arrays.cpp
    1_Introduccion-C++/4_EstructurasDeControl.cpp
    1_Introduccion-C++/5_Operadores.cpp
    1_Introduccion-C++/6_PalabrasReservadasC++.cpp
    2_ProgramacionOrientadaObjetos/1_DelimitadoresAcceso.cpp
    PrimerProgramaConC++/Controladores.h
    PrimerProgramaConC++/RegistroDAO.h
    PrimerProgramaConC++/RegistroHotel.cpp
    PrimerProgramaConC++/UsuariosEntity.h
    CalcularTiempo.h
    CalcularTiempoTest.cpp]]
    #"3_TareasUNI-C++/1_VariablesFlotantes.cpp"
    #[["3_TareasUNI-C++/2_VariablesBoleanas.cpp"
        3_TareasUNI-C++/3_VariablesCadena.cpp
        3_TareasUNI-C++/ProyectoFund.cpp
        3_TareasUNI-C++/Usuarios.cpp
        ]]

        #[[
        ]]
        3_TareasUNI-C++/ProyectoFundamentos/ProyectoFund.cpp
        3_TareasUNI-C++/ProyectoFundamentos/UsuariosEntity.h
        3_TareasUNI-C++/ProyectoFundamentos/Controladores.h
        3_TareasUNI-C++/ProyectoFundamentos/CalendarioTerminal.cpp


)
