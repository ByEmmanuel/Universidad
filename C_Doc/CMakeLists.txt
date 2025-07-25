cmake_minimum_required(VERSION 3.30)
project(C_Doc C)

set(CMAKE_C_STANDARD 11)

# Buscar la librería ncurses
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
# Enlazar la librería ncurses

add_executable(C_Doc
        Algoritmos/_1_Add_Two_Numbers.c

        #[[#Proyecto PE
        ProyectoPE/main.c
        ProyectoPE/LogicaNegocio.c
        ProyectoPE/UsuarioDTO.c
        ProyectoPE/Util.c
        ProyectoPE/UserInterface.c
        ProyectoPE/Pago.c
        ProyectoPE/Clientes.c
        ProyectoPE/RegistrarMotor.c
        ProyectoPE/Testing.c
        ProyectoPE/Almacen.c
        ProyectoPE/UsuarioDAO.c
        ProyectoPE/ApartadoOtros.c
        ProyectoPE/ConstantesMotores.c
        ProyectoPE/SystemLogs.c
        ProyectoPE/reloj.c]]

        ProyectoPE/LogicaNegocio.h
        #ProyectoPE/UsuarioDTO.h
        #ProyectoPE/Util.h
        #ProyectoPE/UserInterface.h
        #ProyectoPE/ConstantesMotores.h
        #ProyectoPE/Testing.h
        #ProyectoPE/reloj.h

        #Logica de programacion

)

target_link_libraries(C_Doc ${CURSES_LIBRARIES})